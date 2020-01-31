#include "Message_Handler.h"
#include "Message_Box.h"
#include "Level_ID.h"
#include <SDL_ttf.h>
#include <SDL.h>
#include <vector>
#include <chrono>
#include <iostream>
#include <atomic>

extern int window_width;
extern int window_height;
extern std::atomic<int> level;

Message_Handler::Message_Handler(int c_level, int font_size) : text_message(0), display(false), images_loaded(false), 
											Box(NULL), current_level(c_level), text_box({})
{

	Sans = TTF_OpenFont("Fonts/Sans.ttf", font_size);
	if (Sans == NULL)
	{
		std::cerr << "Opening Sans Font Error: " << SDL_GetError() << std::endl;
	}
}

void Message_Handler::Destroy_Message_Box()
{
	delete Box;
	Box = NULL;
	display = false;
}


void Message_Handler::Load_Textures(SDL_Renderer*& renderer) 
{
	color = { 255, 255, 255 };
	SDL_Surface* surfaceMessage = TTF_RenderText_Solid(Sans, "The Board is Incomplete!", color);
	messages.push_back(SDL_CreateTextureFromSurface(renderer,surfaceMessage));
	SDL_FreeSurface(surfaceMessage);

	surfaceMessage = TTF_RenderText_Solid(Sans, "The Board has an error!", color);
	messages.push_back(SDL_CreateTextureFromSurface(renderer, surfaceMessage));
	SDL_FreeSurface(surfaceMessage);

	surfaceMessage = TTF_RenderText_Solid(Sans, "The Board is complete! Good Job!", color);
	messages.push_back(SDL_CreateTextureFromSurface(renderer, surfaceMessage));
	SDL_FreeSurface(surfaceMessage);

	surfaceMessage = TTF_RenderText_Solid(Sans, "Select A Difficulty", color);
	messages.push_back(SDL_CreateTextureFromSurface(renderer, surfaceMessage));
	SDL_FreeSurface(surfaceMessage);

	surfaceMessage = TTF_RenderText_Solid(Sans, "Sudoku", color);
	messages.push_back(SDL_CreateTextureFromSurface(renderer, surfaceMessage));
	SDL_FreeSurface(surfaceMessage);

	surfaceMessage = TTF_RenderText_Solid(Sans, "Options", color);
	messages.push_back(SDL_CreateTextureFromSurface(renderer, surfaceMessage));
	SDL_FreeSurface(surfaceMessage);

	surfaceMessage = TTF_RenderText_Solid(Sans, "Save Successful!", color);
	messages.push_back(SDL_CreateTextureFromSurface(renderer, surfaceMessage));
	SDL_FreeSurface(surfaceMessage);

	surfaceMessage = TTF_RenderText_Solid(Sans, "Save Unsuccessful!", color);
	messages.push_back(SDL_CreateTextureFromSurface(renderer, surfaceMessage));
	SDL_FreeSurface(surfaceMessage);

	for (auto m : messages)
	{
		if (m == NULL)
		{
			std::cerr << "Error Loading Message_Handler Text: " << SDL_GetError() << std::endl;
		}
	}


}


void Message_Handler::Set_Display(bool flag)
{

	if (flag == true && display == true)
	{
		delete Box;
		Box = NULL;
	}

	display = flag;
	if (display == true)
	{
		if (text_message == TXT_INCOMPLETE || text_message == TXT_BOARD_ERROR || text_message == TXT_COMPLETE || 
			text_message == TXT_SAVE_SUCCESSFUL || text_message == TXT_SAVE_UNSUCCESSFUL)
		{
			Box = new Message_Box(MESSAGE_BOX_OK);
		}
		else if (text_message == TXT_OPTIONS)
		{
			Box = new Message_Box(MESSAGE_BOX_OPTIONS);
		}
	}
	else if (display == false)
	{
		delete Box;
		Box = NULL;
	}
}

void Message_Handler::Set_Text(int message)
{
	text_message = message;
}

Message_Box* Message_Handler::get_message_box()
{
	return Box;
}


void Message_Handler::render(SDL_Renderer*& renderer) 
{


	if (images_loaded == false && Sans != NULL)
	{
		Load_Textures(renderer);
		images_loaded = true;
	}


	/*Render Message Box Text*/
	if (display == true)
	{

		Box->render(renderer);

		if (text_message == TXT_INCOMPLETE)
		{
			SDL_RenderCopy(renderer, messages[TXT_INCOMPLETE], NULL, &text_box);
		}
		else if (text_message == TXT_BOARD_ERROR)
		{
			SDL_RenderCopy(renderer, messages[TXT_BOARD_ERROR], NULL, &text_box);
		}
		else if (text_message == TXT_COMPLETE)
		{
			SDL_RenderCopy(renderer, messages[TXT_COMPLETE], NULL, &text_box);
		}
		else if (text_message == TXT_OPTIONS)
		{
			SDL_RenderCopy(renderer, messages[TXT_OPTIONS], NULL, &text_box);
		}
		else if (text_message == TXT_SAVE_SUCCESSFUL)
		{
			SDL_RenderCopy(renderer, messages[TXT_SAVE_SUCCESSFUL], NULL, &text_box);
		}
		else if (text_message == TXT_SAVE_UNSUCCESSFUL)
		{
			SDL_RenderCopy(renderer, messages[TXT_SAVE_UNSUCCESSFUL], NULL, &text_box);
		}
	}

	/*Render Standalone Text*/
	switch (current_level)
	{

		case LEVEL_MAIN_MENU:
			SDL_RenderCopy(renderer, messages[TXT_MAIN_MENU], NULL, &text_box);
			break;

		case LEVEL_DIFFICULTY_SELECT:
			SDL_RenderCopy(renderer, messages[TXT_DIFFICULTY_SELECT], NULL, &text_box);
			break;


	}
}


void Message_Handler::update()
{


	switch(current_level)
	{

		case LEVEL_MAIN_MENU:
			text_box.w = window_height / 2;
			text_box.h = window_height / 8;
			text_box.x = 0 + window_width / 2 - text_box.w / 2;
			text_box.y = 0 + window_height * 0.05;
			break;

		case LEVEL_DIFFICULTY_SELECT:
			text_box.w = window_height / 2;
			text_box.h = window_height / 8;
			text_box.x = 0 + window_width / 2 - text_box.w / 2;
			text_box.y = 0 + window_height * 0.10;
			break;

		case LEVEL_SUDOKU:
			if (Box != NULL)
			{
				Box->update();

				if (Box->get_type() == MESSAGE_BOX_OK)
				{
					text_box.w = Box->get_w() * 0.75;
					text_box.h = text_box.w * 0.2;
					text_box.x = Box->get_x() + Box->get_w() - Box->get_w() / 2 - text_box.w / 2;
					text_box.y = Box->get_y() + Box->get_h() - Box->get_h() / 2 - text_box.h;
				}
				else if (Box->get_type() == MESSAGE_BOX_OPTIONS)
				{
					text_box.w = Box->get_w() * 0.50;
					text_box.h = text_box.w * 0.2;
					text_box.x = Box->get_x() + Box->get_w() - Box->get_w() / 2 - text_box.w / 2;
					text_box.y = Box->get_y() + 15;
				}
			}
			break;
	}

}




Message_Handler::~Message_Handler()
{
	for (auto m : messages)
	{
		SDL_DestroyTexture(m);
	}

	delete Box;
	Box = NULL;
}