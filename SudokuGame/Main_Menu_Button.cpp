#include "Main_Menu_Button.h"
#include "GameData.h"
#include "Level_ID.h"
#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include <atomic>

extern int window_width;
extern int window_height;
extern int screen_resolution_width;
extern int screen_resolution_height;
extern std::atomic<int> level;
extern bool level_generated;
extern std::atomic<bool> generate_board;
extern std::atomic<bool> generate_saved_board;
extern bool save_exists;

Main_Menu_Button::Main_Menu_Button(int type)
{
	if (type == BUTTON_EXIT)
	{
		button_type = BUTTON_EXIT;
	}
	else if (type == BUTTON_START)
	{
		button_type = BUTTON_START;
	}
	else if (type == BUTTON_CONTINUE)
	{
		button_type = BUTTON_CONTINUE;
	}

}

void Main_Menu_Button::action()
{
	if (button_type == BUTTON_START)
	{
		level = LEVEL_DIFFICULTY_SELECT;
		level_generated = false;
	}
	else if (button_type == BUTTON_CONTINUE)
	{
		level = LEVEL_SUDOKU;
		GameData::Destroy();
		level_generated = false;
		generate_board = true;
		generate_saved_board = true;
	}
}

void Main_Menu_Button::set_size(int w, int h)
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


void Main_Menu_Button::Load_Image(SDL_Renderer*& renderer)
{

	SDL_Surface* image = NULL;
	if (button_type == BUTTON_START)
	{
		image = IMG_Load("images/sprites/buttons/button_start.png");
	}
	else if (button_type == BUTTON_EXIT)
	{
		image = IMG_Load("images/sprites/buttons/button_exit.png");
	}
	else if (button_type == BUTTON_CONTINUE)
	{
		image = IMG_Load("images/sprites/buttons/button_continue.png");
	}

	if (image == NULL)
	{
		std::cerr << "Error Loading image for Main_Menu_Button: " <<SDL_GetError()<< std::endl;
	}
	textures[0] = SDL_CreateTextureFromSurface(renderer, image);
	SDL_FreeSurface(image);


	if (button_type == BUTTON_START)
	{
		image = IMG_Load("images/sprites/buttons/button_start_mouse_over.png");
	}
	else if (button_type == BUTTON_EXIT)
	{
		image = IMG_Load("images/sprites/buttons/button_exit_mouse_over.png");
	}
	else if (button_type == BUTTON_CONTINUE)
	{
		image = IMG_Load("images/sprites/buttons/button_continue_mouse_over.png");
	}

	if (image == NULL)
	{
		std::cerr << "Error Loading image for Main_Menu_Button: " << SDL_GetError() << std::endl;
	}
	textures[1] = SDL_CreateTextureFromSurface(renderer, image);
	SDL_FreeSurface(image);
}


void Main_Menu_Button::render(SDL_Renderer*& renderer)
{
	if (!image_loaded)
	{
		Load_Image(renderer);
		image_loaded = true;
	}

	if (display == true)
	{
		if (button_type != BUTTON_CONTINUE)
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
		else
		{
			if (save_exists == true)
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

	}
}

void Main_Menu_Button::update()
{
	set_size(window_width / 6, window_width / 12);

	if (button_type == BUTTON_START)
	{
		set_position(0 + window_width / 2 - width / 2, 0 + window_height * 0.50 - height / 2);
	}
	else if (button_type == BUTTON_EXIT)
	{
		set_position(0 + window_width / 2 - width / 2, 0 + window_height * 0.70 - height / 2);
	}
	else if (button_type == BUTTON_CONTINUE)
	{
		set_position(0 + window_width / 2 - width / 2, 0 + window_height * 0.30 - height / 2);
	}

}