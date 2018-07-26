#include "ResourceManager.h"

NV::Resources::ResourceManager::ResourceManager(const std::string & dirPath)
	:m_dirPath(dirPath)
	, m_resLoader(nullptr)
	, m_texIndex(0)
	, m_sceneIndex(0)
{
}

void NV::Resources::ResourceManager::Init()
{
	LoadFilesInDir(m_dirPath);
}

const aiScene * NV::Resources::ResourceManager::GetScene(const uint32_t & index)
{
	return m_scenes[index];
}

NV::IRendering::RawTexData NV::Resources::ResourceManager::GetTexData(const uint32_t & index)
{
	return m_textures[index];
}

void NV::Resources::ResourceManager::LoadFilesInDir(const std::string& dirPath)
{
	const stdfs::directory_iterator end{};
	for (stdfs::directory_iterator iter{ dirPath }; iter != end; ++iter)
	{
		if (stdfs::is_directory(iter->path()))
		{
			LoadFilesInDir(iter->path().string());
		}
		else
		{
			IdentifyResource(iter->path().string());
		}
	}
}

void NV::Resources::ResourceManager::IdentifyResource(const std::string & filePath)
{
	std::string ext = NV::Base::GetExtensionOfFile(filePath);
	if (ext == "spv")
	{
		return;
	}
	if (ext == "obj" || ext == "fbx")
	{
		StoreScene(m_resLoader->LoadMesh(filePath));
		return;
	}
	if (ext == "PNG" || ext == "tga") // TODO: Make this more flexible
	{
		StoreTexture(m_resLoader->LoadTexture(filePath));
		return;
	}
}

void NV::Resources::ResourceManager::StoreScene(const aiScene * scene)
{
	m_scenes.insert(std::pair<uint32_t, const aiScene*>(m_sceneIndex, scene));
	m_sceneIndex++;
}

void NV::Resources::ResourceManager::StoreTexture(NV::IRendering::RawTexData texData)
{
	m_textures.insert(std::pair<uint32_t, NV::IRendering::RawTexData>(m_texIndex, texData));
	m_texIndex++;
}

void NV::Resources::ResourceManager::RemoveScene(const uint32_t & index)
{
	m_scenes.erase(index);
}

void NV::Resources::ResourceManager::RemoveTexture(const uint32_t & index)
{
	m_textures.erase(index);
}


