#include "GameHandler.h"
#include "Library.h"
#include <iostream>

int main(int argc, char** args)
{
    GameHandler main;

    main.OnApplicationStart();

    main.GameLoop();

    main.OnApplicationQuit();

    /*Matrix2D<int> matrix = Matrix2D<int>(20, 20);

    int index = 0;
    for (int i = 0; i < 20; i++)
    {
        for (int j = 0; j < 20; j++)
        {
            *matrix.At(i, j) = index;
            std::cout << "value at row: " << i << ", column: " << j << " is " << *matrix.At(i, j) << std::endl;
            index++;
        }
    }*/

    return 0;
}