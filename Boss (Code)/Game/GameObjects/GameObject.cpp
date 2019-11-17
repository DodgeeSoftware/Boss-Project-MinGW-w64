#include "GameObject.h"

GameObject::GameObject()
{
    this->xVelocity = 0.0f;
    this->yVelocity = 0.0f;
}

GameObject::~GameObject()
{
    //dtor
}

void GameObject::think()
{

}

void GameObject::update()
{
    this->x = this->x + this->xVelocity;
    this->y = this->y + this->yVelocity;
}

void GameObject::draw()
{
    if (this->visibleFlag == false)
        return;
}

void GameObject::clear()
{

}

void GameObject::free()
{

}
