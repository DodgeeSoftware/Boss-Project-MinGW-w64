#ifndef __PHYSICSBIND_H
#define __PHYSICSBIND_H

// C/C++ Includes
#include <string>

// Lua
extern "C"
{
    #include "lua.h"
    #include "lualib.h"
    #include "lauxlib.h"
}

// LuaBridge
#include <LuaBridge/LuaBridge.h>

#include "GamePhysics.h"

namespace LuaBinding
{
    static void PhysicsBind(lua_State* pLuaState)
    {
        luabridge::getGlobalNamespace(pLuaState)
            .beginNamespace ("Physics")
            .addFunction("isCollision",(bool(*)(float, float, float, float, float, float)) &Physics::isCollision)
            .endNamespace ();
    }
}

#endif // __PHYSICSBIND_H
