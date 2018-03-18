#include "pch.h"
#include "DirectXPageViewModelData.h"

DirectXPageViewModelData::DirectXPageViewModelData()
{}

void DirectXPageViewModelData::Notify(const Observable & data)
{
	NotificationManager::Instance().Notify(data);
}
