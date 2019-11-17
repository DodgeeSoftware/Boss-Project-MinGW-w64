#include "Boss.h"

Boss::Boss()
{
    // set underAttack flag
    this->underAttack = false;
    // set dead flag
    this->dead = false;
    // set immuneToDamage flag
    this->immuneToDamage = false;
    // speed
    this->speed = 4.0f;
}

Boss::~Boss()
{

}

void Boss::think()
{

}

void Boss::update()
{
    this->x = this->x + this->xVelocity;
    this->y = this->y + this->yVelocity;
}

void Boss::draw()
{
    if (this->visibleFlag == false)
        return;
}

void Boss::clear()
{

}

void Boss::free()
{

}

void Boss::setUnderAttack(bool underAttack)
{
    this->underAttack = underAttack;
}

bool Boss::isUnderAttack()
{
    return this->underAttack;
}

bool Boss::isDead()
{
    return this->dead;
}

void Boss::setDead(bool dead)
{
    this->dead = dead;
}

void Boss::setImmuneToDamage(bool immuneToDamage)
{
    this->immuneToDamage = immuneToDamage;
}

bool Boss::isImmuneToDamage()
{
    return this->immuneToDamage;
}

float Boss::getSpeed()
{
    return this->speed;
}

void Boss::setSpeed(float speed)
{
    this->speed = speed;
}
