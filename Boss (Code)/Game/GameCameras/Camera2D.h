#ifndef CAMERA2D_H
#define CAMERA2D_H

// C++ Includes
#include <iostream>
#include <cstdlib>

// OS Specific includes
#ifdef _WIN32 || _WIN64 || _WIN7 || _WINXP
    #define GLFW_EXPOSE_NATIVE_WIN32
    #define GLFW_EXPOSE_NATIVE_WGL
    #include <windows.h>
    #include <Tchar.h>
#endif
#ifdef __linux__ || _LINUX
    #define GLFW_EXPOSE_NATIVE_X11
    #define GLFW_EXPOSE_NATIVE_GLX
    #include <X11/Xlib.h>
    #include <X11/Xutil.h>
    #include <X11/Xos.h>
#endif // __linux__
#ifdef TARGET_OS_MAC || _MACOSX
    #define GLFW_EXPOSE_NATIVE_COCOA
    #define GLFW_EXPOSE_NATIVE_NSGL
    #include <GLFW/glfw3native.h>
    #include <Cocoa/Cocoa.h>
#endif // TARGET_OS_MAC

// OpenGL Includes
#include <gl/gl.h>
#include <gl/glu.h>
#include <gl/glext.h>

// OpenGL FrameWork includes
#include <glfw/glfw3.h>
#include <glfw/glfw3native.h>

//// LUA / LUA BIND INCLUDES
//extern "C"
//{
//    #include <lua.h>
//    #include <lualib.h>
//    #include <lauxlib.h>
//}
//#include <luabind/luabind.hpp>
//#include <luabind/operator.hpp>

// CAMERA Includes
#include "ICamera.h"

/** The Camera2D class is a container for an Orthogonal Projection Matrix **/
class Camera2D : public ICamera
{
    // ******************************
    // * CONSTRUCTORS / DESTRUCTORS *
    // ******************************
    public:
        //! Constructor
        Camera2D();
        //! Destructor
        virtual ~Camera2D();

    protected:
        ////! Camera2D Copy constructor
        //Camera2D(const Camera2D& other);

    // ************************
    // * OVERLOADED OPERATORS *
    // ************************
    public:
        // No functions

    protected:
        ////! Camera2D Assignment operator
        //Camera2D& operator=(const Camera2D& other) { return *this; }

    // *********************
    // * GENERAL FUNCTIONS *
    // *********************
    public:
        //! Initilise the camera
        virtual bool init();
        //! Interpolate the camera to the next frame
        virtual void update(float dTime);
        //! Set the viewport for drawing
        virtual void draw();
        //! Clear the Camera
        virtual void clear();
        //! Free the camera
        virtual void free();

    public:
        //! Start
        virtual void start();
        //! Stop
        virtual void stop();
        //! Pause
        virtual void pause();
        //! Resume
        virtual void resume();
        //! Reset
        virtual void reset();

    protected:
        // Running Flag
        bool runningFlag;
        // Paused Flag
        bool pausedFlag;

    // ************************
    // * TRANNSFORM FUNCTIONS *
    // ************************
    public:
        //! Get Horizontal position
        virtual float getX() { return this->x; }
        //! Get Vertical position
        virtual float getY() { return this->y; }
        //! Set Horizontal position
        virtual void setX(float x) { this->x = x; }
        //! Set Vertical position
        virtual void setY(float y) { this->y = y; }
        //! Set Position
        virtual void setPosition(float x, float y) { this->x = x; this->y = y; }
        //! Get Horizontal velocity
        virtual float getXVelocity() { return this->xVelocity; }
        //! Set Horizontal velocity
        virtual void setXVelocity(float xVelocity) { this->xVelocity = xVelocity; }
        //! Get Vertical velocity
        virtual float getYVelocity() { return this->yVelocity; }
        //! Set Vertical velocity
        virtual void setYVelocity(float yVelocity) { this->yVelocity = yVelocity; }
        //! Set Velocity
        virtual void setVelocity(float xVelocity, float yVelocity) { this->xVelocity = xVelocity; this->yVelocity = yVelocity; }
        //! Get Horizontal acceleration
        virtual float getXAcceleration() { return this->xAcceleration; }
        //! Set Horizontal acceleration
        virtual void setXAcceleration(float xAcceleration) { this->xAcceleration = xAcceleration; }
        //! Get Vertical acceleration
        virtual float getYAcceleration() { return this->yVelocity; }
        //! Set Vertical acceleration
        virtual void setYAcceleration(float yAcceleration) { this->yAcceleration = yAcceleration; }
        //! Set acceleration
        virtual void setAcceleration(float xAcceleration, float yAcceleration) { this->xAcceleration = xAcceleration; this->yAcceleration = yAcceleration; }

