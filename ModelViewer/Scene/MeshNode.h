#pragma once

#include "GraphContainerNode.h"
#include "Common\DeviceResources.h"
#include <map>
#include "NodeMaterial.h"
#include <future>
#include <experimental/resumable>
#include <pplawait.h>

using namespace WinRTGLTFParser;
using namespace Microsoft::WRL;
using namespace std;
using namespace DX;
using namespace DirectX;

class MeshNode : public GraphContainerNode
{
public:
	MeshNode(int index);
	virtual ~MeshNode();

	void CompileAndLoadShaders();

	virtual void Draw(ID3D11DeviceContext2 *context);
	virtual void CreateDeviceDependentResources();
	virtual void Initialise(const shared_ptr<DeviceResources>& deviceResources);
	virtual void AfterLoad();

	void CreateBuffer(GLTF_BufferData^ data);
	void CreateTexture(GLTF_TextureData^ data);
	void CreateMaterial(GLTF_MaterialData^ data);
	void CreateTransform(GLTF_TransformData^ data);

	void* operator new(size_t i)
	{
		return _mm_malloc(i, 16);
	}

	void operator delete(void* p)
	{
		_mm_free(p);
	}

private:
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

	shared_ptr<DeviceResources> m_deviceResources;
	map<wstring, BufferWrapper> _buffers;
	ComPtr<ID3D11InputLayout> m_inputLayout;

	ComPtr<ID3D11SamplerState> _spSampler;
	ComPtr<ID3D11ShaderResourceView> _spTexture;

	ComPtr<ID3D11VertexShader> m_vertexShader;
	ComPtr<ID3D11PixelShader> m_pixelShader;
	ComPtr<ID3D11RasterizerState> _pRasterState;

	shared_ptr<NodeMaterial> _material;

	uint32	m_indexCount;
	bool m_loadingComplete;

	shared_ptr<NodeMaterial> _currentMaterial;
};

