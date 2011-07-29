#include "Include.h"

Game::Game()
{
	lastMove = SDL_GetTicks();
	for(int i = 0; i < SDLK_LAST; ++i)
	{
		curKeys[i] = false;
		lastKeys[i] = false;
	}
	srand((unsigned int)time(NULL));
	for(int i = 0; i < MAX_SHAPES; ++i)
		shapes[i].init(rand() % NUM_SHAPES);
	curShape = 0;
	shapes[curShape].y = 0.0f;

	shapes[curShape + 1].x = NEXT_SHAPE_X;
	shapes[curShape + 1].y = NEXT_SHAPE_Y;
}

bool Game::handleEvents()
{
	if(SDL_PollEvent(&e))
	{
		switch(e.type)
		{
		case SDL_QUIT:
			return false;
			break;
		case SDL_KEYDOWN:
			for(int i = 0; i < SDLK_LAST; ++i)
			{
				if(e.key.keysym.sym == i)
					curKeys[i] = true;
			}
			break;
		case SDL_KEYUP:
			for(int i = 0; i < SDLK_LAST; ++i)
			{
				if(e.key.keysym.sym == i)
					curKeys[i] = false;
			}
			break;
		default:
			break;
		}
	}
	if(curKeys[SDLK_ESCAPE] && !lastKeys[SDLK_ESCAPE])
		return false;

	if(curKeys[SDLK_SPACE] && !lastKeys[SDLK_SPACE])
		while(doGravity(curShape));

	if(curKeys[SDLK_UP] && !lastKeys[SDLK_UP])
	{
		float x[BLOCKS_PER_SHAPE], y[BLOCKS_PER_SHAPE];
		for(int i = 0; i < BLOCKS_PER_SHAPE; ++i)
		{
			x[i] = shapes[curShape].blocks[i].x;
			y[i] = shapes[curShape].blocks[i].y;
		}

		shapes[curShape].rotate();

		//dont rotate into another block
		bool rotate = true;
		for(int i = 0; i < BLOCKS_PER_SHAPE; ++i) //current blocks
		{
			for(int a = 0; a < MAX_SHAPES; ++a) //all shapes
			{
				for(int b = 0; b < BLOCKS_PER_SHAPE; ++b) //all blocks
				{
					if(!shapes[a].blocks[b].display)
						continue; //ignore blocks not displayed
					if(a != curShape && shapes[curShape].x + shapes[curShape].blocks[i].x == shapes[a].x + shapes[a].blocks[b].x && shapes[curShape].y + shapes[curShape].blocks[i].y == shapes[a].y + shapes[a].blocks[b].y)
					{
						rotate = false;
						for(int c = 0; c < BLOCKS_PER_SHAPE; ++c)
						{
							shapes[curShape].blocks[c].x = x[c]; //undo rotate
							shapes[curShape].blocks[c].y = y[c]; //undo rotate
						}
					}
				}
				if(!rotate)
					break;
			}
			if(!rotate)
				break;
		}
	}

	if(curKeys[SDLK_DOWN])
		shapes[curShape].speed = DEFAULT_SPEED / 10;
	else
		shapes[curShape].speed = DEFAULT_SPEED;

	bool left = false, right = false;
	for(int i = 0; i < BLOCKS_PER_SHAPE; ++i) //current blocks
	{
		left = shapes[curShape].x + shapes[curShape].blocks[i].x > 0.0f;
		right = shapes[curShape].x + shapes[curShape].blocks[i].x < GAME_WIDTH;
		
		for(int a = 0; a < MAX_SHAPES; ++a) //all shapes
		{
			for(int b = 0; b < BLOCKS_PER_SHAPE; ++b) //all blocks
			{
				if(!shapes[a].blocks[b].display)
					continue; //ignore blocks not displayed
				left = a != curShape && shapes[curShape].x + shapes[curShape].blocks[i].x - 1 == shapes[a].x + shapes[a].blocks[b].x && shapes[curShape].y + shapes[curShape].blocks[i].y == shapes[a].y + shapes[a].blocks[b].y;
				right = a != curShape && shapes[curShape].x + shapes[curShape].blocks[i].x + 1 == shapes[a].x + shapes[a].blocks[b].x && shapes[curShape].y + shapes[curShape].blocks[i].y == shapes[a].y + shapes[a].blocks[b].y;
				if(left || right)
					break;
			}
			if(left || right)
				break;
		}
		if(left || right)
			break;
	}

	if(curKeys[SDLK_LEFT] && !lastKeys[SDLK_LEFT] && !left)
		--shapes[curShape].x;
	if(curKeys[SDLK_RIGHT] && !lastKeys[SDLK_RIGHT] && !right)
		++shapes[curShape].x;

	for(int i = 0; i < BLOCKS_PER_SHAPE; ++i) //keep blocks on screen by moving shapes
	{
		if(shapes[curShape].x + shapes[curShape].blocks[i].x < 0.0f)
			++shapes[curShape].x;
		if(shapes[curShape].x + shapes[curShape].blocks[i].x > GAME_WIDTH)
			--shapes[curShape].x;
		if(shapes[curShape].y + shapes[curShape].blocks[i].y > GAME_HEIGHT)
			--shapes[curShape].y;
	}

	int numBlocks = 0, row = 0;
	bool fullRow = false;

	for(int i = 0; i < GAME_HEIGHT; ++i) //each row
	{
		numBlocks = 0;
		for(int a = 0; a < MAX_SHAPES; ++a) //all shapes
		{
			for(int b = 0; b < BLOCKS_PER_SHAPE; ++b) //all blocks
			{
				if(!shapes[a].blocks[b].display)
					continue; //ignore blocks not displayed
				if(shapes[a].y + shapes[a].blocks[b].y == i)
					++numBlocks;
				fullRow = numBlocks > GAME_WIDTH && shapes[a].speed == 0;
				row = i;
				if(fullRow)
 					break;
			}
			if(fullRow)
				break;
		}
		if(fullRow)
			break;
	}
	if(fullRow)
	{
		for(int i = 0; i < MAX_SHAPES; ++i) //all shapes
		{
			for(int a = 0; a < BLOCKS_PER_SHAPE; ++a) //all blocks
			{
				if(!shapes[i].blocks[a].display)
					continue; //ignore blocks not displayed
				if(shapes[i].y + shapes[i].blocks[a].y == row)
					shapes[i].blocks[a].display = false;
			}
		}

		for(int i = 0; i < MAX_SHAPES; ++i) //all shapes
		{
			doGravity(i);
		}
	}

	int now = SDL_GetTicks();
	if(now - lastMove >= shapes[curShape].speed)
	{
		if(!doGravity(curShape))
		{
			if(shapes[curShape].y == -1.0f)
			{
				MessageBox(NULL, "You Lose", "", NULL);
				return false;
			}
			shapes[curShape].speed = 0;
			++curShape;
			shapes[curShape].x = GAME_WIDTH / 2;
			shapes[curShape].y = -1.0f;

			shapes[curShape + 1].x = NEXT_SHAPE_X;
			shapes[curShape + 1].y = NEXT_SHAPE_Y;
		}

		lastMove = now;
	}

	for(int i = 0; i < SDLK_LAST; ++i)
		lastKeys[i] = curKeys[i];

	return true;
}

