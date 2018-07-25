#pragma once
#pragma region Internal Includes
#pragma endregion //Internal Includes
#pragma region External Includes
#include <string>
#include <experimental/filesystem>
#pragma endregion //External Includes


namespace NV
{
	namespace Resources
	{
		namespace stdfs = std::experimental::filesystem;

		class ResourceManager
		{
		private:
			const std::string m_dirPath;

		public: 
			ResourceManager(const std::string& dirPath);
			void Init();
		private: 
			void LoadFilesInDir();
		};
	}
}