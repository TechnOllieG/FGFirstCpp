#include "Pong.h"
#include <tgmath.h>
#include <iostream>
#include "SymbolDisplay.h"

using namespace std;

Pong::Pong(Vector2Int screenResolution) : Game(screenResolution)
{
    m_name = "Pong";
    m_leftBouncerYPos = (screenResolution.y - m_bouncerWidth) * 0.5f;
    m_rightBouncerYPos = m_leftBouncerYPos;
    m_screenResolution = screenResolution;
    m_ball = new PongBall();
    m_ball->SetPosition(screenResolution.x * 0.5f, screenResolution.y * 0.5f);
}

Pong::~Pong()
{
    delete m_ball;
}

void Pong::HandleInput(SDL_Event event)
{
    m_inputs.PollKeys(event);
}

void Pong::Start()
{
    m_leftBouncer = SDL_Rect
    {
        m_horizontalOffsetFromEdge, (int)round(m_leftBouncerYPos) - ((int)(m_bouncerHeight * 0.5f)),
        m_bouncerWidth, m_bouncerHeight
    };

    m_rightBouncer = SDL_Rect
    {
        m_screenResolution.x - m_horizontalOffsetFromEdge - m_bouncerWidth, (int)round(m_rightBouncerYPos) - ((int)(m_bouncerHeight * 0.5f)),
        m_bouncerWidth, m_bouncerHeight
    };
}

void Pong::FixedUpdate(float fixedTimeStep, float currentTime)
{
    this->m_currentTime = currentTime;

    if (currentTime < m_readyTextDurationAtBeginning)
        return;

    if (!m_gameStarted)
    {
        m_ballDirection = m_startBallDirection;
        m_gameStarted = 1;
    }

    if ((currentTime > m_killCooldown + 1 && currentTime - m_timeOfDeath < m_killCooldown) || m_rightPoints >= m_winningPoints || m_leftPoints >= m_winningPoints)
        return;

    m_ball->SetPosition(m_ball->m_position + m_ballDirection * m_ball->m_speed);

    SetBouncerYPos();

    CheckBallPosition();
}

void Pong::SetBouncerYPos()
{
    if (m_inputs.m_leftBouncerDown)
        m_leftBouncerYPos += m_bouncerMoveSpeed;

    if (m_inputs.m_leftBouncerUp)
        m_leftBouncerYPos -= m_bouncerMoveSpeed;

    if (m_inputs.m_rightBouncerDown)
        m_rightBouncerYPos += m_bouncerMoveSpeed;

    if (m_inputs.m_rightBouncerUp)
        m_rightBouncerYPos -= m_bouncerMoveSpeed;

    float min = m_bouncerHeight * 0.5f;
    float max = m_screenResolution.y - m_bouncerHeight * 0.5f;
    m_leftBouncerYPos = Library::clamp(m_leftBouncerYPos, min, max);
    m_rightBouncerYPos = Library::clamp(m_rightBouncerYPos, min, max);

    m_leftBouncer.y = (int)round(m_leftBouncerYPos) - ((int)(m_bouncerHeight * 0.5f));
    m_rightBouncer.y = (int)round(m_rightBouncerYPos) - ((int)(m_bouncerHeight * 0.5f));
}

void Pong::CheckBallPosition()
{
    Vector2 topRightCornerBall = Vector2(m_ball->m_position.x + m_ball->m_diameter * 0.5f, m_ball->m_position.y - m_ball->m_diameter * 0.5f);
    Vector2 topLeftCornerRBouncer = Vector2(m_rightBouncer.x, m_rightBouncer.y);

    Vector2 topLeftCornerBall = Vector2(topRightCornerBall.x - m_ball->m_diameter, topRightCornerBall.y);
    Vector2 topRightCornerLBouncer = Vector2(m_leftBouncer.x + m_bouncerWidth, m_leftBouncer.y);

    // If bouncing on right bouncer, change direction
    if (topRightCornerBall.x >= topLeftCornerRBouncer.x && topRightCornerBall.y + m_ball->m_diameter > topLeftCornerRBouncer.y && topRightCornerBall.y < topLeftCornerRBouncer.y + m_bouncerHeight)
    {
        float midOfBouncer = topLeftCornerRBouncer.y + m_bouncerHeight * 0.5f;
        float bottomOfBouncer = topLeftCornerRBouncer.y + m_bouncerHeight;
        BounceOnBouncer(Library::clamp(Library::InverseLerp(midOfBouncer, bottomOfBouncer, m_ball->m_position.y), -1, 1), -1);
        return;
    }

    // If bouncing on left bouncer, change direction
    if (topLeftCornerBall.x <= topRightCornerLBouncer.x && topLeftCornerBall.y + m_ball->m_diameter > topRightCornerLBouncer.y && topLeftCornerBall.y < topRightCornerLBouncer.y + m_bouncerHeight)
    {
        float midOfBouncer = topRightCornerLBouncer.y + m_bouncerHeight * 0.5f;
        float bottomOfBouncer = topRightCornerLBouncer.y + m_bouncerHeight;
        BounceOnBouncer(Library::clamp(Library::InverseLerp(midOfBouncer, bottomOfBouncer, m_ball->m_position.y), -1, 1), 1);
        return;
    }

    // If bouncing on top edge, reflect current vector based on the normal
    if(topLeftCornerBall.y <= 0)
    {
        BounceOnEdge(m_topEdgeNormal);
        return;
    }

    // If bouncing on bottom edge, reflect current vector based on the normal
    if(m_ball->m_position.y + m_ball->m_diameter * 0.5f >= m_screenResolution.y)
    {
        BounceOnEdge(m_bottomEdgeNormal);
        return;
    }

    // If touching left wall, give right side a point and reset ball
    if (m_ball->m_position.x - m_ball->m_diameter * 0.5f <= 0)
    {
        OnTouchHorizontalWall(m_leftWallNormal);
        return;
    }

    // If touching right wall, give left side a point and reset ball
    if (m_ball->m_position.x + m_ball->m_diameter * 0.5f >= m_screenResolution.x)
    {
        OnTouchHorizontalWall(m_rightWallNormal);
        return;
    }
}

