#include "pch.h"
#include "GraphContainerNode.h"


GraphContainerNode::GraphContainerNode()
{
}


GraphContainerNode::~GraphContainerNode()
{
}

void GraphContainerNode::Draw(ID3D11DeviceContext2 *context)
{
	for (auto child : _children)
	{
		child->Draw(context);
	}
}

void GraphContainerNode::CreateDeviceDependentResources()
{
	for (auto child : _children)
	{
		child->CreateDeviceDependentResources();
	}
}

void GraphContainerNode::Initialise(const std::shared_ptr<DX::DeviceResources>& deviceResources)
{
	_deviceResources = deviceResources;
}

