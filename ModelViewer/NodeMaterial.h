#pragma once

#include <map>

using namespace Microsoft::WRL;
using namespace std;

class NodeMaterial
{
public:
	NodeMaterial();
	~NodeMaterial();

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
};

