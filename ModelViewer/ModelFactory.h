#pragma once
#include "Scene\GraphNode.h"
#include "Scene\MeshNode.h"
#include "ppltasks.h"
#include <future>
#include <experimental/resumable>

using namespace Windows::Foundation;
using namespace ModelViewer;
using namespace std;
using namespace Platform;
using namespace concurrency;
using namespace WinRTGLTFParser;

class ModelFactory
{
public:
	static ModelFactory& Instance()
	{
		static ModelFactory instance;
		return instance;
	}
	ModelFactory(ModelFactory const&) = delete;
	void operator=(ModelFactory const&) = delete;

	future<shared_ptr<GraphNode>> CreateFromFileAsync(String^ filename);
	void CreateSceneNode(GLTF_SceneNodeData^ data);
	GraphNode *InitialiseMesh(GLTF_SceneNodeData^ data);
	void CreateBuffer(GLTF_BufferData^ data);
	void CreateTexture(GLTF_TextureData^ data);
	void CreateMaterial(GLTF_MaterialData^ data);
	void CreateTransform(GLTF_TransformData^ data);

private:
	ModelFactory();
	GLTF_Parser^ _parser;
	GraphNode *_root;
	GraphNode *_currentNode;
};

