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
	void GameLoop();
private:
	void HandleInput();
	void Start();
	void Update();
	void FixedUpdate();
	void DrawUpdate();
	void ClearScreen();

	SDL_Renderer* renderer;
	SDL_Window* window;
	SDL_Event evt;
	bool applicationRunning;
	/// <summary>Total time since game start in seconds</summary>
	float currentTime;
	float deltaTime;
	Vector2Int resolution;
	Pong* pong;
	const float fixedTimeStep = 0.02;
	float accumulator = 0;
};
