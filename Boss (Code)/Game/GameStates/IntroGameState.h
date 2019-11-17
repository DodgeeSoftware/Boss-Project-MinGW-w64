#ifndef IntroGameState_H
#define IntroGameState_H

#include <cstdio>
/*
#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>
#include <SDL/SDL_Image.h>
#include <SDL/SDL_gfxPrimitives.h>
#include <SDL/SDL_mixer.h>
#include <SDL/SDL_net.h>
*/
#include <GameTimers.h>

#include "IGameState.h"
//#include "Timer.h"
#include <cmath>
/*
extern "C"
{
    #include "lua.h"
    #include "lualib.h"
    #include "lauxlib.h"
}
#include "luabind/luabind.hpp"
*/

class IntroGameState : public IGameState
{
    // *****************************
    // * CONSTRUCTORS / DESTRUCTOR *
    // *****************************
    public:
        //! Default Constructor
        IntroGameState(Game* pGame) : IGameState(pGame) {}
        //! Destructor
        virtual ~IntroGameState() {}

    // *********************
    // * GENERAL FUNCTIONS *
    // *********************
    public:
        //! The state entry callback
        virtual void enter();
        //! Handle incoming input events
        virtual void handleEvents();
        //! Handle all state logic
        virtual void think();
        //! Interpolate to the next frame
        virtual void update();
        //! Draw the state's graphics
        virtual void draw();
        //! Draw the state's GUI objects
        virtual void drawGUI();
        //! A callback for when the state is finished
        virtual void exit();

    public:
        //! Start the State
        virtual void start();
        //! Stop the State()
        virtual void stop();
        //! Pause the State
        virtual void pause();
        //! Resume the State
        virtual void resume();

    private:
        // intro timer
        Timer introSequenceTimer;

};

#endif // IntroGameState_H
