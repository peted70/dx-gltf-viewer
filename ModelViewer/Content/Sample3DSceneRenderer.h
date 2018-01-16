#pragma once

#include "..\Common\DeviceResources.h"
#include "ShaderStructures.h"
#include "..\Common\StepTimer.h"
#include "../SharedGLTFParser/gltfparser.h"
#include <map>
#include <string>
#include "DXGrid.h"
#include "Axis.h"
#include "./Scene/GraphContainerNode.h"

namespace ModelViewer
{
	using namespace WinRTGLTFParser;
	using namespace std;
	using namespace Microsoft::WRL;
	using namespace Windows::System;

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
		void StartTracking(float positionX, float positionY, VirtualKeyModifiers mod);
		void TrackingUpdate(float positionX, float positionY, VirtualKeyModifiers mod);
		void StopTracking(float positionX, float positionY, VirtualKeyModifiers mod);
		bool IsTracking() { return m_tracking; }
		void OnBuffer(GLTF_BufferData^ data);
		void OnTexture(WinRTGLTFParser::GLTF_TextureData^ data);

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

		void DrawGrid(ID3D11DeviceContext2 *context);
		void DrawAxis(ID3D11DeviceContext2 *context, Axis *axis);

		// Cached pointer to device resources.
		shared_ptr<DX::DeviceResources> m_deviceResources;

		// Direct3D resources for cube geometry.
		ComPtr<ID3D11InputLayout>	m_inputLayout;
		ComPtr<ID3D11Buffer>		m_vertexBuffer;
		ComPtr<ID3D11Buffer>		m_indexBuffer;
		ComPtr<ID3D11VertexShader>	m_vertexShader;
		ComPtr<ID3D11PixelShader>	m_pixelShader;
		ComPtr<ID3D11Buffer>		m_constantBuffer;

		ComPtr<ID3D11Buffer>		_lineDrawingConstantBuffer;
		ComPtr<ID3D11InputLayout>	_lineDrawingInputLayout;
		ComPtr<ID3D11VertexShader>	_simpleVertexShader;
		ComPtr<ID3D11PixelShader>	_simplePixelShader;

		ComPtr<ID3D11SamplerState>          _spSampler;
		ComPtr<ID3D11ShaderResourceView>    _spTexture;

		map<wstring, BufferWrapper> _buffers;

		// System resources for cube geometry.
		ModelViewProjectionConstantBuffer	m_constantBufferData;
		LineDrawingConstantBuffer _lineDrawingConstantBufferData;

		uint32	m_indexCount;

		// Variables used with the rendering loop.
		bool	m_loadingComplete;
		float	m_degreesPerSecond;
		bool	m_tracking;

		float _yaw;
		float _pitch;
		float _roll;
		float _zoom;

		unique_ptr<DXGrid> _grid;
		unique_ptr<Axis> _mainAxes;

		ID3D11RasterizerState * _pRasterState;
	};
}

