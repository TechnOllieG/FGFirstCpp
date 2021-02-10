#include<iostream>
#include "SDL.h"
#include "Main.h"

int main(int argc, char** args)
{
    Main::OnApplicationStart();
    const float delay = 1000.0 / 60.0;

    while (applicationRunning)
    {
        Main::CalculateTime();
        Main::ClearScreen();

        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT)
                applicationRunning = false;
            
            Main::Update();
        }

        Main::DrawUpdate();
        SDL_RenderPresent(renderer);
    }

    Main::OnApplicationQuit();
    return 0;
}

void Main::Update()
{

}

void Main::DrawUpdate() 
{
    SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
    SDL_RenderDrawLine(renderer, x, y, x + 50, y);
    x++;
    if (x >= width - 1)
    {
        x = 0;
        y++;
    }
}

void Main::OnApplicationStart()
{
    SDL_Init(SDL_INIT_EVERYTHING);
    applicationRunning = true;

    width = 800;
    height = 600;

    window = SDL_CreateWindow("Getting Started", SDL_WINDOWPOS_UNDEFINED,
        SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_SHOWN);

    renderer = SDL_CreateRenderer(window, -1, 0);
}

void Main::OnApplicationQuit()
{
    SDL_DestroyRenderer(renderer);

    SDL_DestroyWindow(window);

    SDL_Quit();
}

void Main::CalculateTime()
{
    float tempTime = SDL_GetTicks();
    deltaTime = tempTime - totalTime;
    totalTime = tempTime;
}

void Main::ClearScreen()
{
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);
    SDL_RenderPresent(renderer);
}
