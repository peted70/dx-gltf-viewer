#pragma once

#include "Common/ViewModelBase.h"

using namespace Common;

class Observable;

class Observer
{
public:
	virtual ~Observer() = 0;
	virtual void OnNotify(const Observable& data) const = 0;
};

class Observable
{
public:
	virtual void Notify(const Observable& data) = 0;
};

// Hack - will replace with signals/slots
//
class NotificationManager
{
public:
	static NotificationManager& Instance()
	{
		static NotificationManager instance;
		return instance;
	}
	NotificationManager(NotificationManager const&) = delete;
	void operator=(NotificationManager const&) = delete;

	void Register(Observer *observer)
	{
		_list.push_back(observer);
	}
	void Unregister(Observer *observer)
	{
		auto iter = std::find(_list.begin(), _list.end(), observer);
		if (iter != _list.end())
		{
			_list.erase(iter);
		}
	}

	void Notify(const Observable& data)
	{
		for (auto observer : _list)
		{
			observer->OnNotify(data);
		}
	}

private:
	NotificationManager();
	std::vector<Observer*> _list;
};
