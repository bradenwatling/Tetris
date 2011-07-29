#pragma once
#include "Include.h"

class Shape
{
public:
	void init(int Type);
	void rotate();

	struct Block
	{
		float x, y;
		bool display;
	};

	enum
	{
		I, J, L, O, S, T, Z,
	};

	int type;
	Block blocks[BLOCKS_PER_SHAPE];
	int direction;
	int speed;
	float x, y;
	float r, g, b;
private:
};