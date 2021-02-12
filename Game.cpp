#include "Game.h"
#include "Pong.h"

Game::Game()
{
    applicationRunning = 0;
    totalTime = 0;
    deltaTime = 0;
    resolution = Vector2Int(800, 600);
    renderer = 0;
    window = 0;
    evt = SDL_Event();
    pong = new Pong(resolution);
}

Game::~Game()
{
    delete pong;
}

void Game::Update()
{
    while (applicationRunning)
    {
        CalculateTime();
        ClearScreen();

        while (SDL_PollEvent(&evt))
        {
            if (evt.type == SDL_QUIT)
                applicationRunning = false;

            pong->HandleInput(evt, deltaTime);
        }

        DrawUpdate();
        SDL_RenderPresent(renderer);
    }
}

void Game::FixedUpdate()
{

}

void Game::DrawUpdate()
{
    pong->DrawGraphics(renderer);
}

void Game::OnApplicationStart()
{
    SDL_Init(SDL_INIT_EVERYTHING);
    applicationRunning = true;

    window = SDL_CreateWindow("Pong", SDL_WINDOWPOS_UNDEFINED,
        SDL_WINDOWPOS_UNDEFINED, resolution.x, resolution.y, SDL_WINDOW_SHOWN);

    renderer = SDL_CreateRenderer(window, -1, 0);
}

void Game::OnApplicationQuit()
{
    SDL_DestroyRenderer(renderer);

    SDL_DestroyWindow(window);

    SDL_Quit();
}

void Game::CalculateTime()
{
    float tempTime = SDL_GetTicks() * 0.001;
    deltaTime = tempTime - totalTime;
    totalTime = tempTime;
}

void Game::ClearScreen()
{
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);
}