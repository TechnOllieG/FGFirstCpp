#include "PongBall.h"

PongBall::PongBall()
{
    rect = new SDL_Rect{ 0, 0, diameter, diameter };
}

PongBall::~PongBall()
{
    delete rect;
}

void PongBall::SetPosition(float x, float y)
{
    position = Vector2(x, y);
    SetPosition(position);
}

void PongBall::SetPosition(Vector2 pos)
{
    position = pos;
    rect->x = pos.x - diameter * 0.5f;
    rect->y = pos.y - diameter * 0.5f;
}