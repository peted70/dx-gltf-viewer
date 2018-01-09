#include "pch.h"
#include "Sample3DSceneRenderer.h"

#include "..\Common\DirectXHelper.h"
#include "Utility.h"

// Please move me :)
static float lastPosX;
static float lastPosY;
static float lastY;

using namespace D3DTestApp;

using namespace DirectX;
using namespace Windows::Foundation;
using namespace Microsoft::WRL;

ref class EventShim sealed
{
internal:
	EventShim(std::function<void(WinRTGLTFParser::GLTF_BufferData^)> callback):
		callback_(std::move(callback)) 
	{

	}

public:
	void OnBuffer(Platform::Object^ sender, WinRTGLTFParser::GLTF_BufferData^ data)
	{
		callback_(data);
	}

private:
	std::function<void(WinRTGLTFParser::GLTF_BufferData^)> callback_;
};

// Loads vertex and pixel shaders from files and instantiates the cube geometry.
Sample3DSceneRenderer::Sample3DSceneRenderer(const std::shared_ptr<DX::DeviceResources>& deviceResources) :
	m_loadingComplete(false),
	m_degreesPerSecond(45),
	m_indexCount(0),
	m_tracking(false),
	m_deviceResources(deviceResources),
	_yaw(0.0f),
	_pitch(0.0f),
	_roll(0.0f),
	_zoom(1.0f)
{
	CreateDeviceDependentResources();
	CreateWindowSizeDependentResources();
	m_constantBufferData.light_direction = XMFLOAT4(1.7f, 11.0f, 5.7f, 1.0f);

	_grid = make_unique<DXGrid>();
	_grid->Initialise(deviceResources->GetD3DDevice());
	_mainAxes = make_unique<Axis>(1000.0f);
	_mainAxes->Initialise(deviceResources->GetD3DDevice());
}

// Initializes view parameters when the window size changes.
void Sample3DSceneRenderer::CreateWindowSizeDependentResources()
{
	Size outputSize = m_deviceResources->GetOutputSize();
	float aspectRatio = outputSize.Width / outputSize.Height;
	float fovAngleY = 70.0f * XM_PI / 180.0f;

	// This is a simple example of change that can be made when the app is in
	// portrait or snapped view.
	if (aspectRatio < 1.0f)
	{
		fovAngleY *= 2.0f;
	}

	// Note that the OrientationTransform3D matrix is post-multiplied here
	// in order to correctly orient the scene to match the display orientation.
	// This post-multiplication step is required for any draw calls that are
	// made to the swap chain render target. For draw calls to other targets,
	// this transform should not be applied.

	// This sample makes use of a right-handed coordinate system using row-major matrices.
	XMMATRIX perspectiveMatrix = XMMatrixPerspectiveFovRH(
		fovAngleY,
		aspectRatio,
		0.01f,
		1000.0f
		);

	XMFLOAT4X4 orientation = m_deviceResources->GetOrientationTransform3D();

	XMMATRIX orientationMatrix = XMLoadFloat4x4(&orientation);

	XMStoreFloat4x4(
		&m_constantBufferData.projection,
		XMMatrixTranspose(perspectiveMatrix * orientationMatrix)
		);

	static const XMVECTORF32 at = { 0.0f, -0.1f, 0.0f, 0.0f };
	static const XMVECTORF32 up = { 0.0f, 1.0f, 0.0f, 0.0f };

	auto camMatrix = XMMatrixRotationRollPitchYaw(_pitch, _yaw, _roll);

	XMVECTORF32 alongZ = { 0.0f, 0.0f, _zoom };

	auto eye = XMVector3TransformCoord(alongZ, camMatrix);
	XMStoreFloat4x4(&m_constantBufferData.view, XMMatrixTranspose(XMMatrixLookAtRH(eye, at, up)));
}

// Called once per frame, rotates the cube and calculates the model and view matrices.
void Sample3DSceneRenderer::Update(DX::StepTimer const& timer)
{
	if (!m_tracking)
	{
		// Convert degrees to radians, then convert seconds to rotation angle
		//float radiansPerSecond = XMConvertToRadians(m_degreesPerSecond);
		//double totalRotation = timer.GetTotalSeconds() * radiansPerSecond;
		//float radians = static_cast<float>(fmod(totalRotation, XM_2PI));

		Rotate(0.0f);
	}
}

