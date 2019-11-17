#include "Timer.h"

Timer::Timer()
{
    this->timeOffset = 0;
    this->startTime = 0;
    this->pausedTime = 0;
    this->totalPausedTime = 0;
    this->pausedFlag = false;
    this->startedFlag = false;
}

Timer::~Timer()
{

}

void Timer::start()
{
    // set the time at which the time started
    this->startTime = glfwGetTime() * 1000.0;
    // last time get delta was called
    this->lastTime = 0.0;
    // Reset paused time
    this->pausedTime = 0.0;
    // set paused status to false
    this->pausedFlag = false;
    // set startedFlag to true
    this->startedFlag = true;
}

void Timer::stop()
{
    // set the start time to 0.0
    this->startTime = 0.0;
    // Reset paused time
    this->pausedTime = 0.0;
    // set pausedflag status to false
    this->pausedFlag = false;
    // set startedFlag to false
    this->startedFlag = false;
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
    if (this->pausedFlag == false)
    {
        // set paused status to true
        this->pausedFlag = true;
        // store the time at which the pause instruction was executed
        this->pausedTime = glfwGetTime() * 1000.0;
    }
}

void Timer::resume()
{
    // if the timer is paused then resume it
    if (this->pausedFlag == true)
    {
        // Add the total amount of paused time to the startTime
        this->startTime += (glfwGetTime() * 1000.0 - this->pausedTime);
        // set paused status to false
        this->pausedFlag = false;
        // Reset paused time
        this->pausedTime = 0.0;
    }
}

double Timer::getTicks()
{
    // If the timer hasn't been started return 0
    if (this->startedFlag == false)
        return 0.0 + this->timeOffset;
    // if the timer is paused return the time at which we paused it
    if (this->pausedFlag == true)
        return this->pausedTime - this->startTime + this->timeOffset;
    // return the total time running
    return glfwGetTime() * 1000.0 - this->startTime + this->timeOffset;
}

double Timer::getDelta()
{
    // If the timer isn't advancing then delta should be 0.0
    if (this->startedFlag == false || this->pausedFlag == true)
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
    // If the timer is paused or stoped return 0
    if (this->pausedFlag == false || this->startedFlag == false)
        return 0.0;
    // Return how long our timer has been paused for
    return glfwGetTime() * 1000.0 - this->pausedTime;
}

bool Timer::isStarted()
{
    return this->startedFlag;
}

bool Timer::isPaused()
{
    return pausedFlag;
}

float Timer::getOffset()
{
    return this->timeOffset;
}

void Timer::setOffset(float offset)
{
    this->timeOffset = offset;
}
