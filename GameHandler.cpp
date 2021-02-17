#include "GameHandler.h"
#include "Game.h"

GameHandler::GameHandler()
{
    applicationRunning = 0;
    currentTime = 0;
    deltaTime = 0;
    resolution = Vector2Int(800, 600);
    renderer = 0;
    window = 0;
    evt = SDL_Event();
    game = new Pong(resolution);
}

GameHandler::~GameHandler()
{
    delete game;
}

void GameHandler::GameLoop()
{
    GameHandler::Start();

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

void GameHandler::Start()
{
    game->Start();
}

void GameHandler::HandleInput()
{
    game->HandleInput(evt);
}

void GameHandler::Update()
{
    game->Update(deltaTime, currentTime);
}

void GameHandler::FixedUpdate()
{
    game->FixedUpdate(fixedTimeStep, currentTime);
}

void GameHandler::DrawUpdate()
{
    game->DrawGraphics(renderer);
}

void GameHandler::OnApplicationStart()
{
    SDL_Init(SDL_INIT_EVERYTHING);
    applicationRunning = true;

    window = SDL_CreateWindow(game->name.c_str(), SDL_WINDOWPOS_UNDEFINED,
        SDL_WINDOWPOS_UNDEFINED, resolution.x, resolution.y, SDL_WINDOW_SHOWN);

    renderer = SDL_CreateRenderer(window, -1, 0);
}

void GameHandler::OnApplicationQuit()
{
    SDL_DestroyRenderer(renderer);

    SDL_DestroyWindow(window);

    SDL_Quit();
}

void GameHandler::ClearScreen()
{
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);
}