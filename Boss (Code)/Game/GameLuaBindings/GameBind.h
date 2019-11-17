#ifndef __GAMEBIND_H
#define __GAMEBIND_H

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

#include "Game.h"

namespace LuaBinding
{
    static void GameBind(lua_State* pLuaState)
    {
        luabridge::getGlobalNamespace(pLuaState)
            .beginClass<Game>("Game")
                // TODO: Expose more methods and write up psudo methods for things like audio
                //.addConstructor <void (*)(void)>() // Constructor is protected because Game is a singleton
                .addStaticFunction("getInstance", &(Game::getInstance))
                // Config
                .addFunction("getConfig", (GameConfig*(Game::*)()) &Game::getConfig)
                // Input System
                .addFunction("getInputSystem", (InputSystem*(Game::*)()) &Game::getInputSystem)
                // Camera2D
                .addFunction("getCamera2D", (Camera2D*(Game::*)()) &Game::getCamera2D)
                //// Camera#D
                //.addFunction("getCamera3D", (Camera3D*(Game::*)()) &Game::getCamera3D)
                // Player
                .addFunction("getPlayer", (Player*(Game::*)()) &Game::getPlayer)
                // Boss
                .addFunction("getBoss", (Boss*(Game::*)()) &Game::getBoss)
                .addFunction("bossSpeak", (void(Game::*)(const char*)) &Game::bossSpeak)
                // Pause/resume/start/stop
                .addFunction("pause", (void(Game::*)()) &Game::pause)
                .addFunction("resume", (void(Game::*)()) &Game::resume)
                //.addFunction("start", (void(Game::*)()) &Game::start)
                //.addFunction("stop", (void(Game::*)()) &Game::stop)
                // Running
                .addFunction("isRunning", (bool(Game::*)()) &Game::isRunning)
                .addFunction("setRunning", (void(Game::*)()) &Game::setRunning)
                // Application Timer
                .addFunction("getApplicationTicks", (float(Game::*)()) &Game::getApplicationTicks)
                // Boss Bullet
                .addFunction("createBossBullet", (void(Game::*)(float, float, float, float)) &Game::createBossBullet)
                // PlayerBullet
                .addFunction("createPlayerBullet", (void(Game::*)(float, float, float, float)) &Game::createPlayerBullet)
                // WINDOW
                .addFunction("setApplicationIconSmall", (void(Game::*)(std::string)) &Game::setApplicationIconSmall)
                .addFunction("setApplicationIconBig", (void(Game::*)(std::string)) &Game::setApplicationIconBig)
                .addFunction("getWindowCaption", (std::string(Game::*)()) &Game::getWindowCaption)
                .addFunction("setWindowCaption", (void(Game::*)(std::string)) &Game::setWindowCaption)
                .addFunction("isWindowMinimized", (bool(Game::*)()) &Game::isWindowMinimized)
                .addFunction("minimiseWindow", (void(Game::*)()) &Game::minimiseWindow)
                .addFunction("restoreWindow", (void(Game::*)()) &Game::restoreWindow)
                .addFunction("isWindowVisible", (bool(Game::*)()) &Game::isWindowVisible)
                .addFunction("hideWindow", (void(Game::*)()) &Game::hideWindow)
                .addFunction("showWindow", (void(Game::*)()) &Game::showWindow)
                .addFunction("saveScreenShot", (bool(Game::*)()) &Game::saveScreenShot)
                .addFunction("saveScreenShot", (bool(Game::*)(std::string)) &Game::saveScreenShot)
                .addFunction("getWindowX", (float(Game::*)()) &Game::getWindowX)
                .addFunction("setWindowX", (void(Game::*)(float)) &Game::setWindowX)
                .addFunction("getWindowY", (float(Game::*)()) &Game::getWindowY)
                .addFunction("setWindowY", (void(Game::*)(float)) &Game::setWindowY)
                .addFunction("setWindowPosition", (void(Game::*)(int, int)) &Game::setWindowPosition)
                .addFunction("getWindowWidth", (int(Game::*)()) &Game::getWindowWidth)
                .addFunction("getWindowHeight", (int(Game::*)()) &Game::getWindowHeight)
                .addFunction("getWindowFrameWidth", (int(Game::*)()) &Game::getWindowFrameWidth)
                .addFunction("getWindowFrameHeight", (int(Game::*)()) &Game::getWindowFrameHeight)
                .addFunction("getResolutionX", (int(Game::*)()) &Game::getResolutionX)
                .addFunction("getResolutionY", (int(Game::*)()) &Game::getResolutionY)
                .addFunction("setResolution", (void(Game::*)(int, int)) &Game::setResolution)
                .addFunction("isWindowResizable", (bool(Game::*)()) &Game::isWindowResizable)
                .addFunction("isWindowBordered", (bool(Game::*)()) &Game::isWindowBordered)
                .addFunction("showWindowBorder", (void(Game::*)()) &Game::showWindowBorder)
                .addFunction("hideWindowBorder", (void(Game::*)()) &Game::hideWindowBorder)
                .addFunction("getDisplayMode", (int(Game::*)()) &Game::getDisplayMode)
                .addFunction("fullScreenMode", (void(Game::*)()) &Game::fullScreenMode)
                .addFunction("fullScreenWindowedMode", (void(Game::*)()) &Game::fullScreenWindowedMode)
                .addFunction("windowedMode", (void(Game::*)()) &Game::windowedMode)
                .addFunction("turnOnVSync", (void(Game::*)()) &Game::turnOnVSync)
                .addFunction("turnOffVSync", (void(Game::*)()) &Game::turnOffVSync)
                .addFunction("getClearColour", (float*(Game::*)()) &Game::getClearColour)
                .addFunction("getClearColourRed", (float(Game::*)()) &Game::getClearColourRed)
                .addFunction("getClearColourGreen", (float(Game::*)()) &Game::getClearColourGreen)
                .addFunction("getClearColourBlue", (float(Game::*)()) &Game::getClearColourBlue)
                .addFunction("getClearColorAlpha", (float(Game::*)()) &Game::getClearColorAlpha)
                .addFunction("setClearColour", (void(Game::*)(float, float, float, float)) &Game::setClearColour)
                // Test
                .addFunction("print", (void(Game::*)(const char*)) &Game::print)
            .endClass();
    }
}

#endif // __GAMEBIND_H
