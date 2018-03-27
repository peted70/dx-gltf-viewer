#include "pch.h"
#include "MeshNode.h"
#include "Common\DirectXHelper.h"
#include "BufferManager.h"
#include "ImgUtils.h"

MeshNode::MeshNode() : 
	m_loadingComplete(false)
{
}

MeshNode::~MeshNode()
{
}

void MeshNode::Initialise(const std::shared_ptr<DX::DeviceResources>& deviceResources)
{
	GraphContainerNode::Initialise(deviceResources);
	CreateDeviceDependentResources();
}

void MeshNode::CreateDeviceDependentResources()
{
	// Create sampler.
	D3D11_SAMPLER_DESC samplerDesc = {};
	samplerDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
	samplerDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
	samplerDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
	samplerDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
	samplerDesc.ComparisonFunc = D3D11_COMPARISON_NEVER;
	samplerDesc.MinLOD = 0;
	samplerDesc.MaxLOD = D3D11_FLOAT32_MAX;

	DX::ThrowIfFailed(DevResources()->GetD3DDevice()->CreateSamplerState(&samplerDesc, _spSampler.ReleaseAndGetAddressOf()));

	D3D11_RASTERIZER_DESC rasterizerState;
	rasterizerState.FillMode = D3D11_FILL_SOLID;
	rasterizerState.CullMode = D3D11_CULL_BACK;
	rasterizerState.FrontCounterClockwise = true;
	rasterizerState.DepthBias = false;
	rasterizerState.DepthBiasClamp = 0;
	rasterizerState.SlopeScaledDepthBias = 0;
	rasterizerState.DepthClipEnable = false;
	rasterizerState.ScissorEnable = false;
	rasterizerState.MultisampleEnable = true;
	rasterizerState.AntialiasedLineEnable = true;
	DX::ThrowIfFailed(DevResources()->GetD3DDevice()->CreateRasterizerState(&rasterizerState, _pRasterState.ReleaseAndGetAddressOf()));

	// Load shaders asynchronously for model rendering...
	//auto loadVSTask = DX::ReadDataAsync(L"SampleVertexShader.cso");
	//auto loadPSTask = DX::ReadDataAsync(L"SamplePixelShader.cso");
	auto loadVSTask = DX::ReadDataAsync(L"pbrvertex.cso");
	auto loadPSTask = DX::ReadDataAsync(L"pbrpixel.cso");
	//auto loadPSTask = DX::ReadDataAsync(L"PixelTranslated.cso");


	// After the vertex shader file is loaded, create the shader and input layout.
	auto createVSTask = loadVSTask.then([this](const std::vector<byte>& fileData) 
	{
		DX::ThrowIfFailed(
			DevResources()->GetD3DDevice()->CreateVertexShader(
				&fileData[0],
				fileData.size(),
				nullptr,
				&m_vertexShader));

		static const D3D11_INPUT_ELEMENT_DESC vertexDesc[] =
		{
			{ "POSITION",	0,	DXGI_FORMAT_R32G32B32_FLOAT,	0,	0,	D3D11_INPUT_PER_VERTEX_DATA, 0 },
			{ "NORMAL",		0,  DXGI_FORMAT_R32G32B32_FLOAT,	1,	0,	D3D11_INPUT_PER_VERTEX_DATA, 0 },
			{ "TEXCOORD",	0,  DXGI_FORMAT_R32G32_FLOAT,		2,	0,	D3D11_INPUT_PER_VERTEX_DATA, 0 }
		};

		DX::ThrowIfFailed(
			DevResources()->GetD3DDevice()->CreateInputLayout(
				vertexDesc,
				ARRAYSIZE(vertexDesc),
				&fileData[0],
				fileData.size(),
				&m_inputLayout));
		Utility::Out(L"Loaded Vertex Shader");
	});

	// After the pixel shader file is loaded, create the shader and constant buffer.
	auto createPSTask = loadPSTask.then([this](const std::vector<byte>& fileData) 
	{
		DX::ThrowIfFailed(
			DevResources()->GetD3DDevice()->CreatePixelShader(
				&fileData[0],
				fileData.size(),
				nullptr,
				&m_pixelShader));
		Utility::Out(L"Loaded Pixel Shader");
	});

	//concurrency::when_all()
	(createPSTask && createVSTask).then([this]() {
		m_loadingComplete = true;
		Utility::Out(L"Loading Complete");
	});
}

