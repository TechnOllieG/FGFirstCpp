#pragma once
#include "SDL.h"

struct Input
{
public:
	void PollKeys(SDL_Event event);
	bool m_leftBouncerUp;
	bool m_leftBouncerDown;
	bool m_rightBouncerUp;
	bool m_rightBouncerDown;
};