// FRAGMENT SHADER BEGIN 
// GLSL BEGIN 
//#extension GL_OES_standard_derivatives : enable
//uniform highp vec3 webgl_75d497ae915a62ed;
//uniform highp vec3 webgl_53c8c08e89fba347;
//uniform lowp samplerCube webgl_afc1698251295a34;
//uniform lowp samplerCube webgl_9f72333e9c8ea8ab;
//uniform lowp sampler2D webgl_98e618279423cfef;
//uniform lowp sampler2D webgl_e36ab0d768d91b1b;
//uniform lowp sampler2D webgl_c6526bd4fdc2252b;
//uniform highp float webgl_66e0b7f99e337590;
//uniform lowp sampler2D webgl_e3a9b9f14a5d1ea1;
//uniform highp vec3 webgl_872d06f1b932325a;
//uniform lowp sampler2D webgl_a215171353a00b72;
//uniform lowp sampler2D webgl_fef39814f315ce8f;
//uniform highp float webgl_13cc3b85174642f4;
//uniform highp vec2 webgl_ec6aa117a0319d96;
//uniform highp vec4 webgl_2351ae0a609f99ae;
//uniform highp vec3 webgl_2cb748cf0c448a46;
//uniform highp vec4 webgl_ae2fe52d78d24c3e;
//uniform highp vec4 webgl_f1c15989d446e4dc;
//uniform highp vec4 webgl_2ae6aadcd1cd19fe;
//varying highp vec3 webgl_aeb421a2dbbe85e0;
//varying highp vec2 webgl_8b169777ade76cf1;
//varying highp vec3 webgl_eb79210487662846;
//
//struct webgl_2d5e024a41ffb4ef
//{
//	highp float webgl_d345483011602bdc;
//	highp float webgl_1414ae9d4598bc54;
//	highp float webgl_ad7d78d70e30cf43;
//	highp float webgl_7ffc2970e3c6debb;
//	highp float webgl_1f4786e5232138f3;
//	highp float webgl_ae318a32e60ff806;
//	highp float webgl_cb802fb45a3fc157;
//	highp vec3 webgl_d1970c5309fed947; 
//	highp vec3 webgl_276446f1a532bb44; 
//	highp float webgl_bf8effe5e2e481b; 
//	highp vec3 webgl_75e6c6e5d9ced83; 
//	highp vec3 webgl_5d831d5e5122da7d;
//}; 
//
//highp vec4 webgl_22bdc67c25b345fb(in highp vec4 webgl_ecaaf38794c2012f) 
//{ 
//	return webgl_ecaaf38794c2012f; 
//} 
//
//highp vec3 webgl_28f4837284085b1e() 
//{ 
//	highp vec3 webgl_ad053975182a68d9 = dFdx(webgl_aeb421a2dbbe85e0); 
//	highp vec3 webgl_f447c2a9afd92aa = dFdy(webgl_aeb421a2dbbe85e0); 
//	highp vec3 webgl_f0badb42ec990438 = dFdx(vec3(webgl_8b169777ade76cf1, 0.0)); 
//	highp vec3 webgl_13078f86b64f1aab = dFdy(vec3(webgl_8b169777ade76cf1, 0.0)); 
//	highp vec3 webgl_7cac0bd1a28a3c29 = (((webgl_13078f86b64f1aab.y * webgl_ad053975182a68d9) - (webgl_f0badb42ec990438.y * webgl_f447c2a9afd92aa)) / ((webgl_f0badb42ec990438.x * webgl_13078f86b64f1aab.y) - (webgl_13078f86b64f1aab.x * webgl_f0badb42ec990438.y))); 
//	highp vec3 webgl_6066a49efc3ba489 = normalize(webgl_eb79210487662846); 
//	(webgl_7cac0bd1a28a3c29 = normalize((webgl_7cac0bd1a28a3c29 - (webgl_6066a49efc3ba489 * dot(webgl_6066a49efc3ba489, webgl_7cac0bd1a28a3c29))))); 
//	highp vec3 webgl_44a9acbe7629930d = normalize(cross(webgl_6066a49efc3ba489, webgl_7cac0bd1a28a3c29)); 
//	highp vec3 s1055 = webgl_7cac0bd1a28a3c29; 
//	highp vec3 s1056 = webgl_44a9acbe7629930d; 
//	highp vec3 s1057 = webgl_6066a49efc3ba489; 
//	highp mat3 webgl_7c300f8567b12f74 = mat3(s1055[0], s1055[1], s1055[2], s1056[0], s1056[1], s1056[2], s1057[0], s1057[1], s1057[2]); 
//	highp vec3 webgl_dad496b00e4a459a = texture2D(webgl_c6526bd4fdc2252b, webgl_8b169777ade76cf1).xyz; 
//	(webgl_dad496b00e4a459a = normalize((webgl_7c300f8567b12f74 * (((2.0 * webgl_dad496b00e4a459a) - 1.0) * vec3(webgl_66e0b7f99e337590, webgl_66e0b7f99e337590, 1.0))))); 
//	return webgl_dad496b00e4a459a; 
//} 
//
//highp vec3 webgl_934471fe59ed5117(in webgl_2d5e024a41ffb4ef webgl_acd936d0e5c85b6e, in highp vec3 webgl_dad496b00e4a459a, in highp vec3 webgl_13255d5b39d96fd2) 
//{ 
//	highp vec3 webgl_f2ebeacec60af8c9 = webgl_22bdc67c25b345fb(texture2D(webgl_98e618279423cfef, vec2(webgl_acd936d0e5c85b6e.webgl_1414ae9d4598bc54, (1.0 - webgl_acd936d0e5c85b6e.webgl_ae318a32e60ff806)))).xyz; 
//	highp vec3 webgl_34c69f505c4fd836 = webgl_22bdc67c25b345fb(textureCube(webgl_afc1698251295a34, webgl_dad496b00e4a459a)).xyz; 
//	highp vec3 webgl_2df27bc11331106 = webgl_22bdc67c25b345fb(textureCube(webgl_9f72333e9c8ea8ab, webgl_13255d5b39d96fd2)).xyz; 
//	highp vec3 webgl_94f58b122e6fc376 = (webgl_34c69f505c4fd836 * webgl_acd936d0e5c85b6e.webgl_75e6c6e5d9ced83); 
//	highp vec3 webgl_17b20269d25ad846 = (webgl_2df27bc11331106 * ((webgl_acd936d0e5c85b6e.webgl_5d831d5e5122da7d * webgl_f2ebeacec60af8c9.x) + webgl_f2ebeacec60af8c9.y)); 
//	(webgl_94f58b122e6fc376 *= webgl_2ae6aadcd1cd19fe.x); (webgl_17b20269d25ad846 *= webgl_2ae6aadcd1cd19fe.y); 
//	return (webgl_94f58b122e6fc376 + webgl_17b20269d25ad846); 
//} 
//
//highp vec3 webgl_94f58b122e6fc376(in webgl_2d5e024a41ffb4ef webgl_acd936d0e5c85b6e) 
//{ 
//	return (webgl_acd936d0e5c85b6e.webgl_75e6c6e5d9ced83 / 3.1415927); 
//} 
//
//highp vec3 webgl_220567718147325b(in webgl_2d5e024a41ffb4ef webgl_acd936d0e5c85b6e) 
//{ 
//	return (webgl_acd936d0e5c85b6e.webgl_d1970c5309fed947 + ((webgl_acd936d0e5c85b6e.webgl_276446f1a532bb44 - webgl_acd936d0e5c85b6e.webgl_d1970c5309fed947) * pow(clamp((1.0 - webgl_acd936d0e5c85b6e.webgl_1f4786e5232138f3), 0.0, 1.0), 5.0))); 
//} 
//
//highp float webgl_f3b3fab1b6af2635(in webgl_2d5e024a41ffb4ef webgl_acd936d0e5c85b6e) 
//{ 
//	highp float webgl_d345483011602bdc = webgl_acd936d0e5c85b6e.webgl_d345483011602bdc; 
//	highp float webgl_1414ae9d4598bc54 = webgl_acd936d0e5c85b6e.webgl_1414ae9d4598bc54; 
//	highp float webgl_8f212d831e847c86 = webgl_acd936d0e5c85b6e.webgl_bf8effe5e2e481b; 
//	highp float webgl_c4eb0fa9c8982885 = ((2.0 * webgl_d345483011602bdc) / (webgl_d345483011602bdc + sqrt(((webgl_8f212d831e847c86 * webgl_8f212d831e847c86) + ((1.0 - (webgl_8f212d831e847c86 * webgl_8f212d831e847c86)) * (webgl_d345483011602bdc * webgl_d345483011602bdc))))));
//	highp float webgl_5cadaa118055ad85 = ((2.0 * webgl_1414ae9d4598bc54) / (webgl_1414ae9d4598bc54 + sqrt(((webgl_8f212d831e847c86 * webgl_8f212d831e847c86) + ((1.0 - (webgl_8f212d831e847c86 * webgl_8f212d831e847c86)) * (webgl_1414ae9d4598bc54 * webgl_1414ae9d4598bc54))))));
//	return (webgl_c4eb0fa9c8982885 * webgl_5cadaa118055ad85); 
//} 
//
//highp float webgl_6b677a17ea3d987e(in webgl_2d5e024a41ffb4ef webgl_acd936d0e5c85b6e) 
//{ 
//	highp float webgl_274f37d5f121b016 = (webgl_acd936d0e5c85b6e.webgl_bf8effe5e2e481b * webgl_acd936d0e5c85b6e.webgl_bf8effe5e2e481b); 
//	highp float webgl_a34964a2a96b201f = ((((webgl_acd936d0e5c85b6e.webgl_ad7d78d70e30cf43 * webgl_274f37d5f121b016) - webgl_acd936d0e5c85b6e.webgl_ad7d78d70e30cf43) * webgl_acd936d0e5c85b6e.webgl_ad7d78d70e30cf43) + 1.0); 
//	return (webgl_274f37d5f121b016 / ((3.1415927 * webgl_a34964a2a96b201f) * webgl_a34964a2a96b201f)); 
//} 
//
//void main() 
//{ 
//	(gl_FragColor = vec4(0.0, 0.0, 0.0, 0.0)); 
//	highp float webgl_ae318a32e60ff806 = webgl_ec6aa117a0319d96.y; 
//	highp float webgl_538e486927c2e97 = webgl_ec6aa117a0319d96.x; 
//	highp vec4 webgl_b12f930008d316f6 = texture2D(webgl_a215171353a00b72, webgl_8b169777ade76cf1); 
//	(webgl_ae318a32e60ff806 = (webgl_b12f930008d316f6.y * webgl_ae318a32e60ff806)); 
//	(webgl_538e486927c2e97 = (webgl_b12f930008d316f6.z * webgl_538e486927c2e97)); 
//	(webgl_ae318a32e60ff806 = clamp(webgl_ae318a32e60ff806, 0.039999999, 1.0)); 
//	(webgl_538e486927c2e97 = clamp(webgl_538e486927c2e97, 0.0, 1.0)); 
//	highp float webgl_bf8effe5e2e481b = (webgl_ae318a32e60ff806 * webgl_ae318a32e60ff806); 
//	highp vec4 webgl_84bda37ee0e666a0 = (webgl_22bdc67c25b345fb(texture2D(webgl_e36ab0d768d91b1b, webgl_8b169777ade76cf1)) * webgl_2351ae0a609f99ae);
//	highp vec3 webgl_d79e71aa6da73ec7 = vec3(0.039999999, 0.039999999, 0.039999999); 
//	highp vec3 webgl_75e6c6e5d9ced83 = (webgl_84bda37ee0e666a0.xyz * (vec3(1.0, 1.0, 1.0) - webgl_d79e71aa6da73ec7)); 
//	(webgl_75e6c6e5d9ced83 *= (1.0 - webgl_538e486927c2e97)); 
//	highp vec3 webgl_5d831d5e5122da7d = mix(webgl_d79e71aa6da73ec7, webgl_84bda37ee0e666a0.xyz, webgl_538e486927c2e97); 
//	highp float webgl_778323d41fa2a9ee = max(max(webgl_5d831d5e5122da7d.x, webgl_5d831d5e5122da7d.y), webgl_5d831d5e5122da7d.z); 
//	highp float webgl_276446f1a532bb44 = clamp((webgl_778323d41fa2a9ee * 25.0), 0.0, 1.0); 
//	highp vec3 webgl_ae5023af9c1a568 = webgl_5d831d5e5122da7d.xyz;
//	highp vec3 webgl_239d3c0d22b9707e = (vec3(1.0, 1.0, 1.0) * webgl_276446f1a532bb44); 
//	highp vec3 webgl_dad496b00e4a459a = webgl_28f4837284085b1e(); 
//	highp vec3 webgl_f8057cd9a47842a = normalize((webgl_2cb748cf0c448a46 - webgl_aeb421a2dbbe85e0)); 
//	highp vec3 webgl_29c1da7f92128805 = normalize(webgl_75d497ae915a62ed); 
//	highp vec3 webgl_8216a9694030d187 = normalize((webgl_29c1da7f92128805 + webgl_f8057cd9a47842a)); 
//	highp vec3 webgl_13255d5b39d96fd2 = (-normalize(reflect(webgl_f8057cd9a47842a, webgl_dad496b00e4a459a))); 
//	highp float webgl_d345483011602bdc = clamp(dot(webgl_dad496b00e4a459a, webgl_29c1da7f92128805), 0.001, 1.0); 
//	highp float webgl_1414ae9d4598bc54 = (abs(dot(webgl_dad496b00e4a459a, webgl_f8057cd9a47842a)) + 0.001); 
//	highp float webgl_ad7d78d70e30cf43 = clamp(dot(webgl_dad496b00e4a459a, webgl_8216a9694030d187), 0.0, 1.0); 
//	highp float webgl_7ffc2970e3c6debb = clamp(dot(webgl_29c1da7f92128805, webgl_8216a9694030d187), 0.0, 1.0); 
//	highp float webgl_1f4786e5232138f3 = clamp(dot(webgl_f8057cd9a47842a, webgl_8216a9694030d187), 0.0, 1.0); 
//	webgl_2d5e024a41ffb4ef webgl_acd936d0e5c85b6e = webgl_2d5e024a41ffb4ef(webgl_d345483011602bdc, webgl_1414ae9d4598bc54, webgl_ad7d78d70e30cf43, webgl_7ffc2970e3c6debb, webgl_1f4786e5232138f3, webgl_ae318a32e60ff806, webgl_538e486927c2e97, webgl_ae5023af9c1a568, webgl_239d3c0d22b9707e, webgl_bf8effe5e2e481b, webgl_75e6c6e5d9ced83, webgl_5d831d5e5122da7d); 
//	highp vec3 webgl_14a3d02bb2f28360 = webgl_220567718147325b(webgl_acd936d0e5c85b6e); 
//	highp float webgl_adda5e5e6680c563 = webgl_f3b3fab1b6af2635(webgl_acd936d0e5c85b6e); 
//	highp float webgl_807cd7c3f3d33ab6 = webgl_6b677a17ea3d987e(webgl_acd936d0e5c85b6e); 
//	highp vec3 webgl_b059dd4471d1c07 = ((1.0 - webgl_14a3d02bb2f28360) * webgl_94f58b122e6fc376(webgl_acd936d0e5c85b6e)); 
//	highp vec3 webgl_6e49c1f99652b960 = (((webgl_14a3d02bb2f28360 * webgl_adda5e5e6680c563) * webgl_807cd7c3f3d33ab6) / ((4.0 * webgl_d345483011602bdc) * webgl_1414ae9d4598bc54)); 
//	highp vec3 webgl_19dff938713edbff = ((webgl_d345483011602bdc * webgl_53c8c08e89fba347) * (webgl_b059dd4471d1c07 + webgl_6e49c1f99652b960)); 
//	(webgl_19dff938713edbff += webgl_934471fe59ed5117(webgl_acd936d0e5c85b6e, webgl_dad496b00e4a459a, webgl_13255d5b39d96fd2)); 
//	highp float webgl_af3eba424014769 = texture2D(webgl_fef39814f315ce8f, webgl_8b169777ade76cf1).x; 
//	(webgl_19dff938713edbff = mix(webgl_19dff938713edbff, (webgl_19dff938713edbff * webgl_af3eba424014769), webgl_13cc3b85174642f4)); 
//	highp vec3 webgl_ad7a44ca414cb9d7 = (webgl_22bdc67c25b345fb(texture2D(webgl_e3a9b9f14a5d1ea1, webgl_8b169777ade76cf1)).xyz * webgl_872d06f1b932325a); 
//	(webgl_19dff938713edbff += webgl_ad7a44ca414cb9d7); 
//	(webgl_19dff938713edbff = mix(webgl_19dff938713edbff, webgl_14a3d02bb2f28360, webgl_f1c15989d446e4dc.x)); 
//	(webgl_19dff938713edbff = mix(webgl_19dff938713edbff, vec3(webgl_adda5e5e6680c563), webgl_f1c15989d446e4dc.y)); 
//	(webgl_19dff938713edbff = mix(webgl_19dff938713edbff, vec3(webgl_807cd7c3f3d33ab6), webgl_f1c15989d446e4dc.z)); 
//	(webgl_19dff938713edbff = mix(webgl_19dff938713edbff, webgl_6e49c1f99652b960, webgl_f1c15989d446e4dc.w)); 
//	(webgl_19dff938713edbff = mix(webgl_19dff938713edbff, webgl_b059dd4471d1c07, webgl_ae2fe52d78d24c3e.x)); 
//	(webgl_19dff938713edbff = mix(webgl_19dff938713edbff, webgl_84bda37ee0e666a0.xyz, webgl_ae2fe52d78d24c3e.y)); 
//	(webgl_19dff938713edbff = mix(webgl_19dff938713edbff, vec3(webgl_538e486927c2e97), webgl_ae2fe52d78d24c3e.z)); 
//	(webgl_19dff938713edbff = mix(webgl_19dff938713edbff, vec3(webgl_ae318a32e60ff806), webgl_ae2fe52d78d24c3e.w)); 
//	(gl_FragColor = vec4(pow(webgl_19dff938713edbff, vec3(0.45454544, 0.45454544, 0.45454544)), webgl_84bda37ee0e666a0.w)); 
//} 
// GLSL END 
// INITIAL HLSL BEGIN 
struct _webgl_2d5e024a41ffb4ef 
{ 
	float _webgl_d345483011602bdc; 
	float _webgl_1414ae9d4598bc54; 
	float _webgl_ad7d78d70e30cf43; 
	float _webgl_7ffc2970e3c6debb; 
	float _webgl_1f4786e5232138f3; 
	float _webgl_ae318a32e60ff806; 
	float _webgl_cb802fb45a3fc157; 
	float3 _webgl_d1970c5309fed947; 
	float3 _webgl_276446f1a532bb44; 
	float _webgl_bf8effe5e2e481b; 
	float3 _webgl_75e6c6e5d9ced83; 
	float3 _webgl_5d831d5e5122da7d; 
}; 

