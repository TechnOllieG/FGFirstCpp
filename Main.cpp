#include "GameHandler.h"

int main(int argc, char** args)
{
    GameHandler main;

    main.OnApplicationStart();

    main.GameLoop();

    main.OnApplicationQuit();

    return 0;
}