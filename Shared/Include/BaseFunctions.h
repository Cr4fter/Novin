#ifndef _BASE_FUNCTIONS_H_
#define _BASE_FUNCTIONS_H_

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
		static std::vector<char> ReadFile(const std::string& filePath, const int& mode = std::ios::ate);

		static std::string GetExtensionOfFile(const std::string& str);

		static std::string GetFileName(const std::string& filePath);
	}
}
#include "BaseFunctions.hpp"
#endif //_BASE_FUNCTIONS_H_