#pragma pack_matrix(row_major) 

struct rm__webgl_2d5e024a41ffb4ef 
{ 
	float _webgl_d345483011602bdc; 
	float _webgl_1414ae9d4598bc54; 
	float _webgl_ad7d78d70e30cf43; 
	float _webgl_7ffc2970e3c6debb; 
	float _webgl_1f4786e5232138f3; 
	float _webgl_ae318a32e60ff806; 
	float _webgl_cb802fb45a3fc157; 
	float3 _webgl_d1970c5309fed947; 
	float3 _webgl_276446f1a532bb44; 
	float _webgl_bf8effe5e2e481b; 
	float3 _webgl_75e6c6e5d9ced83; 
	float3 _webgl_5d831d5e5122da7d; 
}; 

#pragma pack_matrix(column_major) 

struct std__webgl_2d5e024a41ffb4ef 
{ 
	float _webgl_d345483011602bdc; 
	float _webgl_1414ae9d4598bc54; 
	float _webgl_ad7d78d70e30cf43; 
	float _webgl_7ffc2970e3c6debb; 
	float _webgl_1f4786e5232138f3; 
	float _webgl_ae318a32e60ff806; 
	float _webgl_cb802fb45a3fc157; 
	float3 _webgl_d1970c5309fed947; 
	float3 _webgl_276446f1a532bb44; 
	float _webgl_bf8effe5e2e481b; 
	float3 _webgl_75e6c6e5d9ced83; 
	float3 _webgl_5d831d5e5122da7d; 
}; 

