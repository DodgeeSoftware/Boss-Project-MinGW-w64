#include "GamePadBinder.h"

void GamePadBinder::addButtonBinding(char* name, int button)
{
    if (this->isButtonBinding(name) == true)
    {
        std::map<char*, int>::iterator i = this->buttonMap.find(name);
        i->second = button;
    }
    else
    {
        this->buttonMap[name] = button;
    }
}

void GamePadBinder::removeButtonBinding(char* name)
{
    if (this->isButtonBinding(name) == true)
    {
        std::map<char*, int>::iterator i = this->buttonMap.find(name);
        this->buttonMap.erase(i);
    }
}

int GamePadBinder::getButton(char* name)
{
    for(std::map<char*, int>::iterator i = this->buttonMap.begin(); i != this->buttonMap.end(); i++)
        if (i->first == name)
            return i->second;
    return INT_MAX;
}

bool GamePadBinder::isButtonBinding(char* name)
{
    return (this->buttonMap.find(name) != this->buttonMap.end()) ? true : false;
}

void GamePadBinder::addAxisBinding(char* name, int axis)
{
    if (this->isAxisBinding(name) == true)
    {
        std::map<char*, int>::iterator i = this->axisMap.find(name);
        i->second = axis;
    }
    else
    {
        this->axisMap[name] = axis;
    }
}

void GamePadBinder::removeAxisBinding(char* name)
{
    if (this->isAxisBinding(name) == true)
    {
        std::map<char*, int>::iterator i = this->axisMap.find(name);
        this->axisMap.erase(i);
    }
}

int GamePadBinder::getAxis(char* name)
{
    for(std::map<char*, int>::iterator i = this->axisMap.begin(); i != this->axisMap.end(); i++)
        if (i->first == name)
            return i->second;
    return INT_MAX;
}

bool GamePadBinder::isAxisBinding(char* name)
{
    return (this->axisMap.find(name) != this->axisMap.end()) ? true : false;
}

void GamePadBinder::clear()
{
    this->buttonMap.clear();
    this->axisMap.clear();
}


