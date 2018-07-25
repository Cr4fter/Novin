#pragma once
#pragma region Internal Includes
#include "BaseFunctions.h"
#include "GlobalStructs.h"
#pragma endregion //Internal Includes
#pragma region External Includes
#include "assimp/Importer.hpp"
#include "assimp/scene.h"
#include <string>
#pragma endregion //External Includes

namespace NV
{
	namespace Resources
	{
		class ResourceLoader
		{
		private:

		public: 
			ResourceLoader();
			void LoadShader(const std::string& shaderPath); 
			const aiScene* LoadMesh(const std::string& meshPath);
			NV::IRendering::RawTexData LoadTexture(const std::string& texPath);
		};
	}
}