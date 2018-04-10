#include "pch.h"
#include "TransformViewModel.h"

using namespace ViewModels;

float TransformViewModel::PositionX::get()
{
	if (_selectedNode)
	{
		shared_ptr<GraphContainerNode> derived =
			dynamic_pointer_cast<GraphContainerNode>(_selectedNode);
		return derived->GetTranslation().x;
	}
	return 0.0f;
}

void TransformViewModel::PositionX::set(float val)
{
	shared_ptr<GraphContainerNode> derived =
		dynamic_pointer_cast<GraphContainerNode>(_selectedNode);
	derived->SetTranslation(val, derived->GetTranslation().y, derived->GetTranslation().z);
	OnPropertyChanged(getCallerName(__FUNCTION__));
}

float TransformViewModel::PositionY::get()
{
	if (_selectedNode)
	{
		shared_ptr<GraphContainerNode> derived =
			dynamic_pointer_cast<GraphContainerNode>(_selectedNode);
		return derived->GetTranslation().y;
	}
	return 0.0f;
}

void TransformViewModel::PositionY::set(float val)
{
	shared_ptr<GraphContainerNode> derived =
		dynamic_pointer_cast<GraphContainerNode>(_selectedNode);
	derived->SetTranslation(derived->GetTranslation().x, val, derived->GetTranslation().z);
	OnPropertyChanged(getCallerName(__FUNCTION__));
}

float TransformViewModel::PositionZ::get()
{
	if (_selectedNode)
	{
		shared_ptr<GraphContainerNode> derived =
			dynamic_pointer_cast<GraphContainerNode>(_selectedNode);
		return derived->GetTranslation().z;
	}
	return 0.0f;
}

void TransformViewModel::PositionZ::set(float val)
{
	shared_ptr<GraphContainerNode> derived =
		dynamic_pointer_cast<GraphContainerNode>(_selectedNode);
	derived->SetTranslation(derived->GetTranslation().x, derived->GetTranslation().y, val);
	OnPropertyChanged(getCallerName(__FUNCTION__));
}
