#pragma once

#include "stdafx.h"

namespace GLTFParser
{
	using namespace std;
	using namespace rapidjson;

	class GLTFHeader
	{
	private:
		unsigned char _magic[4];
		unsigned int _version;
		unsigned int _length;

	public:
		GLTFHeader();
		unsigned int length() { return this->_length; }
		void Read(istream& file);
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

		GLTFChunk *Read(istream& file);
	};

	typedef vector<shared_ptr<GLTFChunk>> ChunkList;

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

		void PopulateDocument();

	public:
		function<void(const BufferData&)> Buffers;
		function<void(const TextureData&)> Textures;

		GLTFChunk * BinaryChunk() { return _binaryChunk; }
		Document& document() { return _document; }

		void Read(istream& file);
		void NotifyBuffers(const Document& document, 
						   function<void(const BufferData&)> OnBuffer,
						   function<void(const TextureData&)> OnTexture);
	};
};

