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

	auto es = ref new EventShim(memfun, tmemfun);
	parser->OnBufferEvent += ref new BufferEventHandler(es, &EventShim::OnBuffer);
	parser->OnTextureEvent += ref new TextureEventHandler(es, &EventShim::OnTexture);

	co_await async([&parser, filename, &mesh]() { parser->ParseFile(filename); return mesh.get(); });

	co_return mesh;
}