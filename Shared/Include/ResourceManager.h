#pragma once
#pragma region Internal Includes
#include "BaseFunctions.h"
#include "ResourceLoader.h"
#pragma endregion //Internal Includes
#pragma region External Includes
#include <string>
#include <experimental/filesystem>
#include <map>
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
			ResourceLoader* m_resLoader;
			std::map<uint32_t, const aiScene*> m_scenes;
			std::map<uint32_t, NV::IRendering::RawTexData> m_textures;
			uint32_t m_texIndex;
			uint32_t m_sceneIndex;
		public: 
			ResourceManager(const std::string& dirPath);
			void Init();
			const aiScene* GetScene(const uint32_t& index);
			void RemoveScene(const uint32_t& index);
			void RemoveTexture(const uint32_t& index);
		private: 
			void LoadFilesInDir(const std::string& dirPath);
			void IdentifyResource(const std::string& filePath);
			void StoreScene(const aiScene* scene);
			void StoreTexture(NV::IRendering::RawTexData texData);
		};
	}
}