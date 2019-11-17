#ifndef MOUSE_H
#define MOUSE_H

// C++ Includes
#include <iostream>
#include <map>

/*
// LUA / LUABind includes
extern "C"
{
    #include <lua.h>
    #include <lualib.h>
    #include <lauxlib.h>
}
#include <luabind/luabind.hpp>
#include <luabind/operator.hpp>*/

//// GLEW Includes
//#include <gl/glew.h>
// GLFW Includes
#include <glfw/glfw3.h>
#include <GLFW/glfw3native.h>

//// include the timer class
//#include "Timer.h"

/** The Mouse Class is a container for the mouse **/
class Mouse
{
    // ***************************
    // * CONTRUCTORS/DESTRUCTORS *
    // ***************************
    public:
        //! Default constructor
        Mouse()
        {
            // WINDOW
            this->pWindow = 0;
            // TODO replace this with button array
            // 888888888888888888888888888888888
            // TOGGLES
            this->toggleLeftButton = false;
            this->toggleRightButton = false;
            this->toggleMiddleButton = false;
            // DRAGGING
            this->leftDrag = false;
            this->leftDragRelease = false;
            this->leftDragStartX = 0.0f;
            this->leftDragStartY = 0.0f;
            this->middleDrag = false;
            this->middleDragRelease = false;
            this->middleDragStartX = 0.0f;
            this->middleDragStartY = 0.0f;
            this->rightDrag = false;
            this->rightDragRelease = false;
            this->rightDragStartX = 0.0f;
            this->rightDragStartY = 0.0f;
            // 888888888888888888888888888888888
            // SCROLL WHEEL
            this->scrollWheelX = 0;
            this->scrollWheelY = 0;
            // MULTICLICK
            this->multiClickTimeOut = 0.5f;
            this->leftClickTime = 0.0f;
            this->leftClickCounter = 0;
            this->middleClickTime = 0.0f;
            this->middleClickCounter = 0;
            this->rightClickTime = 0.0f;
            this->rightClickCounter = 0;
            // AnyButton
            this->anyButton = -1;

        }
        //! Destructor
        virtual ~Mouse() {}

    protected:
        ////! Copy Constructor
        //Mouse(Mouse& other) {}

    // ************************
    // * OVERLOADED OPERATORS *
    // ************************
    public:
        // No operators to overload

    protected:
        ////! Assignment operator
        //Mouse& operator=(const Mouse& other) { return *this; }

    // *********************
    // * GENERAL FUNCTIONS *
    // *********************
    public:
        virtual bool init();
        //! Handle Mouse Events
        virtual void handleEvents();
        //! Update the mouse
        virtual void update();
        //! Close the mouse
        virtual void free();

    public:
        //! Flush the Mouse
        virtual void flush();

    // ***********
    // * VISIBLE *
    // ***********
    public:
        //! Is the cursor visible
        virtual bool isVisible() { return (glfwGetInputMode(this->pWindow, GLFW_CURSOR) == GLFW_CURSOR_NORMAL) ? true : false; }
        //! Set visibility for the mouse
        virtual void setVisibility(bool state) { glfwSetInputMode(this->pWindow, GLFW_CURSOR, (state == true) ? GLFW_CURSOR_NORMAL : GLFW_CURSOR_HIDDEN); }
        //! Show Mouse
        virtual void showMouse() { glfwSetInputMode(this->pWindow, GLFW_CURSOR, true); }
        //! Hide Mouse
        virtual void hideMouse() { glfwSetInputMode(this->pWindow, GLFW_CURSOR, false); }

    protected:
        // Members and method

    // **************
    // * POSITIONAL *
    // **************
    public:
        //! Get the horizontal mouse position
        virtual double getX() { return this->x; }
        //! Get the vertical mouse position
        virtual double getY() { return this->y; }
        //! Set the mouse position
        virtual void setPosition(float x, float y);
        //! Was the mouse moved?
        virtual bool wasMoved() { return this->movedFlag; }

    protected:
        // Horizontal position of the mouse
        double x;
        // Vertical position of the mouse
        double y;
        // track if the mouse has moved between this and the last frame
        bool movedFlag;

    // ****************
    // * BUTTONS DOWN *
    // ****************
    public:
        //! Is Button Down
        virtual bool isButtonPressed(int button);
        //! Get the State of the left mouse button
        virtual bool isLeftMouseButtonPressed();
        //! Get the State of the middle mouse button
        virtual bool isMiddleMouseButtonPressed();
        //! Get the State of the right mouse button
        virtual bool isRightMouseButtonPressed();
        //! IsAnyButton
        virtual bool isAnyButton();
        //! GetAnyButton
        virtual int getAnyButton();
        //! Set AnyButton
        virtual void setAnyButton(int anyButton);

    // ******************
    // * TOGGLE BUTTONS *
    // ******************
    public:
        //! Is Button Toggle
        virtual bool isButtonToggled(int button);
        //! Has the left mouse button being toggled
        virtual bool isLeftButtonToggled() { return this->toggleLeftButton; }
        //! Has the middle mouse button being toggled
        virtual bool isMiddleButtonToggled() { return this->toggleMiddleButton; }
        //! Has the right mouse button being toggled
        virtual bool isRightButtonToggled() { return this->toggleRightButton; }

