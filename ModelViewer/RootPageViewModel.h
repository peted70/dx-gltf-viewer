#pragma once

#include "Common/ViewModelBase.h"

using namespace Common;

namespace ViewModels
{
	public ref class RootPageViewModel sealed : public ViewModelBase
	{
	public:
		RootPageViewModel();

		property float LightScale
		{
			float get() { return _lightScale; }
			void set(float val)
			{
				if (_lightScale == val)
					return;
				_lightScale = val;
				OnPropertyChanged(getCallerName(__FUNCTION__));
			}
		}

		property float LightRotation
		{
			float get() { return _lightRotation; }
			void set(float val)
			{
				if (_lightRotation == val)
					return;
				_lightRotation = val;
				OnPropertyChanged(getCallerName(__FUNCTION__));
			}
		}

		property float LightPitch
		{
			float get() { return _lightPitch; }
			void set(float val)
			{
				if (_lightPitch == val)
					return;
				_lightPitch = val;
				OnPropertyChanged(getCallerName(__FUNCTION__));
			}
		}

	private:
		float _lightPitch;
		float _lightRotation;
		float _lightScale;
	};
}
