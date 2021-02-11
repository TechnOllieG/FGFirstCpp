#include "Pong.h"
#include "Library.h"

Pong::Pong(Vector2Int screenResolution)
{
    leftBouncerYPos = (screenResolution.y - bouncerWidth) * 0.5;
    rightBouncerYPos = leftBouncerYPos;
}

void Pong::HandleInput(SDL_Event event, float deltaTime)
{
    if (event.type != SDL_KEYDOWN)
        return;

    SDL_Keycode code = event.key.keysym.sym;
    switch (code)
    {
    case SDLK_w:
    {
        leftBouncerYPos -= bouncerMoveSpeed;
        break;
    }
    case SDLK_s:
    {
        leftBouncerYPos += bouncerMoveSpeed;
        break;
    }
    case SDLK_UP:
    {
        rightBouncerYPos -= bouncerMoveSpeed;
        break;
    }
    case SDLK_DOWN:
    {
        rightBouncerYPos += bouncerMoveSpeed;
        break;
    }
    }
}

void Pong::DrawGraphics(SDL_Renderer* renderer, Vector2Int resolution)
{
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    
    SDL_Rect leftRect = SDL_Rect 
    {
        horizontalOffsetFromEdge, leftBouncerYPos - ((int)(bouncerHeight * 0.5)),
        bouncerWidth, bouncerHeight
    };

    SDL_Rect rightRect = SDL_Rect
    {
        resolution.x - horizontalOffsetFromEdge - bouncerWidth, rightBouncerYPos - ((int)(bouncerHeight * 0.5)),
        bouncerWidth, bouncerHeight
    };

    SDL_RenderFillRect(renderer, &leftRect);
    SDL_RenderFillRect(renderer, &rightRect);
}