#pragma once

#include "Common\StepTimer.h"
#include "Common\DeviceResources.h"
#include "Content\Sample3DSceneRenderer.h"
#include "Content\SampleFpsTextRenderer.h"

// Renders Direct2D and 3D content on the screen.
namespace D3DTestApp
{
	class D3DTestAppMain : public DX::IDeviceNotify
	{
	public:
		D3DTestAppMain(const std::shared_ptr<DX::DeviceResources>& deviceResources);
		~D3DTestAppMain();
		void CreateWindowSizeDependentResources();
		void Update();
		bool Render();

		// IDeviceNotify
		virtual void OnDeviceLost();
		virtual void OnDeviceRestored();

		void StartTracking(float positionX, float positionY, Windows::System::VirtualKeyModifiers mod)
		{
			m_sceneRenderer->StartTracking(positionX, positionY, mod);
		}
		void TrackingUpdate(float positionX, float positionY, Windows::System::VirtualKeyModifiers mod)
		{
			m_pointerLocationX = positionX; m_pointerLocationY = positionY;
			_keyModifiers = mod;
			m_sceneRenderer->TrackingUpdate(positionX, positionY, mod);
		}
		void StopTracking(float positionX, float positionY, VirtualKeyModifiers mod) 
		{ 
			m_pointerLocationX = positionX; m_pointerLocationY = positionY;
			_keyModifiers = mod;
			m_sceneRenderer->StopTracking(positionX, positionY, mod);
		}
		bool IsTracking() { return m_sceneRenderer->IsTracking(); }

	private:
		void ProcessInput();

		// Cached pointer to device resources.
		std::shared_ptr<DX::DeviceResources> m_deviceResources;

		// TODO: Replace with your own content renderers.
		std::unique_ptr<Sample3DSceneRenderer> m_sceneRenderer;
		std::unique_ptr<SampleFpsTextRenderer> m_fpsTextRenderer;

		// Rendering loop timer.
		DX::StepTimer m_timer;

		// Track current input pointer position.
		float m_pointerLocationX;
		float m_pointerLocationY;
		Windows::System::VirtualKeyModifiers _keyModifiers;
	};
}