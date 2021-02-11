#pragma once
#include "SDL.h"
#include "Library.h"

class Pong;

class Game
{
public:
	Game();
	~Game();
	void OnApplicationStart();
	void OnApplicationQuit();
	void Update();
	void DrawUpdate();
	void ClearScreen();
	void CalculateTime();
private:
	SDL_Renderer* renderer;
	SDL_Window* window;
	SDL_Event evt;
	bool applicationRunning;
	/// <summary>Total time since game start in seconds</summary>
	float totalTime;
	float deltaTime;
	Vector2Int resolution;
	Pong* pong;
};