// Rotate the 3D cube model a set amount of radians.
void Sample3DSceneRenderer::Rotate(float radians)
{
	// Prepare to pass the updated model matrix to the shader
	XMStoreFloat4x4(&m_constantBufferData.model, XMMatrixTranspose(XMMatrixRotationY(radians)));
}

void Sample3DSceneRenderer::StartTracking(float positionX, float positionY, VirtualKeyModifiers mod)
{
	//Utility::Out(L"StartTracking [%f %f]", positionX, positionY);

	m_tracking = true;
	lastPosY = positionY;
	lastPosX = positionX;
}

// When tracking, the 3D cube can be rotated around its Y axis by tracking pointer position relative to the output screen width.
void Sample3DSceneRenderer::TrackingUpdate(float positionX, float positionY, VirtualKeyModifiers mod)
{
	if (m_tracking)
	{
		//Utility::Out(L"TrackingUpdate [%f %f]", positionX, positionY);

		if ((int)(mod & VirtualKeyModifiers::Control) != 0)
		{
			_zoom += (positionY - lastPosY) / 10.0f;
		}
		else
		{
			_pitch += (positionY - lastPosY) / 100.0f;
			_yaw += (positionX - lastPosX) / 100.0f;
		}

		lastPosY = positionY;
		lastPosX = positionX;

		CreateWindowSizeDependentResources();
	}
}

void Sample3DSceneRenderer::StopTracking(float positionX, float positionY, VirtualKeyModifiers mod)
{
	m_tracking = false;
}

// Renders one frame using the vertex and pixel shaders.
void Sample3DSceneRenderer::Render()
{
	// Loading is asynchronous. Only draw geometry after it's loaded.
	if (!m_loadingComplete)
	{
		return;
	}

	auto context = m_deviceResources->GetD3DDeviceContext();

	DrawGrid(context);
	DrawAxis(context, _mainAxes.get());

	context->RSSetState(_pRasterState);

	// Prepare the constant buffer to send it to the graphics device.
	context->UpdateSubresource1(
		m_constantBuffer.Get(),
		0,
		NULL,
		&m_constantBufferData,
		0,
		0,
		0
		);

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
	context->VSSetShader(
		m_vertexShader.Get(),
		nullptr,
		0
		);

	// Send the constant buffer to the graphics device.
	context->VSSetConstantBuffers1(
		0,
		1,
		m_constantBuffer.GetAddressOf(),
		nullptr,
		nullptr
		);

	// Attach our pixel shader.
	context->PSSetShader(
		m_pixelShader.Get(),
		nullptr,
		0
		);

	// Set texture and sampler.
	auto sampler = _spSampler.Get();
	context->PSSetSamplers(0, 1, &sampler);

	auto texture = _spTexture.Get();
	context->PSSetShaderResources(0, 1, &texture);

	if (indexed)
	{
		context->DrawIndexed(m_indexCount, 0, 0);
	}
	else
	{
		context->Draw(m_indexCount, 0);
	}
}

void Sample3DSceneRenderer::DrawGrid(ID3D11DeviceContext2 *context)
{
	m_constantBufferData.color.x = 0.45f;
	m_constantBufferData.color.y = 0.45f;
	m_constantBufferData.color.z = 0.45f;

	// Prepare the constant buffer to send it to the graphics device.
	context->UpdateSubresource(m_constantBuffer.Get(), 0, NULL, &m_constantBufferData, 0, 0);

	_grid->RenderBuffers(context);

	context->IASetInputLayout(_lineDrawingInputLayout.Get());

	// Attach our vertex shader.
	context->VSSetShader(_simpleVertexShader.Get(), nullptr, 0);

	// Send the constant buffer to the graphics device.
	context->VSSetConstantBuffers(0, 1, m_constantBuffer.GetAddressOf());

	// Attach our pixel shader.
	context->PSSetShader(_simplePixelShader.Get(), nullptr, 0);

	// Draw the objects.
	context->DrawIndexed(_grid->IndexCount(), 0, 0);
}

