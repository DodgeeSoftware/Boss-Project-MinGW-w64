#include "InputSystem.h"

// TODO: replace these static variables with the local callback
int InputSystem::scrollWheelX = 0;
int InputSystem::scrollWheelY = 0;

bool InputSystem::init()
{
    // Send a message to the console
    std::cout << "bool InputSystem::init()" << std::endl;
    // Make sure a null window cannot pass
    if (this->pWindow == 0)
    {
        // Send a message to the console
        std::cout << "*******************************" << std::endl;
        std::cout << "ERROR: Input System, the window provided was null" << std::endl;
        std::cout << "*******************************" << std::endl;
        // Unable to Initialise input system
        return false;
    }
    // Set window reference for the keyboard
    this->keyboard.setWindow(this->pWindow);
    // Set window reference for the mouse
    this->mouse.setWindow(this->pWindow);
    // Initialise keyboard
    if (this->keyboard.init() == false)
        return false;
    // Initialise mouse
    if (this->mouse.init() == false)
        return false;
    // Initialise gamepads
    if (this->initGamePads() == false)
        return false;
    // send a message to the console
    std::cout << "Number of Gamepads found: " << this->gamePads.size() << std::endl;
    // set the was init flag to true
    this->wasInitFlag = true;

    // Send a message to the console
    std::cout << "bool InputSystem::init() success" << std::endl;
    // input system initialisation successful
    return true;
}

void InputSystem::handleEvents()
{
    // pass events to the Keyboard
    this->keyboard.handleEvents();
    // pass events to the Mouse
    this->mouse.handleEvents();
    // pass events to the GamePads
    this->handleEventsGamePads();
}

void InputSystem::update()
{
    // update the keyboard
    this->keyboard.update();
    // update the mouse
    this->mouse.update();
    // update the game pads
    this->updateGamePads();
}

void InputSystem::free()
{
    // Send a message to the console
    std::cout << "InputSystem::free()" << std::endl;
    // free the keyboard
    this->keyboard.free();
    // free the mouse
    this->mouse.free();
    // free gamepads
    this->clearGamePads();
    // Set was init flag to false
    this->wasInitFlag = false;
    // Send a message to the console
    std::cout << "InputSystem::free() Successful" << std::endl;
}

void InputSystem::flush()
{
    // Send a message to the console
    std::cout << "InputSystem::flush()" << std::endl;
    // Flush the Keyboard
    this->keyboard.flush();
    // Flush the Mouse
    this->mouse.flush();
    // Flush GamePads
    for(std::vector<GamePad*>::iterator i = this->gamePads.begin(); i != this->gamePads.end(); i++)
    {
        // Grab a GamePad
        GamePad* pGamePad = *i;
        // Flush a GamePad
        pGamePad->flush();
    }
    // Send a message to the console
    std::cout << "InputSystem::flush() Successful" << std::endl;
}

bool InputSystem::isGamePad(int number)
{
    // If we have a gamepad then return it
    if (number > 0 && number < MAX_GAMEPADS + 1)
        return (this->gamePads.at(number)->getID() != -1); // NOTE: -1 is a dummy gamepad
    // Failed
    return false;
}

bool InputSystem::isGamePad()
{
    // Go through each gamepad
    for(int i = 0; i < MAX_GAMEPADS + 1; i++)
        if (this->gamePads.at(i)->getID() != -1)
            return true;
    // No real GamePads Found
    return false;
}

GamePad* InputSystem::getGamePad(int number)
{
    // If we have a gamepad then return it
    if (number > 0 && number <= MAX_GAMEPADS)
        return this->gamePads.at(number);
    // Failed
    return this->gamePads.at(0); // Zero is a null gamepad
}

bool InputSystem::initGamePads()
{
    // Clear GamePads
    this->clearGamePads();
    // Make a New GamePad
    GamePad* pNullGamePad = new GamePad();
    // Set the window handle for the NULL Gamepad
    pNullGamePad->setWindow(this->pWindow);
    // Initialise the NULL Gamepad
    pNullGamePad->init(-1);
    // Save the null gamePad to position 0
    this->gamePads.push_back(pNullGamePad);
    // Initialise GamePads
    for(unsigned i = 0; i <= MAX_GAMEPADS; i++)
    {
        // If a GamePad by the ID is present process it
        if (glfwJoystickPresent(i) == GL_TRUE)
        {
            // Send a message to the console
            std::cout << "NOTICE: GamePadFound id = " << i << std::endl;
            // Create a new GamePad
            GamePad* pGamePad = new GamePad();
            // Set window reference for the gamepad
            pGamePad->setWindow(this->pWindow);
            // Initialise the gamepad
            pGamePad->init(i);
            // Save this GamePad
            this->gamePads.push_back(pGamePad);
        }
        // Stop searching after 5 pads (4 excluding null) have been found
        if (this->gamePads.size() >= MAX_GAMEPADS + 1)
        {
            // Send a message to the console
            std::cout << "NOTICE: Only support for 4 GamePads. Program won't look for more." << std::endl;
            // Break out of our for loop
            break;
        }
    }
    // Make sure there are always 4 game Pads no matter what!
    if (this->gamePads.size() < MAX_GAMEPADS + 1)
    {
        // Fill our gamepads list with null gamePads
        for (int i = this->gamePads.size(); i <= MAX_GAMEPADS + 1; i++)
        {
            // Create a new GamePad
            GamePad* pGamePad = new GamePad();
            // Set window reference for the gamepad
            pGamePad->setWindow(this->pWindow);
            // Initialise the gamepad
            pGamePad->init(-1); // NOTE: -1 here makes it a null gamepad
            // Save this GamePad
            this->gamePads.push_back(pGamePad);
        }
    }
    // Success
    return true;
}

