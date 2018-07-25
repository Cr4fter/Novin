#include "ResourceManager.h"

NV::Resources::ResourceManager::ResourceManager(const std::string & dirPath)
	:m_dirPath(dirPath)
{
}

void NV::Resources::ResourceManager::Init()
{
	
}

void NV::Resources::ResourceManager::LoadFilesInDir()
{
	const stdfs::directory_iterator end{};
	for (stdfs::directory_iterator iter{ m_dirPath }; iter != end; ++iter)
	{

	}
}


