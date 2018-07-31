#pragma once
#pragma region Internal Includes
#include "BaseFunctions.h"
#include "GlobalStructs.h"
#pragma endregion //Internal Includes
#pragma region External Includes
#include "assimp/Importer.hpp"
#include "assimp/scene.h"
#include <string>
#include <algorithm>
#pragma endregion //External Includes

namespace NV
{
	namespace Resources
	{
		class ResourceLoader
		{
		private:
			std::vector<NV::IRendering::ShaderPack> m_shaderPacks;
		public: 
			ResourceLoader();
			void LoadShader(const std::string& shaderPath, const std::string& ext); 
			const aiScene* LoadMesh(const std::string& meshPath);
			NV::IRendering::RawTexData LoadTexture(const std::string& texPath);
			inline std::vector<NV::IRendering::ShaderPack> GetShaderPacks() const {return m_shaderPacks;};
		private: 
			void IncludeShaderInPack(NV::IRendering::ShaderPack& pack, std::vector<char> shader, const std::string& ext);
		};
	}
}