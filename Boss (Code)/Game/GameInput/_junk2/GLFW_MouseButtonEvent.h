#ifndef GLFW_MOUSEBUTTONEVENT_H
#define GLFW_MOUSEBUTTONEVENT_H

// TODO: Comment me properly
struct GLFW_MouseButtonEvent
{
    int type;
    int button;
    int action;
    int mods;
    double x;
    double y;
};

#endif // GLFW_MOUSEBUTTONEVENT_H
