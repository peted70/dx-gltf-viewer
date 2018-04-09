#include "pch.h"
#include "DirectXPageViewModel.h"
#include "NotificationManager.h"

using namespace ViewModels;

DirectXPageViewModel::DirectXPageViewModel()
{
	_data = Container::Instance().ResolveDirectXPageViewModelData();
	SceneManager::Instance().RegisterForSelectionChanged(boost::bind(&DirectXPageViewModel::NotifySelectionChanged, this, _1));
}

void DirectXPageViewModel::NotifySelectionChanged(shared_ptr<GraphNode> node)
{

}

float DirectXPageViewModel::LightScale::get()
{
	return _data->LightScale();
}

void DirectXPageViewModel::LightScale::set(float val)
{
	if (_data->LightScale() == val)
		return;
	OnPropertyChanged(getCallerName(__FUNCTION__));
	_data->SetLightScale(val);
}

float DirectXPageViewModel::LightRotation::get()
{
	return _data->LightRotation();
}

void DirectXPageViewModel::LightRotation::set(float val)
{
	if (_data->LightRotation() == val)
		return;
	_data->SetLightRotation(val);
	OnPropertyChanged(getCallerName(__FUNCTION__));
	_data->SetLightDirection(ConvertDirection(LightRotation, LightPitch,
		const_cast<float *>(_data->LightDirection())));
}

float DirectXPageViewModel::LightPitch::get()
{
	return _data->LightPitch();
}

void DirectXPageViewModel::LightPitch::set(float val)
{
	if (_data->LightPitch() == val)
		return;
	_data->SetLightPitch(val);
	OnPropertyChanged(getCallerName(__FUNCTION__));
	_data->SetLightDirection(ConvertDirection(LightRotation, LightPitch,
		const_cast<float *>(_data->LightDirection())));
}

float DirectXPageViewModel::Ibl::get()
{
	return _data->Ibl();
}

void DirectXPageViewModel::Ibl::set(float val)
{
	if (_data->Ibl() == val)
		return;
	_data->SetIbl(val);
	OnPropertyChanged(getCallerName(__FUNCTION__));
}

Color DirectXPageViewModel::LightColour::get()
{
	return ConvertColor(_data->LightColour());
}

void DirectXPageViewModel::LightColour::set(Color val)
{
	if (_data->LightColour()[0] == val.R &&
		_data->LightColour()[1] == val.G &&
		_data->LightColour()[2] == val.B)
		return;
	unsigned char col[3] = { val.R, val.G, val.B };
	_data->SetLightColour(col);
	OnPropertyChanged(getCallerName(__FUNCTION__));
}

bool DirectXPageViewModel::BaseColour::get()
{
	return _data->BaseColour();
}

void DirectXPageViewModel::BaseColour::set(bool val)
{
	if (_data->BaseColour() == val)
		return;
	_data->SetBaseColour(val);
	OnPropertyChanged(getCallerName(__FUNCTION__));
}

Color DirectXPageViewModel::ConvertColor(const unsigned char col[3])
{
	auto ret = new Color();
	ret->R = col[0];
	ret->G = col[1];
	ret->B = col[2];
	return *ret;
}

float *DirectXPageViewModel::ConvertDirection(float rotation, float pitch, float *data)
{
	auto rot = rotation * M_PI / 180;
	auto ptch = pitch * M_PI / 180;
	data[0] = static_cast<float>(sin(rot) * cos(ptch));
	data[1] = static_cast<float>(sin(ptch));
	data[2] = static_cast<float>(cos(rot) * cos(ptch));
	return data;
}
