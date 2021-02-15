#include "Game.h"

int main(int argc, char** args)
{
    Game main;

    main.OnApplicationStart();

    main.GameLoop();

    main.OnApplicationQuit();

    return 0;
}