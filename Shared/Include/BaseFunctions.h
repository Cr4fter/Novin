#pragma once
#pragma region Internal Includes
#pragma endregion //Internal Includes
#pragma region External Includes
#include <string>
#include <fstream>
#include <vector>
#pragma endregion //External Includes

namespace NV
{
	namespace Base
	{ 
		static std::vector<char> ReadFile(const std::string& filePath);
	}
}