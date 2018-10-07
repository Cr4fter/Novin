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
			std::vector<VkPipelineLayout> m_pipelineLayouts;
		public: 
			RendererStorage(VkDevice& logicalDevice);
			uint32_t StoreMesh(MeshData mesh);
			MeshData GetMesh(const int32_t& index) const;
			bool RemoveMesh(const int32_t& index);
			uint32_t StoreShader(VkShaderModule shaderModule);
			VkShaderModule GetShader(const int32_t& index) const;
			bool RemoveShader(const int32_t& index); 
			uint32_t StoreGraphicsPipelineLayout(VkPipelineLayout pipelineLayout);
			VkPipelineLayout GetPipelineLayout(const int32_t& index) const;
			bool RemovePipeline(const int32_t& index); 
			VkDevice GetLogicalDevice() const {
				return m_logicalDevice;
			}
		};
	}
}