#include "Level_Handler.h"
#include "Main_Menu.h"
#include "Difficulty_Select.h"
#include "GameData.h"
#include "Level_ID.h"
#include "Sudoku.h"
#include <atomic>

extern std::atomic<int> level;
bool level_generated = false;
extern std::atomic<bool> generate_board;

void Level_Handler(SDL_Renderer*& renderer)
{
	if (!level_generated)
	{
		GameData::Destroy();

		switch (level.load())
		{
			case LEVEL_MAIN_MENU:
				MainMenu(renderer);
				level_generated = true;
				break;

			case LEVEL_DIFFICULTY_SELECT:
				Difficulty_Select(renderer);
				level_generated = true;
				break;

			case LEVEL_SUDOKU:
				Sudoku(renderer);
				generate_board = true;
				level_generated = true;
				break;
		}


	}

}
