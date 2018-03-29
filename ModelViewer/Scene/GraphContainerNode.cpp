#include "pch.h"
#include "GraphContainerNode.h"
#include "BufferManager.h"

GraphContainerNode::GraphContainerNode(int index) : 
	_index(index)
{
}

GraphContainerNode::~GraphContainerNode()
{
}

void GraphContainerNode::Update(StepTimer const& timer)
{
	for (auto child : _children)
	{
		child->Update(timer);
	}
}

void GraphContainerNode::Draw(ID3D11DeviceContext2 *context)
{
	for (auto child : _children)
	{
		child->Draw(context);
	}
}

GraphNode *GraphContainerNode::FindChildByIndex(int index)
{
	if (Index() == index)
		return this;
	for (auto child : _children)
	{
		return child->FindChildByIndex(index);
	}
	return nullptr;
}

void GraphContainerNode::ForAllChildrenRecursive(function<void(GraphNode&)> func)
{
	func(*this);
	for (auto child : _children)
	{
		func(*child);
		child->ForAllChildrenRecursive(func);
	}
}

void GraphContainerNode::CreateDeviceDependentResources()
{
	for (auto child : _children)
	{
		child->CreateDeviceDependentResources();
	}
}

void GraphContainerNode::Initialise(const std::shared_ptr<DX::DeviceResources>& deviceResources)
{
	_deviceResources = deviceResources;
}

void GraphContainerNode::AddChild(shared_ptr<GraphNode> child)
{
	_children.push_back(child);
}

void GraphContainerNode::CreateTransform(GLTF_TransformData^ data)
{
	// If we are handed a matrix, just apply that, otherwise break down into scale, rotate, translate
	// and generate the matrix from those..
	XMMATRIX matrix;

	if (data->hasMatrix)
	{
		XMFLOAT4X4 mat =
		{
			data->matrix[0],
			data->matrix[1],
			data->matrix[2],
			data->matrix[3],
			data->matrix[4],
			data->matrix[5],
			data->matrix[6],
			data->matrix[7],
			data->matrix[8],
			data->matrix[9],
			data->matrix[10],
			data->matrix[11],
			data->matrix[12],
			data->matrix[13],
			data->matrix[14],
			data->matrix[15]
		};

		XMStoreFloat4x4(&BufferManager::Instance().MVPBuffer().BufferData().model, XMLoadFloat4x4(&mat));
	}
	else
	{
		_scale = { data->scale[0], data->scale[1], data->scale[2] };
		_translation = { data->translation[0], data->translation[1], data->translation[2] };

		// Using the conversion from right-handed coordinate system of OpenGL to left-handed coordinate
		// system of DirectX
		// q.x, q.y, -q.z, -q.w
		//
		_rotation = { data->rotation[0], data->rotation[1], -data->rotation[2], -data->rotation[3] };

		//XMVECTOR scale = { 1.0, 1.0, 1.0 };
		//XMVECTOR translation = { 0.0, 0.0, 0.0 };

		XMVECTOR ypr = { 0.0, 180.0, 0.0 };
		// generate a quaternion from angle for testing...
		XMVECTOR rotQuat = XMQuaternionRotationRollPitchYawFromVector(ypr);

		//auto matrix = XMMatrixRotationQuaternion(quat);

		// Create matrix from scale
		auto matrix = XMMatrixAffineTransformation(_scale, emptyVector, _rotation, _translation);

		// Prepare to pass the updated model matrix to the shader 
		XMStoreFloat4x4(&BufferManager::Instance().MVPBuffer().BufferData().model, matrix);
	}
}
