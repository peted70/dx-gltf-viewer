#pragma once

#include <map>

using namespace Microsoft::WRL;
using namespace std;
using namespace WinRTGLTFParser;

class NodeMaterial
{
public:
	NodeMaterial();
	~NodeMaterial();

	void Initialise(GLTF_MaterialData^ data);

private:
	class TextureWrapper
	{
	public:
		TextureWrapper() {}

	private:
		ComPtr<ID3D11SamplerState> _textureSampler;
		ComPtr<ID3D11ShaderResourceView> _texture;
	};

	map<wstring, TextureWrapper> _textures;
	wstring _name;

	float _emmissiveFactor[3] = {0.0f, 0.0f, 0.0f};

	unsigned int _Pbrmetallicroughness_Basecolortexture = 0;
	unsigned int _Pbrmetallicroughness_Metallicroughnesstexture = 0;
	unsigned int _Normaltexture = 0;
	unsigned int _Occlusiontexture = 0;
	unsigned int _Emissivetexture = 0;
};

