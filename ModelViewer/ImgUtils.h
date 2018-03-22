#pragma once
#include <vector>

using namespace std;
using namespace Microsoft::WRL;

class ImgUtils
{
public:
	static vector<uint8_t> LoadRGBAImage(void *imgFileData, int imgFileDataSize, uint32_t& width, uint32_t& height);
};

