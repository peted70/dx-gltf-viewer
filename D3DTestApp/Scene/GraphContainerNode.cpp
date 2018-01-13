#include "pch.h"
#include "GraphContainerNode.h"


GraphContainerNode::GraphContainerNode()
{
}


GraphContainerNode::~GraphContainerNode()
{
}

void GraphContainerNode::Draw()
{
	for (auto child : _children)
	{
		child->Draw();
	}
}
