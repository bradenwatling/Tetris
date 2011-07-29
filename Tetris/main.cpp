#include "Include.h"

int main(int argc, char* argv[])
{
	Graphics graphics;
	Game game;
	while(game.handleEvents())
	{
		graphics.display(game);
	}
	return 0;
}