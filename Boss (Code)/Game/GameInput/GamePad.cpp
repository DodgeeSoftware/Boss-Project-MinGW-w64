#include "GamePad.h"

bool GamePad::init(int ID)
{
    // send a message to the console
    std::cout << "bool GamePad::init(" << ID << ")" << std::endl;
    // Make sure a null window cannot pass
    if (this->pWindow == 0)
    {
        // Send a message to the console
        std::cout << "*******************************" << std::endl;
        std::cout << "ERROR: GamePad Init The window provided was null" << std::endl;
        std::cout << "bool GamePad::init(" << ID << "fail" << std::endl;
        std::cout << "*******************************" << std::endl;
        // Unable to Initialise input system
        return false;
    }
    this->ID = ID;
    if (this->ID == -1)
    {
        // send a message to the console
        std::cout << "NullGamePad detected" << std::endl;
        // success
        return true;
    }
    // Get the name of the gamepad
    this->name = glfwGetJoystickName(this->ID);
    // Set the button count
    this->buttonStates = glfwGetJoystickButtons(this->ID, &(this->buttonCount));
    // Create the toggle key array
    this->toggleButtons = new bool[this->buttonCount];
    // Reset the togglebuttons
    for (int i = 0; i < this->buttonCount; i++)
        this->toggleButtons[i] = false;
    // Set the axis count
    this->axisStates = glfwGetJoystickAxes(this->ID, &(this->axisCount));
    // send a message to the console
    std::cout << "bool GamePad::init(int ID) success" << std::endl;
    // GamePad initialisation was successful
    return true;
}

void GamePad::handleEvents()
{

}

void GamePad::update()
{
    // Only process buttons if gamepad has had a valid ID and actually has buttons
    if (this->buttonCount > 0 && this->ID != -1)
    {
        // buttonStatesOld is a container for a copy of the button states from the last frame
        unsigned char* buttonStatesOld = new unsigned char[this->buttonCount];
        // Make a copy of the buttonState array from the last frame
        for(int i = 0; i < this->buttonCount; i++)
            buttonStatesOld[i] = buttonStates[i];
        // Get the state of all the buttons on the gamepad
        this->buttonStates = glfwGetJoystickButtons(this->ID, &(this->buttonCount));
        // Setup the toggle button button array for this frame
        for(int i = 0; i < this->buttonCount; i++)
        {
            if (buttonStatesOld[i] == 0 && this->buttonStates[i] != 0)
            {
                this->toggleButtons[i] = true;
            }
            else
            {
                this->toggleButtons[i] = false;
            }
        }
        // Clean up the buttonStatesOld
        delete [] buttonStatesOld;
        // Clean up pointers
        buttonStatesOld = 0;
    }

    if (this->axisCount > 0 && this->ID != -1)
    {
        // Get the state of all the Axes on the gamepad
        this->axisStates = glfwGetJoystickAxes(this->ID, &(this->axisCount));
        this->oldDPadX = this->dPadX;
        this->oldDPadY = this->dPadY;
        this->dPadX = this->getAxisX(0);
        this->dPadY = this->getAxisY(0);

        this->downToggle = false;
        this->upToggle = false;
        this->leftToggle = false;
        this->rightToggle = false;

        if (dPadY > 0 && oldDPadY <= 0)
        {
            this->downToggle = false;
            this->upToggle = true;
        }
        if (dPadY < 0 && oldDPadY >= 0)
        {
            this->upToggle = false;
            this->downToggle = true;
        }
        if (dPadX < 0 && oldDPadX >= 0)
        {
            this->rightToggle = false;
            this->leftToggle = true;
        }
        if (dPadX > 0 && oldDPadX <= 0)
        {
            this->leftToggle = false;
            this->rightToggle = true;
        }
    }

    // ************
    // * ANY AXIS *
    // ************
    // Clear Any Axis
    this->setAnyAxis(-1);
    // Go through each axis
    for (int i = 0; i < this->axisCount; i++)
    {
        if (this->getAxis(i) != 0)
        {
            // Set our AnyAxis
            this->setAnyAxis(i);
            // Break out of our for loop
            break;
        }
    }

    // **************
    // * ANY BUTTON * // NOTE: this method biases buttons from lowest to highest
    // **************
    // Clear Any Button
    this->setAnyButton(-1);
    // Go through each button
    for (int i = 0; i < this->buttonCount; i++)
    {
        // If button is down
        if (this->buttonStates[i] != 0)
        {
            // Set our anyButton value
            this->setAnyButton(i);
            // Break our forloop
            break;
        }

    }
}

