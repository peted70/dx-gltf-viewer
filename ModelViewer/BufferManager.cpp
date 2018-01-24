#include "pch.h"
#include "BufferManager.h"

//template <class T>
//void ConstantBufferData<T>::Initialise(const DeviceResources& devResources)
//{
//	CD3D11_BUFFER_DESC desc(sizeof(T), D3D11_BIND_CONSTANT_BUFFER);
//	auto context = devResources->GetD3DDeviceContext();
//	DX::ThrowIfFailed(context->CreateBuffer(&desc, nullptr, &(ConstantBuffer())));
//}
//
//template <class T>
//void ConstantBufferData<T>::Update(const DeviceResources& devResources)
//{
//	auto context = devResources->GetD3DDeviceContext();
//	context->UpdateSubresource1(ConstantBuffer().Get(), 0, NULL, &(BufferData()), 0, 0, 0);
//}

BufferManager::BufferManager() :
	_cbPerObject(0),
	_cbPerFrame(1),
	_mvpBuffer(0)
{
}