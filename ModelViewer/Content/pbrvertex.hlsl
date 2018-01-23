#define NORMALS
#define UV

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
    float4 position : POSITION;
#ifdef NORMALS
    float3 normal : NORMAL;
#endif
#ifdef UV
    float2 texcoord : TEXCOORD0;
#endif
};

// Per-pixel color data passed through the pixel shader.
struct PixelShaderInput
{
    float4 position : SV_POSITION;
    float3 poswithoutw : POSITION;

#ifdef NORMALS
    float3 normal : NORMAL;
#endif
#ifdef DIFFUSE
    float3 lightdir : TEXCOORD1;
#endif
#ifdef UV
    float2 texcoord : TEXCOORD0;
#endif
};

#ifdef HAS_NORMALS
attribute vec4 a_Normal;
#endif

#ifdef HAS_TANGENTS
attribute vec4 a_Tangent;
#endif

uniform mat4 u_MVPMatrix;
uniform mat4 u_ModelMatrix;

#ifdef HAS_NORMALS
#ifdef HAS_TANGENTS
varying mat3 v_TBN;
#else
varying vec3 v_Normal;
#endif
#endif

PixelShaderInput main(VertexShaderInput input)
{
    PixelShaderInput output;

	// Transform the vertex position into projected space.
    float4 pos = mul(input.position, model);
    output.poswithoutw = float3(pos.xyz) / pos.w;

#ifdef NORMALS
    // If we have normals...
    output.normal = mul(float4(input.normal.xyz, 0.0), model);
#endif

#ifdef UV
    output.texcoord = input.texcoord;
#else
    output.texcoord = float2(0.0ff, 0.0f);
#endif

#ifdef HAS_NORMALS
#ifdef HAS_TANGENTS
  vec3 normalW = normalize(vec3(u_ModelMatrix * vec4(a_Normal.xyz, 0.0)));
  vec3 tangentW = normalize(vec3(u_ModelMatrix * vec4(a_Tangent.xyz, 0.0)));
  vec3 bitangentW = cross(normalW, tangentW) * a_Tangent.w;
  v_TBN = mat3(tangentW, bitangentW, normalW);
#else // HAS_TANGENTS != 1
  v_Normal = normalize(vec3(u_ModelMatrix * vec4(a_Normal.xyz, 0.0)));
#endif
#endif

    // Transform the vertex position into projected space.
    pos = mul(pos, model);
    pos = mul(pos, view);
    pos = mul(pos, projection);
    output.position = pos;

    return output;
}