#pragma once
#include "SDL.h"

struct Input
{
public:
	void PollKeys(SDL_Event event);
	bool leftBouncerUp;
	bool leftBouncerDown;
	bool rightBouncerUp;
	bool rightBouncerDown;
};