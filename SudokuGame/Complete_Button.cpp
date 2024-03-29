#include "Complete_Button.h"
#include <SDL.h>
#include <SDL_image.h>
#include <iostream>

extern int window_width;
extern int window_height;
extern int screen_resolution_width;
extern int screen_resolution_height;

Complete_Button::Complete_Button()
{
	button_type = BUTTON_COMPLETE;
}


void Complete_Button::set_size(int w, int h)
{
	if (w < screen_resolution_height * 0.20)
	{
		width = w;
		height = h;
		button.w = width;
		button.h = height;
	}
	else
	{
		width = screen_resolution_height*0.20;
		height = width/2;
		button.w = width;
		button.h = height;
	}
}


void Complete_Button::Load_Image(SDL_Renderer*& renderer) 
{
	SDL_Surface* image = IMG_Load("images/sprites/buttons/button_complete.png");
	if (image == NULL)
	{
		std::cerr << "Error Loading Complete_Button image: " << SDL_GetError() << std::endl;
	}

	textures[0] = SDL_CreateTextureFromSurface(renderer, image);
	SDL_FreeSurface(image);

	image = IMG_Load("images/sprites/buttons/button_complete_mouse_over.png");
	if (image == NULL)
	{
		std::cerr << "Error Loading Complete_Button image: " << SDL_GetError() << std::endl;
	}
	textures[1] = SDL_CreateTextureFromSurface(renderer, image);
	SDL_FreeSurface(image);
}

void Complete_Button::action()
{

}

void Complete_Button::render(SDL_Renderer*& renderer) 
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

void Complete_Button::update()
{
	set_size(window_width / 7, window_width / 14);
	set_position(window_width - width - 20, window_height - height - 10);
}