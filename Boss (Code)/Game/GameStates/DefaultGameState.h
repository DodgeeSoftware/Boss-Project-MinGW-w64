#ifndef DEFAULTGAMESTATE_H
#define DEFAULTGAMESTATE_H

/*
#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>
#include <SDL/SDL_Image.h>
#include <SDL/SDL_gfxPrimitives.h>
#include <SDL/SDL_mixer.h>
#include <SDL/SDL_net.h>
*/
#include "IGameState.h"
/*
extern "C"
{
    #include "lua.h"
    #include "lualib.h"
    #include "lauxlib.h"
}
#include "luabind/luabind.hpp"
*/
class DefaultGameState : public IGameState
{
    // *****************************
    // * CONSTRUCTORS / DESTRUCTOR *
    // *****************************
    public:
        //! Default Constructor
        DefaultGameState(Game* pGame) : IGameState(pGame) {}
        //! Destructor
        virtual ~DefaultGameState() {}

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

};

#endif // DEFAULTGAMESTATE_H
