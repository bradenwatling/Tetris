#include "Include.h"

Graphics::Graphics()
{
	SDL_Init(SDL_INIT_EVERYTHING);

	int flags = SDL_SWSURFACE | SDL_GL_DOUBLEBUFFER | SDL_OPENGL;
	int msg = MessageBox(NULL, "Would you like to play in fullscreen mode?", "", MB_YESNO);
	if(msg == IDYES)
	{
			flags |= SDL_FULLSCREEN;
	}
	int bpp = 32;
    screen = SDL_SetVideoMode(WIDTH, HEIGHT, bpp, flags);

	SDL_WM_SetCaption("Tetris", NULL);

	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glViewport(0, 0, WIDTH, HEIGHT);

	glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
	glOrtho(0, WIDTH, HEIGHT, 0, 0, 1);
	glMatrixMode(GL_MODELVIEW);

	glEnable(GL_TEXTURE_2D);
}

Graphics::~Graphics()
{
	SDL_FreeSurface(screen);
	SDL_Quit();
}

void Graphics::display(Game game)
{
	glClear(GL_COLOR_BUFFER_BIT);

	glPushMatrix(); //GUI
		glColor3f(1.0f, 1.0f, 1.0f);

		glBegin(GL_LINES);
			glVertex2f((GAME_WIDTH + 1) * BLOCK_WIDTH + 1, 0.0f);
			glVertex2f((GAME_WIDTH + 1) * BLOCK_WIDTH + 1, HEIGHT);
		glEnd();
	glPopMatrix();

	for(int i = 0; i < MAX_SHAPES; ++i) //all shapes
	{
		for(int a = 0; a < BLOCKS_PER_SHAPE; ++a) //all blocks
		{
			if(!game.shapes[i].blocks[a].display)
				continue; //ignore blocks not displayed
			glPushMatrix();
				glTranslatef(BLOCK_WIDTH * game.shapes[i].x + BLOCK_WIDTH * game.shapes[i].blocks[a].x, BLOCK_WIDTH * game.shapes[i].y + BLOCK_WIDTH * game.shapes[i].blocks[a].y, 0.0f);
				
				glColor3f(sin(game.shapes[i].r), sin(game.shapes[i].g), sin(game.shapes[i].b));

				glBegin(GL_QUADS);
					glVertex2f(0.0f, 0.0f);
					glVertex2f(BLOCK_WIDTH, 0.0f);
					glVertex2f(BLOCK_WIDTH, BLOCK_WIDTH);
					glVertex2f(0.0f, BLOCK_WIDTH);
				glEnd();

				glColor3f(0.0f, 0.0f, 0.0f);

				glBegin(GL_LINE_STRIP);
					glVertex2f(0.0f, 0.0f);
					glVertex2f(BLOCK_WIDTH, 0.0f);
					glVertex2f(BLOCK_WIDTH, BLOCK_WIDTH);
					glVertex2f(0.0f, BLOCK_WIDTH);
					glVertex2f(0.0f, 0.0f);
				glEnd();
			glPopMatrix();
		}
	}

	SDL_GL_SwapBuffers();
}

SDL_Surface* Graphics::loadBMP(const char* path)
{
	GLuint texture;
	SDL_Surface* surface;
	GLenum texture_format;
	GLint  nOfColors;
 
	if (surface = SDL_LoadBMP(path))
	{
		nOfColors = surface->format->BytesPerPixel;
		if (nOfColors == 4)     // contains an alpha channel
		{
				if(surface->format->Rmask == 0x000000ff)
						texture_format = GL_RGBA;
				else
						texture_format = GL_BGRA;
		}
		else if(nOfColors == 3)     // no alpha channel
		{
				if(surface->format->Rmask == 0x000000ff)
						texture_format = GL_RGB;
				else
						texture_format = GL_BGR;
		}
		else
		{
				// this error should not go unhandled
		}
 
		glGenTextures(1, &texture);
		glBindTexture(GL_TEXTURE_2D, texture);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexImage2D(GL_TEXTURE_2D, 0, nOfColors, surface->w, surface->h, 0, texture_format, GL_UNSIGNED_BYTE, surface->pixels);

		glColor3f(1.0f, 1.0f, 1.0f);

		return surface;
	}
	SDL_Quit();
	return NULL;
}