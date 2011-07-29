#pragma once
#include "Include.h"

class Graphics
{
public:
Graphics();
	~Graphics();
	void display(Game game);

private:
	SDL_Surface* loadBMP(const char* path);

	SDL_Surface* screen;
};