#pragma once
#include "GraphNode.h"
#include <vector>
#include "../Common/DeviceResources.h"
#include "../Common/StepTimer.h"

using namespace std;
using namespace DX;

class GraphContainerNode :
	public GraphNode
{
public:
	GraphContainerNode();
	virtual ~GraphContainerNode();

	virtual void Update(StepTimer const& timer);

	virtual void Draw(ID3D11DeviceContext2 *context);
	virtual void CreateDeviceDependentResources();
	virtual void Initialise(const std::shared_ptr<DX::DeviceResources>& deviceResources);

	virtual void AddChild(shared_ptr<GraphNode> child);
	std::shared_ptr<DX::DeviceResources> DevResources() { return _deviceResources; }

private:
	vector<shared_ptr<GraphNode>>_children;
	std::shared_ptr<DX::DeviceResources> _deviceResources;
};

