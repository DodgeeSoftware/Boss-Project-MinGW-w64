#ifndef __CONFIGBIND_H
#define __CONFIGBIND_H

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

#include "GameConfig.h"

namespace LuaBinding
{
    static void GameConfigBind(lua_State* pLuaState)
    {
        luabridge::getGlobalNamespace(pLuaState)
            .beginClass<GameConfig>("GameConfig")
                .addConstructor <void (*)(void)>()
                .addFunction("getWidth", (int(GameConfig::*)()) &GameConfig::getWidth)
                .addFunction("setWidth", (void(GameConfig::*)(int)) &GameConfig::setWidth)
                .addFunction("getHeight", (int(GameConfig::*)()) &GameConfig::getHeight)
                .addFunction("setHeight", (void(GameConfig::*)(int)) &GameConfig::setHeight)
            .endClass();
    }
}

#endif // __CONFIGBIND_H