void Sample3DSceneRenderer::DrawAxis(ID3D11DeviceContext2 *context, Axis *axis)
{
	m_constantBufferData.color.x = .15f;
	m_constantBufferData.color.y = .15f;
	m_constantBufferData.color.z = .15f;

	// Prepare the constant buffer to send it to the graphics device.
	context->UpdateSubresource(m_constantBuffer.Get(), 0, NULL, &m_constantBufferData, 0, 0);

	axis->RenderBuffers(context);

	context->IASetInputLayout(_lineDrawingInputLayout.Get());

	// Attach our vertex shader.
	context->VSSetShader(_simpleVertexShader.Get(), nullptr, 0);

	// Send the constant buffer to the graphics device.
	context->VSSetConstantBuffers(0, 1, m_constantBuffer.GetAddressOf());

	// Attach our pixel shader.
	context->PSSetShader(_simplePixelShader.Get(), nullptr, 0);

	// Draw the objects.
	context->DrawIndexed(axis->IndexCount(), 0, 0);
}

void Sample3DSceneRenderer::CreateDeviceDependentResources()
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

	DX::ThrowIfFailed(
		m_deviceResources->GetD3DDevice()->CreateSamplerState(&samplerDesc,
			_spSampler.ReleaseAndGetAddressOf()));

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
	m_deviceResources->GetD3DDevice()->CreateRasterizerState(&rasterizerState, &_pRasterState);

	// Load shaders asynchronously for model rendering...
	auto loadVSTask = DX::ReadDataAsync(L"SampleVertexShader.cso");
	auto loadPSTask = DX::ReadDataAsync(L"SamplePixelShader.cso");

	// After the vertex shader file is loaded, create the shader and input layout.
	auto createVSTask = loadVSTask.then([this](const std::vector<byte>& fileData) {
		DX::ThrowIfFailed(
			m_deviceResources->GetD3DDevice()->CreateVertexShader(
				&fileData[0],
				fileData.size(),
				nullptr,
				&m_vertexShader
				)
			);

		static const D3D11_INPUT_ELEMENT_DESC vertexDesc [] =
		{
			{ "POSITION",	0,	DXGI_FORMAT_R32G32B32_FLOAT,	0,	0,	D3D11_INPUT_PER_VERTEX_DATA, 0 },
			{ "NORMAL",		0,  DXGI_FORMAT_R32G32B32_FLOAT,	1,	0,	D3D11_INPUT_PER_VERTEX_DATA, 0 },
			{ "TEXCOORD",	0,  DXGI_FORMAT_R32G32_FLOAT,		2,	0,	D3D11_INPUT_PER_VERTEX_DATA, 0 }
		};

		DX::ThrowIfFailed(
			m_deviceResources->GetD3DDevice()->CreateInputLayout(
				vertexDesc,
				ARRAYSIZE(vertexDesc),
				&fileData[0],
				fileData.size(),
				&m_inputLayout
				)
			);
	});

	// After the pixel shader file is loaded, create the shader and constant buffer.
	auto createPSTask = loadPSTask.then([this](const std::vector<byte>& fileData) {
		DX::ThrowIfFailed(
			m_deviceResources->GetD3DDevice()->CreatePixelShader(
				&fileData[0],
				fileData.size(),
				nullptr,
				&m_pixelShader
				)
			);

		CD3D11_BUFFER_DESC constantBufferDesc(sizeof(ModelViewProjectionConstantBuffer) , D3D11_BIND_CONSTANT_BUFFER);
		DX::ThrowIfFailed(
			m_deviceResources->GetD3DDevice()->CreateBuffer(
				&constantBufferDesc,
				nullptr,
				&m_constantBuffer
				)
			);
	});

	// Load shaders asynchronously for line rendering...
	auto loadVSTask2 = DX::ReadDataAsync(L"SimpleVertexShader.cso");
	auto loadPSTask2 = DX::ReadDataAsync(L"SimplePixelShader.cso");

	// After the vertex shader file is loaded, create the shader and input layout.
	auto createVSTask2 = loadVSTask2.then([this](const std::vector<byte>& fileData) {
		DX::ThrowIfFailed(
			m_deviceResources->GetD3DDevice()->CreateVertexShader(
				&fileData[0],
				fileData.size(),
				nullptr,
				&_simpleVertexShader
			)
		);

		static const D3D11_INPUT_ELEMENT_DESC SimpleVertexDesc[] =
		{
			{ "POSITION",	0,	DXGI_FORMAT_R32G32B32_FLOAT,	0,	0,	D3D11_INPUT_PER_VERTEX_DATA, 0 },
			{ "COLOR",		0,  DXGI_FORMAT_R32G32B32_FLOAT,	1,	0,	D3D11_INPUT_PER_VERTEX_DATA, 0 }
		};

		DX::ThrowIfFailed(
			m_deviceResources->GetD3DDevice()->CreateInputLayout(
				SimpleVertexDesc,
				ARRAYSIZE(SimpleVertexDesc),
				&fileData[0],
				fileData.size(),
				&_lineDrawingInputLayout
			)
		);
	});

	// After the pixel shader file is loaded, create the shader and constant buffer.
	auto createPSTask2 = loadPSTask2.then([this](const std::vector<byte>& fileData) {
		DX::ThrowIfFailed(
			m_deviceResources->GetD3DDevice()->CreatePixelShader(
				&fileData[0],
				fileData.size(),
				nullptr,
				&_simplePixelShader
			)
		);

		CD3D11_BUFFER_DESC lineDrawingConstantBufferDesc(sizeof(LineDrawingConstantBuffer), D3D11_BIND_CONSTANT_BUFFER);
		DX::ThrowIfFailed(
			m_deviceResources->GetD3DDevice()->CreateBuffer(
				&lineDrawingConstantBufferDesc,
				nullptr,
				&_lineDrawingConstantBuffer
			)
		);
	});

	auto loadModelTask = (createPSTask && createVSTask && createPSTask2 && createVSTask2).then([this]()
	{
		WinRTGLTFParser::GLTF_Parser^ parser = ref new WinRTGLTFParser::GLTF_Parser();
		std::function<void(WinRTGLTFParser::GLTF_BufferData^)> memfun = std::bind(&Sample3DSceneRenderer::OnBuffer, this, std::placeholders::_1);
		auto es = ref new EventShim(memfun);
		parser->OnBufferEvent += ref new BufferEventHandler(es, &EventShim::OnBuffer);

		Windows::Storage::StorageFolder^ installedLocation = Windows::ApplicationModel::Package::Current->InstalledLocation;
		auto fn = installedLocation->Path + "/Assets/BoomBox.glb";
		//auto fn = installedLocation->Path + "/Assets/Box.glb";
		parser->ParseFile(fn);
	});

	loadModelTask.then([this]() {
		m_loadingComplete = true;
	});

	//// Once both shaders are loaded, create the mesh.
	//auto createCubeTask = (createPSTask && createVSTask).then([this] () {

	//	// Load mesh vertices. Each vertex has a position and a color.
	//	static const VertexPositionColor cubeVertices[] = 
	//	{
	//		{XMFLOAT3(-0.5f, -0.5f, -0.5f), XMFLOAT3(0.0f, 0.0f, 0.0f)},
	//		{XMFLOAT3(-0.5f, -0.5f,  0.5f), XMFLOAT3(0.0f, 0.0f, 1.0f)},
	//		{XMFLOAT3(-0.5f,  0.5f, -0.5f), XMFLOAT3(0.0f, 1.0f, 0.0f)},
	//		{XMFLOAT3(-0.5f,  0.5f,  0.5f), XMFLOAT3(0.0f, 1.0f, 1.0f)},
	//		{XMFLOAT3( 0.5f, -0.5f, -0.5f), XMFLOAT3(1.0f, 0.0f, 0.0f)},
	//		{XMFLOAT3( 0.5f, -0.5f,  0.5f), XMFLOAT3(1.0f, 0.0f, 1.0f)},
	//		{XMFLOAT3( 0.5f,  0.5f, -0.5f), XMFLOAT3(1.0f, 1.0f, 0.0f)},
	//		{XMFLOAT3( 0.5f,  0.5f,  0.5f), XMFLOAT3(1.0f, 1.0f, 1.0f)},
	//	};

	//	D3D11_SUBRESOURCE_DATA vertexBufferData = {0};
	//	vertexBufferData.pSysMem = cubeVertices;
	//	vertexBufferData.SysMemPitch = 0;
	//	vertexBufferData.SysMemSlicePitch = 0;
	//	CD3D11_BUFFER_DESC vertexBufferDesc(sizeof(cubeVertices), D3D11_BIND_VERTEX_BUFFER);
	//	DX::ThrowIfFailed(
	//		m_deviceResources->GetD3DDevice()->CreateBuffer(
	//			&vertexBufferDesc,
	//			&vertexBufferData,
	//			&m_vertexBuffer
	//			)
	//		);

	//	// Load mesh indices. Each trio of indices represents
	//	// a triangle to be rendered on the screen.
	//	// For example: 0,2,1 means that the vertices with indexes
	//	// 0, 2 and 1 from the vertex buffer compose the 
	//	// first triangle of this mesh.
	//	static const unsigned short cubeIndices [] =
	//	{
	//		0,2,1, // -x
	//		1,2,3,

	//		4,5,6, // +x
	//		5,7,6,

	//		0,1,5, // -y
	//		0,5,4,

	//		2,6,7, // +y
	//		2,7,3,

	//		0,4,6, // -z
	//		0,6,2,

	//		1,3,7, // +z
	//		1,7,5,
	//	};

	//	m_indexCount = ARRAYSIZE(cubeIndices);

	//	D3D11_SUBRESOURCE_DATA indexBufferData = {0};
	//	indexBufferData.pSysMem = cubeIndices;
	//	indexBufferData.SysMemPitch = 0;
	//	indexBufferData.SysMemSlicePitch = 0;
	//	CD3D11_BUFFER_DESC indexBufferDesc(sizeof(cubeIndices), D3D11_BIND_INDEX_BUFFER);
	//	DX::ThrowIfFailed(
	//		m_deviceResources->GetD3DDevice()->CreateBuffer(
	//			&indexBufferDesc,
	//			&indexBufferData,
	//			&m_indexBuffer
	//			)
	//		);
	//});

	//// Once the cube is loaded, the object is ready to be rendered.
	//createCubeTask.then([this] () {
	//	m_loadingComplete = true;
	//});
}

