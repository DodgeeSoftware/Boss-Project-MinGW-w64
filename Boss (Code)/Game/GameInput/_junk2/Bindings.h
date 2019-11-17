#ifndef BINDINGS_H
#define BINDINGS_H

#include <iostream>
#include <climits>
#include <map>
#include <string>
#include "KeyBinder.h"
#include "MouseBinder.h"
#include "GamePadBinder.h"

// Macro which asks TinyXML to use the TICPP Wrapper
#define TIXML_USE_TICPP
// header for TinyXML
#include <ticpp.h>

class Bindings
{
    public:
        //! Default Constructor
        Bindings() {}
        //! Destructor
        virtual ~Bindings() {}

    public:
        //! Load the keybindings from a file
        bool loadBindings(std::string filename);
        //! Save the keybindings to a file
        bool saveBindings(std::string filename);

    public:
        //! Get the keybinder
        KeyBinder* getKeyBinder() { return &(this->keyBinder); }
        //! Get the mousebinder
        MouseBinder* getMouseBinder() { return &(this->mouseBinder); }
        //! Get the gamepadbinder
        GamePadBinder* getGamePadBinder() { return &(this->gamePadBinder); }

    protected:
        // Keybinder
        KeyBinder keyBinder;
        // Mousebinder
        MouseBinder mouseBinder;
        // Gamepadbinder
        GamePadBinder gamePadBinder;
        // Handle to the configuration file
        ticpp::Document bindingsFile;
};

#endif // BINDINGS_H