#pragma pack_matrix(row_major) 

struct std_rm__webgl_2d5e024a41ffb4ef 
{ 
	float _webgl_d345483011602bdc; 
	float _webgl_1414ae9d4598bc54; 
	float _webgl_ad7d78d70e30cf43; 
	float _webgl_7ffc2970e3c6debb; 
	float _webgl_1f4786e5232138f3; 
	float _webgl_ae318a32e60ff806; 
	float _webgl_cb802fb45a3fc157; 
	float3 _webgl_d1970c5309fed947; 
	float3 _webgl_276446f1a532bb44; 
	float _webgl_bf8effe5e2e481b; 
	float3 _webgl_75e6c6e5d9ced83; 
	float3 _webgl_5d831d5e5122da7d; 
}; 

#pragma pack_matrix(column_major) 

_webgl_2d5e024a41ffb4ef _webgl_2d5e024a41ffb4ef_ctor(float x0, float x1, float x2, float x3, float x4, float x5, float x6, float3 x7, float3 x8, float x9, float3 x10, float3 x11) 
{ 
	_webgl_2d5e024a41ffb4ef structure = { x0, x1, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11}; 
	return structure; 
} 

float2 vec2_ctor(float x0, float x1) 
{ 
	return float2(x0, x1); 
} 

float3 vec3_ctor(float x0) 
{ 
	return float3(x0, x0, x0); 
} 