std::vector<uint8_t> LoadBGRAImage(void *imgFileData, int imgFileDataSize, uint32_t& width, uint32_t& height)
{
	ComPtr<IWICImagingFactory> wicFactory;
	DX::ThrowIfFailed(CoCreateInstance(CLSID_WICImagingFactory2, nullptr, CLSCTX_INPROC_SERVER, IID_PPV_ARGS(&wicFactory)));

	IWICStream *pIWICStream;
	// Create a WIC stream to map onto the memory.
	DX::ThrowIfFailed(wicFactory->CreateStream(&pIWICStream));

	// Initialize the stream with the memory pointer and size.
	DX::ThrowIfFailed(pIWICStream->InitializeFromMemory(reinterpret_cast<BYTE*>(imgFileData), imgFileDataSize));

	ComPtr<IWICBitmapDecoder> decoder;
	DX::ThrowIfFailed(wicFactory->CreateDecoderFromStream(pIWICStream, nullptr, WICDecodeMetadataCacheOnLoad, decoder.GetAddressOf()));

	ComPtr<IWICBitmapFrameDecode> frame;
	DX::ThrowIfFailed(decoder->GetFrame(0, frame.GetAddressOf()));

	DX::ThrowIfFailed(frame->GetSize(&width, &height));

	WICPixelFormatGUID pixelFormat;
	DX::ThrowIfFailed(frame->GetPixelFormat(&pixelFormat));

	uint32_t rowPitch = width * sizeof(uint32_t);
	uint32_t imageSize = rowPitch * height;

	std::vector<uint8_t> image;
	image.resize(size_t(imageSize));

	if (memcmp(&pixelFormat, &GUID_WICPixelFormat32bppBGRA, sizeof(GUID)) == 0)
	{
		DX::ThrowIfFailed(frame->CopyPixels(0, rowPitch, imageSize, reinterpret_cast<BYTE*>(image.data())));
	}
	else
	{
		ComPtr<IWICFormatConverter> formatConverter;
		DX::ThrowIfFailed(wicFactory->CreateFormatConverter(formatConverter.GetAddressOf()));

		BOOL canConvert = FALSE;
		DX::ThrowIfFailed(formatConverter->CanConvert(pixelFormat, GUID_WICPixelFormat32bppBGRA, &canConvert));
		if (!canConvert)
		{
			throw std::exception("CanConvert");
		}

		DX::ThrowIfFailed(formatConverter->Initialize(frame.Get(), GUID_WICPixelFormat32bppBGRA,
			WICBitmapDitherTypeErrorDiffusion, nullptr, 0, WICBitmapPaletteTypeMedianCut));

		DX::ThrowIfFailed(formatConverter->CopyPixels(0, rowPitch, imageSize, reinterpret_cast<BYTE*>(image.data())));
	}

	return image;
}

