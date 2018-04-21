#include "pch.h"
#include "NodeMaterial.h"

NodeMaterial::NodeMaterial()
{
}

NodeMaterial::~NodeMaterial()
{
}

void NodeMaterial::Initialise(GLTF_MaterialData^ data)
{
	_name = data->MaterialName->Data();
	_Emissivetexture = data->Emissivetexture;
	_Normaltexture = data->Normaltexture;
	_Occlusiontexture = data->Occlusiontexture;
	_Pbrmetallicroughness_Basecolortexture = data->Pbrmetallicroughness_Basecolortexture;
	_Pbrmetallicroughness_Metallicroughnesstexture = data->Pbrmetallicroughness_Metallicroughnesstexture;
	_emmissiveFactor.x = data->emmissiveFactor[0];
	_emmissiveFactor.y = data->emmissiveFactor[1];
	_emmissiveFactor.z = data->emmissiveFactor[2];
	_baseColorFactor.x = data->baseColourFactor[0];
	_baseColorFactor.y = data->baseColourFactor[1];
	_baseColorFactor.z = data->baseColourFactor[2];
	_baseColorFactor.w = data->baseColourFactor[3];
	_metallicFactor = data->metallicFactor;
	_roughnessFactor = data->roughnessFactor;
}

void NodeMaterial::AddTexture(unsigned int idx, 
							  unsigned int type,	
							  ComPtr<ID3D11Texture2D> tex, 
							  ComPtr<ID3D11ShaderResourceView> textureResourceView, 
							  ComPtr<ID3D11SamplerState> texSampler)
{
	shared_ptr<TextureWrapper> tw;

	// if we have the index already reference it otherwise create a new one..
	auto found = _textures.find(idx);

	//if (found != _textures.end())
	//{
	//	(*found).second->AddType(type);
	//	return;
	//}

	_textures[type] = make_shared<TextureWrapper>(TextureWrapper(idx, type, tex, textureResourceView, texSampler));

	//// if we have the index already reference it otherwise create a new one..
	//auto found = std::find_if(_textures.begin(), _textures.end(), 
	//	[idx](const std::pair<unsigned int, shared_ptr<TextureWrapper>> tx) { return tx.second->GetIndex() == idx; });
	//if (found != _textures.end())
	//{
	//	tw = found->second;
	//}
	//else
	//{
	//	tw = make_shared<TextureWrapper>(TextureWrapper(idx, tex, textureResourceView, texSampler));
	//}
	//_textures[type] = tw;
}
