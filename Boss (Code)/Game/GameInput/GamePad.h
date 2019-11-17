#ifndef GAMEPAD_H
#define GAMEPAD_H

// C/C++ Inlcudes
#include <iostream>
#include <map>

//// GLEW Includes
//#include <gl/glew.h>
#include <glfw/glfw3.h>

/** The GamePad class is a container for a controller **/
class GamePad
{
    // ******************************
    // * CONSTRUCTORS / DESTRUCTORS *
    // ******************************
    public:
        //! Constructor
        GamePad()
        {
            this->pWindow = 0;
            this->ID = -1;
            this->name = 0;
            this->buttonCount = 0;
            this->buttonStates = 0;
            this->axisCount = 0;
            this->axisStates = 0;
            this->toggleButtons = 0;
            this->upToggle = false;
            this->downToggle = false;
            this->leftToggle = false;
            this->rightToggle = false;
            this->anyAxis = -1;
            this->anyButton = -1;
        }
        //! Destructor
        virtual ~GamePad() {}

    protected:
        ////! Copy constructor
        //GamePad(const GamePad& other) {}

    // ************************
    // * OVERLOADED OPERATORS *
    // ************************
    public:
        // No operators to overload

    protected:
        ////! Assignment operator
        //GamePad& operator=(const GamePad& other) { return *this; }

    // *********************
    // * GENERAL FUNCTIONS *
    // *********************
    public:
        //! Initialise keyboard
        virtual bool init(int ID);
        //! Handle keyboard events
        virtual void handleEvents();
        //! Update GamePad
        virtual void update();
        //! Free GamePad
        virtual void free();

    public:
        //! Flush GamePad
        virtual void flush();

    // ***************************
    // * GAME PAD INFO FUNCTIONS *
    // ***************************
    public:
        //! Get GamePad Name
        virtual const char* getName();
        //! Get GamePad ID
        virtual int getID() { return this->ID; }
        // AN AXIS IS THE D PAD / Analog Stick
        //! Get the total number of axes
        virtual int getAxisCount() { return (this->ID != -1) ? this->axisCount : 0; }
        //! Get the total number of buttons
        virtual int getButtonCount() { return (this->ID != -1) ? this->buttonCount : 0; }
        //! Is Axis
        virtual bool isGamePadAxis(int axis)
        {
            if (this->ID != -1)
                return false;
            if (axis >=0 && axis < this->axisCount)
                return true;
            return false;
        }
        //! Is GamePad button
        virtual bool isGamePadButton(int button)
        {
            if (this->ID != -1)
                return false;
            if (button >=0 && button < this->buttonCount)
                return true;
            return false;
        }
        //! IsAnyAxis
        virtual bool isAnyAxis();
        //! GetAnyAxis
        virtual int getAnyAxis();
        //! Set AnyAxis
        virtual void setAnyAxis(int anyAxis);
        //! Is AnyButton
        virtual bool isAnyButton();
        //! GetAnyButton
        virtual int getAnyButton();
        //! Set AnyButton
        virtual void setAnyButton(int anyButton);

    protected:
        // GamePad identifier
        int ID;
        // GamePad Name
        const char* name;
        // Button count
        int buttonCount;
        // Axis count
        int axisCount;
        // anyAxis
        int anyAxis;
        // anyButton
        int anyButton;

    // *************************
    // * GAMEPAD STATE QUERIES *
    // *************************
    public:
        //! Get axis X
        virtual float getAxisX(int axisNumber);
        //! Get axis Y
        virtual float getAxisY(int axisNumber);
        //! Get an Axis by Number (returns in range +/- 1.0f
        virtual float getAxis(int axisNumber);
        //! Is a button on the game pad down
        virtual bool isButtonPressed(int buttonNumber);
        //! Is a button being toggled
        virtual bool isButtonToggled(int buttonNumber);
        //! Is PressedUp
        virtual bool isPressedUp();
        //! Is PressedDown
        virtual bool isPressedDown();
        //! Is PressedLeft
        virtual bool isPressedLeft();
        //! Is PressedRight
        virtual bool isPressedRight();
        //! Is up on the dpad toggled
        virtual bool isToggleUp();
        //! Is down on the dpad toggled
        virtual bool isToggleDown();
        //! Is left on the dpad toggled
        virtual bool isToggleLeft();
        //! Is right on the dpad toggled
        virtual bool isToggleRight();

