#ifndef CAMERA3D_H
#define CAMERA3D_H

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
    #include <GLFW/glfw3native.h> // TODO:
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

// TODO: Up, Forward Vector
// TODO: I want to decouple OpenGL from this class
/** The Camera3D Class is a wrapper around a Perspective Projection Matrix **/
class Camera3D : public ICamera
{
    // ******************************
    // * CONSTRUCTORS / DESTRUCTORS *
    // ******************************
    public:
        //! Constructor
        Camera3D();
        //! Destructor
        virtual ~Camera3D();

    protected:
        ////! Camera3D Copy constructor
        //Camera3D(const Camera3D& other);

    // ************************
    // * OVERLOADED OPERATORS *
    // ************************
    public:
        // No functions

    protected:
        ////! Camera3D Assignment operator
        //Camera3D& operator=(const Camera3D& other) { return *this; }

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
        //! Free the camera
        virtual void free();
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

    // ************
    // * FRUSTRUM *
    // ************
    public:
        //! Get Field Of View
        virtual float getFieldOfView() { return this->fovy; }
        //! Get Aspect Ratio
        virtual float getAspectRatio() { return this->aspect; }
        //! Get ZNear
        virtual float getZNear() { return this->zNear; }
        //! Get ZFar
        virtual float getZFar() { return this->zFar; }
        //! Set Perspective
        virtual void setPerspective(float fovy, float aspect, float zNear, float zFar);

    protected:
        // Field of view
        float fovy;
        // Aspect Ratio
        float aspect;
        // ZNear
        float zNear;
        // ZFar
        float zFar;

    // ***********************
    // * TRANSFORM FUNCTIONS *
    // ***********************
    public:
        //! Get Horizontal position
        virtual float getX() { return this->x; }
        //! Set Horizontal position
        virtual void setX(float x) { this->x = x; }
        //! Get Vertical position
        virtual float getY() { return this->y; }
        //! Set Vertical position
        virtual void setY(float y) { this->y = y; }
        //! Get Depth position
        virtual float getZ() { return this->z; }
        //! Set Depth position
        virtual void setZ(float z) { this->z = z; }
        //! Set Position
        virtual void setPosition(float x, float y, float z) { this->x = x; this->y = y; this->z = z; }
        //! Get Horizontal velocity
        virtual float getXVelocity() { return this->xVelocity; }
        //! Set Horizontal velocity
        virtual void setXVelocity(float xVelocity) { this->xVelocity = xVelocity; }
        //! Get Vertical velocity
        virtual float getYVelocity() { return this->yVelocity; }
        //! Set Vertical velocity
        virtual void setYVelocity(float yVelocity) { this->yVelocity = yVelocity; }
        //! Get Depth velocity
        virtual float getZVelocity() { return this->zVelocity; }
        //! Set Depth velocity
        virtual void setZVelocity(float zVelocity) { this->zVelocity = zVelocity; }
        //! Set Velocity
        virtual void setVelocity(float xVelocity, float yVelocity, float zVelocity) { this->xVelocity = xVelocity; this->yVelocity = yVelocity; this->zVelocity = zVelocity; }
        //! Get Horizontal acceleration
        virtual float getXAcceleration() { return this->xAcceleration; }
        //! Set Horizontal acceleration
        virtual void setXAcceleration(float xAcceleration) { this->xAcceleration = xAcceleration; }
        //! Get Vertical acceleration
        virtual float getYAcceleration() { return this->yVelocity; }
        //! Set Vertical acceleration
        virtual void setYAcceleration(float yAcceleration) { this->yAcceleration = yAcceleration; }
        //! Get Depth acceleration
        virtual float getZAcceleration() { return this->zVelocity; }
        //! Set Depth acceleration
        virtual void setZAcceleration(float zAcceleration) { this->zAcceleration = zAcceleration; }
        //! Set acceleration
        virtual void setAcceleration(float xAcceleration, float yAcceleration, float zAcceleration) { this->xAcceleration = xAcceleration; this->yAcceleration = yAcceleration; this->zAcceleration = zAcceleration; }
        //! Get Rotation X
        virtual float getRotationX() { return this->pitch; }
        //! Set Rotation X
        virtual void setRotationX(float pitch) { this->pitch = pitch; }
        //! Get Rotation Y
        virtual float getRotationY() { return this->yaw; }
        //! Set Rotation Y
        virtual void setRotationY(float yaw) { this->yaw = yaw; }
        //! Get Rotation Z
        virtual float getRotationZ() { return this->roll; }
        //! Set Rotation Z
        virtual void setRotationZ(float roll) { this->roll = roll; }

    protected:
        // Horizontal position
        float x;
        // Vertical position
        float y;
        // Depth position
        float z;
        // Horizontal velocity
        float xVelocity;
        // Vertical velocity
        float yVelocity;
        // Depth Velocity
        float zVelocity;
        // Horizontal acceleration
        float xAcceleration;
        // Vertical acceleration
        float yAcceleration;
        // Depth acceleration
        float zAcceleration;
        // Pitch
        float pitch;
        // Yaw
        float yaw;
        // Roll
        float roll;

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
        //! Get BoundZ
        virtual float getBoundZ() { return this->boundZ; }
        //! Set BoundZ
        virtual void setBoundZ(float boundZ) { this->boundZ = boundZ; }
        //! Set Bounds Position
        virtual void setBoundPosition(float boundX, float boundY, float boundZ) { this->boundX = boundX; this->boundY = boundY; this->boundZ = boundZ; }
        //! Get BoundWidth
        virtual float getBoundWidth() { return this->boundWidth; }
        //! Set BoundWidth
        virtual void setBoundWidth(float boundWidth) { this->boundWidth = boundWidth; }
        //! Get BoundHeight
        virtual float getBoundHeight() { return this->boundHeight; }
        //! Set BoundHeight
        virtual void setBoundHeight(float boundHeight) { this->boundHeight = boundHeight; }
        //! Get BoundDepth
        virtual float getBoundDepth() { return this->boundDepth; }
        //! Set BoundDepth
        virtual void setBoundDepth(float boundDepth) { this->boundDepth = boundDepth; }
        //! Set Bounds
        virtual void setBounds(float boundX, float boundY, float boundZ, float boundWidth, float boundHeight, float boundDepth) { this->boundX = boundX; this->boundY = boundY; this->boundZ = boundZ; this->boundWidth = boundWidth; this->boundHeight = boundHeight; this->boundDepth = boundDepth; }
        //! Bound Camera
        virtual void boundCamera() { this->boundFlag = true; }
        //! Unbound Camera
        virtual void unboundCamera() { this->boundFlag = false; }

    protected:
        // Memebers for cameraBounds
        bool boundFlag;
        float boundX;
        float boundY;
        float boundZ;
        float boundWidth;
        float boundHeight;
        float boundDepth;

    // ******************
    // * CAMERA EFFECTS *
    // ******************
    public:
        //! Start shake
        void startShake();
        //! Stop shake
        void stopShake();
        //! Set shakebounds
        virtual void setShakeBounds(float shakeX, float shakeY) { this->shakeX = shakeX; this->shakeY = shakeY; }
        //! Shake method
        void shake();

    protected:
        // Shaking state
        bool shaking;
        // shakex
        float shakeX;
        // shakey
        float shakeY;
        // shakez
        float shakeZ;
};

#endif // CAMERA3D_H