void GamePad::free()
{
    // If there is a valid gamepad  and buttons then get rid of the button and toggle button array
    if (this->buttonCount > 0 && this->ID != -1 && this->toggleButtons != 0)
    {
        delete [] this->toggleButtons;
        this->toggleButtons = 0;
        delete [] this->buttonStates;
        this->buttonStates = 0;
        // No buttons
        this->buttonCount = 0;
    }

    if (this->axisCount > 0 && this->ID != -1 && this->axisStates != 0)
    {
        delete [] this->axisStates;
        this->axisStates = 0;
        // No Axes
        this->axisCount = 0;
    }
    // No GamePad ID
    this->ID = -1;
}

void GamePad::flush()
{
    // Flush ButtonStates and ToggleButtons
    for(int i = 0; i < this->buttonCount; i++)
    {
        // TODO: We are going to need to find away to fix this :(
        //this->buttonStates[i] = 0; // NOTE: It is not possible to clear button states array because the pointer points to an array of constants
        this->toggleButtons[i] = false;
    }
    // Reset Axes
    for (int i = 0; i < this->axisCount; i++)
    {
        // TODO: We are going to need to find away to fix this :(
        //this->axisStates[i] = 0.0f; // NOTE: It is not possible to clear axisStates array because the pointer points to an array of constants
    }
    // Reset DPad and OldDPad values
    this->oldDPadX = 0.0f;
    this->oldDPadY = 0.0f;
    this->dPadX = 0.0f;
    this->dPadY = 0.0f;
    // Reset DPad Toggles
    this->upToggle = false;
    this->downToggle = false;
    this->leftToggle = false;
    this->rightToggle = false;
}

const char* GamePad::getName()
{
    // If there is no GamePad then return a default name
    if (this->ID == -1)
        return "NULL GAMEPAD";
    // return the name of this gamepad
    return this->name;
}

bool GamePad::isAnyAxis()
{
    return this->anyAxis != -1;
}

int GamePad::getAnyAxis()
{
    return this->anyAxis;
}

void GamePad::setAnyAxis(int anyAxis)
{
    this->anyAxis = anyAxis;
}

bool GamePad::isAnyButton()
{
    // No Button Pushed
    return this->anyButton != -1;
}

int GamePad::getAnyButton()
{
    return this->anyButton;
}

void GamePad::setAnyButton(int anyButton)
{
    this->anyButton = anyButton;
}

float GamePad::getAxisX(int axisNumber)
{
    // if there is no GamePad return 0.0f
    if (this->ID == -1)
        return 0.0f;
    // Make sure the axisNumber number is inside the correct range
    if (axisNumber < 0 || axisNumber > (this->axisCount - 1))
        return 0;
    // Does the buttonState array have any contents?
    if (sizeof(this->axisStates) / sizeof(unsigned char) == 0)
        return 0;
    // Get the horizontal axis value
    int x = (int)(axisStates[axisNumber * 2 + 0] * 256.0f);
    // Compensate for innaccuracy
    if (abs(x) < 35)
        x = 0;
    // Return the required axis
    return x;
}

float GamePad::getAxisY(int axisNumber)
{
    // if there is no GamePad return 0.0f
    if (this->ID == -1)
        return 0.0f;
    // Make sure the axisNumber number is inside the correct range
    if (axisNumber < 0 || axisNumber > (this->axisCount - 1))
        return 0;
    // Does the buttonState array have any contents?
    if (sizeof(this->axisStates) / sizeof(unsigned char) == 0)
        return 0.0f;
    // Get the vertical axis value
    int y = (int)(axisStates[axisNumber * 2 + 1] * 256.0f);
    // Compensate for innaccuracy
    if (abs(y) < 35)
        y = 0.0f;
    // Return the required axis
    return y;
}

float GamePad::getAxis(int axisNumber)
{
    // Does the buttonState array have any contents?
    if (sizeof(this->axisStates) / sizeof(unsigned char) == 0)
        return 0.0f;
    // If AxisNumber is Valid
    if (axisNumber >= 0 && axisNumber < this->axisCount - 1)
    {
        int value = (int)(axisStates[axisNumber] * 256.0f);
        if (abs(value) < 35)
            value = 0.0f;
        // Return value of Axis
        return value;
    }
    // Invalid axis number return 0
    return 0.0f;
}

