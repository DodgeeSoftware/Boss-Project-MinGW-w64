#ifndef GLFW_KEYBOARDEVENT_H
#define GLFW_KEYBOARDEVENT_H

// TODO: Comment me properly
struct GLFW_KeyboardEvent
{
    int type; // Event type GLFW_KEYUP or GLFW_KEYDOWN
    int state; // GLFW_KEYPRESSED or GLFW_KEYRELEASED
    int key; // The actual key either pressed or released
};

#endif // GLFW_KEYBOARDEVENT_H