float3 vec3_ctor(float x0, float x1, float x2) 
{ 
	return float3(x0, x1, x2); 
} 

float3 vec3_ctor(float2 x0, float x1) 
{ 
	return float3(x0, x1); 
} 

float3x3 mat3_ctor(float x0, float x1, float x2, float x3, float x4, float x5, float x6, float x7, float x8) 
{ 
	return float3x3(x0, x1, x2, x3, x4, x5, x6, x7, x8); 
} 

float4 vec4_ctor(float3 x0, float x1) 
{ 
	return float4(x0, x1); 
} 

// Uniforms 
uniform float _webgl_13cc3b85174642f4 : register(c0); 
uniform float4 _webgl_2351ae0a609f99ae : register(c1); 
uniform float4 _webgl_2ae6aadcd1cd19fe : register(c2); 
uniform float3 _webgl_2cb748cf0c448a46 : register(c3); 
uniform float3 _webgl_53c8c08e89fba347 : register(c4); 
uniform float _webgl_66e0b7f99e337590 : register(c5); 
uniform float3 _webgl_75d497ae915a62ed : register(c6); 
uniform float3 _webgl_872d06f1b932325a : register(c7); 
uniform float4 _webgl_ae2fe52d78d24c3e : register(c8); 
uniform float2 _webgl_ec6aa117a0319d96 : register(c9); 
uniform float4 _webgl_f1c15989d446e4dc : register(c10); 
static const uint _webgl_98e618279423cfef = 0; 
static const uint _webgl_a215171353a00b72 = 1; 
static const uint _webgl_c6526bd4fdc2252b = 2; 
static const uint _webgl_e36ab0d768d91b1b = 3; 
static const uint _webgl_e3a9b9f14a5d1ea1 = 4; 
static const uint _webgl_fef39814f315ce8f = 5; 
uniform Texture2D textures2D[6] : register(t0); 
uniform SamplerState samplers2D[6] : register(s0); 
static const uint _webgl_9f72333e9c8ea8ab = 6; 
static const uint _webgl_afc1698251295a34 = 7; 
static const uint textureIndexOffsetCube = 6; 
static const uint samplerIndexOffsetCube = 6; 
uniform TextureCube texturesCube[2] : register(t6); 
uniform SamplerState samplersCube[2] : register(s6); 

