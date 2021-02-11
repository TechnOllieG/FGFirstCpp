#pragma once
#include "SDL.h"
#include "Library.h"

class Pong
{
public:
	Pong(Vector2Int screenResolution);
	void HandleInput(SDL_Event event, float deltaTime);
	void DrawGraphics(SDL_Renderer* renderer, Vector2Int resolution);

private:
	const int horizontalOffsetFromEdge = 10;
	const float bouncerMoveSpeed = 10;
	const int bouncerWidth = 8;
	const int bouncerHeight = 60;
	int leftBouncerYPos;
	int rightBouncerYPos;
};