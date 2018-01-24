//
// This fragment shader defines a reference implementation for Physically Based Shading of
// a microfacet surface material defined by a glTF model.
//
// References:
// [1] Real Shading in Unreal Engine 4
//     http://blog.selfshadow.com/publications/s2013-shading-course/karis/s2013_pbs_epic_notes_v2.pdf
// [2] Physically Based Shading at Disney
//     http://blog.selfshadow.com/publications/s2012-shading-course/burley/s2012_pbs_disney_brdf_notes_v3.pdf
// [3] README.md - Environment Maps
//     https://github.com/KhronosGroup/glTF-WebGL-PBR/#environment-maps
// [4] "An Inexpensive BRDF Model for Physically based Rendering" by Christophe Schlick
//     https://www.cs.virginia.edu/~jdl/bib/appearance/analytic%20models/schlick94b.pdf

#define NORMALS
#define UV
#define HAS_METALROUGHNESSMAP
#define HAS_OCCLUSIONMAP
#define HAS_EMISSIVEMAP
#define HAS_BASECOLORMAP
#define HAS_NORMALMAP

// First three are 3 channel textures
Texture2D baseColourTexture : register(t0);
SamplerState baseColourSampler : register(s0);

Texture2D normalTexture : register(t1);
SamplerState normalSampler : register(s1);

Texture2D emissionTexture : register(t2);
SamplerState emissionSampler : register(s2);

Texture2D occlusionTexture : register(t3);
SamplerState occlusionSampler : register(s3);

// The following three textures are packed into a single channel
// of one input image..
Texture2D metallicRoughnessTexture : register(t4);
SamplerState metallicRoughnessSampler : register(s4);

//#extension GL_EXT_shader_texture_lod: enable
//#extension GL_OES_standard_derivatives : enable

uniform min16float3 u_LightDirection;
uniform min16float3 u_LightColor;

// Per-pixel color data passed through the pixel shader.
struct PixelShaderInput
{
    min16float4 position : SV_POSITION;
    min16float3 poswithoutw : POSITION;

#ifdef NORMALS
    min16float3 normal : NORMAL;
#endif
#ifdef DIFFUSE
    min16float3 lightdir : TEXCOORD1;
#endif
#ifdef UV
    min16float2 texcoord : TEXCOORD0;
#endif
};

#ifdef USE_IBL
uniform samplerCube u_DiffuseEnvSampler;
uniform samplerCube u_SpecularEnvSampler;
uniform sampler2D u_brdfLUT;
#endif

#ifdef HAS_BASECOLORMAP
uniform sampler2D u_BaseColorSampler;
#endif

#ifdef HAS_NORMALMAP
uniform sampler2D u_NormalSampler;
uniform min16float u_NormalScale;
#endif

#ifdef HAS_EMISSIVEMAP
uniform sampler2D u_EmissiveSampler;
uniform min16float3 u_EmissiveFactor;
#endif

#ifdef HAS_METALROUGHNESSMAP
uniform sampler2D u_MetallicRoughnessSampler;
#endif

#ifdef HAS_OCCLUSIONMAP
uniform sampler2D u_OcclusionSampler;
uniform min16float u_OcclusionStrength;
#endif

uniform min16float2 u_MetallicRoughnessValues;
uniform min16float4 u_BaseColorFactor;
uniform min16float3 u_Camera;

// debugging flags used for shader output of intermediate PBR variables
uniform min16float4 u_ScaleDiffBaseMR;
uniform min16float4 u_ScaleFGDSpec;
uniform min16float4 u_ScaleIBLAmbient;

#ifdef HAS_NORMALS
#ifdef HAS_TANGENTS
varying mat3 v_TBN;
#else
varying min16float3 v_Normal;
#endif
#endif

// Encapsulate the various inputs used by the various functions in the shading equation
// We store values in this struct to simplify the integration of alternative implementations
// of the shading terms, outlined in the Readme.MD Appendix.
struct PBRInfo
{
    min16float NdotL; // cos angle between normal and light direction
    min16float NdotV; // cos angle between normal and view direction
    min16float NdotH; // cos angle between normal and half vector
    min16float LdotH; // cos angle between light direction and half vector
    min16float VdotH; // cos angle between view direction and half vector
    min16float perceptualRoughness; // roughness value, as authored by the model creator (input to shader)
    min16float metalness; // metallic value at the surface
    min16float3 reflectance0; // full reflectance color (normal incidence angle)
    min16float3 reflectance90; // reflectance color at grazing angle
    min16float alphaRoughness; // roughness mapped to a more linear change in the roughness (proposed by [2])
    min16float3 diffuseColor; // color contribution from diffuse lighting
    min16float3 specularColor; // color contribution from specular lighting
};

