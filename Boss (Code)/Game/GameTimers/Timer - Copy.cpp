#include "Timer.h"

void Timer::start()
{
    // set the time at which the time started
    this->startTime = glfwGetTime() * 1000.0;
    // set paused status to false
    this->paused = false;
    // set stopped to false
    this->stopped = false;
    // reset the amount of time this time has been caused
    this->totalPausedTime = 0.0;
    // last time get delta was called
    this->lastTime = 0.0;
}

void Timer::stop()
{
    // set the start time to 0.0
    this->startTime = 0.0;
    // set paused status to false
    this->paused = false;
    // set stopped to true
    this->stopped = true;
}

void Timer::reset()
{
    // stop the timer
    this->stop();
    // start the timer
    this->start();
}

void Timer::pause()
{
    // if the timer is not already paused then pause it
    if (this->paused == false)
    {
        // set paused status to true
        this->paused = true;
        // store the time at which the pause instruction was executed
        this->pausedTime = glfwGetTime() * 1000.0;
    }
}

void Timer::resume()
{
    // if the timer is paused then resume it
    if (this->paused == true)
    {
        // set paused status to false
        this->paused = false;
        // save total time level timer has been paused
        this->totalPausedTime += glfwGetTime() * 1000.0 - this->pausedTime;
    }
}

double Timer::getTicks()
{
    // if the timer is paused and has not been stopped
    if (this->paused == true && this->startTime != 0.0 )
    {
        // return the time at which the timer was paused
        return this->pausedTime - this->startTime - this->totalPausedTime;
    }
    // if the timer has been stopped
    if (this->stopped == true)
    {
        // return zero because the timer has been stopped
        return 0.0;
    }
    // return the total time running minus time paused
    return glfwGetTime() * 1000.0 - this->startTime - this->totalPausedTime;
}

double Timer::getDelta()
{
    // If the timer isn't advancing then delta should be 0.0
    if (this->stopped == true || this->paused == true)
        return 0.0;
    // get the current time ( relative to this timer )
    unsigned timeNow = this->getTicks();
    // the number of m/secs since last called
    unsigned timeDelta = timeNow - this->lastTime;
    // save the current time
    this->lastTime = timeNow;
    // the amount of time since the last access to this function
    return timeDelta;
}

double Timer::getTotalPausedTime()
{
    return totalPausedTime;
}

bool Timer::isStarted()
{
    // if the startTime is 0 then not started yet
    return (startTime) ? true : false;
}

bool Timer::isPaused()
{
    return paused;
}

//void Timer::addTime(double value)
//{
//    this->startTime = this->startTime + value * 1000.0;
//}
//
//void Timer::subtractTime(double value)
//{
//    this->startTime = this->startTime - value * 1000.0;
//}


void Timer::bindToLua(lua_State* pLuaState)
{
    // Bind functions to lua state
    luabind::module(pLuaState)
    [
        // TODO: More bindings
        // .def("addTimer", (bool (GameObject::*)(std::string)) &GameObject::addTimer)
        luabind::class_<Timer>("Timer")
        .def(luabind::constructor<>())
        .def("start", (void (Timer::*)()) &Timer::start)
        .def("stop", (void (Timer::*)()) &Timer::stop)
        .def("pause", (void (Timer::*)()) &Timer::pause)
        .def("resume", (void (Timer::*)()) &Timer::resume)
        .def("reset", (void (Timer::*)()) &Timer::reset)
        .def("getTicks", (double (Timer::*)()) &Timer::getTicks)
        .def("getDelta", (double (Timer::*)()) &Timer::getDelta)
        .def("getTotalPausedTime", (double (Timer::*)()) &Timer::getTotalPausedTime)
        .def("isStarted", (bool (Timer::*)()) &Timer::isStarted)
        .def("isPaused", (bool (Timer::*)()) &Timer::isPaused)
//        .def("addTime", (void(Timer::*)(double)) &Timer::addTime)
//        .def("subtractTime", (void(Timer::*)(double)) &Timer::subtractTime)
        .def("getOffset", (float(Timer::*)()) &Timer::getOffset)
        .def("setOffset", (void(Timer::*)(float)) &Timer::setOffset)
    ];
}