void Sample3DSceneRenderer::OnTexture(WinRTGLTFParser::GLTF_TextureData^ data)
{
	// Create texture.
	D3D11_TEXTURE2D_DESC txtDesc = {};
	txtDesc.MipLevels = txtDesc.ArraySize = 1;
	txtDesc.Format = DXGI_FORMAT_B8G8R8A8_UNORM_SRGB; // sunset.jpg is in sRGB colorspace
	txtDesc.SampleDesc.Count = 1;
	txtDesc.Usage = D3D11_USAGE_IMMUTABLE;
	txtDesc.BindFlags = D3D11_BIND_SHADER_RESOURCE;

	uint32_t width;
	uint32_t height;

	auto image = LoadBGRAImage((void *)data->pSysMem, data->DataSize, width, height);

	D3D11_SUBRESOURCE_DATA initialData = {};
	initialData.pSysMem = image.data();
	initialData.SysMemPitch = txtDesc.Width * sizeof(uint32_t);

	ComPtr<ID3D11Texture2D> tex;
	DX::ThrowIfFailed(
		m_deviceResources->GetD3DDevice()->CreateTexture2D(&txtDesc, &initialData,
			tex.GetAddressOf()));

	DX::ThrowIfFailed(
		m_deviceResources->GetD3DDevice()->CreateShaderResourceView(tex.Get(),
			nullptr, _spTexture.ReleaseAndGetAddressOf()));
}

