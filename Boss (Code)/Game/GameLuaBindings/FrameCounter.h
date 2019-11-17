#ifndef __FRAMECOUNTER_H
#define __FRAMECOUNTER_H

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

#include "FrameCounter.h"

namespace LuaBinding
{
    static void FrameCounterBind(lua_State* pLuaState)
    {
        luabridge::getGlobalNamespace(pLuaState)
            .beginClass<FrameCounter>("FrameCounter")
                .addConstructor <void (*)(void)>()
                .addFunction("start", (void (FrameCounter::*)()) &FrameCounter::start)
                .addFunction("stop", (void (FrameCounter::*)()) &FrameCounter::stop)
                .addFunction("pause", (void (FrameCounter::*)()) &FrameCounter::pause)
                .addFunction("resume", (void (FrameCounter::*)()) &FrameCounter::resume)
                .addFunction("getFPS", (float (FrameCounter::*)()) &FrameCounter::getFPS)
                .addFunction("update", (void (FrameCounter::*)()) &FrameCounter::update)
                .addFunction("getFPSasChar", (const char* (FrameCounter::*)()) &FrameCounter::getFPSasChar)
            .endClass();
    }
}

#endif // __FRAMECOUNTER_H
