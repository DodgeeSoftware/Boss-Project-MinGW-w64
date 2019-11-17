#ifndef __BULLETBIND_H
#define __BULLETBIND_H

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

#include "Bullet.h"

namespace LuaBinding
{
    static void BulletBind(lua_State* pLuaState)
    {
        luabridge::getGlobalNamespace(pLuaState)
            .beginClass<Bullet>("Bullet")
            .endClass();
    }
}

#endif // __BULLETBIND_H
