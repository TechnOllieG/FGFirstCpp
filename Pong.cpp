#include "Pong.h"

using namespace std;

Pong::Pong(Vector2Int screenResolution)
{
    leftBouncerYPos = (screenResolution.y - bouncerWidth) * 0.5;
    rightBouncerYPos = leftBouncerYPos;
    inputs = Input();
    this->screenResolution = screenResolution;
}

void Pong::HandleInput(SDL_Event event, float deltaTime)
{
    inputs.PollKeys(event);

    if (inputs.leftBouncerDown)
        leftBouncerYPos += bouncerMoveSpeed;

    if(inputs.leftBouncerUp)
        leftBouncerYPos -= bouncerMoveSpeed;

    if (inputs.rightBouncerDown)
        rightBouncerYPos += bouncerMoveSpeed;
    
    if (inputs.rightBouncerUp)
        rightBouncerYPos -= bouncerMoveSpeed;

    float min = bouncerHeight * 0.5;
    float max = screenResolution.y - bouncerHeight * 0.5;
    leftBouncerYPos = Library::clamp(leftBouncerYPos, min, max);
    rightBouncerYPos = Library::clamp(rightBouncerYPos, min, max);
}

void Pong::DrawGraphics(SDL_Renderer* renderer)
{
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    
    SDL_Rect leftRect = SDL_Rect 
    {
        horizontalOffsetFromEdge, leftBouncerYPos - ((int)(bouncerHeight * 0.5)),
        bouncerWidth, bouncerHeight
    };

    SDL_Rect rightRect = SDL_Rect
    {
        screenResolution.x - horizontalOffsetFromEdge - bouncerWidth, rightBouncerYPos - ((int)(bouncerHeight * 0.5)),
        bouncerWidth, bouncerHeight
    };

    SDL_RenderFillRect(renderer, &leftRect);
    SDL_RenderFillRect(renderer, &rightRect);
}

Ball::Ball(Vector2Int screenResolution)
{
    this->screenResolution = screenResolution;
    rect = new SDL_Rect();
    SetPosition(screenResolution.x * 0.5f, screenResolution.y * 0.5f);
}

Ball::~Ball()
{
    delete rect;
}

void Ball::SetPosition(float x, float y)
{
    rect->x = x - diameter * 0.5f;
    rect->y = y - diameter * 0.5f;
}