void MeshNode::Draw(ID3D11DeviceContext2 *context)
{
	if (!m_loadingComplete)
		return;

	BufferManager::Instance().MVPBuffer().Update(*(DevResources()));

	unsigned int indexCount = 0;
	bool indexed = false;

	// Get POSITIONS & NORMALS..
	auto pos = _buffers.find(L"POSITION");
	auto normals = _buffers.find(L"NORMAL");
	auto texcoords = _buffers.find(L"TEXCOORD_0");

	auto posBuffer = pos->second.Buffer();
	auto normalBuffer = normals->second.Buffer();
	auto texcoordBuffer = texcoords->second.Buffer();

	ID3D11Buffer *vbs[] =
	{
		*(posBuffer.GetAddressOf()),
		*(normalBuffer.GetAddressOf()),
		*(texcoordBuffer.GetAddressOf())
	};

	unsigned int strides[] = { 3 * sizeof(float), 3 * sizeof(float), 2 * sizeof(float) };
	unsigned int offsets[] = { 0, 0, 0 };
	context->IASetVertexBuffers(0, 3, vbs, strides, offsets);

	auto indices = _buffers.find(L"INDICES");
	indexed = true;
	m_indexCount = indices->second.Data()->BufferDescription->Count;
	context->IASetIndexBuffer(
		indices->second.Buffer().Get(),
		DXGI_FORMAT_R16_UINT, // Each index is one 16-bit unsigned integer (short).
		0
	);

	context->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	context->IASetInputLayout(m_inputLayout.Get());

	// Attach our vertex shader.
	assert(m_vertexShader.Get());
	context->VSSetShader(m_vertexShader.Get(), nullptr, 0);

	// Send the constant buffer to the graphics device.
	context->VSSetConstantBuffers1(0, 1, BufferManager::Instance().MVPBuffer().ConstantBuffer().GetAddressOf(),
		nullptr, nullptr);

	// Attach our pixel shader.
	context->PSSetShader(m_pixelShader.Get(), nullptr, 0);
	context->PSSetConstantBuffers(0, 1, BufferManager::Instance().PerFrameBuffer().ConstantBuffer().GetAddressOf());
	context->PSSetConstantBuffers(1, 1, BufferManager::Instance().PerObjBuffer().ConstantBuffer().GetAddressOf());

	// Iterate through all textures and set them as shader resources...
	auto textures = _material->Textures();

	// Setting the textures and samplers using the GLTF index as the destination slot
	// We load some textures twice here so maybe re-visit..
	for (auto txItr = textures.begin(); txItr != textures.end(); ++txItr)
	{
		auto textureWrapper = txItr->second;

		// Set texture and sampler.
		auto sampler = textureWrapper->GetSampler().Get();
		context->PSSetSamplers(textureWrapper->Type(), 1, &sampler);
		
		//Utility::Out(L"Set texture sampler at slot %d", textureWrapper->Type());
		auto texture = textureWrapper->GetShaderResourceView().Get();
		context->PSSetShaderResources(textureWrapper->Type(), 1, &texture);
	}

	if (indexed)
	{
		context->DrawIndexed(m_indexCount, 0, 0);
	}
	else
	{
		context->Draw(m_indexCount, 0);
	}

	GraphContainerNode::Draw(context);
}

