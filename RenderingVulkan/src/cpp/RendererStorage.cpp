#include "../Header/RendererStorage.h"

uint32_t NV::Rendering::RendererStorage::StoreMesh(MeshData mesh)
{
	m_meshes.push_back(mesh); 
	return m_meshes.size();
}

bool NV::Rendering::RendererStorage::RemoveMesh(const uint32_t & index)
{
	//TODO: Some function to check if there is a mesh at index

	m_meshes.at(index).Release();
	m_meshes.erase(m_meshes.begin() + index);
}
