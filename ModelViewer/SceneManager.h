#pragma once

#include "Scene\RootNode.h"

// Just using this singleton for the time-being until it becomes clearer on how
// to best structure..
//
using namespace std;
using namespace DX;

class SceneManager
{
public:
	static SceneManager& Instance()
	{
		static SceneManager instance; 
		return instance;
	}
	SceneManager(SceneManager const&) = delete;
	void operator=(SceneManager const&) = delete;

	shared_ptr<RootNode> Current();
	void SetDevResources(const shared_ptr<DeviceResources>& deviceResources);
	shared_ptr<DeviceResources> DevResources() { return _deviceResources; }

private:
	SceneManager();

	// Just have once scene for now..
	shared_ptr<RootNode> _sceneNode;
	shared_ptr<DeviceResources> _deviceResources;
};
