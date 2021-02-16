#pragma once
#include "SDL.h"
#include "Library.h"

class Game;

class GameHandler
{
public:
	GameHandler();
	~GameHandler();
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
	Game* game;
	const float fixedTimeStep = 0.02f;
	float accumulator = 0.0f;
};
