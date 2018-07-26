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

NV::Rendering::MeshData NV::Rendering::RendererStorage::GetMesh(const uint32_t & index)
{
	return MeshData();
}

bool NV::Rendering::RendererStorage::RemoveMesh(const uint32_t & index)
{
	if (index > m_meshes.size())
	{
		return false;
	}
	m_meshes.at(index).Release();
	m_meshes.erase(m_meshes.begin() + index);
}

uint32_t NV::Rendering::RendererStorage::StoreShader(VkShaderModule shaderModule)
{
	m_shader.push_back(shaderModule);
	return m_shader.size();
}

VkShaderModule NV::Rendering::RendererStorage::GetShader(const uint32_t & index)
{
	return VkShaderModule();
}

bool NV::Rendering::RendererStorage::RemoveShader(const uint32_t & index)
{
	if (index > m_shader.size())
	{
		return false; 
	}
	vkDestroyShaderModule(m_logicalDevice, m_shader.at(index), nullptr);
	m_shader.erase(m_shader.begin() + index);
	return true; 
}