void Pong::OnTouchHorizontalWall(Vector2 normal)
{
    if (normal.x > 0)
    {
        m_playerThatScored = 2;
        m_rightPoints++;
    }
    else
    {
        m_playerThatScored = 1;
        m_leftPoints++;
    }

    m_ballDirection = -normal;
    m_ball->SetPosition(m_screenResolution.x * 0.5f, m_screenResolution.y * 0.5f);

    if (m_leftPoints >= m_winningPoints || m_rightPoints >= m_winningPoints)
    {
        int midOfScreen = m_screenResolution.y * 0.5f;

        m_leftBouncerYPos = midOfScreen;
        m_rightBouncerYPos = midOfScreen;
        m_leftBouncer.y = midOfScreen - ((int)(m_bouncerHeight * 0.5f));
        m_rightBouncer.y = midOfScreen - ((int)(m_bouncerHeight * 0.5f));
    }

    m_timeOfDeath = m_currentTime;
}

void Pong::BounceOnEdge(Vector2 normal)
{
    Vector2 offsetVector = normal * (Vector2::Dot(normal, m_ballDirection) * 2.0f);
    m_ballDirection = m_ballDirection - offsetVector;
}

void Pong::BounceOnBouncer(float yPosOnBouncer, float xDirection)
{
    Vector2 newDirection = Vector2(xDirection, yPosOnBouncer);
    newDirection.Normalize();
    m_ballDirection = newDirection;
}

void Pong::DrawGraphics(SDL_Renderer* renderer)
{
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

    if(!m_gameStarted)
        ShowReadyText(renderer);

    DrawCounters(renderer);
    SDL_RenderFillRect(renderer, &m_leftBouncer);
    SDL_RenderFillRect(renderer, &m_rightBouncer);

    if ((m_currentTime < m_killCooldown + 1 || m_currentTime - m_timeOfDeath > m_killCooldown) && m_leftPoints < m_winningPoints && m_rightPoints < m_winningPoints)
        SDL_RenderFillRect(renderer, m_ball->m_rect);
    else
        ShowPlayerScoredText(renderer);
}

void Pong::DrawCounters(SDL_Renderer* renderer)
{
    std::string leftString = std::to_string(m_leftPoints);
    int leftLength = leftString.length();

    auto leftNumberDisplays = SymbolDisplay::GetSymbols(leftString, m_screenResolution, m_pixelSizeText,
        Vector2(m_screenResolution.x * 0.5f - m_counterXOffsetFromCenter - m_characterWidth * leftLength + (leftLength - 1) * m_pixelSizeText, m_counterYPos));

    for (int i = 0; i < leftNumberDisplays.size(); i++)
    {
        leftNumberDisplays[i].Draw(renderer);
    }

    auto rightNumberDisplays = SymbolDisplay::GetSymbols(std::to_string(m_rightPoints), m_screenResolution, m_pixelSizeText,
        Vector2Int(m_screenResolution.x * 0.5f + m_counterXOffsetFromCenter, m_counterYPos));

    for (int i = 0; i < rightNumberDisplays.size(); i++)
    {
        rightNumberDisplays[i].Draw(renderer);
    }
}

void Pong::ShowPlayerScoredText(SDL_Renderer* renderer)
{
    std::string suffix = " scored";

    if (m_leftPoints >= m_winningPoints || m_rightPoints >= m_winningPoints)
        suffix = " won";

    auto displays = SymbolDisplay::GetSymbolsCentered("player " + std::to_string(m_playerThatScored) + suffix, m_screenResolution, m_pixelSizeText, m_textYPos);
    for (int i = 0; i < displays.size(); i++)
    {
        displays[i].Draw(renderer);
    }
}

void Pong::ShowReadyText(SDL_Renderer* renderer)
{
    auto displays = SymbolDisplay::GetSymbolsCentered("get ready", m_screenResolution, m_pixelSizeText, m_textYPos);
    for (int i = 0; i < displays.size(); i++)
    {
        displays[i].Draw(renderer);
    }
}