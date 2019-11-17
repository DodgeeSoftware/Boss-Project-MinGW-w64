#ifndef __GAMEPADBIND_H
#define __GAMEPADBIND_H

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

// GamePad
#include "GamePad.h"

namespace LuaBinding
{
    static void GamePadBind(lua_State* pLuaState)
    {
        luabridge::getGlobalNamespace(pLuaState)
            // GamePad Class
            .beginClass<GamePad>("GamePad")
                .addConstructor <void (*)(void)>()
                // General Controller Functions
                .addFunction("getName", (const char* (GamePad::*)()) &GamePad::getName)
                .addFunction("getAxisCount", (int (GamePad::*)()) &GamePad::getAxisCount)
                .addFunction("getAxisX", (float (GamePad::*)(int)) &GamePad::getAxisX)
                .addFunction("getAxisY", (float (GamePad::*)(int)) &GamePad::getAxisY)
                .addFunction("getButtonCount", (int (GamePad::*)()) &GamePad::getButtonCount )
                .addFunction("isGamePadAxis", (bool (GamePad::*)(int)) &GamePad::isGamePadAxis)
                .addFunction("isGamePadButton", (bool (GamePad::*)(int)) &GamePad::isGamePadButton)
                .addFunction("isButtonPressed", (bool (GamePad::*)(int)) &GamePad::isButtonPressed)
                .addFunction("isButtonToggled", (bool (GamePad::*)(int)) &GamePad::isButtonToggled)
                .addFunction("isPressedUp", (bool (GamePad::*)()) &GamePad::isPressedUp)
                .addFunction("isPressedDown", (bool (GamePad::*)()) &GamePad::isPressedDown)
                .addFunction("isPressedLeft", (bool (GamePad::*)()) &GamePad::isPressedLeft)
                .addFunction("isPressedRight", (bool (GamePad::*)()) &GamePad::isPressedRight)
                .addFunction("isToggleUp", (bool (GamePad::*)()) &GamePad::isToggleUp)
                .addFunction("isToggleDown", (bool (GamePad::*)()) &GamePad::isToggleDown)
                .addFunction("isToggleLeft", (bool (GamePad::*)()) &GamePad::isToggleLeft)
                .addFunction("isToggleRight", (bool (GamePad::*)()) &GamePad::isToggleRight)
                 // XBOX Controller Functions
                .addFunction("getLeftStickXAxis", (float (GamePad::*)(int)) &GamePad::getLeftStickXAxis)
                .addFunction("getLeftStickYAxis", (float (GamePad::*)(int)) &GamePad::getLeftStickYAxis)
                .addFunction("getRightStickXAxis", (float (GamePad::*)(int)) &GamePad::getRightStickXAxis)
                .addFunction("getRightStickYAxis", (float (GamePad::*)(int)) &GamePad::getRightStickYAxis)
                .addFunction("getDPadXAxis", (float (GamePad::*)(int)) &GamePad::getDPadXAxis)
                .addFunction("getDPadYAxis", (float (GamePad::*)(int)) &GamePad::getDPadYAxis)
                .addFunction("getTriggers", (float (GamePad::*)(int)) &GamePad::getTriggers)
                .addFunction("getLeftTrigger", (float (GamePad::*)(int)) &GamePad::getLeftTrigger)
                .addFunction("getRightTrigger", (float (GamePad::*)(int)) &GamePad::getRightTrigger)
                .addFunction("isAButtonPressed", (bool (GamePad::*)()) &GamePad::isAButtonPressed)
                .addFunction("isAButtonToggled", (bool (GamePad::*)()) &GamePad::isAButtonToggled)
                .addFunction("isBButtonPressed", (bool (GamePad::*)()) &GamePad::isBButtonPressed)
                .addFunction("isBButtonToggled", (bool (GamePad::*)()) &GamePad::isBButtonToggled)
                .addFunction("isXButtonPressed", (bool (GamePad::*)()) &GamePad::isXButtonPressed)
                .addFunction("isXButtonToggled", (bool (GamePad::*)()) &GamePad::isXButtonToggled)
                .addFunction("isYButtonPressed", (bool (GamePad::*)()) &GamePad::isYButtonPressed)
                .addFunction("isYButtonToggled", (bool (GamePad::*)()) &GamePad::isYButtonToggled)
                .addFunction("isLeftBumperButtonPressed", (bool (GamePad::*)()) &GamePad::isLeftBumperButtonPressed)
                .addFunction("isLeftBumperButtonToggled", (bool (GamePad::*)()) &GamePad::isLeftBumperButtonToggled)
                .addFunction("isRightBumperButtonPressed", (bool (GamePad::*)()) &GamePad::isRightBumperButtonPressed)
                .addFunction("isRightBumperButtonToggled", (bool (GamePad::*)()) &GamePad::isRightBumperButtonToggled)
                .addFunction("isBackButtonPressed", (bool (GamePad::*)()) &GamePad::isBackButtonPressed)
                .addFunction("isBackButtonToggled", (bool (GamePad::*)()) &GamePad::isBackButtonToggled)
                .addFunction("isStartButtonPressed", (bool (GamePad::*)()) &GamePad::isStartButtonPressed)
                .addFunction("isStartButtonToggled", (bool (GamePad::*)()) &GamePad::isStartButtonToggled)
                .addFunction("isLeftStickButtonPressed", (bool (GamePad::*)()) &GamePad::isLeftStickButtonPressed)
                .addFunction("isLeftStickButtonToggled", (bool (GamePad::*)()) &GamePad::isLeftStickButtonToggled)
                .addFunction("isRightStickButtonPressed", (bool (GamePad::*)()) &GamePad::isRightStickButtonPressed)
                .addFunction("isRightStickButtonToggled", (bool (GamePad::*)()) &GamePad::isRightStickButtonToggled)
                .addFunction("isDPadUpButtonPressed", (bool (GamePad::*)()) &GamePad::isDPadUpButtonPressed)
                .addFunction("isDPadUpButtonToggled", (bool (GamePad::*)()) &GamePad::isDPadUpButtonToggled)
                .addFunction("isDPadDownButtonPressed", (bool (GamePad::*)()) &GamePad::isDPadDownButtonPressed)
                .addFunction("isDPadDownButtonToggled", (bool (GamePad::*)()) &GamePad::isDPadDownButtonToggled)
                .addFunction("isDPadLeftButtonPressed", (bool (GamePad::*)()) &GamePad::isDPadLeftButtonPressed)
                .addFunction("isDPadLeftButtonToggled", (bool (GamePad::*)()) &GamePad::isDPadLeftButtonToggled)
                .addFunction("isDPadRightButtonPressed", (bool (GamePad::*)()) &GamePad::isDPadRightButtonPressed)
                .addFunction("isDPadRightButtonToggled", (bool (GamePad::*)()) &GamePad::isDPadRightButtonToggled)
                .addFunction("isDPadRightButtonToggled", (bool (GamePad::*)()) &GamePad::isDPadRightButtonToggled)
                .addFunction("isXboxButtonPressed", (bool (GamePad::*)()) &GamePad::isXboxButtonPressed)
                .addFunction("isXboxButtonToggled", (bool (GamePad::*)()) &GamePad::isXboxButtonToggled)
            .endClass();
            // Globals
            luabridge::push(pLuaState, GLFW_JOYSTICK_1);
            lua_setglobal(pLuaState, "GLFW_JOYSTICK_1");
            luabridge::push(pLuaState, GLFW_JOYSTICK_2);
            lua_setglobal(pLuaState, "GLFW_JOYSTICK_2");
            luabridge::push(pLuaState, GLFW_JOYSTICK_3);
            lua_setglobal(pLuaState, "GLFW_JOYSTICK_3");
            luabridge::push(pLuaState, GLFW_JOYSTICK_4);
            lua_setglobal(pLuaState, "GLFW_JOYSTICK_4");
            luabridge::push(pLuaState, GLFW_JOYSTICK_5);
            lua_setglobal(pLuaState, "GLFW_JOYSTICK_5");
            luabridge::push(pLuaState, GLFW_JOYSTICK_6);
            lua_setglobal(pLuaState, "GLFW_JOYSTICK_6");
            luabridge::push(pLuaState, GLFW_JOYSTICK_7);
            lua_setglobal(pLuaState, "GLFW_JOYSTICK_7");
            luabridge::push(pLuaState, GLFW_JOYSTICK_8);
            lua_setglobal(pLuaState, "GLFW_JOYSTICK_8");
            luabridge::push(pLuaState, GLFW_JOYSTICK_9);
            lua_setglobal(pLuaState, "GLFW_JOYSTICK_9");
            luabridge::push(pLuaState, GLFW_JOYSTICK_10);
            lua_setglobal(pLuaState, "GLFW_JOYSTICK_10");
            luabridge::push(pLuaState, GLFW_JOYSTICK_11);
            lua_setglobal(pLuaState, "GLFW_JOYSTICK_11");
            luabridge::push(pLuaState, GLFW_JOYSTICK_12);
            lua_setglobal(pLuaState, "GLFW_JOYSTICK_12");
            luabridge::push(pLuaState, GLFW_JOYSTICK_13);
            lua_setglobal(pLuaState, "GLFW_JOYSTICK_13");
            luabridge::push(pLuaState, GLFW_JOYSTICK_14);
            lua_setglobal(pLuaState, "GLFW_JOYSTICK_14");
            luabridge::push(pLuaState, GLFW_JOYSTICK_15);
            lua_setglobal(pLuaState, "GLFW_JOYSTICK_15");
            luabridge::push(pLuaState, GLFW_JOYSTICK_LAST);
            lua_setglobal(pLuaState, "GLFW_JOYSTICK_LAST");
            luabridge::push(pLuaState, GLFW_RELEASE);
            lua_setglobal(pLuaState, "GLFW_RELEASE");
            luabridge::push(pLuaState, GLFW_PRESS);
            lua_setglobal(pLuaState, "GLFW_PRESS");
            luabridge::push(pLuaState, GLFW_REPEAT);
            lua_setglobal(pLuaState, "GLFW_REPEAT");
            luabridge::push(pLuaState, 0);
            lua_setglobal(pLuaState, "GLFW_NULL_GAMEPAD");
            luabridge::push(pLuaState, 1);
            lua_setglobal(pLuaState, "GLFW_PLAYER1_GAMEPAD");
            luabridge::push(pLuaState, 2);
            lua_setglobal(pLuaState, "GLFW_PLAYER2_GAMEPAD");
            luabridge::push(pLuaState, 3);
            lua_setglobal(pLuaState, "GLFW_PLAYER3_GAMEPAD");
            luabridge::push(pLuaState, 4);
            lua_setglobal(pLuaState, "GLFW_PLAYER4_GAMEPAD");
            luabridge::push(pLuaState, 5);
            lua_setglobal(pLuaState, "GLFW_PLAYER5_GAMEPAD");
            luabridge::push(pLuaState, 6);
            lua_setglobal(pLuaState, "GLFW_PLAYER6_GAMEPAD");
            luabridge::push(pLuaState, 7);
            lua_setglobal(pLuaState, "GLFW_PLAYER7_GAMEPAD");
            luabridge::push(pLuaState, 8);
            lua_setglobal(pLuaState, "GLFW_PLAYER8_GAMEPAD");
    }
}

#endif // __GAMEPADBIND_H
