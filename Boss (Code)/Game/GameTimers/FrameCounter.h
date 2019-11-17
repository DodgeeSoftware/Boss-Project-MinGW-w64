#ifndef FRAMECOUNTER_H
#define FRAMECOUNTER_H

// C++ Includes
#include <sstream>

/*
// LUA / LUA Bind Includes
extern "C"
{
    #include <lua.h>
    #include <lualib.h>
    #include <lauxlib.h>
}
#include <luabind/luabind.hpp>
#include <luabind/operator.hpp>
*/
// GAME TIMER Includes
#include "Timer.h"

//! The FrameCounter is a simple class designed to calculate the number of frames per second in your application
class FrameCounter
{
    // CONSTRUCTORS / DESTRUCTOS
    public:
        //! Default constructor
        FrameCounter()
        {
            this->frameCounter = 0;
            this->framesPerSecond = 0;
        }
        //! Destructor
        virtual ~FrameCounter() {}

    protected:
        ////! Copy Constructor
        //FrameCounter(const FrameCounter& other) {}

    // OVERLOADED OPERATORS
    public:
        // To functions

    protected:
        ////! Assignment operator
        //FrameCounter& operator=(const FrameCounter& other) { return *this; }

    // GENERAL FUNCTIONS
    public:
        //! Start the FrameCounter
        virtual void start();
        //! Update the FrameCounter
        virtual void update();
        //! Pause the FrameCounter
        virtual void pause();
        //! Resume the FrameCounter
        virtual void resume();
        //! Stop the FrameCounter
        virtual void stop();
        //! Get the current frames per second
        virtual float getFPS() { return framesPerSecond; }
        //! Get the current frames per second as a string
        virtual const char* getFPSasChar();

    protected:
        // Maintain a local timer
        Timer timer;
        // Frame rate counter
        float frameCounter;
        // Frames per second
        float framesPerSecond;
};

#endif // FRAMECOUNTER_H
