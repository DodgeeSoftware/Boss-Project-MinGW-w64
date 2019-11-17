#ifndef GAME_H
#define GAME_H

// C/C++ Includes
#include <iostream>
#include <map>
#include <vector>
#include <Time.h>
#include <ctime>
#include <cstring>

// OS Specific includes
#ifdef _WIN32 || _WIN64 || _WIN7 || _WINXP
    #define GLFW_EXPOSE_NATIVE_WIN32
    #define GLFW_EXPOSE_NATIVE_WGL
    #include <windows.h>
    #include <Tchar.h>
#endif
#ifdef __linux__ || _LINUX
    #define GLFW_EXPOSE_NATIVE_X11
    #define GLFW_EXPOSE_NATIVE_GLX
    #include <X11/Xlib.h>
    #include <X11/Xutil.h>
    #include <X11/Xos.h>
#endif // __linux__
#ifdef TARGET_OS_MAC || _MACOSX
    #define GLFW_EXPOSE_NATIVE_COCOA
    #define GLFW_EXPOSE_NATIVE_NSGL
    #include <Cocoa/Cocoa.h>
#endif // TARGET_OS_MAC

// OpenGL Includes
#include <gl/gl.h>
#include <gl/glu.h>
#include <gl/glext.h>

// OpenGL FrameWork includes
#include <glfw/glfw3.h>
#include <glfw/glfw3native.h>

// Lua
extern "C"
{
    #include "lua.h"
    #include "lualib.h"
    #include "lauxlib.h"
}

// LuaBridge
#include <LuaBridge/LuaBridge.h>

// Game Includes
#include "Version.h"
#include "Globals.h"
#include "GameConfig.h"
#include "GameCameras.h"
#include "GameDrawing.h"
#include "GameInput.h"
#include "GameObjects.h"
#include "GameTimers.h"
#include "GameStates.h"
#include "GameUtils.h"

/** The Game class is the container for the entire application. It is based off a singleton
    design pattern. **/
class Game
{
    // ******************
    // * FRIEND CLASSES *
    // ******************
    friend class DefaultGameState;
    friend class BattleGameState;
    friend class IntroGameState;
    friend class MainMenuGameState;

    // ******************************
    // * CONSTRUCTORS / DESTRUCTORS *
    // ******************************
    /* NOTE: The Contructors/Destructors section is reponsible for creating and
       destorying the game along with setting default parameters */
    public:
        //! Game Destructor
        virtual ~Game();

    protected:
        //! Default Game Constructor
        Game();
        ////! Game Copy constructor
        //Game(const Game& other) {}

    // ************************
    // * OVERLOADED OPERATORS *
    // ************************
    public:
        // Members and methods

    protected:
        // Members and methods

    // ***********************
    // * SINGLETON FUNCTIONS *
    // ***********************
    /* NOTE: This section is for our singleton functions. We
        don't implement a destroy function here rather I clean up
        the Game Class instance when the destructor is called*/
    public:
        //! Create or return a handle to the Game Instance
        static Game* getInstance();

    protected:
        // The single instance of the game class
        static Game* pInstance;

    // ************
    // * GAME RUN *
    // ************
    public:
        //! Game Entry Point
        virtual int run(int argc, char *argv[]);

    // *************
    // * GAME INIT *
    // *************
    /* NOTE: The Init section initialises each and every aspect of the framework */
    public:
        //! Initialise game engine
        virtual bool init();
        //! Initalise Config
        virtual bool initConfig();
        //! Initialise Window
        virtual bool initWindow();
        //! Initialise InputSystem
        virtual bool initInputSystem();
        //! Initialise AudioSystem
        virtual bool initAudio();
        //! Initialise TextSystem
        virtual bool initText();
        //! Initialise Camera
        virtual bool initCamera();

    // ******************************
    // * GAME ENGINE LOOP FUNCTIONS *
    // ******************************
    /* NOTE: These functions are called by the Game's main loop
       and delegate responsibility to a state if one is in use */
    public:
        //! Poll for input and messages
        virtual void handleEvents();
        //! Logic for the game
        virtual void think();
        //! Update the game
        virtual void update();
        //! Draw the game
        virtual void draw();
        //! Draw the GUI
        virtual void drawGUI();
        //! Swap buffers
        virtual void swapBuffers();

