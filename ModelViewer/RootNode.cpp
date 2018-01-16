#include "pch.h"
#include "RootNode.h"

RootNode::RootNode()
{
}

RootNode::~RootNode()
{
}

shared_ptr<GraphNode> RootNode::SelectedNode()
{
	return _selectedNode;
}
