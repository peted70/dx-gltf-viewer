#pragma once

#include <stdafx.h>
#include <istream>
#include "../SharedGLTFParser/gltfparser.h"

namespace WinRTGLTFParser
{
	using namespace Windows::Storage::Streams;
	using namespace Platform;
	using namespace std;

	public delegate void BufferEventHandler(const BufferData&);

	public ref class GLTF_Parser sealed
    {
    public:
		GLTF_Parser();

		event BufferEventHandler^ OnBufferEvent;

		/// <summary>
		/// Will parse a .GLB file given the input filename
		/// Note. this would ideally be a stream interface passed in but since I would need
		/// to write the code to interface a WinRT stream and native C++ stream I am avoinding it
		/// for now. The native implementation uses std::istream. 
		/// </summary>
		/// <param name="Filename"></param>
		/// <returns></returns>
		void ParseFile(String^ Filename);
    };
}
