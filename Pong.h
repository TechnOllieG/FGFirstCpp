#pragma once
#include "SDL.h"
#include "Library.h"
#include "Input.h"
#include "Game.h"

class Ball
{
public:
	Ball(Vector2Int screenResolution);
	~Ball();
	void SetPosition(float x, float y);
	void SetPosition(Vector2 pos);
	Vector2 position;
	SDL_Rect* rect;
	const float speed = 10.0f;
	const int diameter = 12;
private:
	Vector2Int screenResolution;
};

class Pong : public Game
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
	void BounceOnBouncer(float yPosOnBouncer, float xDirection);
	void CheckBallPosition();
	void SetBouncerYPos();
	void BounceOnEdge(Vector2 normal);
	void OnTouchHorizontalWall(Vector2 normal);
	void ShowReadyText(SDL_Renderer* renderer);
	void ShowPlayerScoredText(SDL_Renderer* renderer);
	void DrawCounters(SDL_Renderer* renderer);

	const int winningPoints = 11;
	const int pixelSizeText = 5;
	const int horizontalOffsetFromEdge = 10;
	const float bouncerMoveSpeed = 6.0f;
	const int bouncerWidth = 8;
	const int bouncerHeight = 60;
	const float readyTextDurationAtBeginning = 2.0f;
	const float killCooldown = 1.5f;
	const int characterWidth = pixelSizeText * 3;
	const int counterYPos = 10;
	const int counterXOffsetFromCenter = 20;
	const int textYPos = 100;
	const Vector2 leftWallNormal = Vector2(1, 0);
	const Vector2 rightWallNormal = Vector2(-1, 0);
	const Vector2 topEdgeNormal = Vector2(0, -1);
	const Vector2 bottomEdgeNormal = Vector2(0, 1);
	const Vector2 startBallDirection = leftWallNormal;

	int playerThatScored = 1;
	float timeOfDeath = 0.0f;
	float currentTime = 0.0f;
	int leftPoints = 0;
	int rightPoints = 0;
	float leftBouncerYPos;
	float rightBouncerYPos;
	Vector2 ballDirection;
	SDL_Rect leftBouncer;
	SDL_Rect rightBouncer;
	bool gameStarted = 0;
	Input inputs;
	Vector2Int screenResolution;
	Ball* ball;
};