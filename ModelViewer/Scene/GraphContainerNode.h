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

	float GetRoll(XMFLOAT4 q)
	{
		float x = XMConvertToDegrees(atan2
		(
			2 * q.x * q.w - 2 * q.y * q.z,
			1 - 2 * pow(q.x, 2.0f) - 2 * pow(q.z, 2.0f)
		));

		if (q.x * q.y + q.z * q.w == 0.5)
		{
			x = XMConvertToDegrees((float)(2 * atan2(q.x, q.w)));
		}

		else if (q.x * q.y + q.z * q.w == -0.5)
		{
			x = XMConvertToDegrees((float)(-2 * atan2(q.x, q.w)));
		}
		return x;
	}

	float GetPitch(XMFLOAT4 q)
	{
		float y = XMConvertToDegrees(atan2
		(
			2 * q.y * q.w - 2 * q.x * q.z,
			1 - 2 * pow(q.y, 2.0f) - 2 * pow(q.z, 2.0f)
		));
		if (q.x * q.y + q.z * q.w == 0.5)
		{
			y = 0;
		}
		else if (q.x * q.y + q.z * q.w == -0.5)
		{
			y = 0;
		}
		return y;
	}

	float GetYaw(XMFLOAT4 q)
	{
		float z = XMConvertToDegrees(asin
		(
			2 * q.x * q.y + 2 * q.z * q.w
		));
		return z;
	}

	XMFLOAT3 QuaternionToEuler(XMFLOAT4 q)
	{
		XMFLOAT3 v = { 0.0f, 0.0f, 0.0f };

		v.y = XMConvertToDegrees(atan2
		(
			2 * q.y * q.w - 2 * q.x * q.z,
			1 - 2 * pow(q.y, 2.0f) - 2 * pow(q.z, 2.0f)
		));

		v.z = XMConvertToDegrees(asin
		(
			2 * q.x * q.y + 2 * q.z * q.w
		));

		v.x = XMConvertToDegrees(atan2
		(
			2 * q.x * q.w - 2 * q.y * q.z,
			1 - 2 * pow(q.x, 2.0f) - 2 * pow(q.z, 2.0f)
		));

		if (q.x * q.y + q.z * q.w == 0.5)
		{
			v.x = XMConvertToDegrees((float)(2 * atan2(q.x, q.w)));
			v.y = 0;
		}

		else if (q.x * q.y + q.z * q.w == -0.5)
		{
			v.x = XMConvertToDegrees((float)(-2 * atan2(q.x, q.w)));
			v.y = 0;
		}

		Utility::Out(L"Euler = %f %f %f", v.x, v.y, v.z);
		return v;
	}

	XMFLOAT3 GetScale() { return _scale; }
	XMFLOAT3 GetTranslation() { return _translation; }
	
	float GetRotationX()
	{
		return GetRoll(_rotation);
	}
	
	float GetRotationY()
	{
		return GetPitch(_rotation);
	}
	
	float GetRotationZ()
	{
		return GetYaw(_rotation);
	}

	XMFLOAT3 GetRotation()
	{
		return QuaternionToEuler(_rotation);
	}

	void SetTranslation(float x, float y, float z)
	{
		_translation.x = x;
		_translation.y = y;
		_translation.z = z;
	}

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

