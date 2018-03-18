#pragma once

#include "Common/ViewModelBase.h"

namespace ViewModels
{
	using namespace Common;

	[Windows::UI::Xaml::Data::Bindable]
	public ref class RootPageViewModel sealed : public ViewModelBase
	{
	public:
		RootPageViewModel();

	};
}
