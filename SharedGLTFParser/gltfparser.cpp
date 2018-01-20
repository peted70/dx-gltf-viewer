// gltfparser.cpp : Defines the exported functions for the DLL application.
//

#include "stdafx.h"
#include "GLBGLTFConverter.h"

using namespace GLTFParser;

BufferData::BufferData()
{
	ZeroMemory(&subresource, sizeof(SubresourceData));
	ZeroMemory(&desc, sizeof(BufferDesc));
}

HRESULT ParseFile(std::istream& inStr, std::function<void(const BufferData&)> bufferCallback,
				  std::function<void(const MaterialData&)> materialCallback,
				  std::function<void(const TextureData&)> textureCallback)
{
	try
	{
		GLTFFileData gltfFile;

		gltfFile.Buffers = [bufferCallback](const BufferData& data)
		{
			bufferCallback(data);
		};

		gltfFile.Textures = [textureCallback](const TextureData& data)
		{
			textureCallback(data);
		};

		gltfFile.Materials = [materialCallback](const MaterialData& data)
		{
			materialCallback(data);
		};

		gltfFile.Read(inStr);
	}
	catch (const std::exception& ex)
	{
		return E_FAIL;
	}
	return S_OK;
}