bool GamePad::isButtonPressed(int buttonNumber)
{
    // if there is no GamePad return false
    if (this->ID == -1)
        return false;
    // Make sure the button number is inside the correct range
    if (buttonNumber < 0 || buttonNumber > (this->buttonCount - 1))
        return false;
    // Does the buttonState array have any contents?
    if (sizeof(this->buttonStates) / sizeof(unsigned char) == 0)
        return false;
    // query whether a button is down
    return (this->buttonStates[buttonNumber] == 0) ? false : true;
}

bool GamePad::isButtonToggled(int buttonNumber)
{
    // if there is no GamePad return false
    if (this->ID == -1)
        return false;
    // Make sure the button number is inside the correct range
    if (buttonNumber < 0 || buttonNumber > (buttonCount - 1))
        return false;
    // Make sure toggleButtons has been initialised
    if (this->toggleButtons == 0)
        return false;
    // Return if a button is being toggled
    return toggleButtons[buttonNumber];
}

bool GamePad::isPressedUp()
{
    return this->getAxisY(0) > 0.0f;
}

bool GamePad::isPressedDown()
{
    return this->getAxisY(0) < 0.0f;
}

bool GamePad::isPressedLeft()
{
    return this->getAxisX(0) < 0.0f;
}

bool GamePad::isPressedRight()
{
    return this->getAxisX(0) > 0.0f;
}

bool GamePad::isToggleUp()
{
    // if there is no GamePad return false
    if (this->ID == -1)
        return false;
    // Return upToggle State
    return this->upToggle;
}

bool GamePad::isToggleDown()
{
    // if there is no GamePad return false
    if (this->ID == -1)
        return false;
    // Return downToggle State
    return this->downToggle;
}

bool GamePad::isToggleLeft()
{
    // if there is no GamePad return false
    if (this->ID == -1)
        return false;
    // Return leftToggle State
    return this->leftToggle;
}

bool GamePad::isToggleRight()
{
    // if there is no GamePad return false
    if (this->ID == -1)
        return false;
    // Return rightToggle State
    return this->rightToggle;
}

bool GamePad::addButtonbind(std::string buttonBinding, int value)
{
    // Make buttonBinding uppercase
    buttonBinding = this->toUpperCase(buttonBinding);
    // Add or overwrite a Buttonbinding
    this->buttonBindings[buttonBinding] = value;
}

bool GamePad::isButtonbind(std::string buttonBinding)
{
    // Make buttonBinding uppercase
    buttonBinding = this->toUpperCase(buttonBinding);
    // Try and find a binding
    std::map<std::string, int>::iterator i = this->buttonBindings.find(buttonBinding);
    // If we found a binding return true
    if (i != this->buttonBindings.end())
        return true;
    // No binding found
    return false;
}

int GamePad::getButtonbinding(std::string buttonBinding)
{
    // Make buttonBinding uppercase
    buttonBinding = this->toUpperCase(buttonBinding);
    // Try and find a binding
    std::map<std::string, int>::iterator i = this->buttonBindings.find(buttonBinding);
    // If we found a binding return it
    if (i != this->buttonBindings.end())
        return i->second;
    // No binding found
    return -1;
}

void GamePad::removeButtonbind(std::string buttonBinding)
{
    // Try and find the Buttonbinding
    std::map<std::string, int>::iterator i = this->buttonBindings.find(buttonBinding);
    // If there was a binding then erase it from the map
    if (i !=  this->buttonBindings.end())
        this->buttonBindings.erase(i);
}

void GamePad::clearButtonbindings()
{
    // Clear Buttonbindings
    this->buttonBindings.clear();
}

bool GamePad::isButtonPressed(std::string buttonBinding)
{
    // Try and find the buttonbinding
    std::map<std::string, int>::iterator i = this->buttonBindings.find(buttonBinding);
    // If there was a binding then return its value
    if (i !=  this->buttonBindings.end())
        return this->isButtonPressed(i->second);
    // KeyBinding is either not down or not bound to anything
    return false;
}

bool GamePad::isButtonToggled(std::string buttonBinding)
{
    // Try and find the buttonbinding
    std::map<std::string, int>::iterator i = this->buttonBindings.find(buttonBinding);
    // If there was a binding then return its value
    if (i !=  this->buttonBindings.end())
        return this->isButtonToggled(i->second);
    // KeyBinding is either not down or not bound to anything
    return false;
}

