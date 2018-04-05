#pragma once
#include "GraphNode.h"
#include <vector>
#include <string>
#include "../Common/DeviceResources.h"
#include "../Common/StepTimer.h"

using namespace std;
using namespace DX;
using namespace WinRTGLTFParser;
using namespace DirectX;

const XMFLOAT3 emptyVector = { 0, 0, 0 };

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
	virtual int NumChildren() override;
	virtual const GraphNode& GetChild(int i) override;
	virtual const wstring& Name() const override;
	virtual void SetName(const wstring& name)  override;

	shared_ptr<DeviceResources> DevResources() { return _deviceResources; }
	const shared_ptr<DeviceResources> DevResources() const { return _deviceResources; }

	virtual void CreateTransform(GLTF_TransformData^ data);
	virtual int Index() override { return _index; };

	virtual BoundingBox<float> GetBoundingBox() override;

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
	bool _hasMatrix = false;

	XMFLOAT3 _scale;
	XMFLOAT3 _translation;
	XMFLOAT4 _rotation;

	int _index;

	vector<shared_ptr<GraphNode>>_children;
	shared_ptr<DeviceResources> _deviceResources;
	wstring _name;
};

