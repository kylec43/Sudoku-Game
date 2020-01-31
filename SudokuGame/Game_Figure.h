#ifndef GAME_FIGURE
#define GAME_FIGURE

#include <SDL.h>

class Game_Figure {

protected:
	int x;
	int y;
	virtual void render(SDL_Renderer*&) = 0;
	virtual void update() = 0;
};

#endif