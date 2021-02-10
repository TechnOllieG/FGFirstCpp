#pragma once

SDL_Renderer* renderer;
SDL_Window* window;
SDL_Event event;
bool applicationRunning;
float totalTime;
float deltaTime;
int x = 0;
int y = 0;
float width;
float height;

class Main
{
public:
	static void OnApplicationStart();
	static void OnApplicationQuit();
	static void Update();
	static void DrawUpdate();
	static void ClearScreen();
	static void CalculateTime();
};
