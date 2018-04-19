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
	public:
		class Callbacks
		{
		public:
			function<void(const BufferData&)> Buffers;
			function<void(const TextureData&)> Textures;
			function<void(const MaterialData&)> Materials;
			function<void(const TransformData&)> Transform;
			function<void(const SceneNodeData&)> SceneNode;
		};

		const Callbacks& EventHandlers() const { return _callbacks; }
		Callbacks& EventHandlers() { return _callbacks; }

		GLTFChunk * BinaryChunk() { return _binaryChunk; }
		Document& document() { return _document; }

		void Read(istream& file);
		void CheckExtensions(const Document& document);
		void ParseDocument(const Document& document, const Callbacks& callbacks);
		void LoadScene(const Document& document, const Value& scene, const Callbacks& callbacks);
		void LoadMeshNode(const Document& document, const Value& meshNode, const Callbacks& callbacks);
		void LoadSceneNode(const Document& document, const Value& scene, const Callbacks& callbacks, int nodeIndex, int parentIndex);
		void LoadTransform(const Document& document, const Value& mNode, const Callbacks& callbacks);

	private:
		unique_ptr<GLTFHeader> _header;
		unique_ptr<ChunkList> _chunks;
		Document _document;
		GLTFChunk *_headerChunk;
		GLTFChunk *_binaryChunk;
		GLTFFileData::Callbacks _callbacks;

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
	};
};

