#pragma once

#include "Common\DeviceResources.h"

class GraphNode
{
public:
	GraphNode();
	virtual ~GraphNode();

	virtual void Draw(ID3D11DeviceContext2 *context) = 0;
	virtual void CreateDeviceDependentResources() = 0;
	virtual void Initialise(const std::shared_ptr<DX::DeviceResources>& deviceResources) = 0;
};

