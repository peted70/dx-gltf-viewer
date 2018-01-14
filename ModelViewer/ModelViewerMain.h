#pragma once

#include "Common\StepTimer.h"
#include "Common\DeviceResources.h"
#include "Content\Sample3DSceneRenderer.h"
#include "Content\SampleFpsTextRenderer.h"

// Renders Direct2D and 3D content on the screen.
namespace ModelViewer
{
	class ModelViewerMain : public DX::IDeviceNotify
	{
	public:
		ModelViewerMain(const std::shared_ptr<DX::DeviceResources>& deviceResources);
		~ModelViewerMain();
		void CreateWindowSizeDependentResources();
		void StartTracking(float positionX, float positionY, VirtualKeyModifiers mod) 
		{ 
			m_sceneRenderer->StartTracking(positionX, positionY, mod);
		}
		void TrackingUpdate(float positionX, float positionY, VirtualKeyModifiers mod)
		{ 
			//m_pointerLocationX = positionX;
			//m_pointerLocationY = positionY;
			//m_mod = mod;
			m_sceneRenderer->TrackingUpdate(positionX, positionY, mod);
		}
		void StopTracking(float positionX, float positionY, VirtualKeyModifiers mod) 
		{ 
			m_sceneRenderer->StopTracking(positionX, positionY, mod);
		}
		bool IsTracking() { return m_sceneRenderer->IsTracking(); }
		void StartRenderLoop();
		void StopRenderLoop();
		Concurrency::critical_section& GetCriticalSection() { return m_criticalSection; }

		// IDeviceNotify
		virtual void OnDeviceLost();
		virtual void OnDeviceRestored();

	private:
		void ProcessInput();
		void Update();
		bool Render();

		// Cached pointer to device resources.
		std::shared_ptr<DX::DeviceResources> m_deviceResources;

		// TODO: Replace with your own content renderers.
		std::unique_ptr<Sample3DSceneRenderer> m_sceneRenderer;
		std::unique_ptr<SampleFpsTextRenderer> m_fpsTextRenderer;

		Windows::Foundation::IAsyncAction^ m_renderLoopWorker;
		Concurrency::critical_section m_criticalSection;

		// Rendering loop timer.
		DX::StepTimer m_timer;

		// Track current input pointer position.
		float m_pointerLocationX;
		float m_pointerLocationY;
		VirtualKeyModifiers m_mod;
	};
}