    protected:
        // Horizontal position
        float x;
        // Vertical position
        float y;
        // Horizontal velocity
        float xVelocity;
        // Vertical velocity
        float yVelocity;
        // Horizontal acceleration
        float xAcceleration;
        // Vertical acceleration
        float yAcceleration;

    // *********************
    // * CAMERA BOUNDARIES *
    // *********************
    // NOTE: Camera is a region (x, y, width, height) that the Camera is bound to move inside
    // TODO: Implement boundary behaviour
    public:
        //! Get BoundX
        virtual float getBoundX() { return this->boundX; }
        //! Set BoundX
        virtual void setBoundX(float boundX) { this->boundX = boundX; }
        //! Get BoundY
        virtual float getBoundY() { return this->boundY; }
        //! Set BoundY
        virtual void setBoundY(float boundY) { this->boundY = boundY; }
        //! Set BoundsPosition
        virtual void setBoundPosition(float boundX, float boundY) { this->boundX = boundX; this->boundY = boundY; }
        //! Get BoundWidth
        virtual float getBoundWidth() { return this->boundWidth; }
        //! Set BoundWidth
        virtual void setBoundWidth(float boundWidth) { this->boundWidth = boundWidth; }
        //! Get BoundHeight
        virtual float getBoundHeight() { return this->boundHeight; }
        //! Set BoundHeight
        virtual void setBoundHeight(float boundHeight) { this->boundHeight = boundHeight; }
        //! Set Bounds
        virtual void setBounds(float boundX, float boundY, float boundWidth, float boundHeight) { this->boundX = boundX; this->boundY = boundY; this->boundWidth = boundWidth; this->boundHeight = boundHeight; }
        //! Bound Camera
        virtual void boundCamera() { this->boundFlag = true; }
        //! Unbound Camera
        virtual void unboundCamera() { this->boundFlag = false; }

    protected:
        // Memebers for cameraBounds
        bool boundFlag;
        float boundX;
        float boundY;
        float boundWidth;
        float boundHeight;

    // ********
    // * ZOOM *
    // ********
    public:
        //! Get Zoom
        virtual float getZoom() { return this->zoom; }
        //! Set Zoom
        virtual void setZoom(float value) { this->zoom = value; }
        //! Get Zoom Focus X
        virtual float getZoomFocusX() { return this->zoomFocusX; }
        //! Set Zoom Focus Y
        virtual float getZoomFocusY() { return this->zoomFocusY; }
        //! Set Zoom Focus
        virtual void setZoomFocus(float x, float y) { this->zoomFocusX = x; this->zoomFocusY = y; }
        //! Zoom Reset
        virtual void zoomReset()
        {
            this->zoom = 1.0f;
            this->zoomFocusX = 0.0f;
            this->zoomFocusY = 0.0f;
        }

    protected:
        // Zoom
        float zoom;
        // zoomFocusX
        float zoomFocusX;
        // zoomFocusY
        float zoomFocusY;

    // ******************
    // * CAMERA EFFECTS *
    // ******************
    public:
        //! Start shake
        void startShake();
        //! Stop shake
        void stopShake();
        //! Set shakebounds
        virtual void setShakeBounds(float shakeX, float shakeY);
        //! Shake method
        void shake();

    protected:
        // Shaking state
        bool shaking;
        // shakex
        float shakeX;
        // shakey
        float shakeY;
};

#endif // CAMERA2D_H
