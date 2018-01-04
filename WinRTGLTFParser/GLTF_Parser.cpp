#include "stdafx.h"
#include "GLTF_Parser.h"
#include <fstream>

using namespace Platform;
using namespace WinRTGLTFParser;

GLTF_Parser::GLTF_Parser()
{
}

String^ ToStringHat(char* ch)
{
	std::string s_str = std::string(ch);
	std::wstring wid_str = std::wstring(s_str.begin(), s_str.end());
	const wchar_t* w_char = wid_str.c_str();
	String^ p_string = ref new String(w_char);
	return p_string;
}

void GLTF_Parser::ParseFile(String^ Filename)
{
	std::ifstream infile(Filename->Data(), std::ios::binary);

	if (infile.fail())
	{
		throw Platform::Exception::CreateException(E_FAIL);
	}

	::ParseFile(infile, [this](const BufferData& data)
	{
		auto bd = ref new GLTF_BufferData(data);
		OnBufferEvent(this, bd);
	});

	infile.close();
}
