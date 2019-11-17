#ifndef __BOSSBIND
#define __BOSSBIND

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

#include "Boss.h"

namespace LuaBinding
{
    static void BossBind(lua_State* pLuaState)
    {
        luabridge::getGlobalNamespace(pLuaState)
            .beginClass<Boss>("Boss")
                .addConstructor <void (*)(void)>()
                // Transform
                .addFunction("getX", (float(Boss::*)()) &Boss::getX)
                .addFunction("getY", (float(Boss::*)()) &Boss::getY)
                .addFunction("getXVelocity", (float(Boss::*)()) &Boss::getXVelocity)
                .addFunction("getYVelocity", (float(Boss::*)())& Boss::getYVelocity)
                .addFunction("setX", (void(Boss::*)(float))& Boss::setX)
                .addFunction("setY", (void(Boss::*)(float))& Boss::setY)
                .addFunction("setXVelocity", (void(Boss::*)(float))& Boss::setXVelocity)
                .addFunction("setYVelocity", (void(Boss::*)(float))& Boss::setYVelocity)
                // State
                .addFunction("getState", (std::string(Boss::*)())& Boss::getState)
                .addFunction("setState", (void(Boss::*)(std::string))& Boss::setState)
                // Properties
                .addFunction("getHealth", (int(Boss::*)())& Boss::getHealth)
                .addFunction("getMaxHealth", (int(Boss::*)())& Boss::getMaxHealth)
                .addFunction("setHealth", (void(Boss::*)(int))& Boss::setHealth)
                .addFunction("setMaxHealth", (void(Boss::*)(int))& Boss::setMaxHealth)
                .addFunction("setUnderAttack", (void(Boss::*)(bool)) &Boss::setUnderAttack)
                .addFunction("isUnderAttack", &Boss::isUnderAttack)
                .addFunction("isDead", &Boss::isDead)
                .addFunction("setDead", &Boss::setDead)
                .addFunction("setImmuneToDamage", &Boss::setImmuneToDamage)
                .addFunction("isImmuneToDamage", (bool(Boss::*)()) &Boss::isImmuneToDamage)
                .addFunction("getSpeed", (float(Boss::*)())& Boss::getSpeed)
                .addFunction("setSpeed", (void(Boss::*)(float))& Boss::setSpeed)
                .addFunction("getRadius", (float (Boss::*)()) &Boss::getRadius)
                .addFunction("setRadius", (void (Boss::*)(float)) &Boss::setRadius)
            .endClass();
    }
}

#endif // __BOSSBIND