#ifdef ANGLE_ENABLE_LOOP_FLATTEN 
#define LOOP [loop] 
#define FLATTEN [flatten] 
#else 
#define LOOP 
#define FLATTEN 
#endif 

// Varyings 
static float2 _webgl_8b169777ade76cf1 = {0, 0}; 
static float3 _webgl_aeb421a2dbbe85e0 = {0, 0, 0}; 
static float3 _webgl_eb79210487662846 = {0, 0, 0}; 
static float4 gl_Color[1] = { float4(0, 0, 0, 0) }; 
cbuffer DriverConstants : register(b1) 
{ 
	struct SamplerMetadata 
	{ 
		int baseLevel; 
		int internalFormatBits; 
		int wrapModes; 
		int padding; 
	}; 
	
	SamplerMetadata samplerMetadata[8] : packoffset(c4); 
}; 

#define GL_USES_FRAG_COLOR 
float4 gl_texture2D(uint samplerIndex, float2 t) 
{ 
	return textures2D[samplerIndex].Sample(samplers2D[samplerIndex], float2(t.x, t.y)); 
} 

float4 gl_textureCube(uint samplerIndex, float3 t) 
{ 
	const uint textureIndex = samplerIndex - textureIndexOffsetCube; 
	const uint samplerArrayIndex = samplerIndex - samplerIndexOffsetCube; 
	return texturesCube[textureIndex].Sample(samplersCube[samplerArrayIndex], float3(t.x, t.y, t.z)); 
} ; 

float4 f_webgl_22bdc67c25b345fb_float4(in float4 _webgl_ecaaf38794c2012f) 
{ 
	return _webgl_ecaaf38794c2012f; 
} 

