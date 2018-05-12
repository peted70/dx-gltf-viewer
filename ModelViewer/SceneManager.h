#pragma once

#include "Scene\RootNode.h"
#include <boost\signals2\signal.hpp>

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
	const shared_ptr<RootNode> Current() const;
	void AddNode(shared_ptr<GraphNode> newNode);

	void SetDevResources(const shared_ptr<DeviceResources>& deviceResources);
	shared_ptr<DeviceResources> DevResources() { return _deviceResources; }

	signals::connection RegisterForUpdates(signals::signal<void(SceneManager const&)>::slot_type slot)
	{
		return SceneChanged.connect(slot);
	}

	void UnregisterForUpdates(signals::connection conn)
	{
		conn.disconnect();
	}

	signals::connection RegisterForSelectionChanged(signals::signal<void(shared_ptr<GraphNode>)>::slot_type slot)
	{
		return SelectionChanged.connect(slot);
	}

	void SetSelected(shared_ptr<GraphNode> node);
	shared_ptr<GraphNode> GetSelected();

private:
	SceneManager();

	// Just have once scene for now..
	shared_ptr<RootNode> _sceneNode;
	shared_ptr<DeviceResources> _deviceResources;

	signals::signal<void(SceneManager const&)> SceneChanged;
	signals::signal<void(shared_ptr<GraphNode>)> SelectionChanged;
};
