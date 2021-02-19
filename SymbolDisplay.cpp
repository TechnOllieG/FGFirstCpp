#include "SymbolDisplay.h"
#include <algorithm>

SymbolDisplay::SymbolDisplay(Vector2Int position, int pixelSize, const bool inputData[5][3])
{
	bool* temp = (bool*) *inputData;
	Init(position, pixelSize, temp);
}

SymbolDisplay::SymbolDisplay(Vector2Int position, int pixelSize, int numberToDisplay)
{
	bool* temp = GetArrayFromInt(numberToDisplay);
	Init(position, pixelSize, temp);
}

SymbolDisplay::SymbolDisplay(Vector2Int position, int pixelSize, bool* inputData)
{
	Init(position, pixelSize, inputData);
}

void SymbolDisplay::Init(Vector2Int position, int pixelSize, bool* inputData)
{
	this->m_pixelSize = pixelSize;
	m_rects = std::vector<SDL_Rect>();
	bool temp[5][3] = {};

	memcpy(temp, inputData, sizeof(bool) * 5 * 3);

	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			if (temp[i][j])
			{
				SDL_Rect rect = SDL_Rect{ (int)position.x + j * pixelSize, (int)position.y + i * pixelSize, pixelSize, pixelSize };
				m_rects.push_back(rect);
			}
		}
	}
}

void SymbolDisplay::Draw(SDL_Renderer* renderer)
{
	int size = m_rects.size();
	for (int i = 0; i < size; i++)
	{
		SDL_RenderFillRect(renderer, &m_rects.at(i));
	}
}