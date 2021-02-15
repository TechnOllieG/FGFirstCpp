#include "Game.h"
#include "Pong.h"

Game::Game()
{
    applicationRunning = 0;
    currentTime = 0;
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

void Game::GameLoop()
{
    Game::Start();

    while (applicationRunning)
    {
        ClearScreen();

        float tempTime = SDL_GetTicks() * 0.001;
        deltaTime = tempTime - currentTime;
        currentTime = tempTime;

        accumulator += deltaTime;

        while (accumulator >= fixedTimeStep)
        {
            FixedUpdate();
            accumulator -= fixedTimeStep;
        }

        while (SDL_PollEvent(&evt))
        {
            if (evt.type == SDL_QUIT)
                applicationRunning = false;

            HandleInput();
        }

        Update();

        DrawUpdate();
        SDL_RenderPresent(renderer);
    }
}

void Game::Start()
{
    pong->Start();
}

void Game::HandleInput()
{
    pong->HandleInput(evt);
}

void Game::Update()
{
    pong->Update(deltaTime, currentTime);
}

void Game::FixedUpdate()
{
    pong->FixedUpdate(fixedTimeStep, currentTime);
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

void Game::ClearScreen()
{
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);
}