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
	// Do this for now until we need an insertion point
	return make_shared<RootNode>(*this);
	//return _selectedNode;
}
