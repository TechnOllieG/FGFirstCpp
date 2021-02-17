#include "Pong.h"
#include <tgmath.h>
#include <iostream>
#include "SymbolDisplay.h"

using namespace std;

Pong::Pong(Vector2Int screenResolution) : Game(screenResolution)
{
    name = "Pong";
    leftBouncerYPos = (screenResolution.y - bouncerWidth) * 0.5f;
    rightBouncerYPos = leftBouncerYPos;
    inputs = Input();
    this->screenResolution = screenResolution;
    ball = new Ball(screenResolution);
}

Pong::~Pong()
{
    delete ball;
}

void Pong::HandleInput(SDL_Event event)
{
    inputs.PollKeys(event);
}

void Pong::Start()
{
    leftBouncer = SDL_Rect
    {
        horizontalOffsetFromEdge, (int)round(leftBouncerYPos) - ((int)(bouncerHeight * 0.5f)),
        bouncerWidth, bouncerHeight
    };

    rightBouncer = SDL_Rect
    {
        screenResolution.x - horizontalOffsetFromEdge - bouncerWidth, (int)round(rightBouncerYPos) - ((int)(bouncerHeight * 0.5f)),
        bouncerWidth, bouncerHeight
    };
}

void Pong::Update(float deltaTime, float currentTime)
{

}

void Pong::FixedUpdate(float fixedTimeStep, float currentTime)
{
    this->currentTime = currentTime;

    if (currentTime < readyTextDurationAtBeginning)
        return;

    if (!gameStarted)
    {
        ballDirection = leftWallNormal;
        gameStarted = 1;
    }

    if ((currentTime > killCooldown + 1 && currentTime - timeOfDeath < killCooldown) || rightPoints >= winningPoints || leftPoints >= winningPoints)
        return;

    ball->SetPosition(ball->position + ballDirection * ball->speed);

    SetBouncerYPos();

    CheckBallPosition();
}

void Pong::SetBouncerYPos()
{
    if (inputs.leftBouncerDown)
        leftBouncerYPos += bouncerMoveSpeed;

    if (inputs.leftBouncerUp)
        leftBouncerYPos -= bouncerMoveSpeed;

    if (inputs.rightBouncerDown)
        rightBouncerYPos += bouncerMoveSpeed;

    if (inputs.rightBouncerUp)
        rightBouncerYPos -= bouncerMoveSpeed;

    float min = bouncerHeight * 0.5f;
    float max = screenResolution.y - bouncerHeight * 0.5f;
    leftBouncerYPos = Library::clamp(leftBouncerYPos, min, max);
    rightBouncerYPos = Library::clamp(rightBouncerYPos, min, max);

    leftBouncer.y = (int)round(leftBouncerYPos) - ((int)(bouncerHeight * 0.5f));
    rightBouncer.y = (int)round(rightBouncerYPos) - ((int)(bouncerHeight * 0.5f));
}

void Pong::CheckBallPosition()
{
    Vector2 topRightCornerBall = Vector2(ball->position.x + ball->diameter * 0.5f, ball->position.y - ball->diameter * 0.5f);
    Vector2 topLeftCornerRBouncer = Vector2(rightBouncer.x, rightBouncer.y);

    Vector2 topLeftCornerBall = Vector2(topRightCornerBall.x - ball->diameter, topRightCornerBall.y);
    Vector2 topRightCornerLBouncer = Vector2(leftBouncer.x + bouncerWidth, leftBouncer.y);

    // If bouncing on right bouncer, change direction
    if (topRightCornerBall.x >= topLeftCornerRBouncer.x && topRightCornerBall.y + ball->diameter > topLeftCornerRBouncer.y && topRightCornerBall.y < topLeftCornerRBouncer.y + bouncerHeight)
    {
        float midOfBouncer = topLeftCornerRBouncer.y + bouncerHeight * 0.5f;
        float bottomOfBouncer = topLeftCornerRBouncer.y + bouncerHeight;
        BounceOnBouncer(Library::clamp(Library::InverseLerp(midOfBouncer, bottomOfBouncer, ball->position.y), -1, 1), -1);
    }

    // If bouncing on left bouncer, change direction
    if (topLeftCornerBall.x <= topRightCornerLBouncer.x && topLeftCornerBall.y + ball->diameter > topRightCornerLBouncer.y && topLeftCornerBall.y < topRightCornerLBouncer.y + bouncerHeight)
    {
        float midOfBouncer = topRightCornerLBouncer.y + bouncerHeight * 0.5f;
        float bottomOfBouncer = topRightCornerLBouncer.y + bouncerHeight;
        BounceOnBouncer(Library::clamp(Library::InverseLerp(midOfBouncer, bottomOfBouncer, ball->position.y), -1, 1), 1);
    }

    // If bouncing on top edge, reflect current vector based on the normal
    if(topLeftCornerBall.y <= 0)
    {
        BounceOnEdge(topEdgeNormal);
    }

    // If bouncing on bottom edge, reflect current vector based on the normal
    if(ball->position.y + ball->diameter * 0.5f >= screenResolution.y)
    {
        BounceOnEdge(bottomEdgeNormal);
    }

    // If touching left wall, give right side a point and reset ball
    if (ball->position.x - ball->diameter * 0.5f <= 0)
    {
        OnTouchHorizontalWall(leftWallNormal);
    }

    // If touching right wall, give left side a point and reset ball
    if (ball->position.x + ball->diameter * 0.5f >= screenResolution.x)
    {
        OnTouchHorizontalWall(rightWallNormal);
    }
}

