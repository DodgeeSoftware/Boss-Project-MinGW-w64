#ifndef __MOUSEBIND_H
#define __MOUSEBIND_H

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

#include "Mouse.h"

namespace LuaBinding
{
    static void MouseBind(lua_State* pLuaState)
    {
        luabridge::getGlobalNamespace(pLuaState)
            // Mouse Class
            .beginClass<Mouse>("Mouse")
                .addConstructor <void (*)(void)>()
                .addFunction("getX", (double (Mouse::*)()) &Mouse::getX)
                .addFunction("getY", (double (Mouse::*)()) &Mouse::getY)
                .addFunction("setPosition", (void (Mouse::*)(float, float)) &Mouse::setPosition)
                .addFunction("isLeftMouseButtonPressed", (bool (Mouse::*)()) &Mouse::isLeftMouseButtonPressed)
                .addFunction("isMiddleMouseButtonPressed", (bool (Mouse::*)()) &Mouse::isMiddleMouseButtonPressed)
                .addFunction("isRightMouseButtonPressed", (bool (Mouse::*)()) &Mouse::isRightMouseButtonPressed)
                .addFunction("isLeftButtonToggled", (bool (Mouse::*)()) &Mouse::isLeftButtonToggled)
                .addFunction("isMiddleButtonToggled", (bool (Mouse::*)()) &Mouse::isMiddleButtonToggled)
                .addFunction("isRightButtonToggled", (bool (Mouse::*)()) &Mouse::isRightButtonToggled)
                .addFunction("isVisible", (bool (Mouse::*)()) &Mouse::isVisible)
                .addFunction("setVisibility", (bool (Mouse::*)()) &Mouse::setVisibility)
            .endClass();
        // Globals
        luabridge::push(pLuaState, GLFW_MOUSE_BUTTON_1);
        lua_setglobal(pLuaState, "GLFW_MOUSE_BUTTON_1");
        luabridge::push(pLuaState, GLFW_MOUSE_BUTTON_2);
        lua_setglobal(pLuaState, "GLFW_MOUSE_BUTTON_2");
        luabridge::push(pLuaState, GLFW_MOUSE_BUTTON_3);
        lua_setglobal(pLuaState, "GLFW_MOUSE_BUTTON_3");
        luabridge::push(pLuaState, GLFW_MOUSE_BUTTON_4);
        lua_setglobal(pLuaState, "GLFW_MOUSE_BUTTON_4");
        luabridge::push(pLuaState, GLFW_MOUSE_BUTTON_5);
        lua_setglobal(pLuaState, "GLFW_MOUSE_BUTTON_5");
        luabridge::push(pLuaState, GLFW_MOUSE_BUTTON_6);
        lua_setglobal(pLuaState, "GLFW_MOUSE_BUTTON_6");
        luabridge::push(pLuaState, GLFW_MOUSE_BUTTON_7);
        lua_setglobal(pLuaState, "GLFW_MOUSE_BUTTON_7");
        luabridge::push(pLuaState, GLFW_MOUSE_BUTTON_LEFT);
        lua_setglobal(pLuaState, "GLFW_MOUSE_BUTTON_LEFT");
        luabridge::push(pLuaState, GLFW_MOUSE_BUTTON_RIGHT);
        lua_setglobal(pLuaState, "GLFW_MOUSE_BUTTON_RIGHT");
        luabridge::push(pLuaState, GLFW_MOUSE_BUTTON_MIDDLE);
        lua_setglobal(pLuaState, "GLFW_MOUSE_BUTTON_MIDDLE");
        luabridge::push(pLuaState, GLFW_RELEASE);
        lua_setglobal(pLuaState, "GLFW_RELEASE");
        luabridge::push(pLuaState, GLFW_PRESS);
        lua_setglobal(pLuaState, "GLFW_PRESS");
        luabridge::push(pLuaState, GLFW_REPEAT);
        lua_setglobal(pLuaState, "GLFW_REPEAT");
    }
}

#endif // __MOUSEBIND_H
