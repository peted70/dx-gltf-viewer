#pragma once

#include <functional>

using namespace WinRTGLTFParser;
using namespace std;
using namespace Platform;

ref class EventShim sealed
{
internal:
	EventShim(function<void(GLTF_BufferData^)> bcallback,
			  function<void(GLTF_MaterialData^)> mcallback,
			  function<void(GLTF_TextureData^)> tcallback,
			  function<void(GLTF_TransformData^)> tmcallback) :
		bufferCallback(move(bcallback)),
		materialCallback(move(mcallback)),
		textureCallback(move(tcallback)),
		transformCallback(move(tmcallback))
	{

	}

public:
	void OnBuffer(Platform::Object^ sender, GLTF_BufferData^ data)
	{
		bufferCallback(data);
	}
	void OnTexture(Platform::Object^ sender, GLTF_TextureData^ data)
	{
		textureCallback(data);
	}
	void OnMaterial(Platform::Object^ sender, GLTF_MaterialData^ data)
	{
		materialCallback(data);
	}
	void OnTransform(Platform::Object^ sender, GLTF_TransformData^ data)
	{
		transformCallback(data);
	}

private:
	function<void(GLTF_BufferData^)> bufferCallback;
	function<void(GLTF_TextureData^)> textureCallback;
	function<void(GLTF_MaterialData^)> materialCallback;
	function<void(GLTF_TransformData^)> transformCallback;
};