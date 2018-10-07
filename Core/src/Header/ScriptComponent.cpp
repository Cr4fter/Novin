#include "../Header/ComponentLuaScript.h"

void NV::Scripting::LuaScriptingComponent::Initialize(NV::SceneSystem::GameObject* HostObject)
{
    m_HostObject = HostObject;

    m_LuaInstance = luaL_newstate();
    luaL_openlibs(m_LuaInstance);
    std::string luaCode = "function awake () \n print(\"Lua Awake\") \n end";

    luaL_loadbuffer(m_LuaInstance, luaCode.c_str(), luaCode.length(), HostObject->GetName().c_str());
    lua_pcall(m_LuaInstance, 0, 0, 0);


    lua_getglobal(m_LuaInstance, "Awake");
    lua_pcall(m_LuaInstance, 0, 0, 0);
}

void NV::Scripting::LuaScriptingComponent::Update()
{
    if (!m_Started)
    {
        lua_getglobal(m_LuaInstance, "Start");
        lua_pcall(m_LuaInstance, 0, 0, 0);
        m_Started = true;
    }

    if (!m_SkipUpdate)
    {
        lua_getglobal(m_LuaInstance, "Update");
        if (lua_pcall(m_LuaInstance, 0, 0, 0) != LUA_OK)
        {
            //Script has a faulty or no Update Function. Skipping call next frames!
            m_SkipUpdate = true;
        }
    }
}

void NV::Scripting::LuaScriptingComponent::Teardown()
{
    lua_getglobal(m_LuaInstance, "Teardown");
    lua_pcall(m_LuaInstance, 0, 0, 0);

    lua_close(m_LuaInstance);
}
