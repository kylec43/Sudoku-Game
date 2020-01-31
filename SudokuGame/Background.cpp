#include "Background.h"
#include <iostream>
#include <SDL.h>
#include <SDL_image.h>

Background::Background(SDL_Renderer*& renderer, const std::string& path): background_image(NULL) 
{
	SDL_Surface* image = IMG_Load(path.c_str());

	if (image == NULL) 
	{
		std::cerr << "Failed to load Background image: " << SDL_GetError() << std::endl;
	}
	background_image = SDL_CreateTextureFromSurface(renderer, image);
	SDL_FreeSurface(image);
	image = NULL;
}

void Background::render(SDL_Renderer*& renderer) 
{
	SDL_RenderCopy(renderer, background_image, NULL, NULL);
}

void Background::update() 
{

}

Background::~Background() 
{
	SDL_DestroyTexture(background_image);
	background_image = NULL;
}
