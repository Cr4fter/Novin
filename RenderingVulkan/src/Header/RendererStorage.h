#pragma once
#include <vector>
#include <glm\vec3.hpp>
#include "RenderingInternStructs.h"

namespace NV
{
	namespace Rendering
	{
		class RendererStorage
		{
		private: 
			VkDevice m_logicalDevice;
			std::vector<MeshData> m_meshes;
			std::vector<VkShaderModule> m_shader;
		public: 
			RendererStorage(VkDevice& logicalDevice);
			uint32_t StoreMesh(MeshData mesh);
			MeshData GetMesh(const uint32_t& index);
			bool RemoveMesh(const uint32_t& index);
			uint32_t StoreShader(VkShaderModule shaderModule);
			VkShaderModule GetShader(const uint32_t& index);
			bool RemoveShader(const uint32_t& index); 

		};
	}
}