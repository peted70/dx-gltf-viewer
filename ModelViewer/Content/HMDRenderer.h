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

		void Render();
	};
}
