#ifndef __TIMERBIND_H
#define __TIMERBIND_H

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

#include "Timer.h"

namespace LuaBinding
{
    static void TimerBind(lua_State* pLuaState)
    {
        luabridge::getGlobalNamespace(pLuaState)
            .beginClass<Timer>("Timer")
                .addConstructor <void (*)(void)>()
                .addFunction("start", (void (Timer::*)()) &Timer::start)
                .addFunction("stop", (void (Timer::*)()) &Timer::stop)
                .addFunction("pause", (void (Timer::*)()) &Timer::pause)
                .addFunction("resume", (void (Timer::*)()) &Timer::resume)
                .addFunction("reset", (void (Timer::*)()) &Timer::reset)
                .addFunction("getTicks", (double (Timer::*)()) &Timer::getTicks)
                .addFunction("getDelta", (double (Timer::*)()) &Timer::getDelta)
                .addFunction("getTotalPausedTime", (double (Timer::*)()) &Timer::getTotalPausedTime)
                .addFunction("isStarted", (bool (Timer::*)()) &Timer::isStarted)
                .addFunction("isPaused", (bool (Timer::*)()) &Timer::isPaused)
                .addFunction("getOffset", (float(Timer::*)()) &Timer::getOffset)
                .addFunction("setOffset", (void(Timer::*)(float)) &Timer::setOffset)
            .endClass();
    }
}

#endif // __TIMERBIND_H
