#pragma once

#include "..\Common\DeviceResources.h"
#include "ShaderStructures.h"
#include "..\Common\StepTimer.h"
#include "../SharedGLTFParser/gltfparser.h"
#include <map>
#include <string>

namespace D3DTestApp
{
	using namespace WinRTGLTFParser;
	using namespace std;
	using namespace Microsoft::WRL;

	// This sample renderer instantiates a basic rendering pipeline.
	class Sample3DSceneRenderer
	{
	public:
		Sample3DSceneRenderer(const shared_ptr<DX::DeviceResources>& deviceResources);
		void CreateDeviceDependentResources();
		void CreateWindowSizeDependentResources();
		void ReleaseDeviceDependentResources();
		void Update(DX::StepTimer const& timer);
		void Render();
		void StartTracking();
		void TrackingUpdate(float positionX);
		void StopTracking();
		bool IsTracking() { return m_tracking; }
		void OnBuffer(GLTF_BufferData^ data);

	private:
		void Rotate(float radians);

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
			GLTF_BufferData^ _data;
			ComPtr<ID3D11Buffer> _buffer;
		};

		// Cached pointer to device resources.
		shared_ptr<DX::DeviceResources> m_deviceResources;

		// Direct3D resources for cube geometry.
		ComPtr<ID3D11InputLayout>	m_inputLayout;
		ComPtr<ID3D11Buffer>		m_vertexBuffer;
		ComPtr<ID3D11Buffer>		m_indexBuffer;
		ComPtr<ID3D11VertexShader>	m_vertexShader;
		ComPtr<ID3D11PixelShader>	m_pixelShader;
		ComPtr<ID3D11Buffer>		m_constantBuffer;

		map<wstring, BufferWrapper> _buffers;

		// System resources for cube geometry.
		ModelViewProjectionConstantBuffer	m_constantBufferData;
		uint32	m_indexCount;

		// Variables used with the rendering loop.
		bool	m_loadingComplete;
		float	m_degreesPerSecond;
		bool	m_tracking;
	};
}

