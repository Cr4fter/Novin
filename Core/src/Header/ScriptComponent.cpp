#include "../Header/ComponentLuaScript.h"

void NV::Scripting::LuaScriptingComponent::Initialize(NV::SceneSystem::GameObject* HostObject)
{
    m_HostObject = HostObject;
    m_LuaInstance = luaL_newstate();
    luaL_openlibs(m_LuaInstance);
    std::string luaCode = "function awake () \n print(\"Lua Awake\") \n end";
    luaL_loadbuffer(m_LuaInstance, luaCode.c_str(), luaCode.length(), HostObject->GetName().c_str());

    lua_pcall(m_LuaInstance, 0, 0, 0);

    int error = 0;
    lua_getglobal(m_LuaInstance, "awake");
    error = lua_pcall(m_LuaInstance, 0, 0, 0);

    printf("Error %i\n", error);
    lua_getglobal(m_LuaInstance, "start");
    error = 0;

    error = lua_pcall(m_LuaInstance, 0, 0, 0);
    if (error != 0)
    {
        printf("Error Executing start: %s\n", lua_tostring(m_LuaInstance, -1));
    }

}

void NV::Scripting::LuaScriptingComponent::Update()
{
}

void NV::Scripting::LuaScriptingComponent::Teardown()
{
    lua_close(m_LuaInstance);
}