void Sample3DSceneRenderer::OnBuffer(WinRTGLTFParser::GLTF_BufferData^ data)
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
	D3D11_SUBRESOURCE_DATA vertexBufferData = {0};
	vertexBufferData.pSysMem = (void *)data->BufferDescription->pSysMem;
	vertexBufferData.SysMemPitch = 0;
	vertexBufferData.SysMemSlicePitch = 0;

	std::wstring type(data->BufferDescription->BufferContentType->Data());
	Microsoft::WRL::ComPtr<ID3D11Buffer> buffer;

	CD3D11_BUFFER_DESC vertexBufferDesc(data->SubResource->ByteWidth, bindFlags);
	DX::ThrowIfFailed(
		m_deviceResources->GetD3DDevice()->CreateBuffer(
			&vertexBufferDesc,
			&vertexBufferData,
			&buffer
			)
		);

	BufferWrapper bw(data, buffer);
	_buffers[type] = bw;
}

void Sample3DSceneRenderer::ReleaseDeviceDependentResources()
{
	m_loadingComplete = false;
	m_vertexShader.Reset();
	m_inputLayout.Reset();
	m_pixelShader.Reset();
	m_constantBuffer.Reset();
	_lineDrawingConstantBuffer.Reset();

	m_vertexBuffer.Reset();
	m_indexBuffer.Reset();

	for (auto& buffer : _buffers)
	{
		buffer.second.Buffer().Reset();
	}

	_buffers.clear();
}