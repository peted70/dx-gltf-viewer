#pragma once

#include "Scene\GraphContainerNode.h"

// Just using this singleton for the time-being until it becomes clearer on how
// to best structure..
//
using namespace std;

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

	shared_ptr<GraphContainerNode> Current();

private:
	SceneManager();

	// Just have once scene for now..
	shared_ptr<GraphContainerNode> _sceneNode;
};
