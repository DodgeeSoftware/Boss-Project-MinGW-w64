#ifndef IGAMESTATE_H
#define IGAMESTATE_H

class Game;

/** The IGameState Class is the base class from which all game States inherit
    to use correctly in implemented classes be sure that the State's cpp file
    includes "Game.h" and since the callbacks are pure virtual functions you
    must implement them in derived classes **/
class IGameState
{
    public:
        //! Default Constructor
        IGameState(Game* pGame)
        {
            // Set the local pointer to the game class
            this->pGame = pGame;
            // Running flag to true
            this->runningFlag = true;
            // Paused flag to false
            this->pausedFlag = false;
        }
        //! Destructor
        virtual ~IGameState() {}

    protected:
        // Methods and members

    // *********************
    // * GENERAL FUNCTIONS *
    // *********************
    public:
        //! The state entry callback
        virtual void enter() = 0;
        //! Handle incoming input events
        virtual void handleEvents() = 0;
        //! Handle all state logic
        virtual void think() = 0;
        //! Interpolate to the next frame
        virtual void update() = 0;
        //! Draw the state's graphics
        virtual void draw() = 0;
        //! Draw the state's GUI objects
        virtual void drawGUI() = 0;
        //! A callback for when the state is finished
        virtual void exit() = 0;

    public:
        //! Start the State
        virtual void start() = 0;
        //! Stop the State()
        virtual void stop() = 0;
        //! Pause the State
        virtual void pause() = 0;
        //! Resume the State
        virtual void resume() = 0;

    protected:
        // A pointer to the game
        Game* pGame;
        // Running Flag
        bool runningFlag;
        // Paused Flag
        bool pausedFlag;

    // ********************
    // * WINDOW CALLBACKS *
    // ********************
    public:
        //! On Change Resolution
        virtual void onWindowChangeResolution(int resolutionX, int resolutionY) {}
        //! On FullScreen
        virtual void onWindowFullScreen(bool state) {}
        //! On Reposition
        virtual void onWindowReposition(int newX, int newY) {}
        //! On Resize Window
        virtual void onWindowResize(int newWidth, int newHeight) {}
        //! On Close Window
        virtual void onWindowClose() {}
        //! On Window Refesh
        virtual void onWindowRefresh() {}
        //! On Window Focus Change
        virtual void onWindowFocusChange(bool state) {}
        //! On Window Iconify
        virtual void onWindowIconify(bool state) {}

    // **********************
    // * LANGUAGE CALLBACKS *
    // **********************
    public:
        //! On Change Language
        virtual void onChangeLanguageCallBack(const char* language) {}
};

#endif // IGAMESTATE_H