bool GamePad::addAxisbind(std::string axisBinding, int value)
{
    // Make axisBinding uppercase
    axisBinding = this->toUpperCase(axisBinding);
    // Add or overwrite a Axisbinding
    this->axisBindings[axisBinding] = value;
}

bool GamePad::isAxisbind(std::string axisBinding)
{
    // Make axisBinding uppercase
    axisBinding = this->toUpperCase(axisBinding);
    // Try and find a binding
    std::map<std::string, int>::iterator i = this->axisBindings.find(axisBinding);
    // If we found a binding return true
    if (i != this->axisBindings.end())
        return true;
    // No binding found
    return false;
}

int GamePad::getAxisbinding(std::string axisBinding)
{
    // Make axisBinding uppercase
    axisBinding = this->toUpperCase(axisBinding);
    // Try and find a binding
    std::map<std::string, int>::iterator i = this->axisBindings.find(axisBinding);
    // If we found a binding return it
    if (i != this->axisBindings.end())
        return i->second;
    // No binding found
    return -1;
}

void GamePad::removeAxisbind(std::string axisBinding)
{
    // Try and find the Axisbinding
    std::map<std::string, int>::iterator i = this->axisBindings.find(axisBinding);
    // If there was a binding then erase it from the map
    if (i !=  this->axisBindings.end())
        this->axisBindings.erase(i);
}

void GamePad::clearAxisbindings()
{
    // Clear axisbindings
    this->axisBindings.clear();
}

bool GamePad::isAxisDown(std::string axisBinding)
{
//// TODO: Implement me
//    // Try and find the axisBinding
//    std::map<std::string, int>::iterator i = this->axisBindings.find(axisBinding);
//    // If there was a binding then return its value
//    if (i !=  this->axisBindings.end())
//        return this->isAxisDown(i->second);
    // axisBinding is either not down or not bound to anything
    return false;
}

bool GamePad::isToggleAxis(std::string axisBinding)
{
    /* TODO: can't implement due to design :(
        to achieve this I need to make a big array and perfrom
        toggle operations on each and every axis, which led me
        to further consider the curren't x/y setup I have here
        those axes might be different on different pads hence
        this class needs some work */
    // Axis was Unbound
    return false;
}

// ***************************************
// * SPECIAL FUNCTIONS FOR XBOX GAMEPADS *
// ***************************************

float GamePad::getLeftStickXAxis()
{
    #ifdef _WIN32 || _WIN64 || _WIN7 || _WINXP
        return this->getAxisX(0);
    #endif // _WIN32 || _WIN64

    #ifdef __linux__ || _LINUX
        return this->getAxisX(0);
    #endif // __linux__

    #ifdef TARGET_OS_MAC || _MACOSX
        return this->getAxisX(0);
    #endif // TARGET_OS_MAC
}

float GamePad::getLeftStickYAxis()
{
    #ifdef _WIN32 || _WIN64 || _WIN7 || _WINXP
        return this->getAxisY(0);
    #endif // _WIN32 || _WIN64

    #ifdef __linux__ || _LINUX
        return this->getAxisY(0);
    #endif // __linux__

    #ifdef TARGET_OS_MAC || _MACOSX
        return this->getAxisY(0);
    #endif // TARGET_OS_MAC
}

float GamePad::getRightStickXAxis()
{
    #ifdef _WIN32 || _WIN64 || _WIN7 || _WINXP
        return this->getAxis(4);
    #endif // _WIN32 || _WIN64

    #ifdef __linux__ || _LINUX
        return this->getAxis(4);
    #endif // __linux__

    #ifdef TARGET_OS_MAC || _MACOSX
        return this->getAxis(3);
    #endif // TARGET_OS_MAC
}

float GamePad::getRightStickYAxis()
{
    #ifdef _WIN32 || _WIN64 || _WIN7 || _WINXP
        return this->getAxis(5);
    #endif // _WIN32 || _WIN64

    #ifdef __linux__ || _LINUX
        return this->getAxis(5);
    #endif // __linux__

    #ifdef TARGET_OS_MAC || _MACOSX
        return this->getAxis(4);
    #endif // TARGET_OS_MAC
}

