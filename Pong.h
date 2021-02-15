#pragma once
#include "SDL.h"
#include "Library.h"
#include "Input.h"

class Ball
{
public:
	Ball(Vector2Int screenResolution);
	~Ball();
	void SetPosition(float x, float y);
	Vector2Int position;
	SDL_Rect* rect;
private:
	const int diameter = 12;
	const float speed = 6;
	Vector2Int screenResolution;
};

class Pong
{
public:
	Pong(Vector2Int screenResolution);
	~Pong();
	void HandleInput(SDL_Event event);
	void Start();
	void Update(float deltaTime, float currentTime);
	void FixedUpdate(float fixedTimeStep, float currentTime);
	void DrawGraphics(SDL_Renderer* renderer);

private:
	const int horizontalOffsetFromEdge = 10;
	const float bouncerMoveSpeed = 6;
	const int bouncerWidth = 8;
	const int bouncerHeight = 60;
	float leftBouncerYPos;
	float rightBouncerYPos;
	Input inputs;
	Vector2Int screenResolution;
	Ball* ball;
};