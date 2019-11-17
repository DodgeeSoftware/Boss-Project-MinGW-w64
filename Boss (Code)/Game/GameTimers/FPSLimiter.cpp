#include "FPSLimiter.h"

void FPSLimiter::start()
{
    if (this->limitFramesPerSecond == true)
    {
        this->frameTimer.start();
        this->limitFramesPerSecond = true;
    }
}

void FPSLimiter::update()
{
    // Frame Rate Limiter
    then = now;
    now = (float)frameTimer.getTicks() / 1000.0f;
    accumulator += ((float)now - (float)then);
}

void FPSLimiter::stop()
{
    if (this->limitFramesPerSecond == true)
    {
        this->frameTimer.stop();
        this->limitFramesPerSecond = false;
    }
}

void FPSLimiter::setLimitFramesPerSecond(bool state)
{
    // Reset the present time the frame rate limiter was called
    this->now = 0;
    // Reset the last time the frame rate limiter was called
    this->then = 0;
    // Reset the frame accumulator
    this->accumulator = 0;
    // Toggle the frame timer
    if (limitFramesPerSecond != state)
    {
        // If we are turning on the limit reset the timer else turn it off
        if (state == true)
        {
            // Stop the timer, resetting it
            this->frameTimer.stop();
            // Restart the timer
            this->frameTimer.start();
        }
        else
        {
            // Stop the timer, resetting it
            this->frameTimer.stop();
        }
    }
    // Set the toggle for the frame rate limiter
    this->limitFramesPerSecond = state;
}
