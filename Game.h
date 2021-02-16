#pragma once
#include "SDL.h"
#include "Library.h"
#include <string>

class Game
{
public:
	Game(Vector2Int screenResolution) {};
	virtual void HandleInput(SDL_Event event) {};
	virtual void Start() {};
	virtual void Update(float deltaTime, float currentTime) {};
	virtual void FixedUpdate(float fixedTimeStep, float currentTime) {};
	virtual void DrawGraphics(SDL_Renderer* renderer) {};
	std::string name = "Game";
};