float3 f_webgl_28f4837284085b1e() 
{ 
	float3 _webgl_ad053975182a68d9 = ddx(_webgl_aeb421a2dbbe85e0); 
	float3 _webgl_f447c2a9afd92aa = ddy(_webgl_aeb421a2dbbe85e0); 
	float3 _webgl_f0badb42ec990438 = ddx(vec3_ctor(_webgl_8b169777ade76cf1, 0.0)); 
	float3 _webgl_13078f86b64f1aab = ddy(vec3_ctor(_webgl_8b169777ade76cf1, 0.0)); 
	float3 _webgl_7cac0bd1a28a3c29 = (((_webgl_13078f86b64f1aab.y * _webgl_ad053975182a68d9) - (_webgl_f0badb42ec990438.y * _webgl_f447c2a9afd92aa)) / ((_webgl_f0badb42ec990438.x * _webgl_13078f86b64f1aab.y) - (_webgl_13078f86b64f1aab.x * _webgl_f0badb42ec990438.y))); 
	float3 _webgl_6066a49efc3ba489 = normalize(_webgl_eb79210487662846); 
	(_webgl_7cac0bd1a28a3c29 = normalize((_webgl_7cac0bd1a28a3c29 - (_webgl_6066a49efc3ba489 * dot(_webgl_6066a49efc3ba489, _webgl_7cac0bd1a28a3c29))))); 
	float3 _webgl_44a9acbe7629930d = normalize(cross(_webgl_6066a49efc3ba489, _webgl_7cac0bd1a28a3c29)); 
	float3 _s1055 = _webgl_7cac0bd1a28a3c29; 
	float3 _s1056 = _webgl_44a9acbe7629930d; 
	float3 _s1057 = _webgl_6066a49efc3ba489; 
	float3x3 _webgl_7c300f8567b12f74 = mat3_ctor(_s1055[0], _s1055[1], _s1055[2], _s1056[0], _s1056[1], _s1056[2], _s1057[0], _s1057[1], _s1057[2]); 
	float3 _webgl_dad496b00e4a459a = gl_texture2D(_webgl_c6526bd4fdc2252b, _webgl_8b169777ade76cf1).xyz; 
	(_webgl_dad496b00e4a459a = normalize(mul(transpose(_webgl_7c300f8567b12f74), (((2.0 * _webgl_dad496b00e4a459a) - 1.0) * vec3_ctor(_webgl_66e0b7f99e337590, _webgl_66e0b7f99e337590, 1.0))))); 
	return _webgl_dad496b00e4a459a; 
} 

float3 f_webgl_934471fe59ed5117__webgl_2d5e024a41ffb4ef(in _webgl_2d5e024a41ffb4ef _webgl_acd936d0e5c85b6e, in float3 _webgl_dad496b00e4a459a, in float3 _webgl_13255d5b39d96fd2) 
{ 
	float3 _webgl_f2ebeacec60af8c9 = f_webgl_22bdc67c25b345fb_float4(gl_texture2D(_webgl_98e618279423cfef, vec2_ctor(_webgl_acd936d0e5c85b6e._webgl_1414ae9d4598bc54, (1.0 - _webgl_acd936d0e5c85b6e._webgl_ae318a32e60ff806)))).xyz; 
	float3 _webgl_34c69f505c4fd836 = f_webgl_22bdc67c25b345fb_float4(gl_textureCube(_webgl_afc1698251295a34, _webgl_dad496b00e4a459a)).xyz; 
	float3 _webgl_2df27bc11331106 = f_webgl_22bdc67c25b345fb_float4(gl_textureCube(_webgl_9f72333e9c8ea8ab, _webgl_13255d5b39d96fd2)).xyz; 
	float3 _webgl_94f58b122e6fc376 = (_webgl_34c69f505c4fd836 * _webgl_acd936d0e5c85b6e._webgl_75e6c6e5d9ced83); 
	float3 _webgl_17b20269d25ad846 = (_webgl_2df27bc11331106 * ((_webgl_acd936d0e5c85b6e._webgl_5d831d5e5122da7d * _webgl_f2ebeacec60af8c9.x) + _webgl_f2ebeacec60af8c9.y)); 
	(_webgl_94f58b122e6fc376 *= _webgl_2ae6aadcd1cd19fe.x); 
	(_webgl_17b20269d25ad846 *= _webgl_2ae6aadcd1cd19fe.y); 
	return (_webgl_94f58b122e6fc376 + _webgl_17b20269d25ad846); 
} 

float3 f_webgl_94f58b122e6fc376__webgl_2d5e024a41ffb4ef(in _webgl_2d5e024a41ffb4ef _webgl_acd936d0e5c85b6e) 
{ 
	return (_webgl_acd936d0e5c85b6e._webgl_75e6c6e5d9ced83 / 3.1415927); 
} 

float3 f_webgl_220567718147325b__webgl_2d5e024a41ffb4ef(in _webgl_2d5e024a41ffb4ef _webgl_acd936d0e5c85b6e) 
{ 
	float s1087 = clamp((1.0 - _webgl_acd936d0e5c85b6e._webgl_1f4786e5232138f3), 0.0, 1.0); 
	return (_webgl_acd936d0e5c85b6e._webgl_d1970c5309fed947 + ((_webgl_acd936d0e5c85b6e._webgl_276446f1a532bb44 - _webgl_acd936d0e5c85b6e._webgl_d1970c5309fed947) * ((((s1087 * s1087) * s1087) * s1087) * s1087))); 
} 

