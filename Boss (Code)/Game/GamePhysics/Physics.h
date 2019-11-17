#ifndef PHYSICS_H
#define PHYSICS_H

#include <cmath>
//#include <SDL/sdl.h>
//#include "SDL_Circle.h"

namespace Physics
{
    //bool isCollision(SDL_Rect one, SDL_Rect two, bool eighty);
    //bool isCollision(SDL_Circle one, SDL_Circle two);
    bool isCollision(float oneX, float oneY, float oneRadius, float twoX, float twoY, float twoRadius);
};

#endif // PHYSICS_H
