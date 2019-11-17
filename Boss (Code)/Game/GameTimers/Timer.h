#ifndef TIMER_H
#define TIMER_H

//// OpenGL Extension Wrangler Includes
//#include <gl/glew.h>

// OpenGL FrameWork Includes
#include <glfw/glfw3.h>

/*
// LUA / LUA BIND Includes
extern "C"
{
    #include <lua.h>
    #include <lualib.h>
    #include <lauxlib.h>
}
#include <luabind/luabind.hpp>
#include <luabind/operator.hpp>*/

/** A general purpose timer class. All values are in milliseconds (m/secs) */
class Timer
{
    // ******************************
    // * CONSTRUCTORS / DESTRUCTORS *
    // ******************************
    public:
        //! Constructor
        Timer();
        ////! Copy Constructor
        //Timer(const Timer& other) {}
        //! Destructor
        virtual ~Timer();

    protected:
        // No members or methods

    // ************************
    // * OVERLOADED OPERATORS *
    // ************************
    public:
        // TODO: Implement me
        ////! Assignment operator
        //Timer& operator=(const Timer& other) { return *this; }

    protected:
        // No members or methods

    // *********************
    // * GENERAL FUNCTIONS *
    // *********************
    public:
        //! must call this function to start the timer
        /** calling start again will reset the timer
        use pause and resume to suspend the timer */
        virtual void start();
        //! stop the timer
        /** must use start() if using same timer again */
        virtual void stop();
        //! reset the timer
        /** stops the timer resetting it, then starts it again*/
        virtual void reset();
        //! pause the timer
        /** tracks how much time passes while paused */
        virtual void pause();
        //! resume the current timer
        /** adjusts game time to not count the paused time */
        virtual void resume();
        //! number of m/secs since start() was executed
        /** \return the number of msecs passed since game start
        or 0 if not started or is paused */
        virtual double getTicks();
        //! tracks how many m/secs have passed since the function was last called.
        /** Useful for general purpose timing.
        When used once only in an update and draw cycle for example.
        \return m/secs passed since getDelta() last called */
        virtual double getDelta();
        //! tracks how many m/secs have passed while paused.
        /** Probably useful only for general stats.
        \return m/secs passed in paused state */
        virtual double getTotalPausedTime();
        //! has timer started */
        /** \return true if timer has started */
        virtual bool isStarted();
        //! has timer paused */
        /** \return true if timer is paused */
        virtual bool isPaused();
        //! Get Offset
        /** \return the offset for the timer */
        virtual float getOffset();
        //! Set Offset
        virtual void setOffset(float offset);

    protected:
        // the offset for the time
        double timeOffset;
        // the system time when the timer starts
        double startTime;
        // timer stoped
        bool startedFlag;
        // time at which the pause method was called
        double pausedTime;
        // time passed during a pause
        double totalPausedTime;
        // timer has paused
        bool pausedFlag;
        // the last time the get delta function was called
        double lastTime;
};

#endif // TIMER_H
