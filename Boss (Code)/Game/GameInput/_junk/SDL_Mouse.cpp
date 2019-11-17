#include "SDL_Mouse.h"

void SDL_Mouse::update()
{
    leftClick = false;
    Uint8 buttonState = SDL_GetMouseState(&x, &y);
    if (button1 == false && buttonState&SDL_BUTTON(1) == true)
    {
        leftClick = true;
    }
    button1 = false;
    button2 = false;
    button3 = false;

    if (buttonState&SDL_BUTTON(1)) button1 = true;
    if (buttonState&SDL_BUTTON(2)) button2 = true;
    if (buttonState&SDL_BUTTON(3)) button3 = true;
}

