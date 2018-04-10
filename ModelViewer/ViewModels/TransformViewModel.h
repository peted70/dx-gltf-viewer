#pragma once

#include "Common/ViewModelBase.h"

namespace ViewModels
{
	using namespace Windows::UI::Xaml::Data;

	[Bindable]
	public ref class TransformViewModel sealed : public ViewModelBase
	{
	internal:
		TransformViewModel(shared_ptr<GraphNode> node) :
			_selectedNode(node)
		{

		}

	public:
		property float PositionX { float get(); void set(float val); }
		property float PositionY { float get(); void set(float val); }
		property float PositionZ { float get(); void set(float val); }

	private:
		shared_ptr<GraphNode> _selectedNode;
	};
}