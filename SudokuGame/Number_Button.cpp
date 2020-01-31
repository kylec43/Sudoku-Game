#include "Number_Button.h"
#include <SDL.h>
#include <SDL_image.h>
#include <string>
#include <iostream>

extern int window_width;
extern int window_height;
extern int screen_resolution_width;
extern int screen_resolution_height;

Number_Button::Number_Button(int n): number(n)
{
	button_type = BUTTON_NUMBER;
}

void Number_Button::action()
{

}

void Number_Button::set_size(int w, int h)
{
	if (w < screen_resolution_height * 0.08)
	{
		width = w;
		height = h;
		button.w = width;
		button.h = height;
	}
	else
	{
		width = screen_resolution_height * 0.08;
		height = width;
		button.w = width;
		button.h = height;
	}
}

void Number_Button::Load_Image(SDL_Renderer*& renderer)
{
	std::string path = "images/sprites/buttons/button_" + std::to_string(number) + ".png";
	SDL_Surface* image = IMG_Load(path.c_str());

	if (image == NULL)
	{
		std::cerr << "Error Loading image for Number_Button: " << SDL_GetError() << std::endl;
	}
	textures[0] = SDL_CreateTextureFromSurface(renderer, image);
	SDL_FreeSurface(image);


	path = "images/sprites/buttons/button_" + std::to_string(number) + "_mouse_over.png";
	image = IMG_Load(path.c_str());

	if (image == NULL)
	{
		std::cerr << "Error Loading image for Main_Menu_Button: " << SDL_GetError() << std::endl;
	}
	textures[1] = SDL_CreateTextureFromSurface(renderer, image);
	SDL_FreeSurface(image);
}

int Number_Button::get_value()
{
	return number;
}

void Number_Button::render(SDL_Renderer*& renderer)
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

void Number_Button::update()
{
	set_size(window_width / 18, window_width / 18);
	set_position(0 + window_width/2 - width/2 + (width + 2) * (number- 5), 0 + window_height - height - 10);
}