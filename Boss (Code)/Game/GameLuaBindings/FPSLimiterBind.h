#ifndef __FPSLIMITER_H
#define __FPSLIMITER_H

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

namespace LuaBinding
{
    static void FPSLimiterBind(lua_State* pLuaState)
    {
        luabridge::getGlobalNamespace(pLuaState)
            .beginClass<FPSLimiter>("FPSLimiter")
                .addConstructor <void (*)(void)>()
                .addFunction("start", (void (FPSLimiter::*)()) &FPSLimiter::start)
                .addFunction("stop", (void (FPSLimiter::*)()) &FPSLimiter::stop)
                .addFunction("isFrameUpdate", (bool (FPSLimiter::*)()) &FPSLimiter::isFrameUpdate)
                .addFunction("updateAccumulator", (void (FPSLimiter::*)()) &FPSLimiter::updateAccumulator)
                .addFunction("getDesiredFPS", (float (FPSLimiter::*)()) &FPSLimiter::getDesiredFPS)
                .addFunction("setDesiredFPS", (void (FPSLimiter::*)(float)) &FPSLimiter::setDesiredFPS)
                .addFunction("isLimitFramesPerSecond", (bool (FPSLimiter::*)()) &FPSLimiter::isLimitFramesPerSecond)
                .addFunction("setLimitFramesPerSecond", (void(FPSLimiter::*)(bool)) &FPSLimiter::setLimitFramesPerSecond)
            .endClass();
    }
}

#endif // __FPSLIMITER_H
