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
	};
}
