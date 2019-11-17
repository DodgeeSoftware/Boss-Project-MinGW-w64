#include "Bindings.h"

bool Bindings::loadBindings(std::string filename)
{
    // File names must be longer than zero characters
    if (filename.size() == 0)
    {
        // Send a message to the console
        std::cout << "Cannot open XML document because the filename parameter supplied is blank." << std::endl;
        // Unable to load file
        return false;
    }
    // Attempt to load the bindings file. Capturing exceptions as they occur
    try
    {
        // Load the configuration file
        bindingsFile.LoadFile(filename);
    }
    catch(ticpp::Exception& error)
    {
        // Send the filename of the file which failed to load to the console
        std::cout << "Unable to open XML file: " << filename.c_str() << std::endl;
        // Send the details of the exception to the console
        std::cout << "TiCPP error:\n" << error.m_details << std::endl;
        // There was an error loading the bindings file
        return false;
    }
    // Find the root node
    ticpp::Element* rootElement = bindingsFile.FirstChildElement("Bindings", false);
    // If the bindings tag doesnt exists return false
    if (rootElement == 0)
    {
        std::cout << "Bindings Tag not found" << std::endl;
        return false;
    }
    // Get the keybindings node
    ticpp::Element* keybindingsElement = rootElement->FirstChildElement("KeyBindings", false);
    if (keybindingsElement != 0)
    {
        std::cout << "Key Bindings List" << std::endl;
        ticpp::Iterator<ticpp::Element> i;
        for(i = i.begin(keybindingsElement); i != i.end(); i++)
        {
            std::string name;
            unsigned int ascii;
            i->GetAttribute("name", &name, false);
            i->GetAttribute("ascii", &ascii, false);
            std::cout << "Name: " << name << std::endl;
            std::cout << "ASCII: " << ascii << std::endl;
            keyBinder.addKeyBinding(name.c_str(), ascii);
        }
    }
    // TODO: Implement the mouse bindings
    // Get the keybindings node
    ticpp::Element* mousebindingsElement = rootElement->FirstChildElement("MouseBindings", false);
    if (mousebindingsElement != 0)
    {
        std::cout << "Mouse Bindings List" << std::endl;
        ticpp::Iterator<ticpp::Element> i;
        for(i = i.begin(mousebindingsElement); i != i.end(); i++)
        {
            std::string name;
            //unsigned int ascii;
            i->GetAttribute("name", &name, false);
            //i->GetAttribute("ascii", &ascii, false);
            std::cout << "Name: " << name << std::endl;
            //std::cout << "ASCII: " << ascii << std::endl;
            //mouseBinder.addButtonBinding(name.c_str(), ascii);
        }
    }
    // TODO: Implement the game pad bindings
    ticpp::Element* gamePadBindingsElement = rootElement->FirstChildElement("GamePadBindings", false);
    if (gamePadBindingsElement != 0)
    {
        std::cout << "GamePad Bindings List" << std::endl;
        ticpp::Iterator<ticpp::Element> i;
        for(i = i.begin(gamePadBindingsElement); i != i.end(); i++)
        {
            std::string name;
            //unsigned int ascii;
            i->GetAttribute("name", &name, false);
            //i->GetAttribute("ascii", &ascii, false);
            std::cout << "Name: " << name << std::endl;
            //std::cout << "ASCII: " << ascii << std::endl;
            //gamePadBinder.addButtonBinding(name.c_str(), ascii);
        }
    }
    // *** this space is left blank intentionally ***
    return true;
}

bool Bindings::saveBindings(std::string filename)
{
    // TODO: Implement me
    return false;
}
