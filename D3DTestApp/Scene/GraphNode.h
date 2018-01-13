#pragma once
class GraphNode
{
public:
	GraphNode();
	virtual ~GraphNode();

	virtual void Draw() = 0;
};

