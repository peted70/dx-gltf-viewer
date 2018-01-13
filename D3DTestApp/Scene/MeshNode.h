#pragma once
#include "GraphContainerNode.h"

class MeshNode : public GraphContainerNode
{
public:
	MeshNode();
	virtual ~MeshNode();

	virtual void Draw();
};

