#ifndef __INPUTSYSTEMBIND_H
#define __INPUTSYSTEMBIND_H

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

// InputSystem
#include "InputSystem.h"

namespace LuaBinding
{
    static void InputSystemBind(lua_State* pLuaState)
    {
        luabridge::getGlobalNamespace(pLuaState)
            .beginClass<InputSystem>("InputSystem")
                .addConstructor <void (*)(void)>()
                // TODO: more bindings
                .addFunction("getKeyboard", (Keyboard* (InputSystem::*)()) &InputSystem::getKeyboard)
                .addFunction("getMouse", (Mouse* (InputSystem::*)()) &InputSystem::getMouse)
                .addFunction("getGamePadCount", (int (InputSystem::*)()) &InputSystem::getGamePadCount)
                .addFunction("getGamePad", (GamePad* (InputSystem::*)(int)) &InputSystem::getGamePad)
            .endClass();
    }
}

#endif // __INPUTSYSTEMBIND_H