bool Game::doGravity(int shape)
{
	bool doGravity = true;
	for(int i = 0; i < BLOCKS_PER_SHAPE; ++i) //current blocks
	{
		if(!shapes[shape].blocks[i].display)
			continue; //ignore blocks not displayed

		doGravity = shapes[shape].y + shapes[shape].blocks[i].y != GAME_HEIGHT; //current blocks not off the screen

		for(int a = 0; a < MAX_SHAPES; ++a) //all shapes
		{
			for(int b = 0; b < BLOCKS_PER_SHAPE; ++b) //all blocks
			{
				if(!shapes[a].blocks[b].display)
					continue; //ignore blocks not displayed
				if(a != shape && shapes[shape].y + shapes[shape].blocks[i].y + 1 == shapes[a].y + shapes[a].blocks[b].y && shapes[shape].x + shapes[shape].blocks[i].x == shapes[a].x + shapes[a].blocks[b].x)
				{
					doGravity = false;
					break;
				}
			}
			if(!doGravity)
				break;
		}
		if(!doGravity)
			break;
	}

	if(doGravity)
	{
		if(shape != curShape)
		{
			for(int i = 0; i < BLOCKS_PER_SHAPE; ++i)
			{
				++shapes[shape].blocks[i].y;
			}
		}
		else
			++shapes[shape].y;
	}

	return doGravity;
}