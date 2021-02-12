#pragma once
#include "SDL.h"
#include "Library.h"
#include "Input.h"

class Pong
{
public:
	Pong(Vector2Int screenResolution);
	void HandleInput(SDL_Event event, float deltaTime);
	void DrawGraphics(SDL_Renderer* renderer);

private:
	const int horizontalOffsetFromEdge = 10;
	const float bouncerMoveSpeed = 10;
	const int bouncerWidth = 8;
	const int bouncerHeight = 60;
	int leftBouncerYPos;
	int rightBouncerYPos;
	Input inputs;
	Vector2Int screenResolution;
};

class Ball
{
public:
	Ball(Vector2Int screenResolution);
	~Ball();
	void SetPosition(float x, float y);
	Vector2Int position;
private:
	const int diameter = 8;
	SDL_Rect* rect;
	Vector2Int screenResolution;
};