    // **********************************
    // * START / STOP/ RUNNING / PAUSED *
    // **********************************
    /* NOTE: The Start/Stop/Running/Paused section provides support for pausing, resuming, starting
       and stopping the application */
    public:
        //! Start the Game
        virtual void start();
        //! Stop the Game
        virtual void stop();
        //! Pause the game
        virtual void pause();
        //! Resume the game
        virtual void resume();
        //! Is the game engine paused
        virtual bool isPaused() { return this->paused; }
        //! Get Paused flag for the game engine
        virtual bool getPaused() { return this->paused; }
        //! Set Paused flag for the game engine
        virtual void setPaused(bool state) { this->paused = state; }
        //! Is the game engine running
        virtual bool isRunning() { return this->running; }
        //! Get Game Engine Running
        virtual bool getRunning() { return this->running; }
        //! Set the running state
        virtual void setRunning(bool running) { this->running = running; }

    protected:
        // Keep track of whether or not the game engine running
        bool running;
        // Keep track of whether or not the game engine is paused
        bool paused;

    // ***************
    // * GAME STATES *
    // ***************
    /* NOTE: The GameStates section creates, changes and deletes GameStates
       and keeps track of the state in use */
    public:
        //! Create all game states
        virtual void createGameStates();
        //! Change the current game state
        virtual void changeGameState(const char* state);
        ////! Change the current game state
        //virtual void changeState(IGameState* pGameState);
        //! Clean up all the game states
        virtual void deleteGameStates();

    protected:
        //! Get GameState
        virtual IGameState* getGameState() { return this->pGameState; }

    protected:
        // Pointer to the current game state
        IGameState* pGameState;
        // Keep track of all the game states
        std::map<std::string, IGameState*> gameStateMap;

    // *****************
    // * GAME SHUTDOWN *
    // *****************
    /* NOTE: The Shutdown Section ends the applicaiton and shuts down each and every subsystem */
    protected:
        //! Shutdown the GameEngine
        virtual void quit();
        //! Shutdown Camera
        virtual void shutdownCamera();
        //! Shutdown InputSystem
        virtual void shutdownInputSystem();
        //! Shutdown Window
        virtual void shutdownWindow();
        //! Shutdown Audio
        virtual void shutdownAudio();
        //! Shutdown Font
        virtual void shutdownFont();
        //! Shutdown Config
        virtual void shutdownConfig();

    protected:
        // Methods and Members

    // ******************
    // * GLFW CALLBACKS *
    // ******************
    /* NOTE: The GLFWCallbacks section provides support for GLFW Callbacks in game::
       They are static functions and to get variables local to Game:: use the method
       Game::getInstance. Because that method is static and returns an instance the other
       Static callbacks will easily make use of it. From there our callbacks can do
       pretty much anything */
    public:
        //! Set Window Callbacks
        virtual void setWindowCallBacks();
        //! Window reposition Callback
        static void windowRepositionCallback(GLFWwindow* pWindow, int newX, int newY);
        //! Window resize Callback
        static void windowResizeCallback(GLFWwindow* pWindow, int newWidth, int newHeight);
        //! Window Close Callback
        static void windowCloseCallback(GLFWwindow* pWindow);
        //! Window Refresh Callback
        static void windowRefreshCallback(GLFWwindow* pWindow);
        //! Window Focus Change Callback
        static void windowFocusChangeCallback(GLFWwindow* pWindow, int state);
        //! Window Iconify Callback
        static void windowIconifyCallback(GLFWwindow* pWindow, int state);
        //! Capture GLFW Errors with a callback function
        static void GLFWErrorCallback(int errorCode, const char* description);
        //! Callback when a mouse button is clicked
        static void mouseButtonFunction(GLFWwindow* pWindow, int button, int action, int mods);
        //! Callback for when the cursor changes position
        static void cursorPositionFunction(GLFWwindow* pWindow, double x, double y);
        //! Callback for when the cursor enters the window or leaves
        static void cursorEnterFunction(GLFWwindow* pWindow, int entered);
        //! Callback for when the mouse scroll whell is spun
        static void scrollFunction(GLFWwindow* pWindow, double x, double y);
        //! Callback for when the user presses a key
        static void keyFunction(GLFWwindow* pWindow, int key, int scancode, int action, int mods);
        //! Callback for when the user presses a unicode key
        static void charFunction(GLFWwindow* pWindow, unsigned int codePoint);
        //! Callback for when the user connects / disconnects a GamePad
        static void gamePadFunction(int gamePadID, int event);

    // ********************
    // * APPLICATION TIME *
    // ********************
    /* NOTE: The Application Time section provides a universal timer which
       starts the moment the Game:: start method is called */
    public:
        //! Get the application time
        virtual float getApplicationTicks() { return this->applicationTicks; }

    protected:
        // Application timer
        Timer applicationTimer;
        // Application Ticks
        float applicationTicks;

    // ***************
    // * GAME CONFIG *
    // ***************
    /* NOTE: The GameConfig section provides a way of loading, saving and setting, and using default hardware settings */
    public:
        //! Load Config
        virtual bool loadConfig();
        //! Save Config
        virtual bool saveConfig();
        //! Reset Config (to hardcoded default settings)
        virtual void resetConfig();
        //! Use Default Config
        virtual void useDefaultConfig();

