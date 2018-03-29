#pragma once
#include "GraphNode.h"
#include <vector>
#include "../Common/DeviceResources.h"
#include "../Common/StepTimer.h"

using namespace std;
using namespace DX;
using namespace WinRTGLTFParser;
using namespace DirectX;

const XMVECTOR emptyVector = { 0, 0, 0 };

class GraphContainerNode :
	public GraphNode
{
public:
	GraphContainerNode(int index);
	virtual ~GraphContainerNode();

	virtual void Update(StepTimer const& timer);

	virtual void Draw(ID3D11DeviceContext2 *context);
	virtual void CreateDeviceDependentResources();
	virtual void Initialise(const shared_ptr<DX::DeviceResources>& deviceResources);

	virtual void AfterLoad() override {};
	virtual void ForAllChildrenRecursive(function<void(GraphNode&)> func) override;
	virtual GraphNode *FindChildByIndex(int index) override;

	virtual void AddChild(shared_ptr<GraphNode> child);
	shared_ptr<DeviceResources> DevResources() { return _deviceResources; }

	virtual void CreateTransform(GLTF_TransformData^ data);
	virtual int Index() override { return _index; };

	void* operator new(size_t i)
	{
		return _mm_malloc(i, 16);
	}

	void operator delete(void* p)
	{
		_mm_free(p);
	}

protected:
	XMMATRIX _matrix;

	XMVECTOR _scale;
	XMVECTOR _translation;
	XMVECTOR _rotation;

	int _index;

	vector<shared_ptr<GraphNode>>_children;
	shared_ptr<DeviceResources> _deviceResources;
};