    protected:
        // Left click toggle
        bool toggleLeftButton;
        // Middle click toggle
        bool toggleMiddleButton;
        // Right click toggle
        bool toggleRightButton;
        // Last frame LeftButton
        bool lastFrameLeftButton;
        // Last frame RightButton
        bool lastFrameRightButton;
        // Last frame MiddleButton
        bool lastFrameMiddleButton;
        // AnyButton
        int anyButton;

    // ************
    // * DRAGGING *
    // ************
    public:
        //! Is the left mouse button being dragged
        virtual bool isLeftDrag() { return this->leftDrag; }
        //! Was the left mouse button being dragged and then let go?
        virtual bool isLeftDragRelease() { return this->leftDragRelease; }
        //! Get LeftDragStartX
        virtual float getLeftDragStartX() { return this->leftDragStartX; }
        //! Get LeftDragStartY
        virtual float getLeftDragStartY() { return this->leftDragStartY; }
        //! Is the middle mouse button being dragged
        virtual bool isMiddleDrag() { return this->middleDrag; }
        //! Was the middle mouse button being dragged and then let go?
        virtual bool isMiddleDragRelease() { return this->middleDragRelease; }
        //! Get MiddleDragStartX
        virtual float getMiddleDragStartX() { return this->middleDragStartX; }
        //! Get MiddleDragStartY
        virtual float getMiddleDragStartY() { return this->middleDragStartY; }
        //! Is the right mouse button being dragged
        virtual bool isRightDrag() { return this->rightDrag; }
        //! Was the right mouse button being dragged and then let go?
        virtual bool isRightDragRelease() { return this->rightDragRelease; }
        //! Get RightDragStartX
        virtual float getRightDragStartX() { return this->rightDragStartX; }
        //! Get RightDragStartY
        virtual float getRightDragStartY() { return this->rightDragStartY; }

    protected:
        // Left Drag flag
        bool leftDrag;
        // Left Drag release
        bool leftDragRelease;
        // Starting co-oridnates of left drag
        float leftDragStartX;
        float leftDragStartY;
        // Middle Drag flag
        bool middleDrag;
        // Middle Drag release
        bool middleDragRelease;
        // Starting co-oridnates of middle drag
        float middleDragStartX;
        float middleDragStartY;
        // Middle Drag flag
        bool rightDrag;
        // Right Drag release
        bool rightDragRelease;
        // Starting co-oridnates of middle drag
        float rightDragStartX;
        float rightDragStartY;

    // ****************
    // * SCROLL WHEEL *
    // ****************
    public:
        //! Get ScrollWheelX
        virtual int getScrollWheelX() { return this->scrollWheelX; }
        //! Set ScrollWheelX
        virtual void setScrollWheelX(int value) { this->scrollWheelX = value; }
        //! Get ScrollWheelY
        virtual int getScrollWheelY() { return this->scrollWheelY; }
        //! Set ScrollWheelY
        virtual void setScrollWheelY(int value) { this->scrollWheelY = value; }

    protected:
        // Int Mousewheel
        int scrollWheelX;
        // Int Mousewheel
        int scrollWheelY;

    // **************
    // * MULTICLICK *
    // **************
    public:
        //! Get double click time out
        virtual float getMultiClickTimeOut();
        //! Set double click time out
        virtual void setMultiClickTimeOut(float timeOut);
        //! Get the number of left clicks within multiClickTimeOut period
        virtual bool isDoubleLeftClick();
        //! Get the number of right clicks within multiClickTimeOut period
        virtual bool isDoubleMiddleClick();
        ///! Get the number of right clicks within multiClickTimeOut period
        virtual bool isDoubleRightClick();

    protected:
        // Multi-click time out
        float multiClickTimeOut;
        // TODO - replace repeated code with an array of mouse buttons
        // 888888888888888888888888
        // Left click time
        double leftClickTime;
        // Left click counter
        int leftClickCounter;
        // Middle click time
        double middleClickTime;
        // Middle click counter
        int middleClickCounter;
        // Right click time
        double rightClickTime;
        // Right click counter
        int rightClickCounter;
        // 888888888888888888888888

    // ************
    // * BINDINGS *
    // ************
    public:
        //! Add a Buttonbinding
        virtual void addButtonbind(std::string buttonBinding, int value);
        //! Is a ButtonBinding
        virtual bool isButtonBind(std::string buttonBinding);
        //! Get a ButtonBinding
        virtual int getButtonBind(std::string buttonBinding);
        //! Remove Buttonbinding
        virtual void removeButtonbind(std::string buttonBinding);
        //! Clear Buttonbindings
        virtual void clearButtonbindings();
        //! Query a Buttonbinding's state
        virtual bool isButtonPressed(std::string buttonBinding);
        //! Only true for one frame (onbuttondown)
        virtual bool isButtonToggled(std::string buttonBinding);
        //! Get Button Bindings
        std::map<std::string, int>* getButtonBindings() { return &(this->buttonBindings); }

    protected:
        // Map for keybindings name to buttom
        std::map<std::string, int> buttonBindings;

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

#endif // MOUSE_H
