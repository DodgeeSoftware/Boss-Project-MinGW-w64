#ifndef GLFW_KEYBOARDUNICODEEVENT_H
#define GLFW_KEYBOARDUNICODEEVENT_H

// TODO: Comment me properly
struct GLFW_KeyboardUnicodeEvent
{
    int type; // Event type GLFW_KEYUP or GLFW_KEYDOWN
    int state; // GLFW_KEYPRESSED or GLFW_KEYRELEASED
    int key; // The actual key either pressed or released
};

#endif // GLFW_KEYBOARDUNICODEEVENT_H