float GamePad::getDPadXAxis()
{
    #ifdef _WIN32 || _WIN64 || _WIN7 || _WINXP
        return this->getAxis(6);
    #endif // _WIN32 || _WIN64

    #ifdef __linux__ || _LINUX
        return this->getAxis(7);
    #endif // __linux__

    #ifdef TARGET_OS_MAC || _MACOSX
        return 0.0f; // NOTE: Not supported on this platform
    #endif // TARGET_OS_MAC
}

float GamePad::getDPadYAxis()
{
    #ifdef _WIN32 || _WIN64 || _WIN7 || _WINXP
        return this->getAxis(7);
    #endif // _WIN32 || _WIN64

    #ifdef __linux__ || _LINUX
        return this->getAxis(8);
    #endif // __linux__

    #ifdef TARGET_OS_MAC || _MACOSX
        return 0.0f;  // NOTE: Not supported on this platform
    #endif // TARGET_OS_MAC
}

float GamePad::getTriggers()
{
    #ifdef _WIN32 || _WIN64 || _WIN7 || _WINXP
        return this->getAxis(3);
    #endif // _WIN32 || _WIN64

    #ifdef __linux__ || _LINUX
        return 0.0f; // NOTE: Not supported on this platform
    #endif // __linux__

    #ifdef TARGET_OS_MAC || _MACOSX
        return 0.0f; // NOTE: Not supported on this platform
    #endif // TARGET_OS_MAC
}

float GamePad::getLeftTrigger()
{
    #ifdef _WIN32 || _WIN64 || _WIN7 || _WINXP
        return this->getAxis(9);
    #endif // _WIN32 || _WIN64

    #ifdef __linux__ || _LINUX
        return this->getAxis(3);
    #endif // __linux__

    #ifdef TARGET_OS_MAC || _MACOSX
        return this->getAxis(5);
    #endif // TARGET_OS_MAC
}

float GamePad::getRightTrigger()
{
    #ifdef _WIN32 || _WIN64 || _WIN7 || _WINXP
        return this->getAxis(10);
    #endif // _WIN32 || _WIN64

    #ifdef __linux__ || _LINUX
        return this->getAxis(6);
    #endif // __linux__

    #ifdef TARGET_OS_MAC || _MACOSX
        return this->getAxis(6);
    #endif // TARGET_OS_MAC
}

bool GamePad::isAButtonPressed()
{
    #ifdef _WIN32 || _WIN64 || _WIN7 || _WINXP
        return this->isButtonPressed(0);
    #endif // _WIN32 || _WIN64

    #ifdef __linux__ || _LINUX
        return this->isButtonPressed(0);
    #endif // __linux__

    #ifdef TARGET_OS_MAC || _MACOSX
        return this->isButtonPressed(16);
    #endif // TARGET_OS_MAC
}

bool GamePad::isAButtonToggled()
{
    #ifdef _WIN32 || _WIN64 || _WIN7 || _WINXP
        return this->isButtonToggled(0);
    #endif // _WIN32 || _WIN64

    #ifdef __linux__ || _LINUX
        return this->isButtonToggled(0);
    #endif // __linux__

    #ifdef TARGET_OS_MAC || _MACOSX
        return this->isButtonToggled(16);
    #endif // TARGET_OS_MAC
}

bool GamePad::isBButtonPressed()
{
    #ifdef _WIN32 || _WIN64 || _WIN7 || _WINXP
        return this->isButtonPressed(1);
    #endif // _WIN32 || _WIN64

    #ifdef __linux__ || _LINUX
        return this->isButtonPressed(1);
    #endif // __linux__

    #ifdef TARGET_OS_MAC || _MACOSX
        return this->isButtonPressed(17);
    #endif // TARGET_OS_MAC
}

bool GamePad::isBButtonToggled()
{
    #ifdef _WIN32 || _WIN64 || _WIN7 || _WINXP
        return this->isButtonToggled(1);
    #endif // _WIN32 || _WIN64

    #ifdef __linux__ || _LINUX
        return this->isButtonToggled(1);
    #endif // __linux__

    #ifdef TARGET_OS_MAC || _MACOSX
        return this->isButtonToggled(17);
    #endif // TARGET_OS_MAC
}

