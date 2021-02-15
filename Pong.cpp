#include "Pong.h"
#include <tgmath.h>
#include <iostream>

using namespace std;

Pong::Pong(Vector2Int screenResolution)
{
    leftBouncerYPos = (screenResolution.y - bouncerWidth) * 0.5;
    rightBouncerYPos = leftBouncerYPos;
    inputs = Input();
    this->screenResolution = screenResolution;
    ball = new Ball(screenResolution);
}

Pong::~Pong()
{
    delete ball;
}

void Pong::HandleInput(SDL_Event event)
{
    inputs.PollKeys(event);
}

void Pong::Start()
{

}

void Pong::Update(float deltaTime, float currentTime)
{

}

void Pong::FixedUpdate(float fixedTimeStep, float currentTime)
{
    if (inputs.leftBouncerDown)
        leftBouncerYPos += bouncerMoveSpeed;

    if (inputs.leftBouncerUp)
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
        horizontalOffsetFromEdge, (int) round(leftBouncerYPos) - ((int)(bouncerHeight * 0.5)),
        bouncerWidth, bouncerHeight
    };

    SDL_Rect rightRect = SDL_Rect
    {
        screenResolution.x - horizontalOffsetFromEdge - bouncerWidth, (int) round(rightBouncerYPos) - ((int)(bouncerHeight * 0.5)),
        bouncerWidth, bouncerHeight
    };

    SDL_RenderFillRect(renderer, &leftRect);
    SDL_RenderFillRect(renderer, &rightRect);
    SDL_RenderFillRect(renderer, ball->rect);
    
}

Ball::Ball(Vector2Int screenResolution)
{
    this->screenResolution = screenResolution;
    rect = new SDL_Rect {0, 0, diameter, diameter};
    SetPosition(screenResolution.x * 0.5f, screenResolution.y * 0.5f);
}

Ball::~Ball()
{
    delete rect;
}

void Ball::SetPosition(float x, float y)
{
    position = Vector2Int(x, y);
    rect->x = x - diameter * 0.5f;
    rect->y = y - diameter * 0.5f;
}