float f_webgl_f3b3fab1b6af2635__webgl_2d5e024a41ffb4ef(in _webgl_2d5e024a41ffb4ef _webgl_acd936d0e5c85b6e) 
{ 
	float _webgl_d345483011602bdc = _webgl_acd936d0e5c85b6e._webgl_d345483011602bdc; 
	float _webgl_1414ae9d4598bc54 = _webgl_acd936d0e5c85b6e._webgl_1414ae9d4598bc54; 
	float _webgl_8f212d831e847c86 = _webgl_acd936d0e5c85b6e._webgl_bf8effe5e2e481b; 
	float _webgl_c4eb0fa9c8982885 = ((2.0 * _webgl_d345483011602bdc) / (_webgl_d345483011602bdc + sqrt(((_webgl_8f212d831e847c86 * _webgl_8f212d831e847c86) + ((1.0 - (_webgl_8f212d831e847c86 * _webgl_8f212d831e847c86)) * (_webgl_d345483011602bdc * _webgl_d345483011602bdc)))))); 
	float _webgl_5cadaa118055ad85 = ((2.0 * _webgl_1414ae9d4598bc54) / (_webgl_1414ae9d4598bc54 + sqrt(((_webgl_8f212d831e847c86 * _webgl_8f212d831e847c86) + ((1.0 - (_webgl_8f212d831e847c86 * _webgl_8f212d831e847c86)) * (_webgl_1414ae9d4598bc54 * _webgl_1414ae9d4598bc54)))))); 
	return (_webgl_c4eb0fa9c8982885 * _webgl_5cadaa118055ad85); 
} 

float f_webgl_6b677a17ea3d987e__webgl_2d5e024a41ffb4ef(in _webgl_2d5e024a41ffb4ef _webgl_acd936d0e5c85b6e) 
{ 
	float _webgl_274f37d5f121b016 = (_webgl_acd936d0e5c85b6e._webgl_bf8effe5e2e481b * _webgl_acd936d0e5c85b6e._webgl_bf8effe5e2e481b); 
	float _webgl_a34964a2a96b201f = ((((_webgl_acd936d0e5c85b6e._webgl_ad7d78d70e30cf43 * _webgl_274f37d5f121b016) - _webgl_acd936d0e5c85b6e._webgl_ad7d78d70e30cf43) * _webgl_acd936d0e5c85b6e._webgl_ad7d78d70e30cf43) + 1.0); 
	return (_webgl_274f37d5f121b016 / ((3.1415927 * _webgl_a34964a2a96b201f) * _webgl_a34964a2a96b201f)); 
} 

