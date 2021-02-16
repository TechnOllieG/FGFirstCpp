#pragma once
#include "Library.h"
#include <vector>
#include "SDL.h"

class SymbolDisplay
{
private:
    std::vector<SDL_Rect>* rects;

    const bool** ArrayToPtr(const bool arry[5][3])
    {
        const bool* temp[5] = { arry[0], arry[1],  arry[2], arry[3], arry[4] };
        const bool** temp2 = temp;
        return temp;
    }
public:
	SymbolDisplay(Vector2Int position, int pixelSize, const bool inputData[5][3]);
    ~SymbolDisplay();
	void Draw(SDL_Renderer* renderer);

    void GetArrayFromInt(int numberToDraw)
    {

        switch (numberToDraw)
        {
        case 0:
            return TwoDBools(zero);
        case 1:
            return TwoDBools(one);
        case 2:
            return TwoDBools(two);
        case 3:
            return TwoDBools(three);
        case 4:
            return TwoDBools(four);
        case 5:
            return TwoDBools(five);
        case 6:
            return TwoDBools(six);
        case 7:
            return TwoDBools(seven);
        case 8:
            return TwoDBools(eight);
        case 9:
            return TwoDBools(nine);
        default:
            return TwoDBools(blank);
        }
    }

    const bool blank[5][3] =
    {
            {0, 0, 0},
            {0, 0, 0},
            {0, 0, 0},
            {0, 0, 0},
            {0, 0, 0}
    };

    const bool zero[5][3] =
    {
            {1, 1, 1},
            {1, 0, 1},
            {1, 0, 1},
            {1, 0, 1},
            {1, 1, 1}
    };

    const bool one[5][3] =
    {
            {1, 0, 0},
            {1, 0, 0},
            {1, 0, 0},
            {1, 0, 0},
            {1, 0, 0}
    };

    const bool two[5][3] =
    {
            {1, 1, 1},
            {0, 0, 1},
            {1, 1, 1},
            {1, 0, 0},
            {1, 1, 1}
    };

    const bool three[5][3] =
    {
            {1, 1, 1},
            {0, 0, 1},
            {0, 1, 1},
            {0, 0, 1},
            {1, 1, 1}
    };

    const bool four[5][3] =
    {
            {1, 0, 1},
            {1, 0, 1},
            {1, 1, 1},
            {0, 0, 1},
            {0, 0, 1}
    };

    const bool five[5][3] =
    {
            {1, 1, 1},
            {1, 0, 0},
            {1, 1, 1},
            {0, 0, 1},
            {1, 1, 1}
    };

    const bool six[5][3] =
    {
            {1, 1, 1},
            {1, 0, 0},
            {1, 1, 1},
            {1, 0, 1},
            {1, 1, 1}
    };

    const bool seven[5][3] =
    {
            {1, 1, 1},
            {0, 0, 1},
            {0, 0, 1},
            {0, 0, 1},
            {0, 0, 1}
    };

    const bool eight[5][3] =
    {
            {1, 1, 1},
            {1, 0, 1},
            {1, 1, 1},
            {1, 0, 1},
            {1, 1, 1}
    };

    const bool nine[5][3] =
    {
            {1, 1, 1},
            {1, 0, 1},
            {1, 1, 1},
            {0, 0, 1},
            {1, 1, 1}
    };
};