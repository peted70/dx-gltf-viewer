#pragma once
#include "GraphNode.h"
#include <vector>
#include "../Common/DeviceResources.h"

using namespace std;

class GraphContainerNode :
	public GraphNode
{
public:
	GraphContainerNode();
	virtual ~GraphContainerNode();

	virtual void Draw(ID3D11DeviceContext2 *context);
	virtual void CreateDeviceDependentResources();
	virtual void Initialise(const std::shared_ptr<DX::DeviceResources>& deviceResources);

private:
	vector<shared_ptr<GraphNode>>_children;
	std::shared_ptr<DX::DeviceResources> _deviceResources;
};