bool GamePad::isXButtonPressed()
{
    #ifdef _WIN32 || _WIN64 || _WIN7 || _WINXP
        return this->isButtonPressed(2);
    #endif // _WIN32 || _WIN64

    #ifdef __linux__ || _LINUX
        return this->isButtonPressed(2);
    #endif // __linux__

    #ifdef TARGET_OS_MAC || _MACOSX
        return this->isButtonPressed(18);
    #endif // TARGET_OS_MAC
}

bool GamePad::isXButtonToggled()
{
    #ifdef _WIN32 || _WIN64 || _WIN7 || _WINXP
        return this->isButtonToggled(2);
    #endif // _WIN32 || _WIN64

    #ifdef __linux__ || _LINUX
        return this->isButtonToggled(2);
    #endif // __linux__

    #ifdef TARGET_OS_MAC || _MACOSX
        return this->isButtonToggled(18);
    #endif // TARGET_OS_MAC
}

bool GamePad::isYButtonPressed()
{
    #ifdef _WIN32 || _WIN64 || _WIN7 || _WINXP
        return this->isButtonPressed(3);
    #endif // _WIN32 || _WIN64

    #ifdef __linux__ || _LINUX
        return this->isButtonPressed(3);
    #endif // __linux__

    #ifdef TARGET_OS_MAC || _MACOSX
        return this->isButtonPressed(19);
    #endif // TARGET_OS_MAC
}

bool GamePad::isYButtonToggled()
{
    #ifdef _WIN32 || _WIN64 || _WIN7 || _WINXP
        return this->isButtonToggled(3);
    #endif // _WIN32 || _WIN64

    #ifdef __linux__ || _LINUX
        return this->isButtonToggled(3);
    #endif // __linux__

    #ifdef TARGET_OS_MAC || _MACOSX
        return this->isButtonToggled(19);
    #endif // TARGET_OS_MAC
}

bool GamePad::isLeftBumperButtonPressed()
{
    #ifdef _WIN32 || _WIN64 || _WIN7 || _WINXP
        return this->isButtonPressed(4);
    #endif // _WIN32 || _WIN64

    #ifdef __linux__ || _LINUX
        return this->isButtonPressed(4);
    #endif // __linux__

    #ifdef TARGET_OS_MAC || _MACOSX
        return this->isButtonPressed(13);
    #endif // TARGET_OS_MAC
}

bool GamePad::isLeftBumperButtonToggled()
{
    #ifdef _WIN32 || _WIN64 || _WIN7 || _WINXP
        return this->isButtonToggled(4);
    #endif // _WIN32 || _WIN64

    #ifdef __linux__ || _LINUX
        return this->isButtonToggled(4);
    #endif // __linux__

    #ifdef TARGET_OS_MAC || _MACOSX
        return this->isButtonToggled(13);
    #endif // TARGET_OS_MAC
}

bool GamePad::isRightBumperButtonPressed()
{
    #ifdef _WIN32 || _WIN64 || _WIN7 || _WINXP
        return this->isButtonPressed(5);
    #endif // _WIN32 || _WIN64

    #ifdef __linux__ || _LINUX
        return this->isButtonPressed(5);
    #endif // __linux__

    #ifdef TARGET_OS_MAC || _MACOSX
        return this->isButtonPressed(14);
    #endif // TARGET_OS_MAC
}

bool GamePad::isRightBumperButtonToggled()
{
    #ifdef _WIN32 || _WIN64 || _WIN7 || _WINXP
        return this->isButtonToggled(5);
    #endif // _WIN32 || _WIN64

    #ifdef __linux__ || _LINUX
        return this->isButtonToggled(5);
    #endif // __linux__

    #ifdef TARGET_OS_MAC || _MACOSX
        return this->isButtonToggled(14);
    #endif // TARGET_OS_MAC
}

bool GamePad::isBackButtonPressed()
{
    #ifdef _WIN32 || _WIN64 || _WIN7 || _WINXP
        return this->isButtonPressed(6);
    #endif // _WIN32 || _WIN64

    #ifdef __linux__ || _LINUX
        return this->isButtonPressed(6);
    #endif // __linux__

    #ifdef TARGET_OS_MAC || _MACOSX
        return this->isButtonPressed(10);
    #endif // TARGET_OS_MAC
}

bool GamePad::isBackButtonToggled()
{
    #ifdef _WIN32 || _WIN64 || _WIN7 || _WINXP
        return this->isButtonToggled(6);
    #endif // _WIN32 || _WIN64

    #ifdef __linux__ || _LINUX
        return this->isButtonToggled(6);
    #endif // __linux__

    #ifdef TARGET_OS_MAC || _MACOSX
        return this->isButtonToggled(10);
    #endif // TARGET_OS_MAC
}