void MeshNode::CreateBuffer(WinRTGLTFParser::GLTF_BufferData ^ data)
{
	int bindFlags = 0;
	if (data->BufferDescription->BufferContentType == L"POSITION" ||
		data->BufferDescription->BufferContentType == L"NORMAL" ||
		data->BufferDescription->BufferContentType == L"TEXCOORD_0")
	{
		bindFlags = D3D11_BIND_VERTEX_BUFFER;
	}
	else if (data->BufferDescription->BufferContentType == L"INDICES")
	{
		bindFlags = D3D11_BIND_INDEX_BUFFER;
	}
	else
	{
		return;
	}

	// Create the buffers...
	D3D11_SUBRESOURCE_DATA vertexBufferData = { 0 };
	vertexBufferData.pSysMem = (void *)data->BufferDescription->pSysMem;
	vertexBufferData.SysMemPitch = 0;
	vertexBufferData.SysMemSlicePitch = 0;

	std::wstring type(data->BufferDescription->BufferContentType->Data());
	Microsoft::WRL::ComPtr<ID3D11Buffer> buffer;

	CD3D11_BUFFER_DESC vertexBufferDesc(data->SubResource->ByteWidth, bindFlags);
	DX::ThrowIfFailed(
		DevResources()->GetD3DDevice()->CreateBuffer(
			&vertexBufferDesc,
			&vertexBufferData,
			&buffer
		)
	);

	BufferWrapper bw(data, buffer);
	_buffers[type] = bw;
}

void MeshNode::CreateMaterial(WinRTGLTFParser::GLTF_MaterialData ^ data)
{
	_material = make_shared<NodeMaterial>();
	_material->Initialise(data);
}

void MeshNode::CreateTexture(WinRTGLTFParser::GLTF_TextureData ^ data)
{
	// Don't want to allocate textures we have already allocated..
	// Disabled temporarily
	//if (_material->HasTexture(data->Idx))
	//	return;

	// Create texture.
	D3D11_TEXTURE2D_DESC txtDesc = {};
	txtDesc.MipLevels = txtDesc.ArraySize = 1;

	// TODO: Fix this - understand when to use sRGB and RGB 
	txtDesc.Format = (data->Type == 4 || data->Type == 3) ? DXGI_FORMAT_R8G8B8A8_UNORM : DXGI_FORMAT_R8G8B8A8_UNORM;
	txtDesc.SampleDesc.Count = 1;
	txtDesc.Usage = D3D11_USAGE_IMMUTABLE;
	txtDesc.BindFlags = D3D11_BIND_SHADER_RESOURCE;

	uint32_t width;
	uint32_t height;

	auto image = ImgUtils::LoadRGBAImage((void *)data->pSysMem, data->DataSize, width, height);

	txtDesc.Width = width;
	txtDesc.Height = height;

	D3D11_SUBRESOURCE_DATA initialData = {};
	initialData.pSysMem = image.data();
	initialData.SysMemPitch = txtDesc.Width * sizeof(uint32_t);

	ComPtr<ID3D11Texture2D> tex;
	DX::ThrowIfFailed(
		DevResources()->GetD3DDevice()->CreateTexture2D(&txtDesc, &initialData,
			tex.GetAddressOf()));

	ComPtr<ID3D11ShaderResourceView> textureResourceView;
	DX::ThrowIfFailed(
		DevResources()->GetD3DDevice()->CreateShaderResourceView(tex.Get(),
			nullptr, textureResourceView.ReleaseAndGetAddressOf()));

	// Create sampler.
	D3D11_SAMPLER_DESC samplerDesc = {};
	samplerDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
	samplerDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
	samplerDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
	samplerDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
	samplerDesc.ComparisonFunc = D3D11_COMPARISON_NEVER;
	samplerDesc.MinLOD = 0;
	samplerDesc.MaxLOD = D3D11_FLOAT32_MAX;

	ComPtr<ID3D11SamplerState> texSampler;
	DX::ThrowIfFailed(DevResources()->GetD3DDevice()->CreateSamplerState(&samplerDesc, texSampler.ReleaseAndGetAddressOf()));

	_material->AddTexture(data->Idx, data->Type, tex, textureResourceView, texSampler);
}

