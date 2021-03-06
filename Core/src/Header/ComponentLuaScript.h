#pragma once
#include "IComponent.h"
#include "GameObject.h"
#include "glm/vec3.hpp"
extern "C"
{
#include "../lua/lua.h"
#include "../lua/lauxlib.h"
#include "../lua/lualib.h"
}
namespace NV
{
    namespace Scripting
    {
        class LuaScriptingComponent : public NV::SceneSystem::IComponent
        {
        private:
            lua_State* m_LuaInstance = nullptr;
            bool m_SkipUpdate = false;
            bool m_Started = false;
        public:

            // Geerbt �ber IComponent
            virtual void Initialize(SceneSystem::GameObject * HostObject) override;
            virtual void Update() override;
            virtual void Teardown() override;

            static int GetPosition(lua_State *L);
            //int GetPosition();
        };
    }
}