    public:
        //! Get Config
        virtual GameConfig* getConfig() { return &(this->config); }

    protected:
        // Keep track of the game configuration options
        GameConfig config;

    // **********
    // * WINDOW *
    // **********
    /* NOTE: The Window section is a collection of functions which act upon the window
       such as window caption, minimising a window, restoring a window, setting fullscreen
       or taking a screenshot */
    public:
        //! Set the small application icon
        virtual void setApplicationIconSmall(std::string filename);
        //! Set the big application icon
        virtual void setApplicationIconBig(std::string filename);
        //! Get the window caption
        virtual std::string getWindowCaption();
        //! Set the window caption
        virtual void setWindowCaption(std::string caption);
        //! Is Minimised
        virtual bool isWindowMinimized();
        //! Minimise the application window
        virtual void minimiseWindow();
        //! Restore the application window
        virtual void restoreWindow();
        //! Is the Window Visible
        virtual bool isWindowVisible();
        //! Hide Window
        virtual void hideWindow();
        //! Show Window
        virtual void showWindow();
        //! Save an application screen shot (sequential numbering into the ScreenShots folder)
        virtual bool saveScreenShot();
        //! Save an application screen shot (set the filename and location)
        virtual bool saveScreenShot(std::string filename);
        //! Get WindowX
        virtual int getWindowX();
        //! Set WindowX
        virtual void setWindowX(int windowX);
        //! Get WindowY
        virtual int getWindowY();
        //! Set WindowY
        virtual void setWindowY(int windowY);
        //! Set WindowPosition
        virtual void setWindowPosition(int windowX, int windowY);
        //! Get Window Width
        virtual int getWindowWidth();
        //! Get Window Height
        virtual int getWindowHeight();
        //! Get Window Frame Width
        virtual int getWindowFrameWidth();
        //! Get WindowFrame Height
        virtual int getWindowFrameHeight();
        //! Get ResolutionX
        virtual int getResolutionX();
        //! Get ResolutionY
        virtual int getResolutionY();
        //! Set Resolution
        virtual void setResolution(int xResolution, int yResolution);
        //! Is the Window Resizable
        virtual bool isWindowResizable();
        //! Is the Window Bordered (window border, caption strip etc)
        virtual bool isWindowBordered();
        //! Show the Window Border
        virtual void showWindowBorder();
        //! Hide the Window Border
        virtual void hideWindowBorder();
        //! Get DisplayMode
        virtual int getDisplayMode() { return this->displayMode; }
        //! Set FullScreen
        virtual void fullScreenMode();
        //! Set FullScreenWindow
        virtual void fullScreenWindowedMode();
        //! Set WindowedMode
        virtual void windowedMode();
        //! Turn on Vertical Sync
        virtual void turnOnVSync();
        //! Turn off Vertical Sync
        virtual void turnOffVSync();
        //! Get Clear Colour
        virtual float* getClearColour();
        //! Get Clear Colour Red
        virtual float getClearColourRed();
        //! Get Clear Colour Green
        virtual float getClearColourGreen();
        //! Get Clear Colour Blue
        virtual float getClearColourBlue();
        //! Get Clear Colour Alpha
        virtual float getClearColorAlpha();
        //! Set Clear Colour
        virtual void setClearColour(float red, float green, float blue, float alpha);

    protected:
        // A pointer to the game window
        GLFWwindow* pWindow;
        // Display Mode
        int displayMode;
        // Window Caption
        std::string windowCaption;
        // Window X
        int windowX;
        // Window Y
        int windowY;
        /* TODO: I want to replace these locals and instead ask GLFW what the resolution is
            this will make for cleaner GLFW Callbacks. That could however cause it to slow down
            if the glfw implementation queries the opengl state to get the size   */
        // Horizontal Resolution
        int xResolution;
        // Vertical Resolution
        int yResolution;
        // Small Application Icon
        std::string smallApplicationIcon;
        // Big Application Icon
        std::string bigApplicationIcon;
        // Vertical Sync
        bool vSync;
        // Clear Colour
        float clearColour[4];
        // TODO: Consider window Position as a local and provide accessor at Game::