const min16float M_PI = 3.141592653589793;
const min16float c_MinRoughness = 0.04;

min16float4 SRGBtoLINEAR(min16float4 srgbIn)
{
#ifdef MANUAL_SRGB
#ifdef SRGB_FAST_APPROXIMATION
    min16float3 linOut = pow(srgbIn.xyz,min16float3(2.2));
#else //SRGB_FAST_APPROXIMATION
    min16float3 bLess = step(min16float3(0.04045),srgbIn.xyz);
    min16float3 linOut = lerp( srgbIn.xyz/min16float3(12.92), pow((srgbIn.xyz+min16float3(0.055))/min16float3(1.055),min16float3(2.4)), bLess );
#endif //SRGB_FAST_APPROXIMATION
    return min16float4(linOut,srgbIn.w);;
#else //MANUAL_SRGB
    return srgbIn;
#endif //MANUAL_SRGB
}

// Find the normal for this fragment, pulling either from a predefined normal map
// or from the interpolated mesh normal and tangent attributes.
min16float3 getNormal(float3 position, float2 uv)
{
    // Retrieve the tangent space matrix
#ifndef HAS_TANGENTS
    min16float3 pos_dx = ddx(position);
    min16float3 pos_dy = ddy(position);
    min16float3 tex_dx = ddx(min16float3(uv, 0.0));
    min16float3 tex_dy = ddy(min16float3(uv, 0.0));
    min16float3 t = (tex_dy.y * pos_dx - tex_dx.y * pos_dy) / (tex_dx.x * tex_dy.y - tex_dy.x * tex_dx.y);

#ifdef HAS_NORMALS
    min16float3 ng = normalize(v_Normal);
#else
    min16float3 ng = cross(pos_dx, pos_dy);
#endif

    t = normalize(t - ng * dot(ng, t));
    min16float3 b = normalize(cross(ng, t));
    float3x3 tbn = float3x3(t, b, ng);

#else // HAS_TANGENTS
    mat3 tbn = v_TBN;
#endif

#ifdef HAS_NORMALMAP
    min16float3 n = normalTexture.Sample(normalSampler, uv).rgb;

    // Need to check the multiplication is equivalent..
    n = normalize(mul(tbn, ((2.0 * n - 1.0) * min16float3(u_NormalScale, u_NormalScale, 1.0))));

    //n = normalize(tbn * ((2.0 * n - 1.0) * min16float3(u_NormalScale, u_NormalScale, 1.0)));
#else
    min16float3 n = tbn[2].xyz;
#endif

    return n;
}

#ifdef USE_IBL
// Calculation of the lighting contribution from an optional Image Based Light source.
// Precomputed Environment Maps are required uniform inputs and are computed as outlined in [1].
// See our README.md on Environment Maps [3] for additional discussion.
min16float3 getIBLContribution(PBRInfo pbrInputs, min16float3 n, min16float3 reflection)
{
    min16float mipCount = 9.0; // resolution of 512x512
    min16float lod = (pbrInputs.perceptualRoughness * mipCount);
    // retrieve a scale and bias to F0. See [1], Figure 3
    min16float3 brdf = SRGBtoLINEAR(
    texture2D( u_brdfLUT, min16float2
    (pbrInputs.NdotV, 1.0 - pbrInputs.perceptualRoughness))).
    rgb;
    min16float3
    diffuseLight = SRGBtoLINEAR(textureCube(u_DiffuseEnvSampler, n)).rgb;

#ifdef USE_TEX_LOD
    min16float3 specularLight = SRGBtoLINEAR(textureCubeLodEXT(u_SpecularEnvSampler, reflection, lod)).rgb;
#else
    min16float3 specularLight = SRGBtoLINEAR(textureCube(u_SpecularEnvSampler, reflection)).rgb;
#endif

    min16float3 diffuse = diffuseLight * pbrInputs.diffuseColor;
    min16float3 specular = specularLight * (pbrInputs.specularColor * brdf.x + brdf.y);

    // For presentation, this allows us to disable IBL terms
    diffuse *= u_ScaleIBLAmbient.x;
    specular *= u_ScaleIBLAmbient.y;

    return diffuse + specular;
}
#endif

