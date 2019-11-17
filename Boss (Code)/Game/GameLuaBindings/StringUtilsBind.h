#ifndef __STRINGUTILS_h
#define __STRINGUTILS_h

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

// String Utils
#include "StringUtils.h"

namespace LuaBinding
{
    static void StringUtilsBind(lua_State* pLuaState)
    {
        luabridge::getGlobalNamespace(pLuaState)
            .beginNamespace ("Utils")
                .addFunction("split", (std::vector<std::string>& (*)(const std::string&, char, std::vector<std::string>& elems)) &Utils::split)
                .addFunction("split", (std::vector<std::string>(*)(const std::string&, char)) &Utils::split)
                .addFunction("removeWhiteSpace", (std::string(*)(std::string)) &Utils::removeWhiteSpace)
                .addFunction("toUpper", (std::string(*)(std::string)) &Utils::toUpper)
                .addFunction("toLower", (std::string(*)(std::string)) &Utils::toLower)
                .addFunction("toString", (std::string(*)(bool)) &Utils::toString)
                .addFunction("toBool", (bool(*)(std::string)) &Utils::toBool)
                .addFunction("toString", (std::string(*)(long)) &Utils::toString)
                .addFunction("toLong", (long(*)(std::string)) &Utils::toLong)
                .addFunction("toString", (std::string(*)(unsigned int)) &Utils::toString)
                .addFunction("toUnsignedInt", (unsigned int(*)(std::string)) &Utils::toUnsignedInt)
                .addFunction("toString", (std::string(*)(int)) &Utils::toString)
                .addFunction("toInt", (int(*)(std::string)) &Utils::toInt)
                .addFunction("toString", (std::string(*)(float)) &Utils::toString)
                .addFunction("toFloat", (float(*)(std::string)) &Utils::toFloat)
                .addFunction("toString", (std::string(*)(double)) &Utils::toString)
                .addFunction("toDouble", (double(*)(std::string)) &Utils::toDouble)
                .addFunction("toString", (std::string(*)(short int value)) &Utils::toString)
                .addFunction("toShortInt", (short int(*)(std::string)) &Utils::toShortInt)
                .addFunction("toString", (std::string(*)(unsigned long)) &Utils::toString)
                .addFunction("toUnsignedLong", (unsigned long(*)(std::string)) &Utils::toUnsignedLong)
                .addFunction("toString", (std::string(*)(long long)) &Utils::toString)
                .addFunction("toLongLong", (long long(*)(std::string)) &Utils::toLongLong)
                .addFunction("toString", (std::string(*)(unsigned long long value)) &Utils::toString)
                .addFunction("toUnsignedLongLong", (unsigned long long(*)(std::string)) &Utils::toUnsignedLongLong)
                .addFunction("toString", (std::string(*)(char value)) &Utils::toString)
                .addFunction("toString", (std::string(*)(unsigned char)) &Utils::toString)
                .addFunction("toLong", (long(*)(const char*)) &Utils::toLong)
                .addFunction("toInt", (int(*)(const char*)) &Utils::toInt)
                .addFunction("toFloat", (float(*)(const char*)) &Utils::toFloat)
                .addFunction("toBool", (bool(*)(const char*)) &Utils::toBool)
            .endNamespace ();
    }
}

#endif // __STRINGUTILS_h