    // ****************
    // * FRAME TIMING *
    // ****************
    /* NOTE: THe Game Frame Timing section is responsible for keeping the frame rate stable */
    public:
        //! Get frames per second
        virtual float getFPS() { return this->fpsCounter.getFPS(); }
        //! Get the desired FPS
        virtual float getDesiredFPS() { return this->desiredFPS; }
        //! Set the desired FPS
        virtual void setDesiredFPS(float value) { this->desiredFPS = value; }
        //! Is the frame rate being limited
        virtual bool isLimitFramesPerSecond() { return this->limitFramesPerSecond; }
        //! Toggle frame rate limiter
        virtual void setLimitFramesPerSecond(bool state);
        //! Get the renders per second
        virtual float getRPS() { return this->rpsCounter.getFPS(); }

    protected:
        // Frame Timer
        Timer frameTimer;
        // Keep track of the game's frames per second
        FrameCounter fpsCounter;
        // Keep track of the game's renders per second
        FrameCounter rpsCounter;
        // Keep track of the desired frame rate
        float desiredFPS;
        // The current time of update
        float now;
        // The last time update was called
        float then;
        // Accumulator between update calls
        float accumulator;
        // Toggle for the frame rate limiter
        bool limitFramesPerSecond;

    // **************
    // * GAME INPUT *
    // **************
    /* NOTE: The input section exposes keyboard, mouse and gamepads */
    public:
        //! Get Input System
        virtual InputSystem* getInputSystem() { return &(this->inputSystem); }

    protected:
        // Input System
        InputSystem inputSystem;

    // ************
    // * CAMERA2D *
    // ************
    public:
        //! Get Camera2D
        Camera2D* getCamera2D() { return &(this->camera2D); }

    protected:
        // Camera2D
        Camera2D camera2D;

    // ****************
    // * GAME DRAWING *
    // ****************
    /* NOTE: This exposes a handy opengl draw class */
    public:
        //! Get the OpenGLDrawing Class
        virtual OpenGLDraw* getOpenGLDraw() { return OpenGLDraw::getInstance(); }

    protected:
        // Methods and members

    // ****************
    // * GAME OBJECTS *
    // ****************
    public:

    protected:

    // **********
    // * PLAYER *
    // **********
    public:
        //! Load Player
        virtual bool loadPlayer(const char* filename);
        //! Think Player
        virtual void thinkPlayer();
        //! Update Player
        virtual void updatePlayer();
        //! Draw Player
        virtual void drawPlayer();
        //! Clear Player
        virtual void clearPlayer();
        //! Free Player
        virtual void freePlayer();
        //! Get Player
        virtual Player* getPlayer() { return &(this->player); }

    public:
        //! Create Player Bullets
        virtual void createPlayerBullet(float x, float y, float xVel, float yVel);
        //! Update Player Bullets
        virtual void updatePlayerBullets();
        //! Draw Player Bullet
        virtual void drawPlayerBullet();
        //! Clear Player Bullets
        virtual void clearPlayerBullets();
        //! Player Bullets
        virtual std::vector<Bullet>* getPlayerBullets() { return &(this->playerBullets); }

    protected:
        std::vector<Bullet> playerBullets;
        Player player;
        lua_State* pPlayerScript;

    // ********
    // * BOSS *
    // ********
    public:
        //! Load Boss
        virtual bool loadBoss(const char* filename);
        //! Think Boss
        virtual void thinkBoss();
        //! Update Boss
        virtual void updateBoss();
        //! Draw Boss
        virtual void drawBoss();
        //! Clear Bosses
        virtual void clearBoss();
        //! Free Bosses
        virtual void freeBoss();

    public:
        //! Update Boss Bullets
        virtual void updateBossBullets();
        //! Draw Boss Bullets
        virtual void drawBossBullets();
        //! Clear Boss Bullets
        virtual void clearBossBullets();

    public:
        //! Boss Speak
        virtual void bossSpeak(const char* text);

    public:
        //! Create Boss Bullets
        virtual void createBossBullet(float x, float y, float xVel, float yVel);
        //! Boss Bullets
        virtual std::vector<Bullet>* getBossBullets() { return &(this->bossBullets); }
        //! Get Boss
        virtual Boss* getBoss() { return &(this->boss); }

    protected:
        std::vector<Bullet> bossBullets;
        Boss boss;
        lua_State* pBossScript;

    // ********************
    // * LUASTATE FACTORY *
    // ********************
    /* NOTE: We create the luaStates at engine singleton scope
        to ensure that all engine objects can be bound to it.
        The class which uses this lua state should clean it up */
    public:
        //! Makes a LuaState and binds engine objects to it
        static lua_State* makeLuaState();
        //! Panic function for lua errors
        static int luaPanic(lua_State* pLua_State);

    public:
        //! Print text
        virtual void print(const char* text)
        {
            std::cout << text << std::endl;
        }

    protected:
        // Methods and members

    //// *******************
    //// * SCRIPT BINDINGS *
    //// *******************
    //static void bindToLua(lua_State* pLuaState);
};

#endif // GAME_H
