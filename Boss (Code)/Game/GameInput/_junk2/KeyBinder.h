#ifndef KEYBINDER_H
#define KEYBINDER_H

#include <map>

class KeyBinder
{
    public:
        //! Default Constructor
        KeyBinder()
        {
            this->keyMap.clear();
        }
        //! Destructor
        virtual ~KeyBinder() {}

    public:
        //! Set a keybinding
        void addKeyBinding(const char* name, unsigned char ascii);
        //! Remove a keybinding
        void removeKeyBinding(const char* name);
        //! Get a keybinding
        unsigned char getKeyBinding(const char* name);
        //! Is binding
        bool isKeyBinding(const char* name);
        //! Clear all keybindings
        void clear();

    private:
        // Key map
        std::map<const char*, unsigned char> keyMap;
};

#endif // KEYBINDER_H
