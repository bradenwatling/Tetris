#pragma once
#define WIDTH 640
#define HEIGHT 480

#define PI 3.14159265f

#define DEFAULT_SPEED 250
#define BLOCK_WIDTH 20.0f
#define GAME_WIDTH 10
#define GAME_HEIGHT 23 //HEIGHT / BLOCK_WIDTH - 1
#define MAX_SHAPES 1024

#define NEXT_SHAPE_X GAME_WIDTH + 4
#define NEXT_SHAPE_Y 4

#define BLOCKS_PER_SHAPE 4
#define NUM_SHAPES 7

#include <SDL.h>
#include <SDL_opengl.h>
#include <math.h>
#include <time.h>

#include "Shape.h"
#include "Game.h"
#include "Graphics.h"

using namespace std;