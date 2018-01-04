#ifndef _GLTF_PARSER_H
#define _GLTF_PARSER_H

#include <istream>

namespace WinRTGLTFParser
{
	using namespace Windows::Storage::Streams;
	using namespace Platform;
	using namespace std;

	public ref class GLTF_SubresourceData sealed
	{
	public:
		property unsigned int ByteWidth;
		property unsigned int BindFlags;
		property unsigned int CPUAccessFlags;
		property unsigned int MiscFlags;
		property unsigned int StructureByteStride;
	};

	public ref class GLTF_BufferDesc sealed
	{
	public:
		property IntPtr pSysMem;
		property unsigned int SysMemPitch;
		property unsigned int SysMemSlicePitch;
	};

	public ref class GLTF_BufferData sealed
	{
	internal:
		GLTF_BufferData(const BufferData& data)
		{
			_subData.ByteWidth = data.desc.ByteWidth;
			_subData.BindFlags = data.desc.BindFlags;
			_subData.CPUAccessFlags = data.desc.CPUAccessFlags;
			_subData.MiscFlags = data.desc.MiscFlags;
			_subData.StructureByteStride = data.desc.StructureByteStride;
		}

	private:
		GLTF_SubresourceData _subData;
		GLTF_BufferDesc _bufDesc;
	};

	public delegate void BufferEventHandler(Platform::Object^ sender, GLTF_BufferData^);

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

#endif //_GLTF_PARSER_H