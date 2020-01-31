#include "Difficulty_Button.h"
#include "Level_ID.h"
#include "GameData.h"
#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include <atomic>

extern int window_width;
extern int window_height;
extern int screen_resolution_width;
extern int screen_resolution_height;
extern std::atomic<int> level;
extern std::atomic<int> difficulty_level;
extern bool level_generated;

Difficulty_Button::Difficulty_Button(int difficulty): difficulty_type(difficulty)
{
	button_type = BUTTON_DIFFICULTY;
}

int Difficulty_Button::get_difficulty_type()
{
	return difficulty_type;
}

void Difficulty_Button::action()
{
	if (difficulty_type == EASY)
	{
		difficulty_level = DIFFICULTY_EASY;
	}
	else if (difficulty_type == MEDIUM)
	{
		difficulty_level = DIFFICULTY_MEDIUM;
	}
	else if (difficulty_type == HARD)
	{
		difficulty_level = DIFFICULTY_HARD;
	}
	GameData::Destroy();
	level = LEVEL_SUDOKU;
	level_generated = false;
}

void Difficulty_Button::set_size(int w, int h)
{
	if (w < screen_resolution_height * 0.25)
	{
		width = w;
		height = h;
		button.w = width;
		button.h = height;
	}
	else
	{
		width = screen_resolution_height * 0.20;
		height = width / 2;
		button.w = width;
		button.h = height;
	}
}


void Difficulty_Button::Load_Image(SDL_Renderer*& renderer)
{

	SDL_Surface* image = NULL;
	if (difficulty_type == EASY)
	{
		image = IMG_Load("images/sprites/buttons/button_easy.png");
	}
	else if (difficulty_type == MEDIUM)
	{
		image = IMG_Load("images/sprites/buttons/button_medium.png");
	}
	else if (difficulty_type == HARD)
	{
		image = IMG_Load("images/sprites/buttons/button_hard.png");
	}

	if (image == NULL)
	{
		std::cerr << "Error Loading image for Difficulty_Button: " << SDL_GetError() << std::endl;
	}
	textures[0] = SDL_CreateTextureFromSurface(renderer, image);
	SDL_FreeSurface(image);


	if (difficulty_type == EASY)
	{
		image = IMG_Load("images/sprites/buttons/button_easy_mouse_over.png");
	}
	else if (difficulty_type == MEDIUM)
	{
		image = IMG_Load("images/sprites/buttons/button_medium_mouse_over.png");
	}
	else if (difficulty_type == HARD)
	{
		image = IMG_Load("images/sprites/buttons/button_hard_mouse_over.png");
	}

	if (image == NULL)
	{
		std::cerr << "Error Loading image for Difficulty_Button: " << SDL_GetError() << std::endl;
	}
	textures[1] = SDL_CreateTextureFromSurface(renderer, image);
	SDL_FreeSurface(image);
}


void Difficulty_Button::render(SDL_Renderer*& renderer)
{
	if (!image_loaded)
	{
		Load_Image(renderer);
		image_loaded = true;
	}

	if (display == true)
	{
		if (image_type == UNFOCUSED_IMAGE)
		{
			SDL_RenderCopy(renderer, textures[UNFOCUSED_IMAGE], NULL, &button);
		}
		else if (image_type == FOCUSED_IMAGE)
		{
			SDL_RenderCopy(renderer, textures[FOCUSED_IMAGE], NULL, &button);
		}
	}
}

void Difficulty_Button::update()
{
	set_size(window_width / 6, window_width / 12);

	if (difficulty_type == EASY)
	{
		set_position(0 + window_width / 2 - width / 2, 0 + window_height * 0.40 - height / 2);
	}
	else if (difficulty_type == MEDIUM)
	{
		set_position(0 + window_width / 2 - width / 2, 0 + window_height * 0.60 - height / 2);
	}
	else if (difficulty_type == HARD)
	{
		set_position(0 + window_width / 2 - width / 2, 0 + window_height * 0.80 - height / 2);
	}
}