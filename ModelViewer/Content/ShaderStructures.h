#pragma once

#define DIFFUSE

namespace ModelViewer
{
	// Constant buffer used to send MVP matrices to the vertex shader.
	__declspec(align(16)) struct ModelViewProjectionConstantBuffer
	{
		DirectX::XMFLOAT4X4 model;
		DirectX::XMFLOAT4X4 view;
		DirectX::XMFLOAT4X4 projection;

#ifdef DIFFUSE
		DirectX::XMFLOAT4 light_direction;
		DirectX::XMFLOAT3 color;
#endif

	};

	__declspec(align(16)) struct LineDrawingConstantBuffer
	{
		DirectX::XMFLOAT3 pos;
		DirectX::XMFLOAT3 color;
	};

	// Used to send per-vertex data to the vertex shader.
	struct VertexPositionColor
	{
		DirectX::XMFLOAT3 pos;
		DirectX::XMFLOAT3 color;
	};
}