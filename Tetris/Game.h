#pragma once
#include "Include.h"



class Game
{
public:
	Game();
	bool handleEvents();
	bool doGravity(int shape);

	Shape shapes[MAX_SHAPES];
	int curShape;
private:
	SDL_Event e;
	int lastMove;
	bool lastKeys[SDLK_LAST];
	bool curKeys[SDLK_LAST];
};