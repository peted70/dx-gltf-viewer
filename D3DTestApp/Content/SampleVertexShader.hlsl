#define DIFFUSE
// A constant buffer that stores the three basic column-major matrices for composing geometry.
cbuffer ModelViewProjectionConstantBuffer : register(b0)
{
	matrix model;
	matrix view;
	matrix projection;
#ifdef DIFFUSE
	float4 light_direction;
    float3 color;
#endif
};

// Per-vertex data used as input to the vertex shader.
struct VertexShaderInput
{
	float3 pos : POSITION;
#ifdef DIFFUSE
    float3 normal : NORMAL;
    float2 texcoord : TEXCOORD0;
#endif
};

// Per-pixel color data passed through the pixel shader.
struct PixelShaderInput
{
	float4 pos : SV_POSITION;
#ifdef DIFFUSE
    float3 normal : NORMAL;
    float3 lightdir : TEXCOORD1;
    float2 texcoord : TEXCOORD0;
#endif
};

// Simple shader to do vertex processing on the GPU.
PixelShaderInput main(VertexShaderInput input)
{
	PixelShaderInput output;
	float4 pos = float4(input.pos, 1.0f);

	// Transform the vertex position into projected space.
	pos = mul(pos, model);
	pos = mul(pos, view);
	pos = mul(pos, projection);
	output.pos = pos;

    output.texcoord = input.texcoord;

#ifdef DIFFUSE
    output.lightdir = normalize(light_direction);
    output.normal = normalize(mul(input.normal, model));
#endif

	return output;
}
