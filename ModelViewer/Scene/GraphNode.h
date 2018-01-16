#pragma once
class GraphNode
{
public:
	GraphNode();
	virtual ~GraphNode();

	virtual void Draw(ID3D11DeviceContext2 *context) = 0;
	virtual void CreateDeviceDependentResources() = 0;
};

