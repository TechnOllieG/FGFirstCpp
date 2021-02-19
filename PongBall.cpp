#include "PongBall.h"

PongBall::PongBall()
{
    m_rect = new SDL_Rect{ 0, 0, m_diameter, m_diameter };
}

PongBall::~PongBall()
{
    delete m_rect;
}

void PongBall::SetPosition(float x, float y)
{
    m_position = Vector2(x, y);
    SetPosition(m_position);
}

void PongBall::SetPosition(Vector2 pos)
{
    m_position = pos;
    m_rect->x = pos.x - m_diameter * 0.5f;
    m_rect->y = pos.y - m_diameter * 0.5f;
}