bool GamePad::isStartButtonPressed()
{
    #ifdef _WIN32 || _WIN64 || _WIN7 || _WINXP
        return this->isButtonPressed(7);
    #endif // _WIN32 || _WIN64

    #ifdef __linux__ || _LINUX
        return this->isButtonPressed(7);
    #endif // __linux__

    #ifdef TARGET_OS_MAC || _MACOSX
        return this->isButtonPressed(9);
    #endif // TARGET_OS_MAC
}

bool GamePad::isStartButtonToggled()
{
    #ifdef _WIN32 || _WIN64 || _WIN7 || _WINXP
        return this->isButtonToggled(7);
    #endif // _WIN32 || _WIN64

    #ifdef __linux__ || _LINUX
        return this->isButtonToggled(7);
    #endif // __linux__

    #ifdef TARGET_OS_MAC || _MACOSX
        return this->isButtonToggled(9);
    #endif // TARGET_OS_MAC
}

bool GamePad::isLeftStickButtonPressed()
{
    #ifdef _WIN32 || _WIN64 || _WIN7 || _WINXP
        return this->isButtonPressed(8);
    #endif // _WIN32 || _WIN64

    #ifdef __linux__ || _LINUX
        return this->isButtonPressed(9);
    #endif // __linux__

    #ifdef TARGET_OS_MAC || _MACOSX
        return this->isButtonPressed(11);
    #endif // TARGET_OS_MAC
}

bool GamePad::isLeftStickButtonToggled()
{
    #ifdef _WIN32 || _WIN64 || _WIN7 || _WINXP
        return this->isButtonToggled(8);
    #endif // _WIN32 || _WIN64

    #ifdef __linux__ || _LINUX
        return this->isButtonToggled(9);
    #endif // __linux__

    #ifdef TARGET_OS_MAC || _MACOSX
        return this->isButtonToggled(11);
    #endif // TARGET_OS_MAC
}

bool GamePad::isRightStickButtonPressed()
{
    #ifdef _WIN32 || _WIN64 || _WIN7 || _WINXP
        return this->isButtonPressed(9);
    #endif // _WIN32 || _WIN64

    #ifdef __linux__ || _LINUX
        return this->isButtonPressed(10);
    #endif // __linux__

    #ifdef TARGET_OS_MAC || _MACOSX
        return this->isButtonPressed(12);
    #endif // TARGET_OS_MAC
}

bool GamePad::isRightStickButtonToggled()
{
    #ifdef _WIN32 || _WIN64 || _WIN7 || _WINXP
        return this->isButtonToggled(9);
    #endif // _WIN32 || _WIN64

    #ifdef __linux__ || _LINUX
        return this->isButtonToggled(10);
    #endif // __linux__

    #ifdef TARGET_OS_MAC || _MACOSX
        return this->isButtonToggled(12);
    #endif // TARGET_OS_MAC
}

bool GamePad::isDPadUpButtonPressed()
{
    #ifdef _WIN32 || _WIN64 || _WIN7 || _WINXP
        /* TODO: get this behaviour working!
            currently always return false, because on windows, Up on the DPad is an axis
            I want it to grab the actual axis value */
        return false;
    #endif // _WIN32 || _WIN64

    #ifdef __linux__ || _LINUX
        return this->isButtonPressed(13);
    #endif // __linux__

    #ifdef TARGET_OS_MAC || _MACOSX
        return this->isButtonPressed(5);
    #endif // TARGET_OS_MAC
}

bool GamePad::isDPadUpButtonToggled()
{
    #ifdef _WIN32 || _WIN64 || _WIN7 || _WINXP
        /* TODO: get this behaviour working!
            currently always return false, because on windows, Up on the DPad is an axis
            I want it to grab the actual axis value */
        return false;
    #endif // _WIN32 || _WIN64

    #ifdef __linux__ || _LINUX
        return this->isButtonToggled(13);
    #endif // __linux__

    #ifdef TARGET_OS_MAC || _MACOSX
        return this->isButtonToggled(5);
    #endif // TARGET_OS_MAC
}