float4 main() : SV_TARGET
{ 
	(gl_Color[0] = float4(0.0, 0.0, 0.0, 0.0)); 
	float _webgl_ae318a32e60ff806 = _webgl_ec6aa117a0319d96.y; 
	float _webgl_538e486927c2e97 = _webgl_ec6aa117a0319d96.x; 
	float4 _webgl_b12f930008d316f6 = gl_texture2D(_webgl_a215171353a00b72, _webgl_8b169777ade76cf1); 
	(_webgl_ae318a32e60ff806 = (_webgl_b12f930008d316f6.y * _webgl_ae318a32e60ff806)); 
	(_webgl_538e486927c2e97 = (_webgl_b12f930008d316f6.z * _webgl_538e486927c2e97)); 
	(_webgl_ae318a32e60ff806 = clamp(_webgl_ae318a32e60ff806, 0.039999999, 1.0)); 
	(_webgl_538e486927c2e97 = clamp(_webgl_538e486927c2e97, 0.0, 1.0)); 
	float _webgl_bf8effe5e2e481b = (_webgl_ae318a32e60ff806 * _webgl_ae318a32e60ff806); 
	float4 _webgl_84bda37ee0e666a0 = (f_webgl_22bdc67c25b345fb_float4(gl_texture2D(_webgl_e36ab0d768d91b1b, _webgl_8b169777ade76cf1)) * _webgl_2351ae0a609f99ae); 
	float3 _webgl_d79e71aa6da73ec7 = {0.039999999, 0.039999999, 0.039999999}; 
	float3 _webgl_75e6c6e5d9ced83 = (_webgl_84bda37ee0e666a0.xyz * (float3(1.0, 1.0, 1.0) - _webgl_d79e71aa6da73ec7)); 
	(_webgl_75e6c6e5d9ced83 *= (1.0 - _webgl_538e486927c2e97)); 
	float3 _webgl_5d831d5e5122da7d = lerp(_webgl_d79e71aa6da73ec7, _webgl_84bda37ee0e666a0.xyz, _webgl_538e486927c2e97); 
	float _webgl_778323d41fa2a9ee = max(max(_webgl_5d831d5e5122da7d.x, _webgl_5d831d5e5122da7d.y), _webgl_5d831d5e5122da7d.z); 
	float _webgl_276446f1a532bb44 = clamp((_webgl_778323d41fa2a9ee * 25.0), 0.0, 1.0); 
	float3 _webgl_ae5023af9c1a568 = _webgl_5d831d5e5122da7d.xyz; 
	float3 _webgl_239d3c0d22b9707e = (float3(1.0, 1.0, 1.0) * _webgl_276446f1a532bb44); 
	float3 _webgl_dad496b00e4a459a = f_webgl_28f4837284085b1e(); 
	float3 _webgl_f8057cd9a47842a = normalize((_webgl_2cb748cf0c448a46 - _webgl_aeb421a2dbbe85e0)); 
	float3 _webgl_29c1da7f92128805 = normalize(_webgl_75d497ae915a62ed); 
	float3 _webgl_8216a9694030d187 = normalize((_webgl_29c1da7f92128805 + _webgl_f8057cd9a47842a)); 
	float3 _webgl_13255d5b39d96fd2 = (-normalize(reflect(_webgl_f8057cd9a47842a, _webgl_dad496b00e4a459a))); 
	float _webgl_d345483011602bdc = clamp(dot(_webgl_dad496b00e4a459a, _webgl_29c1da7f92128805), 0.001, 1.0); 
	float _webgl_1414ae9d4598bc54 = (abs(dot(_webgl_dad496b00e4a459a, _webgl_f8057cd9a47842a)) + 0.001); 
	float _webgl_ad7d78d70e30cf43 = clamp(dot(_webgl_dad496b00e4a459a, _webgl_8216a9694030d187), 0.0, 1.0); 
	float _webgl_7ffc2970e3c6debb = clamp(dot(_webgl_29c1da7f92128805, _webgl_8216a9694030d187), 0.0, 1.0); 
	float _webgl_1f4786e5232138f3 = clamp(dot(_webgl_f8057cd9a47842a, _webgl_8216a9694030d187), 0.0, 1.0); 
	_webgl_2d5e024a41ffb4ef _webgl_acd936d0e5c85b6e = _webgl_2d5e024a41ffb4ef_ctor(_webgl_d345483011602bdc, _webgl_1414ae9d4598bc54, _webgl_ad7d78d70e30cf43, _webgl_7ffc2970e3c6debb, _webgl_1f4786e5232138f3, _webgl_ae318a32e60ff806, _webgl_538e486927c2e97, _webgl_ae5023af9c1a568, _webgl_239d3c0d22b9707e, _webgl_bf8effe5e2e481b, _webgl_75e6c6e5d9ced83, _webgl_5d831d5e5122da7d); 
	float3 _webgl_14a3d02bb2f28360 = f_webgl_220567718147325b__webgl_2d5e024a41ffb4ef(_webgl_acd936d0e5c85b6e); 
	float _webgl_adda5e5e6680c563 = f_webgl_f3b3fab1b6af2635__webgl_2d5e024a41ffb4ef(_webgl_acd936d0e5c85b6e); 
	float _webgl_807cd7c3f3d33ab6 = f_webgl_6b677a17ea3d987e__webgl_2d5e024a41ffb4ef(_webgl_acd936d0e5c85b6e); 
	float3 _webgl_b059dd4471d1c07 = ((1.0 - _webgl_14a3d02bb2f28360) * f_webgl_94f58b122e6fc376__webgl_2d5e024a41ffb4ef(_webgl_acd936d0e5c85b6e)); 
	float3 _webgl_6e49c1f99652b960 = (((_webgl_14a3d02bb2f28360 * _webgl_adda5e5e6680c563) * _webgl_807cd7c3f3d33ab6) / ((4.0 * _webgl_d345483011602bdc) * _webgl_1414ae9d4598bc54)); 
	float3 _webgl_19dff938713edbff = ((_webgl_d345483011602bdc * _webgl_53c8c08e89fba347) * (_webgl_b059dd4471d1c07 + _webgl_6e49c1f99652b960)); 
	(_webgl_19dff938713edbff += f_webgl_934471fe59ed5117__webgl_2d5e024a41ffb4ef(_webgl_acd936d0e5c85b6e, _webgl_dad496b00e4a459a, _webgl_13255d5b39d96fd2)); 
	float _webgl_af3eba424014769 = gl_texture2D(_webgl_fef39814f315ce8f, _webgl_8b169777ade76cf1).x; 
	(_webgl_19dff938713edbff = lerp(_webgl_19dff938713edbff, (_webgl_19dff938713edbff * _webgl_af3eba424014769), _webgl_13cc3b85174642f4)); 
	float3 _webgl_ad7a44ca414cb9d7 = (f_webgl_22bdc67c25b345fb_float4(gl_texture2D(_webgl_e3a9b9f14a5d1ea1, _webgl_8b169777ade76cf1)).xyz * _webgl_872d06f1b932325a); 
	(_webgl_19dff938713edbff += _webgl_ad7a44ca414cb9d7); 
	(_webgl_19dff938713edbff = lerp(_webgl_19dff938713edbff, _webgl_14a3d02bb2f28360, _webgl_f1c15989d446e4dc.x)); 
	(_webgl_19dff938713edbff = lerp(_webgl_19dff938713edbff, vec3_ctor(_webgl_adda5e5e6680c563), _webgl_f1c15989d446e4dc.y)); 
	(_webgl_19dff938713edbff = lerp(_webgl_19dff938713edbff, vec3_ctor(_webgl_807cd7c3f3d33ab6), _webgl_f1c15989d446e4dc.z)); 
	(_webgl_19dff938713edbff = lerp(_webgl_19dff938713edbff, _webgl_6e49c1f99652b960, _webgl_f1c15989d446e4dc.w)); 
	(_webgl_19dff938713edbff = lerp(_webgl_19dff938713edbff, _webgl_b059dd4471d1c07, _webgl_ae2fe52d78d24c3e.x)); 
	(_webgl_19dff938713edbff = lerp(_webgl_19dff938713edbff, _webgl_84bda37ee0e666a0.xyz, _webgl_ae2fe52d78d24c3e.y)); 
	(_webgl_19dff938713edbff = lerp(_webgl_19dff938713edbff, vec3_ctor(_webgl_538e486927c2e97), _webgl_ae2fe52d78d24c3e.z)); 
	(_webgl_19dff938713edbff = lerp(_webgl_19dff938713edbff, vec3_ctor(_webgl_ae318a32e60ff806), _webgl_ae2fe52d78d24c3e.w)); 
	(gl_Color[0] = vec4_ctor(pow(_webgl_19dff938713edbff, float3(0.45454544, 0.45454544, 0.45454544)), _webgl_84bda37ee0e666a0.w)); 
	return gl_Color[0];
} 

// INITIAL HLSL END // FRAGMENT SHADER END