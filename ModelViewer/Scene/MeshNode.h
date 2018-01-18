#pragma once

#include "GraphContainerNode.h"
#include "Common\DeviceResources.h"
#include <map>

using namespace WinRTGLTFParser;
using namespace Microsoft::WRL;

class MeshNode : public GraphContainerNode
{
public:
	MeshNode();
	virtual ~MeshNode();

	virtual void Draw(ID3D11DeviceContext2 *context);
	virtual void CreateDeviceDependentResources();
	virtual void Initialise(const std::shared_ptr<DX::DeviceResources>& deviceResources);

	void CreateBuffer(GLTF_BufferData^ data);
	void CreateTexture(GLTF_TextureData^ data);

private:
	vector<uint8_t> LoadBGRAImage(void *imgFileData, int imgFileDataSize, uint32_t& width, uint32_t& height);

	class BufferWrapper
	{
	public:
		BufferWrapper(GLTF_BufferData^ data, ComPtr<ID3D11Buffer> buffer) :
			_data(data),
			_buffer(buffer)
		{
		}
		BufferWrapper() {}
		ComPtr<ID3D11Buffer>& Buffer() { return _buffer; }

		GLTF_BufferData^ Data() { return _data; }

	private:
		GLTF_BufferData ^ _data;
		ComPtr<ID3D11Buffer> _buffer;
	};

	shared_ptr<DX::DeviceResources> m_deviceResources;
	map<wstring, BufferWrapper> _buffers;
	ComPtr<ID3D11InputLayout> m_inputLayout;

	ComPtr<ID3D11SamplerState> _spSampler;
	ComPtr<ID3D11ShaderResourceView> _spTexture;

	ComPtr<ID3D11VertexShader> m_vertexShader;
	ComPtr<ID3D11PixelShader> m_pixelShader;
	ComPtr<ID3D11RasterizerState> _pRasterState;

	uint32	m_indexCount;
	bool m_loadingComplete;
};