// Basic Lambertian diffuse
// Implementation from Lambert's Photometria https://archive.org/details/lambertsphotome00lambgoog
// See also [1], Equation 1
min16float3 diffuse(PBRInfo pbrInputs)
{
    return pbrInputs.diffuseColor / M_PI;
}

// The following equation models the Fresnel reflectance term of the spec equation (aka F())
// Implementation of fresnel from [4], Equation 15
min16float3 specularReflection(PBRInfo pbrInputs)
{
    return pbrInputs.reflectance0 + (pbrInputs.reflectance90 - pbrInputs.reflectance0) * pow(clamp(1.0 - pbrInputs.VdotH, 0.0, 1.0), 5.0);
}

// This calculates the specular geometric attenuation (aka G()),
// where rougher material will reflect less light back to the viewer.
// This implementation is based on [1] Equation 4, and we adopt their modifications to
// alphaRoughness as input as originally proposed in [2].
min16float geometricOcclusion(PBRInfo pbrInputs)
{
    min16float NdotL = pbrInputs.NdotL;
    min16float NdotV = pbrInputs.NdotV;
    min16float r = pbrInputs.alphaRoughness;

    min16float attenuationL = 2.0 * NdotL / (NdotL + sqrt(r * r + (1.0 - r * r) * (NdotL * NdotL)));
    min16float attenuationV = 2.0 * NdotV / (NdotV + sqrt(r * r + (1.0 - r * r) * (NdotV * NdotV)));
    return attenuationL * attenuationV;
}

// The following equation(s) model the distribution of microfacet normals across the area being drawn (aka D())
// Implementation from "Average Irregularity Representation of a Roughened Surface for Ray Reflection" by T. S. Trowbridge, and K. P. Reitz
// Follows the distribution function recommended in the SIGGRAPH 2013 course notes from EPIC Games [1], Equation 3.
min16float microfacetDistribution(PBRInfo pbrInputs)
{
    min16float roughnessSq = pbrInputs.alphaRoughness * pbrInputs.alphaRoughness;
    min16float f = (pbrInputs.NdotH * roughnessSq - pbrInputs.NdotH) * pbrInputs.NdotH + 1.0;
    return roughnessSq / (M_PI * f * f);
}

