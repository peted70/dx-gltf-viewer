#pragma once

#include "Common\DeviceResources.h"
#include "Common\StepTimer.h"

using namespace std;
using namespace DX;

class GraphNode
{
public:
	GraphNode();
	virtual ~GraphNode();

	virtual void Update(StepTimer const& timer) = 0;
	virtual void Draw(ID3D11DeviceContext2 *context) = 0;
	virtual void CreateDeviceDependentResources() = 0;
	virtual void Initialise(const std::shared_ptr<DX::DeviceResources>& deviceResources) = 0;
	virtual void AddChild(shared_ptr<GraphNode> child) = 0;
};