void InputSystem::handleEventsGamePads()
{
// TODO: Get rid of me
//    // Handle events on the null gamepad
//    this->nullGamePad.handleEvents();
    // pass events to the game pads
    for(std::vector<GamePad*>::iterator i = this->gamePads.begin(); i != this->gamePads.end(); i++)
    {
        // Type cast object to a game pad
        GamePad* pGamePad = *i;
        // Invoke handle events on the gamepad object
        pGamePad->handleEvents();
    }
}

void InputSystem::updateGamePads()
{
// TODO: Get rid of me
//    // Update the null Gamepad
//    this->nullGamePad.update();
    // Update the Gamepads
    for(std::vector<GamePad*>::iterator i = this->gamePads.begin(); i != this->gamePads.end(); i++)
    {
        // Type cast object to a game pad
        GamePad* pGamePad = *i;
        // Update the gamepad object
        pGamePad->update();
    }
}

void InputSystem::clearGamePads()
{
// TODO: Get rid of me
//    // Free the NullGamePad
//    this->nullGamePad.free();
    // free each gamepad one at a time
    for(std::vector<GamePad*>::iterator i = this->gamePads.begin(); i != this->gamePads.end(); i++)
    {
        // Type cast object to a game pad
        GamePad* pGamePad = *i;
        // close a GamePad
        pGamePad->free();
        // Delete GamePad
        delete pGamePad;
    }
    // Clear the game pad map
    this->gamePads.clear();
}

bool InputSystem::addGamePadByID(int id)
{
    // Send a message to the console
    std::cout << "bool InputSystem::addGamePadByID(" << id << ")" << std::endl;
    // Count Available GamePad Slots
    int availableGamePadSlots = 0;
    for (int i = 1; i < this->gamePads.size(); i++)
        if (this->gamePads.at(i)->getID() == -1)
            availableGamePadSlots++;
    if (availableGamePadSlots == 0)
    {
        // Send a message to the console
        std::cout << "ERROR: no spare slots to add the new GamePad" << std::endl;
        std::cout << "bool InputSystem::addGamePadByID(" << id << ") failed" << std::endl;
    }
    /* Go through each of the GamePads (skipping the
        null GamePad at position 0*/
    for (int i = 1; i < this->gamePads.size(); i++)
    {
        /* Lets overwrite the very first null GamePad
            with our new GamePad*/
        if (this->gamePads.at(i)->getID() == -1)
        {
            // Delete the old GamePad
            delete this->gamePads.at(i);
            // Create a new GamePad
            GamePad* pGamePad = new GamePad();
            // Set window reference for the gamepad
            pGamePad->setWindow(this->pWindow);
            // Initialise the gamepad
            pGamePad->init(id);
            // Yep we are done
            break;
        }
    }
    // Send a message to the console
    std::cout << "bool InputSystem::addGamePadByID(" << id << ") success" << std::endl;
}

void InputSystem::removeGamePadByID(int id)
{
    // Validate GamePadID
    if (id == -1)
        return;
    // free each gamepad one at a time
    for(std::vector<GamePad*>::iterator i = this->gamePads.begin(); i != this->gamePads.end(); i++)
    {
        // Type cast object to a game pad
        GamePad* pGamePad = *i;
        /* If we found a GamePad with this ID
            then remove it */
        if (pGamePad->getID() == id)
        {
            /* TODO: I want to delete the GamePad here
                then replace it with a null gamepad not change
                the GamePad Vector at all! */
            // Delete the GamePad
            delete pGamePad;
            /* Create a new GamePad assigning it to the
                old location*/
            pGamePad = new GamePad();
            // Set window reference for the gamepad
            pGamePad->setWindow(this->pWindow);
            // Initialise the gamepad
            pGamePad->init(-1); // NOTE: -1 here makes it a null gamepad
            // We are done so break
            break;
        }
    }
}

void InputSystem::onKey(int key, int scancode, int action, int mods)
{
    // TODO: implement me
}

void InputSystem::onChar(unsigned int codePoint)
{
    // TODO: implement me
}

void InputSystem::onMouseButton(int button, int action, int mods)
{
    // TODO: implement me
}

void InputSystem::onMouseMove(double newX, double newY)
{
    // TODO: implement me
}

void InputSystem::onMouseEnter(int entered)
{
    // TODO: implement me
}

void InputSystem::onMouseScroll(double scrollX, double scrollY)
{
    // TODO: implement me
}

void InputSystem::onGamePad(int gamePadID, int event)
{
    std::cout << "%%% void InputSystem::onGamePad(int gamePadID, int event)" << std::endl;

    // Validate GamePad
    if (gamePadID == -1)
        return;
    // if a GamePad was Connected
    if (event == GLFW_CONNECTED)
    {
        // Add our GamePadByID
        this->addGamePadByID(gamePadID);
    }
    // if a GamePad was Disconnected
    if (event == GLFW_DISCONNECTED)
    {
        // Add our GamePadByID
        this->removeGamePadByID(gamePadID);
    }
}
