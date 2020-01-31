#include "Save_Button.h"
#include "GameData.h"
#include "Sudoku_Board.h"
#include <SDL.h>
#include <SDL_image.h>
#include <fstream>
#include <string>
#include <iostream>
#include <atomic>
#include <Windows.h>
#include <ShlObj_core.h>

extern int window_width;
extern int window_height;
extern int screen_resolution_width;
extern int screen_resolution_height;
extern bool window_maximized;
extern bool save_exists;
extern std::atomic<bool> generate_board;

Save_Button::Save_Button(): board_saved(false)
{
	button_type = BUTTON_SAVE;
}

void Save_Button::action()
{
	if (save())
	{
		board_saved = true;
	}

	std::fstream file("sudoku_save_file");
	if (file.is_open())
	{
		save_exists = true;
		file.close();
	}
}

bool Save_Button::board_is_saved()
{
	return board_saved;
}

int Save_Button::get_value()
{
	return board_is_saved();
}


void Save_Button::set_size(int w, int h)
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

void Save_Button::Load_Image(SDL_Renderer*& renderer)
{
	SDL_Surface* image = IMG_Load("images/sprites/buttons/button_save.png");

	if (image == NULL)
	{
		std::cerr << "Error Loading image for Save_Button: " << SDL_GetError() << std::endl;
	}
	textures[0] = SDL_CreateTextureFromSurface(renderer, image);
	SDL_FreeSurface(image);


	image = IMG_Load("images/sprites/buttons/button_save_mouse_over.png");

	if (image == NULL)
	{
		std::cerr << "Error Loading image for Save_Button: " << SDL_GetError() << std::endl;
	}
	textures[1] = SDL_CreateTextureFromSurface(renderer, image);
	SDL_FreeSurface(image);
}

void Save_Button::render(SDL_Renderer*& renderer)
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

void Save_Button::update()
{

}


bool Save_Button::save()
{

	char documents_path[MAX_PATH];
	SHGetFolderPath(NULL, CSIDL_PERSONAL, NULL, SHGFP_TYPE_CURRENT, documents_path);
	std::string path = documents_path;
	path = path + "/SudokuGame/";

	if (generate_board == false)
	{
		std::ofstream file(path + "sudoku_save_file");

		Sudoku_Board*& board = GameData::sudoku_board;

		/*Save sudoku_board*/
		for (int i = 0; i < 9; i++)
		{
			for (int j = 0; j < 9; j++)
			{
				if (board->tile_index(i, j).is_read_only())
				{
					file << std::to_string(board->tile_index(i, j).get_number()) << " ";
				}
				else
				{
					file << std::to_string(-board->tile_index(i, j).get_number()) << " ";
				}

				if ((j + 1) % 9 == 0)
				{
					file << "\n";
				}
			}
		}

		file << "\n";

		/*Save sudoku_board solution*/
		for (int i = 0; i < 9; i++)
		{
			for (int j = 0; j < 9; j++)
			{
				file << std::to_string(board->solution_index(i, j)) << " ";

				if ((j + 1) % 9 == 0)
				{
					file << "\n";
				}
			}
		}

		file.close();
		return true;
	}

	return false;
}
