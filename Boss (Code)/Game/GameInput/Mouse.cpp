#include "Mouse.h"

bool Mouse::init()
{
    std::cout << "bool Mouse::init()" << std::endl;
    // Make sure a null window cannot pass
    if (this->pWindow == 0)
    {
        // Send a message to the console
        std::cout << "*******************************" << std::endl;
        std::cout << "ERROR: Mouse Init, the window provided was null" << std::endl;
        std::cout << "bool Mouse::init() failed" << std::endl;
        std::cout << "*******************************" << std::endl;
        // Unable to Initialise input system
        return false;
    }
    // Send a message to the console
    std::cout << "bool Mouse::init() success" << std::endl;
    // Mouse initialisation was successful
    return true;
}

void Mouse::handleEvents()
{
    // ***********************
    // * MOUSE DRAG HANDLING *
    // ***********************

    // 888888888888888888888

    // Make a horizontal variable for the mouse x position
    double currentX = 0.0;
    // Make a vertical variable for the mouse x position
    double currentY = 0.0;
    // Get the mouse position
    glfwGetCursorPos(this->pWindow, &currentX, &currentY);

    /* If our leftDrag flag is false, our mouse has changed position and left button is down then
        set the leftDragFlag to true and store the starting x,y coordinate pair to track dragging*/
    if (this->leftDrag == false &&
        (this->x != currentX || this->y != currentY) && glfwGetMouseButton(this->pWindow, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS)
    {
        this->leftDrag = true;
        this->leftDragStartX = currentX;
        this->leftDragStartY = currentY;
    }
    /* If the left button is no longer held down */
    if (glfwGetMouseButton(this->pWindow, GLFW_MOUSE_BUTTON_LEFT) == GLFW_RELEASE)
    {
        /* if we were dragging in the last frame */
        if (this->leftDrag == true)
        {
            /* then set the dragRelease flag to true */
            this->leftDragRelease = true;
        }
        else
        {
            /*  otherwise clear the drag release flag  */
            this->leftDragRelease = false;
        }
    }
    // If the left button is no longer held down then turn off our leftDragFlag
    if (glfwGetMouseButton(this->pWindow, GLFW_MOUSE_BUTTON_LEFT) == GLFW_RELEASE)
    {
        this->leftDrag = false;
    }

//    // Left Dragging
//    if (glfwGetMouseButton(this->pWindow, GLFW_MOUSE_BUTTON_LEFT) == GLFW_RELEASE)
//    {
//        if (this->leftDrag == true)
//        {
//            this->leftDragRelease = true;
//        }
//        else
//        {
//            this->leftDragRelease = false;
//        }
//    }
//
//    if (glfwGetMouseButton(this->pWindow, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS && this->lastFrameLeftButton == true)
//    {
//        this->leftDrag = true;
//        this->leftDragRelease = false;
//    }
//    else
//    {
//        this->leftDrag = false;
//    }

    /* If our middleDrag flag is false, our mouse has changed position and middle button is down then
        set the middleDragFlag to true and store the starting x,y coordinate pair to track dragging*/
    if (this->middleDrag == false &&
        (this->x != currentX || this->y != currentY) && glfwGetMouseButton(this->pWindow, GLFW_MOUSE_BUTTON_MIDDLE) == GLFW_PRESS)
    {
        this->middleDrag = true;
        this->middleDragStartX = currentX;
        this->middleDragStartY = currentY;
    }
    /* If the middle button is no longer held down */
    if (glfwGetMouseButton(this->pWindow, GLFW_MOUSE_BUTTON_MIDDLE) == GLFW_RELEASE)
    {
        /* if we were dragging in the last frame */
        if (this->middleDrag == true)
        {
            /* then set the dragRelease flag to true */
            this->middleDragRelease = true;
        }
        else
        {
            /*  otherwise clear the drag release flag  */
            this->middleDragRelease = false;
        }
    }
    // If the middle button is no longer held down then turn off our middleDragFlag
    if (glfwGetMouseButton(this->pWindow, GLFW_MOUSE_BUTTON_MIDDLE) == GLFW_RELEASE)
    {
        this->middleDrag = false;
    }

//    // Middle Dragging
//    if (glfwGetMouseButton(this->pWindow, GLFW_MOUSE_BUTTON_MIDDLE) == GLFW_RELEASE)
//    {
//        if (this->middleDrag == true)
//        {
//            this->middleDragRelease = true;
//        }
//        else
//        {
//            this->middleDragRelease = false;
//        }
//    }
//    if (glfwGetMouseButton(this->pWindow, GLFW_MOUSE_BUTTON_MIDDLE) == GLFW_PRESS && this->lastFrameMiddleButton == true)
//    {
//        this->middleDrag = true;
//        this->middleDragRelease = false;
//    }
//    else
//    {
//        this->middleDrag = false;
//    }


    /* If our rightDrag flag is false, our mouse has changed position and right button is down then
        set the middleDragFlag to true and store the starting x,y coordinate pair to track dragging*/
    if (this->rightDrag == false &&
        (this->x != currentX || this->y != currentY) && glfwGetMouseButton(this->pWindow, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_PRESS)
    {
        this->rightDrag = true;
        this->rightDragStartX = currentX;
        this->rightDragStartY = currentY;
    }
    /* If the right button is no longer held down */
    if (glfwGetMouseButton(this->pWindow, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_RELEASE)
    {
        /* if we were dragging in the last frame */
        if (this->rightDrag == true)
        {
            /* then set the dragRelease flag to true */
            this->rightDragRelease = true;
        }
        else
        {
            /*  otherwise clear the drag release flag  */
            this->rightDragRelease = false;
        }
    }
    // If the right button is no longer held down then turn off our rightDragFlag
    if (glfwGetMouseButton(this->pWindow, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_RELEASE)
    {
        this->rightDrag = false;
    }

//    // Right Dragging
//    if (glfwGetMouseButton(this->pWindow, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_RELEASE)
//    {
//        if (this->rightDrag == true)
//        {
//            this->rightDragRelease = true;
//        }
//        else
//        {
//            this->rightDragRelease = false;
//        }
//    }
//    if (glfwGetMouseButton(this->pWindow, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_PRESS && this->lastFrameRightButton == true)
//    {
//        this->rightDrag = true;
//        this->rightDragRelease = false;
//    }
//    else
//    {
//        this->rightDrag = false;
//    }

    // ***************
    // * MULTICLICKS *
    // ***************
    // Left MultiClick
    if (glfwGetMouseButton(this->pWindow, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS && this->lastFrameLeftButton == false)
    {
        if (this->leftClickCounter == 0)
        {
            this->leftClickTime = glfwGetTime();
        }
        this->leftClickCounter++;
    }
    // Middle MultiClick
    if (glfwGetMouseButton(this->pWindow, GLFW_MOUSE_BUTTON_MIDDLE) == GLFW_PRESS && this->lastFrameMiddleButton == false)
    {
        if (this->middleClickCounter == 0)
        {
            this->middleClickTime = glfwGetTime();
        }
        this->middleClickCounter++;
    }
    // Right MultiClick
    if (glfwGetMouseButton(this->pWindow, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_PRESS && this->lastFrameRightButton == false)
    {
        if (this->rightClickCounter == 0)
        {
            this->rightClickTime = glfwGetTime();
        }
        this->rightClickCounter++;
    }

    // ******************
    // * BUTTON TOGGLES *
    // ******************
    if (glfwGetMouseButton(this->pWindow, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS && this->lastFrameLeftButton == false)
    {
        toggleLeftButton = true;
        this->lastFrameLeftButton = true;
    }
    else
    {
        toggleLeftButton = false;
        //std::cout << "Left Mouse Toggle False" << std::endl;
        this->lastFrameLeftButton = false;
    }

    if (glfwGetMouseButton(this->pWindow, GLFW_MOUSE_BUTTON_MIDDLE) == GLFW_PRESS && this->lastFrameMiddleButton == false)
    {
        toggleMiddleButton = true;
        this->lastFrameMiddleButton = true;
    }
    else
    {
        toggleMiddleButton = false;
        this->lastFrameMiddleButton = false;
    }

    if (glfwGetMouseButton(this->pWindow, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_PRESS && this->lastFrameRightButton == false)
    {
        toggleRightButton = true;
        this->lastFrameRightButton = true;
    }
    else
    {
        toggleRightButton = false;
        this->lastFrameRightButton = false;
    }


//    if (leftClickCounter >= 2)
//    {
//        leftClickCounter = 0;
//        leftClickTimer.stop();
//    }
//    if (middleClickCounter >= 2)
//    {
//        middleClickCounter = 0;
//        middleClickTimer.stop();
//    }
//    if (rightClickCounter >= 2)
//    {
//        rightClickCounter = 0;
//        rightClickTimer.stop();
//    }
}

void Mouse::update()
{
    // **********************************
    // * Keep Tracked of the moved Flag *
    // **********************************
    double xTemp = 0.0f;
    double yTemp = 0.0f;
    // Get the mouse position
    glfwGetCursorPos(this->pWindow, &xTemp, &yTemp);
    if (this->x == xTemp && this->y == yTemp)
    {
        this->movedFlag = false;
    }
    else
    {
        this->movedFlag = true;
    }
    // ***************************
    // * Track the Mous Position *
    // ***************************
    // Get the mouse position
    glfwGetCursorPos(this->pWindow, &(this->x), &(this->y));

    // Keep a record of this frame's button state for the next frame's toggle queries
    this->lastFrameLeftButton = ((glfwGetMouseButton(this->pWindow, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS) ? true : false);
    this->lastFrameRightButton = ((glfwGetMouseButton(this->pWindow, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_PRESS) ? true : false);
    this->lastFrameMiddleButton = ((glfwGetMouseButton(this->pWindow, GLFW_MOUSE_BUTTON_MIDDLE) == GLFW_PRESS) ? true : false);

    // ********************
    // * MULTICLICK LOGIC *
    // ********************
    if (glfwGetTime() > this->leftClickTime + this->multiClickTimeOut)
    {
        this->leftClickTime = 0.0f;
        this->leftClickCounter = 0;
    }
    if (glfwGetTime() > this->middleClickTime + this->multiClickTimeOut)
    {
        this->middleClickTime = 0.0f;
        this->middleClickCounter = 0;
    }
    if (glfwGetTime() > this->rightClickTime + this->multiClickTimeOut)
    {
        this->rightClickTime = 0.0f;
        this->rightClickCounter = 0;
    }

    // ****************
    // * SCROLL WHEEL *
    // ****************
    this->scrollWheelX = 0;
    this->scrollWheelY = 0;
}

void Mouse::free()
{
    // TODO: Implement me
}

void Mouse::flush()
{
    this->x = 0.0f;
    this->y = 0.0f;
    this->toggleLeftButton = false;
    this->toggleMiddleButton = false;
    this->toggleRightButton = false;
    /* TODO: I want to make the mouse class only query the hardware
        during the update and we want to flush them here */
    this->lastFrameLeftButton = false;
    this->lastFrameRightButton = false;
    this->lastFrameMiddleButton = false;
    //Flush Drag
    this->leftDrag = false;
    this->leftDragRelease = false;
    this->middleDrag = false;
    this->middleDragRelease = false;
    this->rightDrag = false;
    this->rightDragRelease = false;
    // Flush ScrollWheel
    this->scrollWheelX = 0.0f;
    this->scrollWheelY = 0.0f;
    // Flush Multiclick counters
    this->leftClickCounter = 0.0f;
    this->middleClickCounter = 0.0f;
    this->rightClickCounter = 0.0f;
}

void Mouse::setPosition(float x, float y)
{
    // set the position of the mouse
    glfwSetCursorPos(this->pWindow, (double)x, (double)y);
}

bool Mouse::isButtonPressed(int button)
{
    return ((glfwGetMouseButton(this->pWindow, button) == GLFW_PRESS) ? true : false);
}

bool Mouse::isButtonToggled(int button)
{
    // TODO: We need to implement toggles differently
    return false;
}

bool Mouse::isLeftMouseButtonPressed()
{
    // return the State of the left mouse button
    return ((glfwGetMouseButton(this->pWindow, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS) ? true : false);
}

bool Mouse::isMiddleMouseButtonPressed()
{
    // return the State of the middle mouse button
    return ((glfwGetMouseButton(this->pWindow, GLFW_MOUSE_BUTTON_MIDDLE) == GLFW_PRESS) ? true : false);
}

bool Mouse::isRightMouseButtonPressed()
{
    // return the State of the right mouse button
    return ((glfwGetMouseButton(this->pWindow, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_PRESS) ? true : false);
}

bool Mouse::isAnyButton()
{
    return this->anyButton != -1;
}

int Mouse::getAnyButton()
{
    return this->anyButton;
}

void Mouse::setAnyButton(int anyButton)
{
    this->anyButton = anyButton;
}

float Mouse::getMultiClickTimeOut()
{
    return multiClickTimeOut;
}

void Mouse::setMultiClickTimeOut(float timeOut)
{
    this->multiClickTimeOut = timeOut;
}

bool Mouse::isDoubleLeftClick()
{
    return (leftClickCounter == 2) ? true: false;
}

bool Mouse::isDoubleMiddleClick()
{
    return (middleClickCounter == 2) ? true: false;
}

bool Mouse::isDoubleRightClick()
{
    return (rightClickCounter == 2) ? true: false;
}

void Mouse::addButtonbind(std::string buttonBinding, int value)
{
    // Make the button binding uppercase
    buttonBinding = this->toUpperCase(buttonBinding);
    // Add or overwrite a buttonBinding
    this->buttonBindings[buttonBinding] = value;
}

bool Mouse::isButtonBind(std::string buttonBinding)
{
    // Make the button binding uppercase
    buttonBinding = this->toUpperCase(buttonBinding);
    // Try and find a button bindings
    std::map<std::string, int>::iterator i = this->buttonBindings.find(buttonBinding);
    // If we find the button binding return true
    if (i != this->buttonBindings.end())
        return true;
    // We didn't find a binding return false
    return false;
}

int Mouse::getButtonBind(std::string buttonBinding)
{
    // Make the button binding uppercase
    buttonBinding = this->toUpperCase(buttonBinding);
    // Try and find a button bindings
    std::map<std::string, int>::iterator i = this->buttonBindings.find(buttonBinding);
    // If we find the button binding return it
    if (i != this->buttonBindings.end())
        return i->second;
    // We didn't find a binding return -1
    return -1;
}

void Mouse::removeButtonbind(std::string buttonBinding)
{
    // Make the button binding uppercase
    buttonBinding = this->toUpperCase(buttonBinding);
    // Try and find the buttonbinding
    std::map<std::string, int>::iterator i = this->buttonBindings.find(buttonBinding);
    // If there was a binding then erase it from the map
    if (i !=  this->buttonBindings.end())
        this->buttonBindings.erase(i);
}

void Mouse::clearButtonbindings()
{
    // Clear buttonbinding
    this->buttonBindings.clear();
}

bool Mouse::isButtonPressed(std::string buttonBinding)
{
    // Make the button binding uppercase
    buttonBinding = this->toUpperCase(buttonBinding);
    // Try and find the buttonBinding
    std::map<std::string, int>::iterator i = this->buttonBindings.find(buttonBinding);
    // If there was a binding then return its value
    if (i !=  this->buttonBindings.end())
        return this->isButtonPressed(i->second);
    // buttonBinding is either not down or not bound to anything
    return false;
}

bool Mouse::isButtonToggled(std::string buttonBinding)
{
/* TODO: To implement this we need
    to change the way the mouse class works
    instead of left/right/middle button
    toggles and flags we need to use an array of buttons
    and an array of toggles. The specific left/right/middle buttons
    should use GLFW_MOUSE_BUTTON_LEFT, GLFW_MOUSE_BUTTON_MIDDLE, GLFW_MOUSE_BUTTON_RIGHT
    to query them so we still have the appearance of hard coded queries. This will allow
    support for mice with multiple buttons */
//    // Try and find the buttonBinding
//    std::map<std::string, int>::iterator i = this->buttonBindings.find(buttonBinding);
//    // If there was a binding then return its value
//    if (i !=  this->buttonBindings.end())
//        return this->isKeyToggled(i->second);
    // buttonBinding is either not down or not bound to anything
    return false;
}
