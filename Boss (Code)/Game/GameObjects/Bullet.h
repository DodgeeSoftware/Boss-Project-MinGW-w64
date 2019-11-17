#ifndef BULLET_H
#define BULLET_H

#include "GameObject.h"

class Bullet : public GameObject
{
    // *******************************
    // * CONSTRUCTORS / DDESTRUCTORS *
    // *******************************

    public:
        //! Constructor
        Bullet() {}
        //! Destructor
        virtual ~Bullet() {}

    protected:

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

    // ********************
    // * BULLET FUNCTIONS *
    // ********************

    public:
        // Methods and members

    protected:
        // Members and methods
};

#endif // BULLET_H
