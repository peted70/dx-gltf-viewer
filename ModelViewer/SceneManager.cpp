#include "pch.h"
#include "SceneManager.h"

SceneManager::SceneManager()
{
	_sceneNode = make_shared<GraphContainerNode>();
}

shared_ptr<GraphContainerNode> SceneManager::Current()
{
	return _sceneNode;
}
