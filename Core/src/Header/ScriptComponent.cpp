#include "../Header/ComponentLuaScript.h"

typedef int(*lua_CFunction) (lua_State *L);

void NV::Scripting::LuaScriptingComponent::Initialize(NV::SceneSystem::GameObject* HostObject)
{
    m_HostObject = HostObject;

    m_LuaInstance = luaL_newstate();
    luaL_openlibs(m_LuaInstance);
    std::string luaCode = "function awake () \n print(GetPosition()) \n end";

    luaL_loadbuffer(m_LuaInstance, luaCode.c_str(), luaCode.length(), HostObject->GetName().c_str());
    lua_pcall(m_LuaInstance, 0, 0, 0);

    // --- Register Magic Functions ---

    //lua_register(m_LuaInstance, "GetPosition", GetPosition);

    lua_pushcfunction(m_LuaInstance, GetPosition);
    lua_setglobal(m_LuaInstance, "GetPosition");

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

int NV::Scripting::LuaScriptingComponent::GetPosition(lua_State *L)
{
    //lua_pushnumber(m_LuaInstance, m_HostObject->GetTransform()->GetPosition().x);
    //lua_pushnumber(m_LuaInstance, m_HostObject->GetTransform()->GetPosition().y);
    //lua_pushnumber(m_LuaInstance, m_HostObject->GetTransform()->GetPosition().z);

    

    lua_pushnumber(L, 1);
    lua_pushnumber(L, 2);
    lua_pushnumber(L, 3);
    return 3;
}