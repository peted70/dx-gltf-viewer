#pragma once

#include <boost\di.hpp>
#include <iostream>

using namespace std;
namespace di = boost::di;

class Container
{
public:
	static Container& Instance()
	{
		static Container instance;
		return instance;
	}

	template<class T>
	T Create()
	{
		return injector.create<T>();
	}

	shared_ptr<DirectXPageViewModelData> ResolveDirectXPageViewModelData()
	{
		if (_dxPageVMData == nullptr)
			_dxPageVMData = make_shared<DirectXPageViewModelData>();
		return _dxPageVMData;
	}

private:
	Container() 
		//:
		//injector(di::make_injector(di::bind<IInterface>().to<MyInterfaceImplementation>().in(di::singleton)))
	{
	}
	shared_ptr<DirectXPageViewModelData> _dxPageVMData;
	//di::injector<DirectXPageViewModelData> injector;
};


