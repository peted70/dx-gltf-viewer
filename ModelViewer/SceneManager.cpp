#include "pch.h"
#include "SceneManager.h"

SceneManager::SceneManager()
{
	_sceneNode = make_shared<RootNode>(-1);
}

void SceneManager::Notify(const Observable & data)
{
	NotificationManager::Instance().Notify(data);
}

shared_ptr<RootNode> SceneManager::Current()
{
	return _sceneNode;
}

const shared_ptr<RootNode> SceneManager::Current() const
{
	return _sceneNode;
}

void SceneManager::AddNode(shared_ptr<GraphNode> newNode)
{
	Current()->AddChild(newNode);
	SceneChanged(*this);
}

void SceneManager::SetDevResources(const std::shared_ptr<DX::DeviceResources>& deviceResources)
{
	_deviceResources = deviceResources;
}