bool GamePad::isDPadDownButtonPressed()
{
    #ifdef _WIN32 || _WIN64 || _WIN7 || _WINXP
        /* TODO: get this behaviour working!
            currently always return false, because on windows, Down on the DPad is an axis
            I want it to grab the actual axis value */
        return false;
    #endif // _WIN32 || _WIN64

    #ifdef __linux__ || _LINUX
        return this->isButtonPressed(14);
    #endif // __linux__

    #ifdef TARGET_OS_MAC || _MACOSX
        return this->isButtonPressed(6);
    #endif // TARGET_OS_MAC
}

bool GamePad::isDPadDownButtonToggled()
{
    #ifdef _WIN32 || _WIN64 || _WIN7 || _WINXP
        /* TODO: get this behaviour working!
            currently always return false, because on windows, Down on the DPad is an axis
            I want it to grab the actual axis value */
        return false;
    #endif // _WIN32 || _WIN64

    #ifdef __linux__ || _LINUX
        return this->isButtonToggled(14);
    #endif // __linux__

    #ifdef TARGET_OS_MAC || _MACOSX
        return this->isButtonToggled(6);
    #endif // TARGET_OS_MAC
}

bool GamePad::isDPadLeftButtonPressed()
{
    #ifdef _WIN32 || _WIN64 || _WIN7 || _WINXP
        /* TODO: get this behaviour working!
            currently always return false, because on windows, Left on the DPad is an axis
            I want it to grab the actual axis value */
        return false;
    #endif // _WIN32 || _WIN64

    #ifdef __linux__ || _LINUX
        return this->isButtonPressed(11);
    #endif // __linux__

    #ifdef TARGET_OS_MAC || _MACOSX
        return this->isButtonPressed(7);
    #endif // TARGET_OS_MAC
}

bool GamePad::isDPadLeftButtonToggled()
{
    #ifdef _WIN32 || _WIN64 || _WIN7 || _WINXP
        /* TODO: get this behaviour working!
            currently always return false, because on windows, Left on the DPad is an axis
            I want it to grab the actual axis value */
        return false;
    #endif // _WIN32 || _WIN64

    #ifdef __linux__ || _LINUX
        return this->isButtonToggled(11);
    #endif // __linux__

    #ifdef TARGET_OS_MAC || _MACOSX
        return this->isButtonToggled(7);
    #endif // TARGET_OS_MAC
}

bool GamePad::isDPadRightButtonPressed()
{
    #ifdef _WIN32 || _WIN64 || _WIN7 || _WINXP
        /* TODO: get this behaviour working!
            currently always return false, because on windows, Right on the DPad is an axis
            I want it to grab the actual axis value */
        return false;
    #endif // _WIN32 || _WIN64

    #ifdef __linux__ || _LINUX
        return this->isButtonPressed(12);
    #endif // __linux__

    #ifdef TARGET_OS_MAC || _MACOSX
        return this->isButtonPressed(8);
    #endif // TARGET_OS_MAC
}

bool GamePad::isDPadRightButtonToggled()
{
    #ifdef _WIN32 || _WIN64 || _WIN7 || _WINXP
        /* TODO: get this behaviour working!
            currently always return false, because on windows, Right on the DPad is an axis
            I want it to grab the actual axis value */
        return false;
    #endif // _WIN32 || _WIN64

    #ifdef __linux__ || _LINUX
        return this->isButtonToggled(12);
    #endif // __linux__

    #ifdef TARGET_OS_MAC || _MACOSX
        return this->isButtonToggled(8);
    #endif // TARGET_OS_MAC
}

bool GamePad::isXboxButtonPressed()
{
    #ifdef _WIN32 || _WIN64 || _WIN7 || _WINXP
        return this->isButtonPressed(15);
    #endif // _WIN32 || _WIN64

    #ifdef __linux__ || _LINUX
        return this->isButtonPressed(15);
    #endif // __linux__

    #ifdef TARGET_OS_MAC || _MACOSX
        return this->isButtonPressed(15);
    #endif // TARGET_OS_MAC
}

bool GamePad::isXboxButtonToggled()
{
    #ifdef _WIN32 || _WIN64 || _WIN7 || _WINXP
        return this->isButtonToggled(15);
    #endif // _WIN32 || _WIN64

    #ifdef __linux__ || _LINUX
        return this->isButtonToggled(15);
    #endif // __linux__

    #ifdef TARGET_OS_MAC || _MACOSX
        return this->isButtonToggled(15);
    #endif // TARGET_OS_MAC
}
