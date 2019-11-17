#ifndef INPUTSYSTEM_H
#define INPUTSYSTEM_H

#define MAX_GAMEPADS 4

// C/C++ Inlcudes
#include <string>
#include <map>
#include <deque>
#include <vector>
//// GLEW Includes
//#include <gl/glew.h>
// GLFW Includes
#include <glfw/glfw3.h>

// GameInput Includes
#include "Keyboard.h"
#include "Mouse.h"
#include "GamePad.h"


#define GLFW_NULL_GAMEPAD 0,
#define GLFW_PLAYER1_GAMEPAD 1,
#define GLFW_PLAYER2_GAMEPAD 2,
#define GLFW_PLAYER3_GAMEPAD 3,
#define GLFW_PLAYER4_GAMEPAD 4,
#define GLFW_PLAYER5_GAMEPAD 5,
#define GLFW_PLAYER6_GAMEPAD 6,
#define GLFW_PLAYER7_GAMEPAD 7,
#define GLFW_PLAYER8_GAMEPAD 8

/** The InputSystem class is a centralized location for keeping track of
    all input hardware attached to the system. This class keeps track of
    the keyboard, the mouse and game pads. **/
class InputSystem
{
    // ***************************
    // * CONSTRUCTORS/DESTRUCTOR *
    // ***************************
    public:
        //! Default constructor
        InputSystem()
        {
            // GLFW Window
            this->pWindow = 0;
            // Init Flag
            this->wasInitFlag = false;
            // Clear GamePad lists
            this->gamePads.clear();
        }
        //! Destructor
        virtual ~InputSystem() {}

    protected:
        ////! Copy constructor
        //InputSystem(const InputSystem& other) {}

    // ************************
    // * OVERLOADED OPERATORS *
    // ************************
    public:
        // No operators to overload

    protected:
        ////! Assignment operator
        //InputSystem& operator=(const InputSystem& other) { return *this; }

    // **********
    // * WINDOW *
    // **********
    public:
        //! Get Window
        virtual GLFWwindow* getWindow() { return this->pWindow; }
        //! Set Window
        virtual void setWindow(GLFWwindow* pWindow) { this->pWindow = pWindow; }
        //! Is Window
        virtual bool isWindow() { return this->pWindow != 0; }

    protected:
        // A handle to the window collecting input
        GLFWwindow* pWindow;

    // *********************
    // * GENERAL FUNCTIONS *
    // *********************
    public:
        //! Initialise input system
        virtual bool init();
        //! Handle system events
        virtual void handleEvents();
        //! Update the input system
        virtual void update();
        //! Free resources allocated by the input system
        virtual void free();
        //! was the gamepad system initialised
        virtual bool wasInit() { return this->wasInitFlag; } // Note: its possible to use "return SDL_WasInit(SDL_INIT_EVERYTHING) & SDL_INIT_JOYSTICK;" though untested

    public:
        //! Flush the input system (sets everything to false for the frame)
        virtual void flush();

    protected:
        // Has the system been initialised
        bool wasInitFlag;

    // ************************************
    // * KEYBOARD/MOUSE/GAMEPAD ACCESSORS *
    // ************************************
    public:
        //! Get Keyboard
        virtual Keyboard* getKeyboard() { return &(this->keyboard); }
        //! Get Mouse
        virtual Mouse* getMouse() { return &(this->mouse); }
        //! Get GamePad count
        virtual int getGamePadCount() { return this->gamePads.size(); }
        //! Is GamePad
        virtual bool isGamePad(int number);
        //! Is there a GamePad
        virtual bool isGamePad();
        //! Get GamePad
        virtual GamePad* getGamePad(int number);

    // INTERNALLY USED GAMEPAD FUNCTIONS
    protected:
        //! init Gamepads
        virtual bool initGamePads();
        //! Handle events
        virtual void handleEventsGamePads();
        //! Update gamepads
        virtual void updateGamePads();
        //! Clear gamepads
        virtual void clearGamePads();

    protected:
        //! Add GamePad by ID
        virtual bool addGamePadByID(int id);
        //! Remove GamePad by ID
        virtual void removeGamePadByID(int id);

    protected:
        // Keyboard
        Keyboard keyboard;
        // Mouse
        Mouse mouse;
        /* NOTE: A cheap hack to get the scroll wheel from GLFW
                In GLFW 3.0 the glfwGetMouseWheel function was replaced by a static call back
                assumes only one mouse can exists which is pretty reasonable.
                It has to be hacked this way due to the design of GLFW q_q which only allows access
                to the scrollwhell from a c style function callback */
        static int scrollWheelX;
        static int scrollWheelY;
        // GamePad List
        std::vector<GamePad*> gamePads;
        // Null GamePad (used when unable to get a gamepad by id)
        GamePad nullGamePad;

    // *************************
    // * GLFW CALLBACK HANDLER *
    // *************************
    /* TODO: Consider this problem, the callbacks here are defined on a per window basis
        yet windows are required for things such as keypresses ... I need to give this some thought
        in terms of design now */
    // Keyboard Callbacks
    public:
        //! Callback for when the user presses a key
        void onKey(int key, int scancode, int action, int mods);
        //! Callback for when the user presses a unicode key
        void onChar(unsigned int codePoint);

    // Mouse Callbacks
    public:
        //! Callback when a mouse button is clicked
        void onMouseButton(int button, int action, int mods);
        //! Callback for when the cursor changes position
        void onMouseMove(double newX, double newY);
        //! Callback for mouse entering the window
        void onMouseEnter(int entered);
        //! Callback for when the mouse scroll whell is spun
        void onMouseScroll(double scrollX, double scrollY);

    // GamePad Callbacks
    public:
        //! Callback for when the user connects / disconnects a GamePad
        void onGamePad(int gamePadID, int event);

    protected:
        // Methods and Members
};

#endif // INPUTSYSTEM_H
