#include "Physics.h"

namespace Physics
{
/*    bool isCollision(SDL_Rect one, SDL_Rect two, bool eighty)
    {
        double left1, left2;
        double right1, right2;
        double top1, top2;
        double bottom1, bottom2;
        if ( eighty == true )
        {
            left1 = one.x + one.w*.1;
            left2 = two.x + two.w*.1;
            right1 = one.x + one.w*.9;
            right2 = two.x + two.w*.9;
            top1 = one.y + one.h*.1;
            top2 = two.y + two.h*.1;
            bottom1 = one.y + one.h*.9;
            bottom2 = two.y + two.h*.9;
        }
        else
        {
            left1 = one.x;
            left2 = two.x;
            right1 = one.x + one.w;
            right2 = two.x + two.w;
            top1 = one.y;
            top2 = two.y;
            bottom1 = one.y + one.h;
            bottom2 = two.y + two.h;
        }

        // test to see if any side of one is inside two
        if ( bottom1 < top2 )
            return false;
        if ( top1 > bottom2 )
            return false;
        if ( right1 < left2 )
            return false;
        if ( left1 > right2 )
            return false;
        return true;
    }
    */

    /*bool isCollision(SDL_Circle one, SDL_Circle two)
    {
        if (sqrt((two.x - one.x)*(two.x - one.x) + (two.y - one.y)*(two.y - one.y)) < (one.radius + two.radius))
            return true;
        return false;
    }*/

    bool isCollision(float oneX, float oneY, float oneRadius, float twoX, float twoY, float twoRadius)
    {
        if (sqrt((twoX - oneX)*(twoX - oneX) + (twoY - oneY)*(twoY - oneY)) < (oneRadius + twoRadius))
            return true;
        return false;
    }
}
