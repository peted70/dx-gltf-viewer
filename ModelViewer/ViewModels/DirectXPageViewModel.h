#pragma once

#include "Common/ViewModelBase.h"
#include "NotificationManager.h"
#include "DirectXPageViewModelData.h"

#define _USE_MATH_DEFINES
#include <math.h>

namespace ViewModels
{
	using namespace Common;
	using namespace Windows::UI;
	using namespace Windows::UI::Xaml::Data;

	[Bindable]
	public ref class DirectXPageViewModel sealed : public ViewModelBase
	{
	public:
		property float LightScale
		{
			float get() { return _data._lightScale; }
			void set(float val)
			{
				if (_data._lightScale == val)
					return;
				_data._lightScale = val;
				OnPropertyChanged(getCallerName(__FUNCTION__));
				_data.Notify(_data);
			}
		}

		property float LightRotation
		{
			float get() { return _data._lightRotation; }
			void set(float val)
			{
				if (_data._lightRotation == val)
					return;
				_data._lightRotation = val;
				OnPropertyChanged(getCallerName(__FUNCTION__));
				ConvertDirection(LightRotation, LightPitch, _data._lightDirection);
				_data.Notify(_data);
			}
		}

		property float LightPitch
		{
			float get() { return _data._lightPitch; }
			void set(float val)
			{
				if (_data._lightPitch == val)
					return;
				_data._lightPitch = val;
				OnPropertyChanged(getCallerName(__FUNCTION__));
				ConvertDirection(LightRotation, LightPitch, _data._lightDirection);
				_data.Notify(_data);
			}
		}

		property float Ibl
		{
			float get() { return _data._ibl; }
			void set(float val)
			{
				if (_data._ibl == val)
					return;
				_data._ibl = val;
				OnPropertyChanged(getCallerName(__FUNCTION__));
				_data.Notify(_data);
			}
		}

		property Color LightColour
		{
			Color get() { return ConvertColor(_data._lightColour); }
			void set(Windows::UI::Color val)
			{
				if (_data._lightColour[0] == val.R && 
					_data._lightColour[1] == val.G &&
					_data._lightColour[2] == val.B)
					return;

				_data._lightColour[0] = val.R;
				_data._lightColour[1] = val.G;
				_data._lightColour[2] = val.B;

				OnPropertyChanged(getCallerName(__FUNCTION__));
				_data.Notify(_data);
			}
		}

	private:

		Color ConvertColor(float col[3])
		{
			auto ret = new Color();
			ret->R = col[0];
			ret->G = col[1];
			ret->B = col[2];
			return *ret;
		}

		float *ConvertDirection(float rotation, float pitch, float data[])
		{
			auto rot = rotation * M_PI / 180;
			auto ptch = pitch * M_PI / 180;
			data[0] = sin(rot) * cos(ptch);
			data[1] = sin(ptch);
			data[2] = cos(rot) * cos(ptch);
			return data;
		}

		DirectXPageViewModelData _data;
	};

}