    protected:
        // Axes state array
        const float* axisStates;
        // Button state array
        const unsigned char* buttonStates;
        // Button Toggle Array
        bool* toggleButtons;
        // GamePad x in last frame
        float oldDPadX;
        // GamePad y in last frame
        float oldDPadY;
        // GamePad x current frame
        float dPadX;
        // GamePad y current frame
        float dPadY;
        // Is GamePad being pushed up? (true only once, while being pushed)
        bool upToggle;
        // Is GamePad being pushed down? (true only once, while being pushed)
        bool downToggle;
        // Is GamePad being pushed left? (true only once, while being pushed)
        bool leftToggle;
        // Is GamePad being pushed right? (true only once, while being pushed)
        bool rightToggle;

    // *******************
    // * BUTTON BINDINGS *
    // *******************
    public:
        //! Add a Buttonbinding
        virtual bool addButtonbind(std::string buttonBinding, int value);
        //! Is ButtonBinding
        virtual bool isButtonbind(std::string buttonBinding);
        //! Get ButtonBinding
        virtual int getButtonbinding(std::string buttonBinding);
        //! Remove Buttonbinding
        virtual void removeButtonbind(std::string buttonBinding);
        //! Clear Buttonbindings
        virtual void clearButtonbindings();
        //! Query a Buttonbinding's state
        virtual bool isButtonPressed(std::string buttonBinding);
        //! Only true for one frame (onbuttondown)
        virtual bool isButtonToggled(std::string buttonBinding);
        //! Get ButtonBindings
        virtual std::map<std::string, int>* getButttonBindings() { return &(this->buttonBindings); }

    protected:
        // Map for keybindings name to buttom
        std::map<std::string, int> buttonBindings;

    // *****************
    // * AXIS BINDINGS *
    // *****************
    public:
        //! Add an Axisbinding
        virtual bool addAxisbind(std::string axisBinding, int value);
        //! Is AxisBinding
        virtual bool isAxisbind(std::string axisBinding);
        //! Get ButtonBinding
        virtual int getAxisbinding(std::string axisBinding);
        //! Remove Axisbinding
        virtual void removeAxisbind(std::string axisBinding);
        //! Clear Axisbindings
        virtual void clearAxisbindings();
        //! Query a Axisbinding's state
        virtual bool isAxisDown(std::string axisBinding);
        //! Only true for one frame (onbuttondown)
        virtual bool isToggleAxis(std::string axisBinding);
        //! Get AxisBindings
        virtual std::map<std::string, int>* getAxisBindings() { return &(this->axisBindings); }

    protected:
        // Map of keybindings name to axis
        std::map<std::string, int> axisBindings;

    // *************************************
    // * SPECIAL XBOX CONTROLLER FUNCTIONS * // TODO: Manage toggles too
    // *************************************
    // Axes
    public:
        //! Get the Left Stick XAxis
        virtual float getLeftStickXAxis();
        //! Get the Left Stick YAxis
        virtual float getLeftStickYAxis();
        //! Get the Right Stick XAxis
        virtual float getRightStickXAxis();
        //! Get the Right Stick YAxis
        virtual float getRightStickYAxis();
        // NOTE: DPad is a button on MacOS and Linux and an Axis on Windows
        //! Get the DPadX Axis
        virtual float getDPadXAxis();
        // NOTE: DPad is a button on MacOS and Linux and an Axis on Windows
        //! Get the DPadY Axis
        virtual float getDPadYAxis();
        //! Get the Triggers (in range 0 to 1 for right trigger and range 0 to -1 for left trigger)
        virtual float getTriggers();
        //! Get Left Trigger
        virtual float getLeftTrigger();
        //! Get Right Trigger
        virtual float getRightTrigger();

