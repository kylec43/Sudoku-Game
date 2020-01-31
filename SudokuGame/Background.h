#ifndef BACKGROUND
#define BACKGROUND

#include "Game_Figure.h"
#include <SDL.h>
#include <string>

class Background : public Game_Figure {
public:
	Background(SDL_Renderer*&, const std::string&);
	void render(SDL_Renderer*&) override;
	void update() override;
	~Background();

private:
	SDL_Texture* background_image;
};


#endif