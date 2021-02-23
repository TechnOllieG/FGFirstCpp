#include "Input.h"
#include <iostream>

void Input::PollKeys(SDL_Event event)
{
    bool state;

    if (event.type == SDL_KEYDOWN)
        state = true;
    else if (event.type == SDL_KEYUP)
        state = false;
    else
        return;

    SDL_Keycode code = event.key.keysym.sym;
    switch (code)
    {
    case SDLK_w:
    {
        leftBouncerUp = state;
        break;
    }
    case SDLK_s:
    {
        leftBouncerDown = state;
        break;
    }
    case SDLK_UP:
    {
        rightBouncerUp = state;
        break;
    }
    case SDLK_DOWN:
    {
        rightBouncerDown = state;
        break;
    }
    }
}