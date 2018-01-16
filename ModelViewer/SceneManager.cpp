#include "pch.h"
#include "SceneManager.h"

SceneManager::SceneManager()
{
	_sceneNode = make_shared<RootNode>();
}

shared_ptr<RootNode> SceneManager::Current()
{
	return _sceneNode;
}

void SceneManager::SetDevResources(const std::shared_ptr<DX::DeviceResources>& deviceResources)
{
	_deviceResources = deviceResources;
}
