#ifndef __PLAYERBIND_H
#define __PLAYERBIND_H

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

#include "Player.h"

namespace LuaBinding
{
    static void PlayerBind(lua_State* pLuaState)
    {
        luabridge::getGlobalNamespace(pLuaState)
            .beginClass<Player>("Player")
                .addConstructor <void (*)(void)>()
                // Transform
                .addFunction("getX", (float(Player::*)())& Player::getX)
                .addFunction("getY", (float(Player::*)())& Player::getY)
                .addFunction("getXVelocity", (float(Player::*)())& Player::getXVelocity)
                .addFunction("getYVelocity", (float(Player::*)())& Player::getYVelocity)
                .addFunction("setX", (void(Player::*)(float))& Player::setX)
                .addFunction("setY", (void(Player::*)(float))& Player::setY)
                .addFunction("setXVelocity", (void(Player::*)(float))& Player::setXVelocity)
                .addFunction("setYVelocity", (void(Player::*)(float))& Player::setYVelocity)
                // State
                .addFunction("getState", (std::string(Player::*)())& Player::getState)
                .addFunction("setState", (void(Player::*)(std::string))& Player::setState)
                // Properties
                .addFunction("getHealth", (int(Player::*)())& Player::getHealth)
                .addFunction("getMaxHealth", (int(Player::*)())& Player::getMaxHealth)
                .addFunction("setHealth", (void(Player::*)(int))& Player::setHealth)
                .addFunction("setMaxHealth", (void(Player::*)(int))& Player::setMaxHealth)
                .addFunction("setUnderAttack", (void(Player::*)(bool))& Player::setUnderAttack)
                .addFunction("isUnderAttack", (bool(Player::*)())& Player::isUnderAttack)
                .addFunction("setDead", (void(Player::*)(bool))& Player::setDead)
                .addFunction("isDead", (bool(Player::*)())& Player::isDead)
                .addFunction("setImmuneToDamage", (void(Player::*)(bool))& Player::setImmuneToDamage)
                .addFunction("isImmuneToDamage", (bool(Player::*)())& Player::isImmuneToDamage)
                .addFunction("getSpeed", (float(Player::*)())& Player::getSpeed)
                .addFunction("setSpeed", (void(Player::*)(float))& Player::setSpeed)
                .addFunction("getRadius", (float (Player::*)()) &Player::getRadius)
                .addFunction("setRadius", (void (Player::*)(float)) &Player::setRadius)
            .endClass();
    }
}

#endif // __PLAYERBIND_H
