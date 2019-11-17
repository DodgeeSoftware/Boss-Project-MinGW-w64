#ifndef __COLOUR_H
#define __COLOUR_H

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

#include "Colour.h"

namespace LuaBinding
{
    static void ColourBind(lua_State* pLuaState)
    {
        luabridge::getGlobalNamespace(pLuaState)
            .beginClass<Colour>("Colour")
                .addConstructor <void (*)(void)>()
                .addConstructor <void (*)(float, float, float, float)>()
                .addFunction("normalise", (void (Colour::*)()) &Colour::normalise)
                .addFunction("normalised", (Colour (Colour::*)()) &Colour::normalised)
                .addFunction("magnitude", (Colour (Colour::*)(float)) &Colour::magnitude)
//                // Assignment Operator Overloading is not supported by lua and for good reason (script locals could accidently be assigned program addresses *nods* )
//                .def(luabind::self + Colour())
//                .def(luabind::self - Colour())
//                .def(luabind::self * float())
//                .def(luabind::self / float())
//                .def(luabind::self == Colour())
//                .def(luabind::self != Colour())
                .addProperty ("red", &Colour::red)
                .addProperty ("green", &Colour::green)
                .addProperty ("blue", &Colour::blue)
                .addProperty ("alpha", &Colour::alpha)
                .addProperty ("r", &Colour::red)
                .addProperty ("g", &Colour::green)
                .addProperty ("b", &Colour::blue)
                .addProperty ("a", &Colour::alpha)
            .endClass();
    }
}

#endif // __COLOUR_H
