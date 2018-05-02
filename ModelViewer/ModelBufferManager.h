#pragma once
#include "BufferCache.h"

class ModelBufferManager
{
public:
	static ModelBufferManager& Instance()
	{
		static ModelBufferManager instance;
		return instance;
	}
	ModelBufferManager(ModelBufferManager const&) = delete;
	void operator=(ModelBufferManager const&) = delete;

	BufferCache<ID3D11BufferWrapper> *CurrentBufferCache()
	{
		if (_currBufferCache == nullptr)
		{
			_currBufferCache = make_unique<BufferCache<ID3D11BufferWrapper>>();
		}
		return _currBufferCache.get();
	}

private:
	ModelBufferManager();

	unique_ptr<BufferCache<ID3D11BufferWrapper>> _currBufferCache = nullptr;
};

