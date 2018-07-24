#include "pch.h"
#include "BaseFunctions.h"

TEST(BaseFunctions, ReadFileSizeCheck) {
	std::vector<char> buffer = NV::Base::ReadFile("../Demoproject//shaders//frag.spv", std::ios::binary);
	
	EXPECT_NE(buffer.size(), 0);
}