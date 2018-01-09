#define DIFFUSE

Texture2D shaderTexture;
SamplerState samplerState;

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

// A pass-through function for the (interpolated) color data.
float4 main(PixelShaderInput input) : SV_TARGET
{
    float4 diffuseColor = float4(1.0f, 0.0f, 0.0f, 1.0f);

    float4 value = shaderTexture.Sample(samplerState, input.texcoord);

#ifdef DIFFUSE
    diffuseColor = diffuseColor * saturate(dot(input.lightdir, input.normal));
#endif

    return (0.5f * diffuseColor) + (0.5f * value);

}
