#pragma once

#define DIFFUSE

namespace ModelViewer
{
	using namespace DirectX;

	// Constant buffer used to send MVP matrices to the vertex shader.
	__declspec(align(16)) struct ModelViewProjectionConstantBuffer
	{
		XMFLOAT4X4 model;
		XMFLOAT4X4 view;
		XMFLOAT4X4 projection;

#ifdef DIFFUSE
		XMFLOAT4 light_direction;
		XMFLOAT3 color;
#endif

	};

	__declspec(align(16)) struct LineDrawingConstantBuffer
	{
		XMFLOAT3 pos;
		XMFLOAT3 color;
	};

	// Used to send per-vertex data to the vertex shader.
	struct VertexPositionColor
	{
		XMFLOAT3 pos;
		XMFLOAT3 color;
	};

	struct Light
	{
		XMFLOAT3 dir;
		XMFLOAT3 colour;
	};

	__declspec(align(16)) struct cbPerFrame
	{
		Light light;
	};

	__declspec(align(16)) struct cbPerObject
	{
		float normalScale;
		XMFLOAT3 emissiveFactor;
		float occlusionStrength;
		XMFLOAT2 metallicRoughnessValues;
		XMFLOAT4 baseColorFactor;
		XMFLOAT3 camera;

		// debugging flags used for shader output of intermediate PBR variables
		XMFLOAT4 scaleDiffBaseMR;
		XMFLOAT4 scaleFGDSpec;
		XMFLOAT4 scaleIBLAmbient;
	};
}