#define DIFFUSE

// Per-pixel color data passed through the pixel shader.
struct PixelShaderInput
{
	float4 pos : SV_POSITION;
#ifdef DIFFUSE
    float3 normal : NORMAL;
    float3 lightdir : TEXCOORD1;
#endif

};

// A pass-through function for the (interpolated) color data.
float4 main(PixelShaderInput input) : SV_TARGET
{
    float4 diffuseColor = float4(1.0f, 0.0f, 0.0f, 1.0f);

#ifdef DIFFUSE
    diffuseColor = diffuseColor * saturate(dot(input.lightdir, input.normal));
#endif

    return diffuseColor;

}
