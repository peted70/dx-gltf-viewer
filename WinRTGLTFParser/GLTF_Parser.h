#ifndef _GLTF_PARSER_H
#define _GLTF_PARSER_H

#include <istream>

namespace WinRTGLTFParser
{
	using namespace Windows::Storage::Streams;
	using namespace Platform;
	using namespace std;

	String^ ToStringHat(char* ch);

	public ref class GLTF_MaterialData sealed
	{
	internal:
		GLTF_MaterialData(const MaterialData& data)
		{
			MaterialName = ToStringHat(const_cast<char *>(data.MaterialName));
			emmissiveFactor = ref new Array<float>(3);
			emmissiveFactor[0] = data.emmissiveFactor[0];
			emmissiveFactor[1] = data.emmissiveFactor[1];
			emmissiveFactor[2] = data.emmissiveFactor[2];

			Pbrmetallicroughness_Basecolortexture = data.Pbrmetallicroughness_Basecolortexture;
			Pbrmetallicroughness_Metallicroughnesstexture = data.Pbrmetallicroughness_Metallicroughnesstexture;
			Normaltexture = data.Normaltexture;
			Occlusiontexture = data.Occlusiontexture;
			Emissivetexture = data.Emissivetexture;
		}

	public:
		property String^ MaterialName;
		property Array<float>^ emmissiveFactor;

		property unsigned int Pbrmetallicroughness_Basecolortexture;
		property unsigned int Pbrmetallicroughness_Metallicroughnesstexture;
		property unsigned int Normaltexture;
		property unsigned int Occlusiontexture;
		property unsigned int Emissivetexture;
	};

	public ref class GLTF_TextureData sealed
	{
	internal:
		GLTF_TextureData(const TextureData& data)
		{
			pSysMem = (IntPtr)(void *)data.pSysMem;
			DataSize = data.dataSize;
			ImgWidth = data.imgWidth;
			ImgHeight = data.imgHeight;
		}

	public:
		property IntPtr pSysMem;
		property unsigned int DataSize;
		property unsigned int ImgWidth;
		property unsigned int ImgHeight;
	};

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
		property String^ BufferContentType;
		property unsigned int Count;
	};

	public ref class GLTF_BufferData sealed
	{
	internal:
		GLTF_BufferData(const BufferData& data)
		{
			_subData = ref new GLTF_SubresourceData();

			_subData->ByteWidth = data.desc.ByteWidth;
			_subData->BindFlags = data.desc.BindFlags;
			_subData->CPUAccessFlags = data.desc.CPUAccessFlags;
			_subData->MiscFlags = data.desc.MiscFlags;
			_subData->StructureByteStride = data.desc.StructureByteStride;

			_bufDesc = ref new GLTF_BufferDesc();

			_bufDesc->pSysMem = (IntPtr)(void *)(data.subresource.pSysMem);
			_bufDesc->SysMemPitch = data.subresource.SysMemPitch;
			_bufDesc->SysMemSlicePitch = data.subresource.SysMemSlicePitch;
			_bufDesc->BufferContentType = ToStringHat(const_cast<char *>(data.desc.BufferContentType));

			_bufDesc->Count = data.desc.Count;
		}

	public:
		property GLTF_SubresourceData^ SubResource 
		{
			GLTF_SubresourceData^ get() { return _subData; }
		}

		property GLTF_BufferDesc^ BufferDescription
		{
			GLTF_BufferDesc^ get() { return _bufDesc; }
		}

	private:
		GLTF_SubresourceData^ _subData;
		GLTF_BufferDesc^ _bufDesc;
	};

	public delegate void BufferEventHandler(Platform::Object^ sender, GLTF_BufferData^);
	public delegate void TextureEventHandler(Platform::Object^ sender, GLTF_TextureData^);
	public delegate void MaterialEventHandler(Platform::Object^ sender, GLTF_MaterialData^);

	public ref class GLTF_Parser sealed
    {
    public:
		GLTF_Parser();

		event BufferEventHandler^ OnBufferEvent;
		event TextureEventHandler^ OnTextureEvent;
		event MaterialEventHandler^ OnMaterialEvent;

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