#pragma once
#include "Library.h"
#include "SDL.h"

class PongBall
{
public:
	PongBall();
	~PongBall();
	void SetPosition(float x, float y);
	void SetPosition(Vector2 pos);
	Vector2 m_position;
	SDL_Rect* m_rect;
	const float m_speed = 9.0f;
	const int m_diameter = 12;
private:
	Vector2Int m_screenResolution;
};