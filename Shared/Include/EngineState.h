#pragma once
#include "iniContainer.h"

namespace NV
{
    namespace Core
    {
        class EngineState
        {
            bool m_IsRunning;
            Tools::iniContainer* m_UserConfig;
            Tools::iniContainer* m_ProjectSettings;
        public:
            EngineState(std::string PathToProject);
            ~EngineState();
            std::unique_ptr<Tools::iniContainer> GetUserConfig();
            std::unique_ptr<Tools::iniContainer> GetProjectConfig();
            bool GetIsRunning() const;
            void SetIsRunning();
        };
    }
}
