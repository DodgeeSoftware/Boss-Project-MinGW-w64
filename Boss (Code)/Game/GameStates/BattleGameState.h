#ifndef __BATTLEGAMESTATE_H
#define __BATTLEGAMESTATE_H

// C/C++ Includes
#include <ctime>
#include <cstdlib>

// Game Includes
#include "GamePhysics.h"
#include "GameTimers.h"

#include "IGameState.h"

class BattleGameState : public IGameState
{
    // *****************************
    // * CONSTRUCTORS / DESTRUCTOR *
    // *****************************
    public:
        //! Default Constructor
        BattleGameState(Game* pGame);
        //! Destructor
        virtual ~BattleGameState();

    protected:
        //! Copy Constructor
        BattleGameState(const BattleGameState& other);

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

    protected:
        // State Timer
        Timer stateTimer;

    // ****************************
    // * INITIALISATION FUNCTIONS *
    // ****************************
    protected:
        //! Init Window
        virtual bool initWindow();
        //! Initialise the scene
        virtual bool initScene();
        //! Init GUI
        virtual bool initGUI();

    // *********************
    // * BATTLE GAME STATE *
    // *********************
    public:
        // Members and methods

    protected:
        //! Restart the Battle
        virtual void restart();
        //! handle when the player's bullets hit the boss
        virtual void doPlayerBulletAndBossBulletCollisions();
        //! handle when the Boss's bullet's strike the player
        virtual void doBossBulletAndPlayerBulletCollisions();
        //! Handle when the player collides with the boss
        virtual void doPlayerBossCollisions();
        //! Bound the player to the world boundaries
        virtual void boundPlayerToWorldBoundaries();
        //! Bound the boss to the world boundaries
        virtual void boundBossToWorldBoundaries();
        //! Bound the Boss Bullets to the world boundaries
        virtual void boundBossBulletsToWorldBoundaries();
        //! Kill Boss
        virtual void killBoss();
        //! Kill the Player
        virtual void killPlayer();

    protected:
        // underAttackTimer
        Timer underAttackTimer;
        // explodeEffectTimer
        Timer explodeEffectTimer;
        // youWinTimer
        Timer youWinTimer;
        // youLoseTimer
        Timer youLoseTimer;
};

#endif // __BATTLEGAMESTATE_H
