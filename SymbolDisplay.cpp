#include "SymbolDisplay.h"
#include <algorithm>

SymbolDisplay::SymbolDisplay(Vector2Int position, int pixelSize, const bool inputData[5][3])
{
	rects = new std::vector<SDL_Rect>;

	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			if (inputData[i][j])
			{
				SDL_Rect rect = SDL_Rect{ (int) position.x + j * pixelSize, (int)position.y + i * pixelSize, pixelSize, pixelSize };
				rects->push_back(rect);
			}
		}
	}
}

SymbolDisplay::~SymbolDisplay()
{
	delete rects;
}

void SymbolDisplay::Draw(SDL_Renderer* renderer)
{
	int size = rects->size();
	for (int i = 0; i < size; i++)
	{
		SDL_RenderFillRect(renderer, &rects->at(i));
	}
}