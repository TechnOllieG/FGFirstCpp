#pragma once
#include "Library.h"
#include "SDL.h"

struct PongBall
{
public:
	PongBall();
	~PongBall();
	void SetPosition(float x, float y);
	void SetPosition(Vector2 pos);
	Vector2 position;
	SDL_Rect* rect;
	const float speed = 9.0f;
	const int diameter = 12;
private:
	Vector2Int m_screenResolution;
};