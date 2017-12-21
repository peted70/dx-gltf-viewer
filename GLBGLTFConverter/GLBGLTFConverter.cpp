// GLBGLTFConverter.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <intrin.h>
#include <memory>
#include <rapidjson\rapidjson.h>
#include <rapidjson\document.h>
#include <Windows.h>
#include <vector>
#include <functional>

using namespace std;
using namespace rapidjson;

/**	Header
The 20 - byte header consists of the following five 4 - byte entries :
magic is the ASCII string 'glTF', and can be used to identify the arraybuffer as Binary glTF.
version is an uint32 that indicates the version of the Binary glTF container format.Currently available versions are shown in Table 1.
length is the total length of the Binary glTF, including header, content, and body, in bytes.
contentLength is the length, in bytes, of the glTF content.It must be greater than zero.
contentFormat specifies the format of the glTF content.A list of all valid values currently available is in Table 2.
Table 1: Valid values for version
Decimal
Hex
Description
1
0x00000001
Version 1
Table 2: Valid values for contentFormat
Decimal
Hex
Description
0
0x00000000
JSON */
class GLTFHeader
{
private:
	unsigned char _magic[4];
	unsigned int _version;
	unsigned int _length;

public:
	GLTFHeader() :
		_version(0),
		_length(0)
	{
	}

	unsigned int length() { return this->_length; }

	void Read(ifstream& file)
	{
		file.read((char *)(&_magic[0]), 4);
		file.read((char *)&_version, sizeof(unsigned int));
		file.read((char *)&_length, sizeof(unsigned int));
	}
};

struct Component
{
	const char *Type;
	int NumBytes;
};

Component NumComponentsByType[] =
{
	{ "SCALAR", 1 },
	{ "VEC2", 2 },
	{ "VEC3", 3 },
	{ "VEC4", 4 },
	{ "MAT2", 4 },
	{ "MAT3", 9 },
	{ "MAT4", 16 }
};

class GLTFChunk
{
private:
	unsigned int _chunkLength;
	unsigned int _chunkType;
	unique_ptr<unsigned char[]> _chunkData;

	enum ChunkType
	{	
		JSON = 0x4E4F534A,
		BIN = 0x004E4942
	};
	
public:
	bool IsJson() { return _chunkType == ChunkType::JSON; }
	bool IsBinary() { return _chunkType == ChunkType::BIN; }

	unsigned int ChunkLength() { return _chunkLength; }
	unsigned char *ChunkData() { return _chunkData.get(); }

	//GLTFChunk(GLTFChunk&& other)
	//{
	//}

	GLTFChunk *Read(ifstream& file)
	{
		// Ensure we are on a 4-byte boundary..
		streamoff currPos = file.tellg();
		streamoff padding = currPos % 4;
		if (padding > 0)
		{
			file.seekg(padding, file.cur);
		}
		else
		{
			//file.seekg((streamoff)4, file.cur);
		}
		
		file.read((char *)(&_chunkLength), sizeof(unsigned int));
		file.read((char *)&_chunkType, sizeof(unsigned int));

		if (_chunkType != ChunkType::BIN && _chunkType != ChunkType::JSON)
		{
			// Unknown chunk type just skip over it..
			file.seekg(_chunkLength);
		}
		else
		{
			_chunkData = make_unique<unsigned char[]>(_chunkLength);
			file.read((char *)_chunkData.get(), _chunkLength);

			int toAdd = _chunkLength % 4;
			if (toAdd > 0)
			{
				file.seekg((streamoff)toAdd, file.cur);
			}

			return this;
		}
		return nullptr;
	}
};

typedef vector<shared_ptr<GLTFChunk>> ChunkList;

struct SubresourceData
{
	const void *pSysMem;
	unsigned int SysMemPitch;
	unsigned int SysMemSlicePitch;
};

struct BufferDesc
{
	unsigned int ByteWidth;
	unsigned int BindFlags;
	unsigned int CPUAccessFlags;
	unsigned int MiscFlags;
	unsigned int StructureByteStride;
};

class BufferData
{
public:
	BufferData()
	{
		ZeroMemory(&subresource, sizeof(SubresourceData));
		ZeroMemory(&desc, sizeof(BufferDesc));
	}
	SubresourceData subresource;
	BufferDesc desc;
};

class GLTFFileData
{
private:
	unique_ptr<GLTFHeader> _header;
	unique_ptr<ChunkList> _chunks;
	Document _document;
	GLTFChunk *_headerChunk;
	GLTFChunk *_binaryChunk;

	enum ComponentType
	{
		BYTE = 5120, // 1
		UNSIGNED_BYTE = 5121, // 1
		SHORT = 5122, // 2
		UNSIGNED_SHORT = 5123, // 2
		UNSIGNED_INT = 5125, // 4
		FLOAT = 5126 // 4
	};

