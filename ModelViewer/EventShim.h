#pragma once

#include <functional>

ref class EventShim sealed
{
internal:
	EventShim(std::function<void(WinRTGLTFParser::GLTF_BufferData^)> bcallback,
		std::function<void(WinRTGLTFParser::GLTF_TextureData^)> tcallback) :
		bufferCallback(std::move(bcallback)),
		textureCallback(std::move(tcallback))
	{

	}

public:
	void OnBuffer(Platform::Object^ sender, WinRTGLTFParser::GLTF_BufferData^ data)
	{
		bufferCallback(data);
	}
	void OnTexture(Platform::Object^ sender, WinRTGLTFParser::GLTF_TextureData^ data)
	{
		textureCallback(data);
	}

private:
	std::function<void(WinRTGLTFParser::GLTF_BufferData^)> bufferCallback;
	std::function<void(WinRTGLTFParser::GLTF_TextureData^)> textureCallback;
};