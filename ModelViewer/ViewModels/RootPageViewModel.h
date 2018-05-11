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

		property bool Loading { bool get(); void set(bool val); }

	private:
		bool _loading = false;
	};
}
