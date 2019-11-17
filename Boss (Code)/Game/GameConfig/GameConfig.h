#ifndef GAMECONFIG_H
#define GAMECONFIG_H

// C/C++ Includes
#include <iostream>
#include <string.h>
#include <fstream>

class GameConfig
{
    // ***************
    // * CONSTRUCTOR *
    // ***************
    public:
        //! Constructor
        GameConfig();
        //! Destructor
        virtual ~GameConfig();

    protected:
        // Members and methods

    // *************
    // * OPERATORS *
    // *************

    public:
        // Methods and members

    protected:
        // Methods and members

    // *********************
    // * GENERAL FUNCTIONS *
    // *********************
    public:
        //! Load a configuration file
        virtual bool load(std::string filename);
        //! Save a configurations file
        virtual bool save(std::string filename);
        //! Clear the configuration
        virtual void clear();
        //! Send contents of the configuration manager to the console
        virtual void toConsole();

    protected:
        // Methods and members

    // ***************
    // * CONFIG DATA *
    // ***************
    public:
        //! Get width
        virtual int getWidth() { return this->width; }
        //! Set width
        virtual void setWidth(int width) { this->width = width; }
        //! Get Height
        virtual int getHeight() { return this->height; }
        //! Set Height
        virtual void setHeight(int height) { this->height = height; }

    protected:
        // Width of application window
        unsigned int width;
        // Height of application window
        unsigned int height;
};

#endif // GAMECONFIG_H
