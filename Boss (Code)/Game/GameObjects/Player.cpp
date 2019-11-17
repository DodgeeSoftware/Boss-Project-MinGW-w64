#include "Player.h"

Player::Player()
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

Player::~Player()
{

}

void Player::think()
{

}

void Player::update()
{
    this->x = this->x + this->xVelocity;
    this->y = this->y + this->yVelocity;
}

void Player::draw()
{
    if (this->visibleFlag == false)
        return;
}

void Player::clear()
{

}

void Player::free()
{

}

void Player::setUnderAttack(bool underAttack)
{
    this->underAttack = underAttack;
}

bool Player::isUnderAttack()
{
    return this->underAttack;
}

bool Player::isDead()
{
    return this->dead;
}

void Player::setDead(bool dead)
{
    this->dead = dead;
}

void Player::setImmuneToDamage(bool immuneToDamage)
{
    this->immuneToDamage = immuneToDamage;
}

bool Player::isImmuneToDamage()
{
    return this->immuneToDamage;
}

float Player::getSpeed()
{
    return this->speed;
}

void Player::setSpeed(float speed)
{
    this->speed = speed;
}
