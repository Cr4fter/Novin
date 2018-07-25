#pragma once
#pragma region Internal Includes
#pragma endregion // Internal Includes
#include "BaseFunctions.h"
#pragma region External Includes
#include <string>
#pragma endregion //External Includes


namespace NV
{
	namespace Tools
	{
		class ShaderLoader
		{
		public:
			bool LoadFile(std::string& filePath);
		};
	}
}