min16float4 main(PixelShaderInput input) : SV_TARGET
{
    // Metallic and Roughness material properties are packed together
    // In glTF, these factors can be specified by fixed scalar values
    // or from a metallic-roughness map
    min16float perceptualRoughness = u_MetallicRoughnessValues.y;
    min16float metallic = u_MetallicRoughnessValues.x;

#ifdef HAS_METALROUGHNESSMAP
    // Roughness is stored in the 'g' channel, metallic is stored in the 'b' channel.
    // This layout intentionally reserves the 'r' channel for (optional) occlusion map data
    min16float4 mrSample = metallicRoughnessTexture.Sample(metallicRoughnessSampler, input.texcoord);
    perceptualRoughness = mrSample.g * perceptualRoughness;
    metallic = mrSample.b * metallic;
#endif

    perceptualRoughness = clamp(perceptualRoughness, c_MinRoughness, 1.0);
    metallic = clamp(metallic, 0.0, 1.0);

    // Roughness is authored as perceptual roughness; as is convention,
    // convert to material roughness by squaring the perceptual roughness [2].
    min16float alphaRoughness = perceptualRoughness * perceptualRoughness;

    // The albedo may be defined from a base texture or a flat color

#ifdef HAS_BASECOLORMAP
    min16float4 baseColor = SRGBtoLINEAR(baseColourTexture.Sample(baseColourSampler, input.texcoord)) * u_BaseColorFactor;
#else
    min16float4 baseColor = u_BaseColorFactor;
#endif

    min16float3 f0 = min16float3(0.04, 0.04, 0.04);
    min16float3 diffuseColor = baseColor.rgb * (min16float3(1.0, 1.0, 1.0) - f0);

    diffuseColor *= 1.0 - metallic;
    min16float3 specularColor = lerp(f0, baseColor.rgb, metallic);

    // Compute reflectance.
    min16float reflectance = max(max(specularColor.r, specularColor.g), specularColor.b);

    // For typical incident reflectance range (between 4% to 100%) set the grazing reflectance to 100% for typical fresnel effect.
    // For very low reflectance range on highly diffuse objects (below 4%), incrementally reduce grazing reflecance to 0%.
    min16float reflectance90 = clamp(reflectance * 25.0, 0.0, 1.0);
    min16float3 specularEnvironmentR0 = specularColor.rgb;
    min16float3 specularEnvironmentR90 = min16float3(1.0, 1.0, 1.0) * reflectance90;

    min16float3 n = getNormal(input.poswithoutw, input.texcoord); // normal at surface point
    min16float3 v = normalize(u_Camera - input.poswithoutw); // Vector from surface point to camera
    min16float3 l = normalize(u_LightDirection); // Vector from surface point to light
    min16float3 h = normalize(l + v); // Half vector between both l and v
    min16float3 reflection = -normalize(reflect(v, n));

    min16float NdotL = clamp(dot(n, l), 0.001, 1.0);
    min16float NdotV = abs(dot(n, v)) + 0.001;
    min16float NdotH = clamp(dot(n, h), 0.0, 1.0);
    min16float LdotH = clamp(dot(l, h), 0.0, 1.0);
    min16float VdotH = clamp(dot(v, h), 0.0, 1.0);

    PBRInfo pbrInputs;
    pbrInputs.NdotL = NdotL;
    pbrInputs.NdotV = NdotV;
    pbrInputs.NdotH = NdotH;
    pbrInputs.LdotH = LdotH;
    pbrInputs.VdotH = VdotH;
    pbrInputs.perceptualRoughness = perceptualRoughness;
    pbrInputs.metalness = metallic;
    pbrInputs.reflectance0 = specularEnvironmentR0;
    pbrInputs.reflectance90 = specularEnvironmentR90;
    pbrInputs.alphaRoughness = alphaRoughness;
    pbrInputs.diffuseColor = diffuseColor;
    pbrInputs.specularColor = specularColor;

    // Calculate the shading terms for the microfacet specular shading model
    min16float3 F = specularReflection(pbrInputs);
    min16float G = geometricOcclusion(pbrInputs);
    min16float D = microfacetDistribution(pbrInputs);

    // Calculation of analytical lighting contribution
    min16float3 diffuseContrib = (1.0 - F) * diffuse(pbrInputs);
    min16float3 specContrib = F * G * D / (4.0 * NdotL * NdotV);
    min16float3 color = NdotL * u_LightColor * (diffuseContrib + specContrib);

    // Calculate lighting contribution from image based lighting source (IBL)
#ifdef USE_IBL
    color += getIBLContribution(pbrInputs, n, reflection);
#endif

    // Apply optional PBR terms for additional (optional) shading
#ifdef HAS_OCCLUSIONMAP
    min16float ao = occlusionTexture.Sample(occlusionSampler, input.texcoord).r;
    color = lerp(color, color * ao, u_OcclusionStrength);
#endif

#ifdef HAS_EMISSIVEMAP
    min16float3 emissive = SRGBtoLINEAR(emissionTexture.Sample(emissionSampler, input.texcoord)).rgb * u_EmissiveFactor;
    color += emissive;
#endif

    // This section uses lerp to override final color for reference app visualization
    // of various parameters in the lighting equation.
    color = lerp(color, F, u_ScaleFGDSpec.x);
    color = lerp(color, min16float3(G, G, G), u_ScaleFGDSpec.y);
    color = lerp(color, min16float3(D, D, D), u_ScaleFGDSpec.z);
    color = lerp(color, specContrib, u_ScaleFGDSpec.w);

    color = lerp(color, diffuseContrib, u_ScaleDiffBaseMR.x);
    color = lerp(color, baseColor.rgb, u_ScaleDiffBaseMR.y);
    color = lerp(color, min16float3(metallic, metallic, metallic), u_ScaleDiffBaseMR.z);
    color = lerp(color, min16float3(perceptualRoughness, perceptualRoughness, perceptualRoughness), u_ScaleDiffBaseMR.w);

    return min16float4(pow(color, min16float3(1.0 / 2.2, 1.0 / 2.2, 1.0 / 2.2)), baseColor.a);
}