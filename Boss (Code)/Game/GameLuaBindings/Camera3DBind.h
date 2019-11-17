#ifndef __CAMERA3DBIND_H
#define __CAMERA3DBIND_H

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

#include "Camera3D.h"

namespace LuaBinding
{
    static void Camera3DBind(lua_State* pLuaState)
    {
        luabridge::getGlobalNamespace(pLuaState)
            .beginClass<Camera3D>("Camera3D")
                .addConstructor <void (*)(void)>()
                .addFunction("getX", (float (Camera3D::*)(void)) &Camera3D::getX)
                .addFunction("setX", (void (Camera3D::*)(float)) &Camera3D::setX)
                .addFunction("getY", (float (Camera3D::*)(void)) &Camera3D::getY)
                .addFunction("setY", (void (Camera3D::*)(float)) &Camera3D::setY)
                .addFunction("getZ", (float (Camera3D::*)(void)) &Camera3D::getZ)
                .addFunction("setZ", (void (Camera3D::*)(float)) &Camera3D::setZ)

                .addFunction("getXVelocity", (float (Camera3D::*)(void)) &Camera3D::getXVelocity)
                .addFunction("setXVelocity", (void (Camera3D::*)(float)) &Camera3D::setXVelocity)
                .addFunction("getYVelocity", (float (Camera3D::*)(void)) &Camera3D::getYVelocity)
                .addFunction("setYVelocity", (void (Camera3D::*)(float)) &Camera3D::setYVelocity)
                .addFunction("getZVelocity", (float (Camera3D::*)(void)) &Camera3D::getZVelocity)
                .addFunction("setZVelocity", (void (Camera3D::*)(float)) &Camera3D::setZVelocity)

                .addFunction("getViewPortWidth", (float (Camera3D::*)(void)) &Camera3D::getViewPortWidth)
                .addFunction("getViewPortHeight", (float (Camera3D::*)(void)) &Camera3D::getViewPortHeight)
                .addFunction("setViewPortWidth", (void (Camera3D::*)(float)) &Camera3D::setViewPortWidth)
                .addFunction("setViewPortHeight", (void (Camera3D::*)(float)) &Camera3D::setViewPortHeight)

                .addFunction("setShakeBounds", (void (Camera3D::*)(float, float)) &Camera3D::setShakeBounds)
                .addFunction("startShake", (void (Camera3D::*)()) &Camera3D::startShake)
                .addFunction("stopShake", (void (Camera3D::*)()) &Camera3D::stopShake)
            .endClass();
    }
}

#endif // __CAMERA3DBIND_H
