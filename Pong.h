#pragma once
#include "SDL.h"
#include "Library.h"
#include "Input.h"
#include "Game.h"
#include "PongBall.h"

class Pong : public Game
{
public:
	Pong(Vector2Int screenResolution);
	~Pong();
	void HandleInput(SDL_Event event);
	void Start();
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

	const int m_winningPoints = 11;
	const int m_pixelSizeText = 5;
	const int m_horizontalOffsetFromEdge = 10;
	const float m_bouncerMoveSpeed = 6.0f;
	const int m_bouncerWidth = 8;
	const int m_bouncerHeight = 60;
	const float m_readyTextDurationAtBeginning = 2.0f;
	const float m_killCooldown = 1.5f;
	const int m_characterWidth = m_pixelSizeText * 3;
	const int m_counterYPos = 10;
	const int m_counterXOffsetFromCenter = 20;
	const int m_textYPos = 100;
	const Vector2 m_leftWallNormal = Vector2(1, 0);
	const Vector2 m_rightWallNormal = Vector2(-1, 0);
	const Vector2 m_topEdgeNormal = Vector2(0, -1);
	const Vector2 m_bottomEdgeNormal = Vector2(0, 1);
	const Vector2 m_startBallDirection = m_leftWallNormal;

	int m_playerThatScored = 1;
	float m_timeOfDeath = 0.0f;
	float m_currentTime = 0.0f;
	int m_leftPoints = 0;
	int m_rightPoints = 0;
	float m_leftBouncerYPos;
	float m_rightBouncerYPos;
	Vector2 m_ballDirection;
	SDL_Rect m_leftBouncer;
	SDL_Rect m_rightBouncer;
	bool m_gameStarted = false;
	Input m_inputs;
	Vector2Int m_screenResolution;
	PongBall* m_ball;
};