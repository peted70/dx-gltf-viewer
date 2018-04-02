#pragma once

#include "Common/ViewModelBase.h"
#include "NotificationManager.h"
#include "DirectXPageViewModelData.h"
#include "Content\Sample3DSceneRenderer.h"
#include <memory>
#include "Container.h"

#define _USE_MATH_DEFINES
#include <math.h>

namespace ViewModels
{
	using namespace Common;
	using namespace Windows::UI;
	using namespace Windows::UI::Xaml::Data;
	using namespace ModelViewer;

	[Bindable]
	public ref class DirectXPageViewModel sealed : public ViewModelBase
	{
	public:
		DirectXPageViewModel()
		{
			_data = Container::Instance().ResolveDirectXPageViewModelData();
		}

		property float LightScale
		{
			float get() { return _data->LightScale(); }
			void set(float val)
			{
				if (_data->LightScale() == val)
					return;
				OnPropertyChanged(getCallerName(__FUNCTION__));
				_data->SetLightScale(val);
			}
		}

		property float LightRotation
		{
			float get() { return _data->LightRotation(); }
			void set(float val)
			{
				if (_data->LightRotation() == val)
					return;
				_data->SetLightRotation(val);
				OnPropertyChanged(getCallerName(__FUNCTION__));
				_data->SetLightDirection(ConvertDirection(LightRotation, LightPitch, 
					const_cast<float *>(_data->LightDirection())));
			}
		}

		property float LightPitch
		{
			float get() { return _data->LightPitch(); }
			void set(float val)
			{
				if (_data->LightPitch() == val)
					return;
				_data->SetLightPitch(val);
				OnPropertyChanged(getCallerName(__FUNCTION__));
				_data->SetLightDirection(ConvertDirection(LightRotation, LightPitch, 
					const_cast<float *>(_data->LightDirection())));
			}
		}

		property float Ibl
		{
			float get() { return _data->Ibl(); }
			void set(float val)
			{
				if (_data->Ibl() == val)
					return;
				_data->SetIbl(val);
				OnPropertyChanged(getCallerName(__FUNCTION__));
			}
		}

		property Color LightColour
		{
			Color get() { return ConvertColor(_data->LightColour()); }
			void set(Windows::UI::Color val)
			{
				if (_data->LightColour()[0] == val.R &&
					_data->LightColour()[1] == val.G &&
					_data->LightColour()[2] == val.B)
					return;
				unsigned char col[3] = { val.R, val.G, val.B };
				_data->SetLightColour(col);
				OnPropertyChanged(getCallerName(__FUNCTION__));
			}
		}

		property bool BaseColour
		{
			bool get() { return _data->BaseColour(); }
			void set(bool val)
			{
				if (_data->BaseColour() == val)
					return;
				_data->SetBaseColour(val);
				OnPropertyChanged(getCallerName(__FUNCTION__));
			}
		}

		property bool Metallic
		{
			bool get() { return _data->Metallic(); }
			void set(bool val)
			{
				if (_data->Metallic() == val)
					return;
				_data->SetMetallic(val);
				OnPropertyChanged(getCallerName(__FUNCTION__));
			}
		}

		property bool Roughness
		{
			bool get() { return _data->Roughness(); }
			void set(bool val)
			{
				if (_data->Roughness() == val)
					return;
				_data->SetRoughness(val);
				OnPropertyChanged(getCallerName(__FUNCTION__));
			}
		}

		property bool Diffuse
		{
			bool get() { return _data->Diffuse(); }
			void set(bool val)
			{
				if (_data->Diffuse() == val)
					return;
				_data->SetDiffuse(val);
				OnPropertyChanged(getCallerName(__FUNCTION__));
			}
		}

		property bool Specular
		{
			bool get() { return _data->Specular(); }
			void set(bool val)
			{
				if (_data->Specular() == val)
					return;
				_data->SetSpecular(val);
				OnPropertyChanged(getCallerName(__FUNCTION__));
			}
		}

		property bool F
		{
			bool get() { return _data->F(); }
			void set(bool val)
			{
				if (_data->F() == val)
					return;
				_data->SetF(val);
				OnPropertyChanged(getCallerName(__FUNCTION__));
			}
		}

		property bool G
		{
			bool get() { return _data->G(); }
			void set(bool val)
			{
				if (_data->G() == val)
					return;
				_data->SetG(val);
				OnPropertyChanged(getCallerName(__FUNCTION__));
			}
		}

		property bool D
		{
			bool get() { return _data->D(); }
			void set(bool val)
			{
				if (_data->D() == val)
					return;
				_data->SetD(val);
				OnPropertyChanged(getCallerName(__FUNCTION__));
			}
		}

	private:

		Color ConvertColor(const unsigned char col[3])
		{
			auto ret = new Color();
			ret->R = col[0];
			ret->G = col[1];
			ret->B = col[2];
			return *ret;
		}

		float *ConvertDirection(float rotation, float pitch, float *data)
		{
			auto rot = rotation * M_PI / 180;
			auto ptch = pitch * M_PI / 180;
			data[0] = static_cast<float>(sin(rot) * cos(ptch));
			data[1] = static_cast<float>(sin(ptch));
			data[2] = static_cast<float>(cos(rot) * cos(ptch));
			return data;
		}

		std::shared_ptr<DirectXPageViewModelData> _data;
	};
}

