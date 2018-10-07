#include "../Header/RendererStorage.h"

NV::Rendering::RendererStorage::RendererStorage(VkDevice& logicalDevice)
	:m_logicalDevice(logicalDevice)
{
}

uint32_t NV::Rendering::RendererStorage::StoreMesh(MeshData mesh)
{
	m_meshes.push_back(mesh);
	return m_meshes.size();
}

NV::Rendering::MeshData NV::Rendering::RendererStorage::GetMesh(const int32_t & index) const
{
	return m_meshes.at(index);
}

bool NV::Rendering::RendererStorage::RemoveMesh(const int32_t & index)
{
	if (index > m_meshes.size() || index < 0)
	{
		return false;
	}
	m_meshes.at(index).Release();
	m_meshes.erase(m_meshes.begin() + index);
	return true;
}

uint32_t NV::Rendering::RendererStorage::StoreShader(VkShaderModule shaderModule)
{
	m_shader.push_back(shaderModule);
	return m_shader.size();
}

VkShaderModule NV::Rendering::RendererStorage::GetShader(const int32_t & index) const
{
	return m_shader.at(index);
}

bool NV::Rendering::RendererStorage::RemoveShader(const int32_t & index)
{
	if (index > m_shader.size() || index < 0)
	{
		return false;
	}
	vkDestroyShaderModule(m_logicalDevice, m_shader.at(index), nullptr);
	m_shader.erase(m_shader.begin() + index);
	return true;
}

uint32_t NV::Rendering::RendererStorage::StoreGraphicsPipelineLayout(VkPipelineLayout pipelineLayout)
{
	m_pipelineLayouts.push_back(pipelineLayout);
	return m_pipelineLayouts.size();
}

VkPipelineLayout NV::Rendering::RendererStorage::GetPipelineLayout(const int32_t & index) const
{
	return m_pipelineLayouts.at(index);
}

bool NV::Rendering::RendererStorage::RemovePipeline(const int32_t & index)
{
	if (index > m_pipelineLayouts.size() || index < 0)
	{
		return false;
	}
	vkDestroyPipelineLayout(m_logicalDevice, m_pipelineLayouts.at(index), nullptr);
	m_pipelineLayouts.erase(m_pipelineLayouts.begin() + index);
	return true;
}
