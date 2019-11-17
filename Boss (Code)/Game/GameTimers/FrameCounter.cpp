#include "FrameCounter.h"

void FrameCounter::start()
{
    // start the FPS timer
    timer.start();
    // reset the frame counter
    frameCounter = 0;
}

void FrameCounter::update()
{
    // has the timer started
    if ( timer.isStarted() == true && timer.isPaused() == false )
    {
        // has 1 second elapsed
        if ( timer.getTicks() > 1000.0f )
        {
            // update the framesPerSecond
            framesPerSecond = frameCounter;
            // reset the timer
            this->start();
        }
        else
        {
            // increment the frame counter
            frameCounter++;
        }
    }
}

void FrameCounter::pause()
{
    // pause the frame rate counter
    timer.pause();
}

void FrameCounter::resume()
{
    // resume the frame rate counter
    timer.resume();
}

void FrameCounter::stop()
{
    // stop the FPS timer
    timer.stop();
    // reset the frame counter
    frameCounter = 0;
}

const char* FrameCounter::getFPSasChar()
{
    std::stringstream ss;
    ss << framesPerSecond;
    return ss.str().c_str();
}
