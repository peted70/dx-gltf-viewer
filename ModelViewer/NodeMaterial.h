#pragma once

#include <map>

using namespace Microsoft::WRL;
using namespace std;
using namespace WinRTGLTFParser;

class TextureWrapper
{
public:
	TextureWrapper(unsigned int type,
		ComPtr<ID3D11Texture2D> tex,
		ComPtr<ID3D11ShaderResourceView> textureResourceView,
		ComPtr<ID3D11SamplerState> texSampler) :
		_type(type),
		_tex(tex),
		_textureResourceView(textureResourceView),
		_textureSampler(texSampler)
	{}

	ComPtr<ID3D11SamplerState> GetSampler() { return _textureSampler; }
	ComPtr<ID3D11ShaderResourceView> GetShaderResourceView() { return _textureResourceView; }
	ComPtr<ID3D11Texture2D> GetTexture() { return _tex; }
	unsigned int GetType() { return _type; }

private:
	ComPtr<ID3D11SamplerState> _textureSampler;
	ComPtr<ID3D11ShaderResourceView> _textureResourceView;
	ComPtr<ID3D11Texture2D> _tex;
	unsigned int _type;
};

class NodeMaterial
{
public:
	NodeMaterial();
	~NodeMaterial();

	void Initialise(GLTF_MaterialData^ data);
	void AddTexture(unsigned int idx, 
					unsigned int type,
					ComPtr<ID3D11Texture2D> tex, 
					ComPtr<ID3D11ShaderResourceView> textureResourceView, 
					ComPtr<ID3D11SamplerState> texSampler);
	shared_ptr<TextureWrapper> GetTexture(unsigned int idx) { return _textures[idx]; }
	bool HasTexture(unsigned int idx) { return _textures.find(idx) != _textures.end(); }
	unsigned int GetNumTextures() { return _textures.size(); }

private:
	map<unsigned int, shared_ptr<TextureWrapper>> _textures;
	wstring _name;

	float _emmissiveFactor[3] = {0.0f, 0.0f, 0.0f};

	unsigned int _Pbrmetallicroughness_Basecolortexture = 0;
	unsigned int _Pbrmetallicroughness_Metallicroughnesstexture = 0;
	unsigned int _Normaltexture = 0;
	unsigned int _Occlusiontexture = 0;
	unsigned int _Emissivetexture = 0;
};

