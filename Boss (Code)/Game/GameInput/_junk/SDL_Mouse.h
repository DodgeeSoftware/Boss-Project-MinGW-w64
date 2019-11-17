#ifndef SDL_MOUSE_H
#define SDL_MOUSE_H

#include <SDL/sdl.h>

class SDL_Mouse
{
    public:
        SDL_Mouse() {}
        virtual ~SDL_Mouse() {}
        float getX();
        float getY();
        bool getButton1();
        bool getButton2();
        bool getButton3();
        bool isLeftClick();
        void update();
        void setVisible(bool state);
        bool getVisible();


    protected:

    private:
        int x;
        int y;
        bool button1;
        bool button2;
        bool button3;
        bool leftClick;
        bool visible;
};

inline float SDL_Mouse::getX() { return this->x; }
inline float SDL_Mouse::getY()  { return this->y; }
inline bool SDL_Mouse::getButton1() { return this->button1; }
inline bool SDL_Mouse::getButton2() { return this->button2; }
inline bool SDL_Mouse::getButton3() { return this->button3; }
inline bool SDL_Mouse::isLeftClick() { return this->leftClick; }
inline void SDL_Mouse::setVisible(bool state)
{
    visible = state;
    if (state == true)
        SDL_ShowCursor(SDL_TRUE);
    else
        SDL_ShowCursor(SDL_FALSE);
}

#endif // MOUSE_H
