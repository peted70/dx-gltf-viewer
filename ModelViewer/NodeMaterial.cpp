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
	_emmissiveFactor[0] = data->emmissiveFactor[0];
	_emmissiveFactor[1] = data->emmissiveFactor[1];
	_emmissiveFactor[2] = data->emmissiveFactor[2];
}

void NodeMaterial::AddTexture(unsigned int idx, 
							  unsigned int type,	
							  ComPtr<ID3D11Texture2D> tex, 
							  ComPtr<ID3D11ShaderResourceView> textureResourceView, 
							  ComPtr<ID3D11SamplerState> texSampler)
{
	auto tw = make_shared<TextureWrapper>(TextureWrapper(type, tex, textureResourceView, texSampler));
	_textures[idx] = tw;
}
