#include "Keyboard.h"

bool Keyboard::init()
{
    // send a message to the console
    std::cout << "bool Keyboard::init()" << std::endl;
    // Make sure a null window cannot pass
    if (this->pWindow == 0)
    {
        // Send a message to the console
        std::cout << "*******************************" << std::endl;
        std::cout << "ERROR: Keyboard Init Error: The window provided was null" << std::endl;
        std::cout << "bool Keyboard::init() failed" << std::endl;
        std::cout << "*******************************" << std::endl;
        // Unable to Initialise input system
        return false;
    }
    // Flush the keyboard
    this->flush();
    // build the last frame keys down array
    this->saveKeysDown();
    // populate the get keysdown array
    this->getKeysDown();
    // populate the togglekeysdown array
    this->getToggleKeysDown();
    // send a message to the console
    std::cout << "bool Keyboard::init() success" << std::endl;
    // Keyboard initialisation was successful
    return true;
}

void Keyboard::handleEvents()
{
    // This function is intentially left blank
}

void Keyboard::update()
{
    // build the keydown array
    this->getKeysDown();
    // build the toggle keys array
    this->getToggleKeysDown();
    // build the last frame keys down array
    this->saveKeysDown();
    // Clear anyKey
    this->setAnyKey(-1);
}

void Keyboard::free()
{
    // Flush the keyboard
    this->flush();
}

void Keyboard::flush()
{
    // Initialise three arrays
    for(int i = 0; i < GLFW_KEY_LAST; i++)
    {
        this->keyDownArray[i] = false;
        this->lastFrameKeyDownArray[i] = false;
        this->toggleKeyArray[i] = false;
        //this->toggleKeyMaskArray[i] = true;
    }
}

bool Keyboard::isKeyPressed(int key)
{
    // if the incoming key is pressed than return true
    return this->keyDownArray[key];
}

bool Keyboard::isKeyToggled(int key)
{
    // if the key was pressed
    return this->toggleKeyArray[key];
}

void Keyboard::getKeysDown()
{
    for(unsigned int i = 0; i < GLFW_KEY_LAST; i++)
        this->keyDownArray[i] = ((glfwGetKey(this->pWindow, i) == GLFW_PRESS) ? true : false);
}

void Keyboard::saveKeysDown()
{
    for(unsigned int i = 0; i < GLFW_KEY_LAST; i++)
        this->lastFrameKeyDownArray[i] = this->keyDownArray[i];
}

void Keyboard::getToggleKeysDown()
{
    // Build the togglekey array for the frame
    for(unsigned int i = 0; i < GLFW_KEY_LAST; i++)
    {
        /* If there has been a change between the keydown array and the present state of the keyboard
            then a key has either been pressed or released*/
        if ((this->lastFrameKeyDownArray[i] != this->keyDownArray[i] &&
                this->keyDownArray[i] == true) &&
                this->toggleKeyMaskArray[i] == false)
        {
            this->toggleKeyArray[i] = true;
            this->toggleKeyMaskArray[i] = true;
        }
        else
        {
            this->toggleKeyMaskArray[i] = false;
            this->toggleKeyArray[i] = false;
        }
    }
}

bool Keyboard::isAnyKey()
{
    return anyKey != -1;
}

int Keyboard::getAnyKey()
{
    return anyKey;
}

void Keyboard::setAnyKey(int key)
{
    this->anyKey = key;
}

bool Keyboard::addKeybind(std::string keyBinding, int value)
{
    // Make the KeyBinding Upper case
    keyBinding = this->toUpperCase(keyBinding);
    // Add or overwrite a keybinding
    this->keyBindings[keyBinding] = value;
}

bool Keyboard::isKeybind(std::string keyBinding)
{
    // Make the KeyBinding Upper case
    keyBinding = this->toUpperCase(keyBinding);
    // Try and find the Keybind
    std::map<std::string, int>::iterator i = this->keyBindings.find(keyBinding);;
    // Return true if we found a binding by this name
    if (i != this->keyBindings.end())
        return true;
    // Failure
    return false;
}

int Keyboard::getKeybind(std::string keyBinding)
{
    // Make the KeyBinding Upper case
    keyBinding = this->toUpperCase(keyBinding);
    // If we have a binding returns its value
    if (this->isKeybind(keyBinding) == true)
        return this->keyBindings[keyBinding];
    // Failure
    return -1;
}

void Keyboard::removeKeybind(std::string keyBinding)
{
    // Make the KeyBinding Upper case
    keyBinding = this->toUpperCase(keyBinding);
    // Try and find the keybinding
    std::map<std::string, int>::iterator i = this->keyBindings.find(keyBinding);
    // If there was a binding then erase it from the map
    if (i !=  this->keyBindings.end())
        this->keyBindings.erase(i);
}

void Keyboard::clearKeybindings()
{
    // Clear Keybindings
    this->keyBindings.clear();
}

bool Keyboard::isKeyPressed(std::string keyBinding)
{
    // Make the KeyBinding Upper case
    keyBinding = this->toUpperCase(keyBinding);
    // Try and find the keybinding
    std::map<std::string, int>::iterator i = this->keyBindings.find(keyBinding);
    // If there was a binding then return its value
    if (i !=  this->keyBindings.end())
        return this->isKeyPressed(i->second);
    // KeyBinding is either not down or not bound to anything
    return false;
}

bool Keyboard::isKeyToggled(std::string keyBinding)
{
    // Make the KeyBinding Upper case
    keyBinding = this->toUpperCase(keyBinding);
    // Try and find the keybinding
    std::map<std::string, int>::iterator i = this->keyBindings.find(keyBinding);
    // If there was a binding then return its value
    if (i !=  this->keyBindings.end())
        return this->isKeyToggled(i->second);
    // KeyBinding is either not down or not bound to anything
    return false;
}
