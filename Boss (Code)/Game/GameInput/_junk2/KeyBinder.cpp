#include "KeyBinder.h"

void KeyBinder::addKeyBinding(const char* name, unsigned char ascii)
{
    if (this->isKeyBinding(name) == true)
    {
        std::map<const char*, unsigned char>::iterator i = this->keyMap.find(name);
        i->second = ascii;
    }
    else
    {
        this->keyMap[name] = ascii;
    }
}

void KeyBinder::removeKeyBinding(const char* name)
{
    if (this->isKeyBinding(name) == true)
    {
        std::map<const char*, unsigned char>::iterator i = this->keyMap.find(name);
        this->keyMap.erase(i);
    }
}

unsigned char KeyBinder::getKeyBinding(const char* name)
{
    for(std::map<const char*, unsigned char>::iterator i = this->keyMap.begin(); i != this->keyMap.end(); i ++)
        if (i->first == name)
            return i->second;
    return 0;
}

bool KeyBinder::isKeyBinding(const char* name)
{
    return (this->keyMap.find(name) != this->keyMap.end()) ? true : false;
}

void KeyBinder::clear()
{
    this->keyMap.clear();
}

