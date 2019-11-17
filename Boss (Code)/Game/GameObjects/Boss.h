#ifndef BOSS_H
#define BOSS_H

#include "GameObject.h"

class Boss : public GameObject
{
    // ***************
    // * CONSTRUCTOR *
    // ***************
    public:
        //! Constructor
        Boss();
        //! Destructor
        virtual ~Boss();

    protected:
        // Members and methods

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

    // ****************
    // * BOSS MEMBERS *
    // ****************

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
        // speed
        float speed;
};

#endif // BOSS_H
