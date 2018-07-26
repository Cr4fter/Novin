#include "EngineState.h"
#include <iostream>
#include "Path.hpp"

NV::Core::EngineState::EngineState(const std::string PathToProject) : m_IsRunning(true)
{
    const std::string PathToProjectWithConfig = Tools::Path::Combine(PathToProject, "ProjectConfig.ini");

    m_ProjectSettings = new Tools::iniContainer(PathToProjectWithConfig);
    std::cout << m_ProjectSettings->GetValue("ProjectName") << std::endl;
    std::string PersistentPath = Tools::Path::GetPersistantDataPath(m_ProjectSettings->GetValue("ProjectName"));
    std::cout << PersistentPath << std::endl;
    if (!Tools::Path::dirExists(PersistentPath))
    {
        Tools::Path::CreateDir(PersistentPath);
    }
    m_UserConfig = new Tools::iniContainer(Tools::Path::Combine(PersistentPath, "UserData.ini"));
}

NV::Core::EngineState::~EngineState()
{
    delete m_UserConfig;
}

std::unique_ptr<NV::Tools::iniContainer> NV::Core::EngineState::GetUserConfig()
{
    return std::unique_ptr<Tools::iniContainer>(m_UserConfig);
}

std::unique_ptr<NV::Tools::iniContainer> NV::Core::EngineState::GetProjectConfig()
{
    return std::unique_ptr<Tools::iniContainer>(m_ProjectSettings);
}

bool NV::Core::EngineState::GetIsRunning() const
{
    return m_IsRunning;
}

void NV::Core::EngineState::SetIsRunning()
{
    m_IsRunning = false;
}
