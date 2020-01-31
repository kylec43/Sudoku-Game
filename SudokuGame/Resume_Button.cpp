#include "Resume_Button.h"
#include <SDL.h>
#include <SDL_image.h>
#include <iostream>

extern int window_width;
extern int window_height;
extern int screen_resolution_width;
extern int screen_resolution_height;

Resume_Button::Resume_Button()
{
	button_type = BUTTON_RESUME;
}

void Resume_Button::action()
{

}

void Resume_Button::set_size(int w, int h)
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

void Resume_Button::Load_Image(SDL_Renderer*& renderer)
{
	SDL_Surface* image = IMG_Load("images/sprites/buttons/button_resume.png");

	if (image == NULL)
	{
		std::cerr << "Error Loading image for Resume_Button: " << SDL_GetError() << std::endl;
	}
	textures[0] = SDL_CreateTextureFromSurface(renderer, image);
	SDL_FreeSurface(image);
	image = IMG_Load("images/sprites/buttons/button_resume_mouse_over.png");

	if (image == NULL)
	{
		std::cerr << "Error Loading image for Resume_Button: " << SDL_GetError() << std::endl;
	}
	textures[1] = SDL_CreateTextureFromSurface(renderer, image);
	SDL_FreeSurface(image);
}

void Resume_Button::render(SDL_Renderer*& renderer)
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

void Resume_Button::update()
{

}