    // Buttons
    public:
        //! Is A Button Pressed
        virtual bool isAButtonPressed();
        //! Is A Button Toggled
        virtual bool isAButtonToggled();
        //! Is B Button Pressed
        virtual bool isBButtonPressed();
        //! Is B Button Toggled
        virtual bool isBButtonToggled();
        //! Is X Button Pressed
        virtual bool isXButtonPressed();
        //! Is X Button Toggled
        virtual bool isXButtonToggled();
        //! Is Y Button Pressed
        virtual bool isYButtonPressed();
        //! Is Y Button Toggled
        virtual bool isYButtonToggled();
        //! Is LeftBumper Button Pressed
        virtual bool isLeftBumperButtonPressed();
        //! Is LeftBumper Button Toggled
        virtual bool isLeftBumperButtonToggled();
        //! Is RightBumper Button Pressed
        virtual bool isRightBumperButtonPressed();
        //! Is RightBumper Button Toggled
        virtual bool isRightBumperButtonToggled();
        //! Is Back Button Pressed
        virtual bool isBackButtonPressed();
        //! Is Back Button Toggled
        virtual bool isBackButtonToggled();
        //! Is Start Button Pressed
        virtual bool isStartButtonPressed();
        //! Is Start Button Toggled
        virtual bool isStartButtonToggled();
        //! Is LeftStick Button Pressed
        virtual bool isLeftStickButtonPressed();
        //! Is LeftStick Button Toggled
        virtual bool isLeftStickButtonToggled();
        //! Is RightStick Button Pressed
        virtual bool isRightStickButtonPressed();
        //! Is RightStick Button Toggled
        virtual bool isRightStickButtonToggled();
        // NOTE: DPad is a button on MacOS and Linux and an Axis on Windows
        //! Is Up Button Pressed
        virtual bool isDPadUpButtonPressed();
        // NOTE: DPad is a button on MacOS and Linux and an Axis on Windows
        //! Is Up Button Toggled
        virtual bool isDPadUpButtonToggled();
        // NOTE: DPad is a button on MacOS and Linux and an Axis on Windows
        //! Is Down Button Pressed
        virtual bool isDPadDownButtonPressed();
        // NOTE: DPad is a button on MacOS and Linux and an Axis on Windows
        //! Is Down Button Toggled
        virtual bool isDPadDownButtonToggled();
        // NOTE: DPad is a button on MacOS and Linux and an Axis on Windows
        //! Is Left Button Pressed
        virtual bool isDPadLeftButtonPressed();
        // NOTE: DPad is a button on MacOS and Linux and an Axis on Windows
        //! Is Left Button Toggled
        virtual bool isDPadLeftButtonToggled();
        // NOTE: DPad is a button on MacOS and Linux and an Axis on Windows
        //! Is Right Button Pressed
        virtual bool isDPadRightButtonPressed();
        // NOTE: DPad is a button on MacOS and Linux and an Axis on Windows
        //! Is Right Button Toggled
        virtual bool isDPadRightButtonToggled();
        // NOTE: DPad is a button on MacOS and Linux and an Axis on Windows
        //! Is XBox Button Pressed
        virtual bool isXboxButtonPressed();
        //! Is XBox Toggle Button
        virtual bool isXboxButtonToggled();

    protected:
        // Members and methods

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
    // * UTILITY FUNCTIONS *
    // *********************
    protected:
        //! Convert to upper case
        virtual std::string toUpperCase(std::string text)
        {
            std::string buffer;
            for(unsigned int i = 0; i < text.size(); i++)
            {
                char ch = text.at(i);
                buffer += std::toupper(ch);
            }
            return buffer;
        }
        //! Convert to lower case
        virtual std::string toLowerCase(std::string text)
        {
            std::string buffer;
            for(unsigned int i = 0; i < text.size(); i++)
            {
                char ch = text.at(i);
                buffer += std::tolower(ch);
            }
            return buffer;
        }
};

#endif // GAMEPAD_H
