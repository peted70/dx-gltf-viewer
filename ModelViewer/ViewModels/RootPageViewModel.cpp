#include "pch.h"
#include "RootPageViewModel.h"

using namespace ViewModels;

RootPageViewModel::RootPageViewModel()
{
}

bool RootPageViewModel::Loading::get()
{
	return _loading;
}

void RootPageViewModel::Loading::set(bool val)
{
	if (_loading == val)
		return;
	OnPropertyChanged(getCallerName(__FUNCTION__));
}
