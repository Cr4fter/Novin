#include "pch.h"
#include "BaseFunctions.h"

TEST(BaseFunctions, ReadFileSizeCheck) {
	std::vector<char> buffer = NV::Base::ReadFile("../Demoproject//shaders//frag.spv", std::ios::binary);
	
	EXPECT_NE(buffer.size(), 0);
}

TEST(BaseFunctions, GetExtensionOfFileCheck)
{
	std::string str = NV::Base::GetExtensionOfFile("test.x.obj"); 
	std::string checkStr = "obj";
	EXPECT_STREQ(str.c_str(), checkStr.c_str());
}