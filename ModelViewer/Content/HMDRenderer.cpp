#include "pch.h"
#include "HMDRenderer.h"
#include "../OpenVR/header/openvr.h" 
#include "Utility.h"

using namespace ModelViewer;
using namespace vr;

HMDRenderer::HMDRenderer(const shared_ptr<DX::DeviceResources>& deviceResources) :
	_deviceResources(deviceResources)

{
}

HMDRenderer::~HMDRenderer()
{
}

void HMDRenderer::Initialise()
{
	auto runtime = VR_IsRuntimeInstalled();
	auto hmd = VR_IsHmdPresent();

	Utility::Out(L"Runtime present: %S", runtime ? "YES" : "NO");
	Utility::Out(L"HMD present: %S", hmd ? "YES" : "NO");

	if (!hmd || !runtime)
	{
		Utility::Out(L"Continuing without VR support");
		return;
	}

	EVRInitError error = VRInitError_None;
	_system = VR_Init(&error, EVRApplicationType::VRApplication_Scene);
 	if (error != vr::VRInitError_None)
	{
		_system = nullptr;
		Utility::Out(L"Unable to init VR runtime: %s", VR_GetVRInitErrorAsEnglishDescription(error));
		return;
	}

	_system->GetRecommendedRenderTargetSize(&_renderWidth, &_renderHeight);
	Utility::Out(L"Render Size = [%d %d]", _renderWidth, _renderHeight);

	if (_system == nullptr)
	{
		Utility::Out(L"Error [%d] - lookup here https://developer.valvesoftware.com/w/index.php?title=Category:SteamVRHelp", error);
		VR_Shutdown();
		return;
	}

	char deviceName[k_unMaxPropertyStringSize];

	// Iterate through all the allowed devices and print basic data for those connected 
	for (int td = k_unTrackedDeviceIndex_Hmd; td<k_unMaxTrackedDeviceCount; td++)
	{
		if (_system->IsTrackedDeviceConnected(td)) // Check if that device is connected 
		{
			auto td_class = _system->GetTrackedDeviceClass(td);
			auto deviceId = _system->GetStringTrackedDeviceProperty(td, Prop_TrackingSystemName_String, &deviceName[0], k_unMaxPropertyStringSize);

			Utility::Out(L"Type [%d] Name [%s]", deviceName);
		}
	}

	_renderModels = (IVRRenderModels *)vr::VR_GetGenericInterface(vr::IVRRenderModels_Version, &error);
	if (!_renderModels)
	{
		_system = nullptr;
		VR_Shutdown();
		Utility::Out(L"Unable to get render model interface : %s", VR_GetVRInitErrorAsEnglishDescription(error));
		return;
	}

	if (!VRCompositor())
	{
		Utility::Out(L"Compositor initialization failed. See log file for details\n");
		return;
	}



	// Just shut down until we have implemented something....
	VR_Shutdown();
}

void HMDRenderer::Render()
{

}

