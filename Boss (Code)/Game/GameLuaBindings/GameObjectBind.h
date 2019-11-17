#ifndef __GAMEOBJECTBIND_H
#define __GAMEOBJECTBIND_H

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

#include "GameObject.h"

namespace LuaBinding
{
    static void GameObjectBind(lua_State* pLuaState)
    {
        luabridge::getGlobalNamespace(pLuaState)
            // GameObject Class
            .beginClass<GameObject>("GameObject")
                .addConstructor <void (*)(void)>()
                // Transform
                .addFunction("getX", (float (GameObject::*)()) &GameObject::getX)
                .addFunction("setX", (void (GameObject::*)(float)) &GameObject::setX)
                .addFunction("getY", (float (GameObject::*)()) &GameObject::getY)
                .addFunction("setY", (void (GameObject::*)(float)) &GameObject::setY)
                .addFunction("getXVelocity", (float (GameObject::*)()) &GameObject::getXVelocity)
                .addFunction("setXVelocity", (void (GameObject::*)(float)) &GameObject::setXVelocity)
                .addFunction("getYVelocity", (float (GameObject::*)()) &GameObject::getYVelocity)
                .addFunction("setYVelocity", (void (GameObject::*)(float)) &GameObject::setYVelocity)
                // Properties
                .addFunction("getHealth", (int (GameObject::*)()) &GameObject::getHealth)
                .addFunction("setHealth", (void (GameObject::*)(int)) &GameObject::setHealth)
                .addFunction("getMaxHealth", (int (GameObject::*)()) &GameObject::getMaxHealth)
                .addFunction("setMaxHealth", (void (GameObject::*)(int)) &GameObject::setMaxHealth)
                .addFunction("getRadius", (float (GameObject::*)()) &GameObject::getRadius)
                .addFunction("setRadius", (void (GameObject::*)(float)) &GameObject::setRadius)
                // State
                .addFunction("getState", (std::string (GameObject::*)()) &GameObject::getState)
                .addFunction("setState", (void (GameObject::*)(std::string)) &GameObject::setState)
            .endClass();
    }
}

#endif // __GAMEOBJECTBIND_H
