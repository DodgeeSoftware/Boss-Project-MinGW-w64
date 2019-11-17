#ifndef FPSLIMITER_H
#define FPSLIMITER_H

/*
// LUA / LUA BIND Includes
extern "C"
{
    #include <lua.h>
    #include <lualib.h>
    #include <lauxlib.h>
}
#include <luabind/luabind.hpp>
#include <luabind/operator.hpp>
*/

// Game Timer Includes
#include "Timer.h"

/** The FPSLimiter is a class which can be used to limit frame rate **/
class FPSLimiter
{
    // CONSTRUCTOR / DESTRUCTOR
    public:
        //! Constructor
        FPSLimiter()
        {
            this->now = 0;
            this->then = 0;
            this->accumulator = 0;
            this->desiredFPS = 60.0f;
            this->limitFramesPerSecond = false;
        }
        //! Destructor
        virtual ~FPSLimiter() {}

    protected:
        ////! Copy Constructor
        //FPSLimiter(const FPSLimiter& other) {}

    // OVERLOADED OPERATORS
    public:
        // To functions

    protected:
        ////! Assignment operator
        //FPSLimiter& operator=(const FPSLimiter& other) { return *this; }

    // GENERAL FUNCTIONS
    public:
        //! init the frame rate limiter
        virtual void start();
        //! advance the frame rate limiter
        virtual void update();
        //! init the frame rate limiter
        virtual void stop();
        //! return true if the frame needs to be updated
        virtual bool isFrameUpdate() { return accumulator > (1.0f / desiredFPS); }
        //! adjust the accumulator for this frame
        virtual void updateAccumulator() { accumulator -= (1.0f / desiredFPS); }
        //! Get the desired FPS
        virtual float getDesiredFPS() { return this->desiredFPS; }
        //! Set the desired FPS
        virtual void setDesiredFPS(float value) { this->desiredFPS = value; }
        //! Is the frame rate being limited
        virtual bool isLimitFramesPerSecond() { return this->limitFramesPerSecond; }
        //! Toggle frame rate limiter
        virtual void setLimitFramesPerSecond(bool state);

    protected:
        // Frame Timer
        Timer frameTimer;
        // Keep track of the desired frame rate
        float desiredFPS;
        // The current time of update
        float now;
        // The last time update was called
        float then;
        // Accumulator between update calls
        float accumulator;
        // Toggle for the frame rate limiter
        bool limitFramesPerSecond;
};

#endif // FPSLIMITER_H