void Pong::OnTouchHorizontalWall(Vector2 normal)
{
    if (normal.x > 0)
    {
        playerThatScored = 2;
        rightPoints++;
    }
    else
    {
        playerThatScored = 1;
        leftPoints++;
    }

    ballDirection = -normal;
    ball->SetPosition(screenResolution.x * 0.5f, screenResolution.y * 0.5f);

    if (leftPoints >= winningPoints || rightPoints >= winningPoints)
    {
        int midOfScreen = screenResolution.y * 0.5f;

        leftBouncerYPos = midOfScreen;
        rightBouncerYPos = midOfScreen;
        leftBouncer.y = midOfScreen - ((int)(bouncerHeight * 0.5f));
        rightBouncer.y = midOfScreen - ((int)(bouncerHeight * 0.5f));
    }

    timeOfDeath = currentTime;
}

void Pong::BounceOnEdge(Vector2 normal)
{
    Vector2 offsetVector = normal * (Vector2::Dot(normal, ballDirection) * 2.0f);
    ballDirection = ballDirection - offsetVector;
}

void Pong::BounceOnBouncer(float yPosOnBouncer, float xDirection)
{
    Vector2 newDirection = Vector2(xDirection, yPosOnBouncer);
    newDirection.Normalize();
    ballDirection = newDirection;
}

void Pong::DrawGraphics(SDL_Renderer* renderer)
{
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

    if(!gameStarted)
        ShowReadyText(renderer);

    DrawCounters(renderer);
    SDL_RenderFillRect(renderer, &leftBouncer);
    SDL_RenderFillRect(renderer, &rightBouncer);

    if ((currentTime < killCooldown + 1 || currentTime - timeOfDeath > killCooldown) && leftPoints < winningPoints && rightPoints < winningPoints)
        SDL_RenderFillRect(renderer, ball->rect);
    else
        ShowPlayerScoredText(renderer);
}

void Pong::DrawCounters(SDL_Renderer* renderer)
{
    std::string leftString = std::to_string(leftPoints);
    int leftLength = leftString.length();

    auto leftNumberDisplays = SymbolDisplay::GetSymbols(leftString, screenResolution, pixelSizeText,
        Vector2(screenResolution.x * 0.5f - counterXOffsetFromCenter - characterWidth * leftLength + (leftLength - 1) * pixelSizeText, counterYPos));

    for (int i = 0; i < leftNumberDisplays.size(); i++)
    {
        leftNumberDisplays[i].Draw(renderer);
    }

    auto rightNumberDisplays = SymbolDisplay::GetSymbols(std::to_string(rightPoints), screenResolution, pixelSizeText,
        Vector2Int(screenResolution.x * 0.5f + counterXOffsetFromCenter, counterYPos));

    for (int i = 0; i < rightNumberDisplays.size(); i++)
    {
        rightNumberDisplays[i].Draw(renderer);
    }
}

void Pong::ShowPlayerScoredText(SDL_Renderer* renderer)
{
    std::string suffix = " scored";

    if (leftPoints >= winningPoints || rightPoints >= winningPoints)
        suffix = " won";

    auto displays = SymbolDisplay::GetSymbolsCentered("player " + std::to_string(playerThatScored) + suffix, screenResolution, pixelSizeText, textYPos);
    for (int i = 0; i < displays.size(); i++)
    {
        displays[i].Draw(renderer);
    }
}

void Pong::ShowReadyText(SDL_Renderer* renderer)
{
    auto displays = SymbolDisplay::GetSymbolsCentered("get ready", screenResolution, pixelSizeText, textYPos);
    for (int i = 0; i < displays.size(); i++)
    {
        displays[i].Draw(renderer);
    }
}

Ball::Ball(Vector2Int screenResolution)
{
    this->screenResolution = screenResolution;
    rect = new SDL_Rect {0, 0, diameter, diameter};
    SetPosition(screenResolution.x * 0.5f, screenResolution.y * 0.5f);
}

Ball::~Ball()
{
    delete rect;
}

void Ball::SetPosition(float x, float y)
{
    position = Vector2(x, y);
    SetPosition(position);
}

void Ball::SetPosition(Vector2 pos)
{
    position = pos;
    rect->x = pos.x - diameter * 0.5f;
    rect->y = pos.y - diameter * 0.5f;
}