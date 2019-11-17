#ifndef __CAMERA2DBIND_H
#define __CAMERA2DBIND_H

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

#include "Camera2D.h"

namespace LuaBinding
{
    static void Camera2DBind(lua_State* pLuaState)
    {
        luabridge::getGlobalNamespace(pLuaState)
            .beginClass<Camera2D>("Camera2D")
                .addConstructor <void (*)(void)>()
                .addFunction("getX", (float (Camera2D::*)(void)) &Camera2D::getX)
                .addFunction("setX", (void (Camera2D::*)(float)) &Camera2D::setX)
                .addFunction("getY", (float (Camera2D::*)(void)) &Camera2D::getY)
                .addFunction("setY", (void (Camera2D::*)(float)) &Camera2D::setY)
                .addFunction("getXVelocity", (float (Camera2D::*)(void)) &Camera2D::getXVelocity)
                .addFunction("setXVelocity", (void (Camera2D::*)(float)) &Camera2D::setXVelocity)
                .addFunction("getYVelocity", (float (Camera2D::*)(void)) &Camera2D::getYVelocity)
                .addFunction("setYVelocity", (void (Camera2D::*)(float)) &Camera2D::setYVelocity)
                .addFunction("getViewPortWidth", (float (Camera2D::*)()) &Camera2D::getViewPortWidth)
                .addFunction("getViewPortHeight", (float (Camera2D::*)()) &Camera2D::getViewPortHeight)
                .addFunction("setViewPortWidth", (void (Camera2D::*)(float)) &Camera2D::setViewPortWidth)
                .addFunction("setViewPortHeight", (void (Camera2D::*)(float)) &Camera2D::setViewPortHeight)
                .addFunction("getZoom", (float (Camera2D::*)()) &Camera2D::getZoom)
                .addFunction("setZoom", (void (Camera2D::*)(float)) &Camera2D::setZoom)
                .addFunction("getZoomFocusX", (float (Camera2D::*)()) &Camera2D::getZoomFocusX)
                .addFunction("setZoomFocus", (void (Camera2D::*)(float, float)) &Camera2D::setZoomFocus)
                .addFunction("getZoomFocusY", (float (Camera2D::*)()) &Camera2D::getZoomFocusY)
                .addFunction("setShakeBounds", (void (Camera2D::*)(float, float)) &Camera2D::setShakeBounds)
                .addFunction("startShake", (void (Camera2D::*)()) &Camera2D::startShake)
                .addFunction("stopShake", (void (Camera2D::*)()) &Camera2D::stopShake)
            .endClass();
    }
}

#endif // __CAMERA2DBIND_H
