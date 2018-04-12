#pragma once
namespace ModelViewer
{
	using namespace std;
	using namespace DX;

	class HMDRenderer
	{
	public:
		HMDRenderer(const shared_ptr<DeviceResources>& deviceResources);
		~HMDRenderer();

		void Initialise();
		void Render();

	private:
		bool _active = false;
		shared_ptr<DeviceResources> _deviceResources;
		IVRSystem *_system = nullptr;
		uint32_t _renderWidth = 0;
		uint32_t _renderHeight = 0;
		IVRRenderModels *_renderModels;
	};
}
