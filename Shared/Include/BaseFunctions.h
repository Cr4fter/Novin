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
		/**
		 * reads out a file and returns it as char vector
		 * @param filePath The path of the file you want to read out
		 * @param mode The mode describes which data format you want to read out like binary, default = std::ios::in. 
		 * @return A vector of chars.
		 */
		static std::vector<char> ReadFile(const std::string& filePath, const int& mode = std::ios::in);
	}
}