	void PopulateDocument()
	{
		_document.Parse((const char *)_headerChunk->ChunkData(), 
			_headerChunk->ChunkLength());
	}

public:

	GLTFChunk * BinaryChunk() { return _binaryChunk; }
	Document& document() { return _document; }
	void Read(ifstream& file)
	{
		_header = make_unique<GLTFHeader>();
		_header->Read(file);

		_chunks = make_unique<ChunkList>();

		while (!file.eof())
		{
			streamoff pos = file.tellg();
			int length = _header->length();

			if (pos >= (streamoff)length)
				break;
			
			auto chunk = make_shared<GLTFChunk>();
			auto chunkData = chunk.get()->Read(file);
			if (chunkData == nullptr)
				continue;
			if (chunkData->IsJson())
				_headerChunk = chunkData;
			else if (chunkData->IsBinary())
				_binaryChunk = chunkData;

			_chunks.get()->push_back(chunk);
		}

		PopulateDocument();
	}

	void NotifyBuffers(const Document& document, function<void(const BufferData&)> OnBuffer)
	{
		const Value& a = document["scenes"];
		assert(a.IsArray());
		for (SizeType i = 0; i < a.Size(); i++)
		{
			const Value& scene = a[i];
			const Value& nodes = scene["nodes"];
			assert(nodes.IsArray());
			for (SizeType j = 0; j < nodes.Size(); j++)
			{
				int nodeIndex = nodes[j].GetInt();
				const Value& nodesArray = document["nodes"];
				assert(nodesArray.IsArray());
				const Value& sceneNode = nodesArray[nodeIndex];

				int meshIndex = sceneNode["mesh"].GetInt();
				string meshName = sceneNode["name"].GetString();

				// Lookup the mesh in the 'meshes' collection...
				const Value& meshesArray = document["meshes"];
				assert(meshesArray.IsArray());
				const Value& meshNode = meshesArray[meshIndex];

				const Value& primitives = meshNode["primitives"];
				meshName = meshNode["name"].GetString();

				assert(primitives.IsArray());

				// Loop around the primitives that make up the mesh and create 
				// buffers for them...
				for (SizeType p = 0; p < primitives.Size(); p++)
				{
					const Value& primitiveObject = primitives[p];

					const Value& attributesObject = primitiveObject["attributes"];
					int indicesIdx = primitiveObject["indices"].GetInt();
					int materialIdx = primitiveObject["material"].GetInt();

					if (primitiveObject.HasMember("mode"))
					{
						int mode = primitiveObject["mode"].GetInt();
					}

					for (Value::ConstMemberIterator itr = attributesObject.MemberBegin();
						itr != attributesObject.MemberEnd(); ++itr)
					{
						int accessorIdx = itr->value.GetInt();

						// Lookup the accessor..
						const Value& accessors = document["accessors"];
						assert(accessors.IsArray());
						const Value& Accessor = accessors[accessorIdx];

						int bufferViewIdx = Accessor["bufferView"].GetInt();

						// Get the raw data from the binary chunk...
						const Value& bufferViews = document["bufferViews"];
						assert(bufferViews.IsArray());
						const Value& bufferView = bufferViews[bufferViewIdx];

						int bufferIdx = bufferView["buffer"].GetInt();
						int byteOffset = 0;
						if (bufferView.HasMember("byteOffset"))
							byteOffset = bufferView["byteOffset"].GetInt();
						int byteLength = bufferView["byteLength"].GetInt();

						// Finally, we have enough info to retrieve the buffer data...
						const Value& buffer = document["buffers"];
						assert(buffer.IsArray());
						const Value& buff = buffer[bufferIdx];
						byteLength = buff["byteLength"].GetInt();

						auto binaryChunkBuffer = BinaryChunk()->ChunkData();

						BufferData data;
						data.subresource.pSysMem = binaryChunkBuffer + byteOffset;
						data.subresource.SysMemPitch = 0;
						data.subresource.SysMemSlicePitch = 0;
l						data.desc.ByteWidth = byteLength;

						// Notify that we have a buffer and pass parameters required to create it
						stringstream debugText;
						debugText << "Buffer:" << itr->name.GetString() << endl;
						OutputDebugStringA(debugText.str().c_str());
						OnBuffer(data);
					}
				}

				OutputDebugStringA(meshName.c_str());
			}
		}
	}
};

int main(int argc, char **argv)
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	std::string fileStr;
	if (argc > 1)
	{
		fileStr = argv[1];
	}
	else
	{
		std::cout << "Error: you must supply an input file";
		return -1;
	}

	std::ifstream infile(fileStr, std::ios::binary);

	if (infile.fail())
	{
		std::cout << "Error: can't read the file";
		return false;
	}

	GLTFFileData gltfFile;
	gltfFile.Read(infile);

	Document& document = gltfFile.document();

	infile.close();

    return 0;
}

