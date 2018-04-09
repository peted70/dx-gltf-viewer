#pragma once

#include "Common\DeviceResources.h"
#include "Common\StepTimer.h"
#include "BoundingBox.h"
#include <Rpc.h>

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
	virtual void AfterLoad() = 0;
	virtual BoundingBox<float> GetBoundingBox() = 0;
	virtual void ForAllChildrenRecursive(function<void(GraphNode&)> func) = 0;
	virtual void ForAllChildrenRecursiveUntil(function<bool(GraphNode&)> func) = 0;
	virtual GraphNode *FindChildByIndex(int index) = 0;
	virtual GraphNode *FindChildById(GUID id) = 0;
	virtual int NumChildren() = 0;
	virtual shared_ptr<GraphNode> GetChild(int i) = 0;
	virtual const wstring& Name() const = 0;
	virtual void SetName(const wstring& name) = 0;
	virtual int Index() = 0;
	virtual GUID GetId() = 0;
	virtual bool IsSelected() = 0;
	virtual void SetSelected(bool sel) = 0;
};

