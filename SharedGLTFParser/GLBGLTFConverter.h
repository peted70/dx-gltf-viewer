#pragma once

#include "stdafx.h"

#ifndef LEGACY_LOADER
#include <GLTFSDK/Deserialize.h>
#include <GLTFSDK/Serialize.h>
#include <GLTFSDK/GLTFResourceWriter.h>
#include <GLTFSDK/GLBResourceReader.h>

using namespace Microsoft::glTF;
#endif

namespace GLTFParser
{
	using namespace std;
#ifdef LEGACY_LOADER
	using namespace rapidjson;
#endif
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

		class ParserContext
		{
		public:
			ParserContext(const GLTFDocument& document,
				const Callbacks& callbacks,
				const GLBResourceReader& resources) :
				_document(document),
				_callbacks(callbacks),
				_resources(resources)
			{

			}

			const GLTFDocument& document() const { return _document; }
			const Callbacks& callbacks() const { return _callbacks; }
			const GLBResourceReader& resources() const { return _resources; }

		private:
			const GLTFDocument& _document;
			const Callbacks& _callbacks;
			const GLBResourceReader& _resources;
		};

		const Callbacks& EventHandlers() const { return _callbacks; }
		Callbacks& EventHandlers() { return _callbacks; }

		GLTFChunk * BinaryChunk() { return _binaryChunk; }
#ifdef LEGACY_LOADER
		Document& document() { return _document; }
#else
#endif

		void Read(shared_ptr<istream> file);

#ifndef LEGACY_LOADER
		void CheckExtensions(const GLTFDocument& document);
#else
		void CheckExtensions(const Document& document);
#endif
#ifndef LEGACY_LOADER
		void ParseDocument(const ParserContext& parser);
#else
		void ParseDocument(const Document& document, const Callbacks& callbacks);
#endif
#ifndef LEGACY_LOADER
		void LoadScene(const ParserContext& parser, const Scene& scene);
		void LoadMeshNode(const ParserContext& parser, const Node& mNode);
		void LoadTransform(const ParserContext& parser, const Node& mNode);
		void LoadSceneNode(const ParserContext& parser, const Node& sceneNode, int nodeIndex, int parentIndex);
		void LoadMaterialNode(const ParserContext& parser, const Material& mNode);
		void LoadMaterialTextures(const ParserContext& parser, const Material& mNode);
		void LoadTexture(const ParserContext& parser, const Texture& texture);
		void LoadBufferFromAccessorId(const ParserContext& parser, const string& accessorId, 
									  const string& bufferType);
		void LoadBuffer(const ParserContext& parser, const BufferView& bufferView,
						const string& bufferType, const Accessor& accessor) const;
#else
		void LoadScene(const Document& document, const Value& scene, const Callbacks& callbacks);
		void LoadMeshNode(const Document& document, const Value& meshNode, const Callbacks& callbacks);
		void LoadTransform(const Document& document, const Value& mNode, const Callbacks& callbacks);
		void LoadSceneNode(const Document& document, const Value& scene, const Callbacks& callbacks, int nodeIndex, int parentIndex);
#endif

	private:


		unique_ptr<GLTFHeader> _header;
		unique_ptr<ChunkList> _chunks;
#ifdef LEGACY_LOADER
		Document _document;
#else

#endif
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

