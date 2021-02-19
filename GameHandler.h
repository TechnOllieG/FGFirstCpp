#pragma once
#include "SDL.h"
#include "Pong.h"

class Game;

class GameHandler
{
public:
	GameHandler();
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

	SDL_Renderer* m_renderer = 0;
	SDL_Window* m_window = 0;
	SDL_Event m_evt;
	bool m_applicationRunning = false;
	/// <summary>Total time since game start in seconds</summary>
	float m_currentTime = 0.0f;
	float m_deltaTime = 0.0f;
	float m_accumulator = 0.0f;
	Vector2Int m_resolution = Vector2Int(800, 600);;
	Game* m_game;

	const float m_fixedTimeStep = 0.02f;
};
