#include "pch.h"
#include "SceneContext.h"
#include <D3D11_2.h>

SceneContext::SceneContext(ID3D11DeviceContext2 *context) :
	_context(context)
{
}

SceneContext::~SceneContext()
{
}
