#ifndef GLFW_EVENT_H
#define GLFW_EVENT_H

#include <GLFW_KeyboardEvent.h>
#include <GLFW_KeyboardUnicodeEvent.h>
#include <GLFW_MouseButtonEvent.h>
#include <GLFW_MouseEnterEvent.h>
#include <GLFW_MouseScrollEvent.h>

struct GLFW_Event
{
    int type;
    GLFW_KeyboardEvent key;
    GLFW_KeyboardUnicodeEvent keyUnicode;
    GLFW_MouseButtonEvent button;
    GLFW_MouseEnterEvent enter;
    GLFW_MouseScrollEvent scroll;
};

#endif // GLFW_EVENT_H
