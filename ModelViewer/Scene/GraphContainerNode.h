#pragma once
#include "GraphNode.h"
#include <vector>
#include <string>
#include "../Common/DeviceResources.h"
#include "../Common/StepTimer.h"
#include <Rpc.h>

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
	virtual void ForAllChildrenRecursiveUntil(function<bool(GraphNode&)> func) override;
	virtual GraphNode *FindChildByIndex(int index) override;
	virtual GraphNode *FindChildById(GUID id) override;

	virtual void AddChild(shared_ptr<GraphNode> child);
	virtual int NumChildren() override;
	virtual shared_ptr<GraphNode> GetChild(int i) override;
	virtual const wstring& Name() const override;
	virtual void SetName(const wstring& name)  override;

	shared_ptr<DeviceResources> DevResources() { return _deviceResources; }
	const shared_ptr<DeviceResources> DevResources() const { return _deviceResources; }

	virtual void CreateTransform(GLTF_TransformData^ data);
	virtual int Index() override { return _index; };
	virtual GUID GetId() override { return _guid; }

	virtual bool IsSelected() override;
	virtual void SetSelected(bool sel) override ;

	virtual BoundingBox<float> GetBoundingBox() override;

	void* operator new(size_t i)
	{
		return _mm_malloc(i, 16);
	}

	void operator delete(void* p)
	{
		_mm_free(p);
	}

	bool IsEqual(const GraphContainerNode& other)
	{
		return _guid == other._guid;
	}

	XMFLOAT3 GetScale() { return _scale; }
	XMFLOAT3 GetTranslation() { return _translation; }
	XMFLOAT3 GetRotation() 
	{
		// Need to convert quaternion rotation here into yaw, pitch and roll..
		XMFLOAT3 ypr;

		ypr.x = _roll = XMConvertToDegrees(atan2(2 * _rotation.y*_rotation.w + 2 * _rotation.x*_rotation.z, 
			1 - 2 * _rotation.y*_rotation.y - 2 * _rotation.z*_rotation.z));
		ypr.y = _pitch = XMConvertToDegrees(atan2(2 * _rotation.x*_rotation.w + 2 * _rotation.y*_rotation.z, 
			1 - 2 * _rotation.x*_rotation.x - 2 * _rotation.z*_rotation.z));
		ypr.z = _yaw = XMConvertToDegrees(asin(2 * _rotation.x*_rotation.y + 2 * _rotation.z*_rotation.w));

		return ypr; 
	}

	void SetTranslation(float x, float y, float z)
	{
		_translation.x = x;
		_translation.y = y;
		_translation.z = z;
	}

	//void SetRotation(float yaw, float pitch, float roll)
	//{
	//	XMVECTOR vec = { XMConvertToRadians(yaw), XMConvertToRadians(pitch), XMConvertToRadians(roll) };
	//	auto quat = XMQuaternionRotationRollPitchYawFromVector(vec);
	//	XMStoreFloat4(&_rotation, quat);
	//}

	void SetRotationYaw(float yaw)
	{
		XMVECTOR vec = { XMConvertToRadians(_roll), XMConvertToRadians(_pitch), XMConvertToRadians(yaw) };
		auto quat = XMQuaternionRotationRollPitchYawFromVector(vec);
		XMStoreFloat4(&_rotation, quat);
		_yaw = yaw;
	}

	void SetRotationPitch(float pitch)
	{
		XMVECTOR vec = { XMConvertToRadians(_roll), XMConvertToRadians(pitch), XMConvertToRadians(_yaw) };
		auto quat = XMQuaternionRotationRollPitchYawFromVector(vec);
		XMStoreFloat4(&_rotation, quat);
		_pitch = pitch;
	}

	void SetRotationRoll(float roll)
	{
		XMVECTOR vec = { XMConvertToRadians(roll), XMConvertToRadians(_pitch), XMConvertToRadians(_yaw) };
		auto quat = XMQuaternionRotationRollPitchYawFromVector(vec);
		XMStoreFloat4(&_rotation, quat);
		_roll = roll;
	}

	void SetScale(float x, float y, float z)
	{
		_scale.x = x;
		_scale.y = y;
		_scale.z = z;
	}

protected:
	XMMATRIX _matrix;
	bool _hasMatrix = false;

	XMFLOAT3 _scale;
	XMFLOAT3 _translation;
	XMFLOAT4 _rotation;
	float _yaw, _pitch, _roll;

	int _index;

	vector<shared_ptr<GraphNode>>_children;
	shared_ptr<DeviceResources> _deviceResources;
	wstring _name;
	bool _selected = false;
	GUID _guid;
};

