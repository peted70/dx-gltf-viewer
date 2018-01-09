#pragma once

#include <iostream>
#include <functional>

// The following ifdef block is the standard way of creating macros which make exporting 
// from a DLL simpler. All files within this DLL are compiled with the GLTFPARSER_EXPORTS
// symbol defined on the command line. This symbol should not be defined on any project
// that uses this DLL. This way any other project whose source files include this file see 
// GLTFPARSER_API functions as being imported from a DLL, whereas this DLL sees symbols
// defined with this macro as being exported.
#ifdef GLTFPARSER_EXPORTS
#define GLTFPARSER_API __declspec(dllexport)
#else
#define GLTFPARSER_API __declspec(dllimport)
#endif

typedef long HRESULT;

class GLTFPARSER_API TextureData
{
public:
	TextureData() {}

	const void *pSysMem;
	unsigned int dataSize;
	unsigned int imgWidth;
	unsigned int imgHeight;
};

struct GLTFPARSER_API SubresourceData
{
	const void *pSysMem;
	unsigned int SysMemPitch;
	unsigned int SysMemSlicePitch;
};

struct GLTFPARSER_API BufferDesc
{
	unsigned int ByteWidth;
	unsigned int BindFlags;
	unsigned int CPUAccessFlags;
	unsigned int MiscFlags;
	unsigned int StructureByteStride;
	const char *BufferContentType;
	unsigned int Count;
};

class GLTFPARSER_API BufferData
{
public:
	BufferData();
	SubresourceData subresource;
	BufferDesc desc;
};

HRESULT GLTFPARSER_API ParseFile(std::istream& inStr, std::function<void(const BufferData&)> bufferCallback);
