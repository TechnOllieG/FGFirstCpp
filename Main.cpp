#include "Game.h"

int main(int argc, char** args)
{
    Game main;

    main.OnApplicationStart();

    main.Update();

    main.OnApplicationQuit();

    return 0;
}