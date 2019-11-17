#ifndef PLAYER_H
#define PLAYER_H

//#include <SDL/sdl.h>
#include "GameObject.h"

class Player : public GameObject
{
    // ***************
    // * CONSTRUCTOR *
    // ***************
    public:
        //! Constructor
        Player();
        //! Destructor
        virtual ~Player();

    protected:
        // Methods and members

    // *************
    // * OPERATORS *
    // *************

    public:
        // Methods and members

    protected:
        // Methods and members

    // *************************
    // * GAME OBJECT FUNCTIONS *
    // *************************

    public:
        //! Think
        virtual void think();
        //! Update
        virtual void update();
        //! Draw
        virtual void draw();
        //! Clear
        virtual void clear();
        //! Free
        virtual void free();

    protected:
        // Members and methods

    // ******************
    // * PLAYER MEMBERS *
    // ******************
    public:
        //! Set Under Attack
        virtual void setUnderAttack(bool underAttack);
        //! Is Under Attack
        virtual bool isUnderAttack();
        //! Is Dead
        virtual bool isDead();
        //! Set Dead
        virtual void setDead(bool dead);
        //! Set Immune To Damage
        virtual void setImmuneToDamage(bool immuneToDamage);
        //! Is Immune To Damage
        virtual bool isImmuneToDamage();
        //! Get Speed
        virtual float getSpeed();
        //! Set Speed
        virtual void setSpeed(float speed);

    protected:
        // underAttack flag
        bool underAttack;
        // dead flag
        bool dead;
        // immuneToDamage flag
        bool immuneToDamage;
        // Speed
        float speed;
};

#endif // PLAYER_H
