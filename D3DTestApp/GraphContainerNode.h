#pragma once
#include "GraphNode.h"
#include <vector>

using namespace std;

class GraphContainerNode :
	public GraphNode
{
public:
	GraphContainerNode();
	virtual ~GraphContainerNode();

	virtual void Draw();

private:
	vector<shared_ptr<GraphNode>>_children;
};

