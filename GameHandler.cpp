#include "GameHandler.h"
#include "Game.h"

GameHandler::GameHandler()
{
    m_game = new Pong(m_resolution);
}

void GameHandler::GameLoop()
{
    GameHandler::Start();

    while (m_applicationRunning)
    {
        ClearScreen();

        float tempTime = SDL_GetTicks() * 0.001;
        m_deltaTime = tempTime - m_currentTime;
        m_currentTime = tempTime;

        m_accumulator += m_deltaTime;

        while (m_accumulator >= m_fixedTimeStep)
        {
            FixedUpdate();
            m_accumulator -= m_fixedTimeStep;
        }

        while (SDL_PollEvent(&m_evt))
        {
            if (m_evt.type == SDL_QUIT)
                m_applicationRunning = false;

            HandleInput();
        }

        Update();

        DrawUpdate();
        SDL_RenderPresent(m_renderer);
    }
}

void GameHandler::Start()
{
    m_game->Start();
}

void GameHandler::HandleInput()
{
    m_game->HandleInput(m_evt);
}

void GameHandler::Update()
{
    m_game->Update(m_deltaTime, m_currentTime);
}

void GameHandler::FixedUpdate()
{
    m_game->FixedUpdate(m_fixedTimeStep, m_currentTime);
}

void GameHandler::DrawUpdate()
{
    m_game->DrawGraphics(m_renderer);
}

void GameHandler::OnApplicationStart()
{
    SDL_Init(SDL_INIT_EVERYTHING);
    m_applicationRunning = true;

    m_window = SDL_CreateWindow(m_game->m_name.c_str(), SDL_WINDOWPOS_UNDEFINED,
        SDL_WINDOWPOS_UNDEFINED, m_resolution.x, m_resolution.y, SDL_WINDOW_SHOWN);

    m_renderer = SDL_CreateRenderer(m_window, -1, 0);
}

void GameHandler::OnApplicationQuit()
{
    SDL_DestroyRenderer(m_renderer);

    SDL_DestroyWindow(m_window);

    SDL_Quit();

    delete m_game;
}

void GameHandler::ClearScreen()
{
    SDL_SetRenderDrawColor(m_renderer, 0, 0, 0, 255);
    SDL_RenderClear(m_renderer);
}