#include "pch.h"
#include "ModelFactory.h"
#include "EventShim.h"
#include "SceneManager.h"

ModelFactory::ModelFactory()
{
}


ModelFactory::~ModelFactory()
{
}

future<shared_ptr<MeshNode>> ModelFactory::CreateFromFileAsync(String^ filename)
{
	WinRTGLTFParser::GLTF_Parser^ parser = ref new WinRTGLTFParser::GLTF_Parser();

	auto mesh = std::make_shared<MeshNode>();

	auto devResources = SceneManager::Instance().DevResources();
	mesh->Initialise(devResources);

	std::function<void(WinRTGLTFParser::GLTF_BufferData^)> memfun = std::bind(&MeshNode::CreateBuffer, mesh, std::placeholders::_1);
	std::function<void(WinRTGLTFParser::GLTF_TextureData^)> tmemfun = std::bind(&MeshNode::CreateTexture, mesh, std::placeholders::_1);
	std::function<void(WinRTGLTFParser::GLTF_MaterialData^)> mmemfun = std::bind(&MeshNode::CreateMaterial, mesh, std::placeholders::_1);
	std::function<void(WinRTGLTFParser::GLTF_TransformData^)> tmmemfun = std::bind(&MeshNode::CreateTransform, mesh, std::placeholders::_1);

	auto es = ref new EventShim(memfun, mmemfun, tmemfun, tmmemfun);
	parser->OnBufferEvent += ref new BufferEventHandler(es, &EventShim::OnBuffer);
	parser->OnTextureEvent += ref new TextureEventHandler(es, &EventShim::OnTexture);
	parser->OnMaterialEvent += ref new MaterialEventHandler(es, &EventShim::OnMaterial);
	parser->OnTransformEvent += ref new TransformEventHandler(es, &EventShim::OnTransform);

	co_await async([&parser, filename, &mesh]() { parser->ParseFile(filename); return mesh.get(); });

	mesh->AfterLoad();

	co_return mesh;
}