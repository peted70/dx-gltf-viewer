#include "pch.h"
#include "ModelFactory.h"


ModelFactory::ModelFactory()
{
}


ModelFactory::~ModelFactory()
{
}

future<GraphNode *> ModelFactory::CreateFromFileAsync()
{
	WinRTGLTFParser::GLTF_Parser^ parser = ref new WinRTGLTFParser::GLTF_Parser();
	std::function<void(WinRTGLTFParser::GLTF_BufferData^)> memfun = std::bind(&Sample3DSceneRenderer::OnBuffer, this, std::placeholders::_1);
	std::function<void(WinRTGLTFParser::GLTF_TextureData^)> tmemfun = std::bind(&Sample3DSceneRenderer::OnTexture, this, std::placeholders::_1);

	auto es = ref new EventShim(memfun, tmemfun);
	parser->OnBufferEvent += ref new BufferEventHandler(es, &EventShim::OnBuffer);
	parser->OnTextureEvent += ref new TextureEventHandler(es, &EventShim::OnTexture);

	parser->ParseFile(file->Name);

	co_return new MeshNode();
}
