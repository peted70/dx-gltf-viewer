attribute vec4 a_Position;

#ifdef HAS_NORMALS
attribute vec4 a_Normal;
#endif

#ifdef HAS_TANGENTS
attribute vec4 a_Tangent;
#endif

#ifdef HAS_UV
attribute vec2 a_UV;
#endif

uniform mat4 u_MVPMatrix;
uniform mat4 u_ModelMatrix;

varying vec3v_Position;
varying vec2v_UV;

#ifdef HAS_NORMALS
#ifdef HAS_TANGENTS
varying mat3 v_TBN;
#else
varying vec3 v_Normal;
#endif
#endif

float4 main(float4 pos : POSITION) : SV_POSITION
{
    vec4 pos = u_ModelMatrix * a_Position;
    v_Position = vec3(pos.xyz) / pos.w;

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

#ifdef HAS_UV
  v_UV = a_UV;
#else
    v_UV = vec2(0., 0.);
#endif

    return u_MVPMatrix * a_Position; // needs w for proper perspective correction
}