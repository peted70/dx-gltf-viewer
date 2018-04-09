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
		DirectXPageViewModel();

		property float LightScale { float get(); void set(float val); }
		property float LightRotation { float get(); void set(float val); }
		property float LightPitch { float get(); void set(float val); }
		property float Ibl { float get(); void set(float val); }
		property Color LightColour { Color get(); void set(Color val); }
		property bool BaseColour { bool get(); void set(bool val); }

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

		property float PositionX
		{
			float get() 
			{
				if (_selectedNode)
				{
					shared_ptr<GraphContainerNode> derived =
						dynamic_pointer_cast<GraphContainerNode>(_selectedNode);
					return derived->GetTranslation().x;
				}
				return 0.0f;
			}
			void set(float val)
			{
				OnPropertyChanged(getCallerName(__FUNCTION__));
			}
		}

	private:
		void NotifySelectionChanged(shared_ptr<GraphNode> node);
		Color ConvertColor(const unsigned char col[3]);
		float *ConvertDirection(float rotation, float pitch, float *data);

		shared_ptr<DirectXPageViewModelData> _data;
		shared_ptr<GraphNode> _selectedNode;
	};
}

