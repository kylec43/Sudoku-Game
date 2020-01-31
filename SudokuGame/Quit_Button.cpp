#include <SDL.h>
#include <SDL_image.h>
#include "Quit_Button.h"
#include "Level_ID.h"
#include "GameData.h"
#include <iostream>
#include <atomic>

extern int window_width;
extern int window_height;
extern int screen_resolution_width;
extern int screen_resolution_height;
extern std::atomic<int> level;
extern bool level_generated;


Quit_Button::Quit_Button()
{
	button_type = BUTTON_QUIT;
}

void Quit_Button::action()
{
		GameData::Destroy();
		level = LEVEL_MAIN_MENU;
		level_generated = false;
	
}

void Quit_Button::set_size(int w, int h)
{
	if (w < screen_resolution_height * 0.50)
	{
		width = w;
		height = h;
		button.w = width;
		button.h = height;
	}
	else
	{
		width = screen_resolution_height * 0.30;
		height = width / 3;
		button.w = width;
		button.h = height;
	}
}

void Quit_Button::Load_Image(SDL_Renderer*& renderer)
{
	SDL_Surface* image = IMG_Load("images/sprites/buttons/button_quit.png");

	if (image == NULL)
	{
		std::cerr << "Error Loading image for Quit_Button: " << SDL_GetError() << std::endl;
	}
	textures[0] = SDL_CreateTextureFromSurface(renderer, image);
	SDL_FreeSurface(image);


	image = IMG_Load("images/sprites/buttons/button_quit_mouse_over.png");

	if (image == NULL)
	{
		std::cerr << "Error Loading image for Quit_Button: " << SDL_GetError() << std::endl;
	}
	textures[1] = SDL_CreateTextureFromSurface(renderer, image);
	SDL_FreeSurface(image);
}

void Quit_Button::render(SDL_Renderer*& renderer)
{
	if (!image_loaded)
	{
		Load_Image(renderer);
		image_loaded = true;
	}

	if (image_type == UNFOCUSED_IMAGE)
	{
		SDL_RenderCopy(renderer, textures[UNFOCUSED_IMAGE], NULL, &button);
	}
	else if (image_type == FOCUSED_IMAGE)
	{
		SDL_RenderCopy(renderer, textures[FOCUSED_IMAGE], NULL, &button);
	}
}

void Quit_Button::update()
{

}