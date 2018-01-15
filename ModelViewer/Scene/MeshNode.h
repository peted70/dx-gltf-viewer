#pragma once
#include "GraphContainerNode.h"
#include "Common\DeviceResources.h"

class MeshNode : public GraphContainerNode
{
public:
	MeshNode();
	virtual ~MeshNode();

	virtual void Draw();
	void CreateBuffer(WinRTGLTFParser::GLTF_BufferData^ data);
	void CreateTexture(WinRTGLTFParser::GLTF_TextureData^ data);

private:
	shared_ptr<DX::DeviceResources> m_deviceResources;
};

