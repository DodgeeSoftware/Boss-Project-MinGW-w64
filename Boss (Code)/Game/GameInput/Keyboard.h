#ifndef KEYBOARD_H
#define KEYBOARD_H

// C++ Includes
#include <iostream>
#include <map>

//// GLEW Includes
//#include <gl/glew.h>
// GLFW Includes
#include <glfw/glfw3.h>

/** The Keyboard Class is a container for the keyboard **/
class Keyboard
{
    // ***************************
    // * CONTRUCTORS/DESTRUCTORS *
    // ***************************
    public:
        //! Default Constructor
        Keyboard()
        {
            // Initialise three arrays
            for(int i = 0; i < GLFW_KEY_LAST; i++)
            {
                this->keyDownArray[i] = false;
                this->lastFrameKeyDownArray[i] = false;
                this->toggleKeyArray[i] = false;
                this->toggleKeyMaskArray[i] = false;
            }
            // AnyButton
            this->anyKey = -1;
        }
        //! Destructor
        virtual ~Keyboard() {}

    protected:
        ////! Copy Constructor
        //Keyboard(Keyboard& other) {}

    // ************************
    // * OVERLOADED OPERATORS *
    // ************************
    public:
        // No public operators

    protected:
        ////! Assignment operator
        //Keyboard& operator=(const Keyboard& other) { return *this; }

    // GENERAL FUNCTIONS
    public:
        //! Initialise keyboard
        virtual bool init();
        //! Handle keyboard events
        virtual void handleEvents();
        //! Update the keyboard
        virtual void update();
        //! Close the keyboard
        virtual void free();

    public:
        //! Flush the Keyboard
        virtual void flush();

    // ***************
    // * KEY QUERIES *
    // ***************
    public:
        //! Query a key's state
        virtual bool isKeyPressed(int key);
        //! Only true for one frame (onkeydown)
        virtual bool isKeyToggled(int key);

    public:
        //! Is AnyKey
        virtual bool isAnyKey();
        //! Get AnyKey
        virtual int getAnyKey();
        //! Set AnyKey
        virtual void setAnyKey(int key);

    protected:
        //! Populate the get KeysDown array
        virtual void getKeysDown();
        //! Populate the Last Frame Key Down Array
        virtual void saveKeysDown();
        //! Populate the toggle keys array
        virtual void getToggleKeysDown();

    protected:
        // Anykey
        int anyKey;
        // Array of keyboard keys
        bool keyDownArray[GLFW_KEY_LAST];
        // Array of keyboard keys for the last frame
        bool lastFrameKeyDownArray[GLFW_KEY_LAST];
        // Pressed key array
        bool toggleKeyArray[GLFW_KEY_LAST];
        // A mask for the toggle key
        bool toggleKeyMaskArray[GLFW_KEY_LAST];

    // ****************
    // * KEY BINDINGS *
    // ****************
    public:
        //! Add a Keybinding
        virtual bool addKeybind(std::string keyBinding, int value);
        //! Is Keybinding
        virtual bool isKeybind(std::string keyBinding);
        //! Get a Keybinding
        virtual int getKeybind(std::string keyBinding);
        //! Remove Keybinding
        virtual void removeKeybind(std::string keyBinding);
        //! Clear Keybindings
        virtual void clearKeybindings();
        //! Query a keybinding's state
        virtual bool isKeyPressed(std::string keyBinding);
        //! Only true for one frame (onkeydown)
        virtual bool isKeyToggled(std::string keyBinding);
        //! Get KeyBindings
        std::map<std::string, int>* getKeyBindings() { return &(this->keyBindings); }

    protected:
        // Map for keybindings name to GLFW key int
        std::map<std::string, int> keyBindings;

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

#endif // KEYBOARD_H
