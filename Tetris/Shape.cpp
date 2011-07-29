#include "Include.h"

void Shape::init(int Type)
{
	type = Type;
	direction = 0;
	speed = DEFAULT_SPEED;
	x = GAME_WIDTH / 2.0f;
	y = -10.0f;
	for(int i = 0; i < BLOCKS_PER_SHAPE; ++i)
		blocks[i].display = true;

	switch(type)
	{
	case Shape::I:
		for(int i = 0; i < BLOCKS_PER_SHAPE; ++i)
		{
			blocks[i].x = 0.0f;
			blocks[i].y = (float)-i;
		}
		r = 0.0f; g = 1.0f; b = 1.0f;
		break;
	case Shape::J:
		for(int i = 0; i < BLOCKS_PER_SHAPE; ++i)
		{
			blocks[i].x = (float)-floor((double)i / 3.0f);
			blocks[i].y = i == 3 ? (float)-i + 3 : (float)-i;
		}
		r = 0.0f; g = 0.0f; b = 1.0f;
		break;
	case Shape::L:
		for(int i = 0; i < BLOCKS_PER_SHAPE; ++i)
		{
			blocks[i].x = (float)floor((double)i / 3.0f);
			blocks[i].y = i == 3 ? (float)-i + 3 : (float)-i;
		}
		r = 1.0f; g = 0.5f; b = 0.0f;
		break;
	case Shape::O:
		for(int i = 0; i < BLOCKS_PER_SHAPE; ++i)
		{
			blocks[i].x = i >= 2 ? 1.0f : 0.0f;
			blocks[i].y = (float)-(i % 2);
		}
		r = 1.0f; g = 1.0f; b = 0.0f;
		break;
	case Shape::S:
		for(int i = 0; i < BLOCKS_PER_SHAPE; ++i)
		{
			blocks[i].x = i >= 2 ? (float)i - 2 : (float)i - 1;
			blocks[i].y = (float)-floor((double)i / 2.0f);
		}
		r = 0.0f; g = 1.0f; b = 0.0f;
		break;
	case Shape::T:
		for(int i = 0; i < BLOCKS_PER_SHAPE; ++i)
		{
			blocks[i].x = i == 3 ? 0.0f : i - 1;
			blocks[i].y = i == 3 ? 0.0f : -1.0f;
		}
		r = 1.0f; g = 0.0f; b = 1.0f;
		break;
	case Shape::Z:
		for(int i = 0; i < BLOCKS_PER_SHAPE; ++i)
		{
			blocks[i].x = i >= 2 ? (float)-i + 2 : (float)-i + 1;
			blocks[i].y = -(float)floor((double)i / 2.0f);
		}
		r = 1.0f; g = 0.0f; b = 0.0f;
		break;
	}
}

void Shape::rotate()
{
	++direction;
	int absDirection = abs(direction) % 4;
	for(int i = 0; i < BLOCKS_PER_SHAPE; ++i)
	{
		float x = blocks[i].x, y = blocks[i].y;
		switch(absDirection)
		{
		case 0:
			blocks[i].x = -y;
			blocks[i].y = x;
			break;
		case 1:
			blocks[i].x = -y;
			blocks[i].y = x;
			break;
		case 2:
			blocks[i].x = -y;
			blocks[i].y = x;
			break;
		case 3:
			blocks[i].x = -y;
			blocks[i].y = x;
			break;
		}
	}
}