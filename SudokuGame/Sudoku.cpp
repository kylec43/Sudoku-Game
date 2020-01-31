#include <SDL.h>
#include "Main_Menu.h"
#include "Background.h"
#include "Sudoku_Board.h"
#include "Complete_Button.h"
#include "Options_Button.h"
#include "Number_Button.h"
#include "Message_Handler.h"
#include "Message_Box.h"
#include "Level_ID.h"
#include "GameData.h"
#include <atomic>

extern int window_width;
extern int window_height;
extern std::atomic<bool> generate_board;

void Sudoku(SDL_Renderer*& renderer)
{
	generate_board = true;
	GameData::background = (new Background(renderer, "images/backgrounds/mountains.bmp"));
	GameData::sudoku_board = (new Sudoku_Board(window_width/2 - window_width/4, window_height * 0.10, 32));
	GameData::buttons.push_back(new Complete_Button());
	GameData::buttons.push_back(new Options_Button());
	GameData::message_handler = (new Message_Handler(LEVEL_SUDOKU, 100));

	for (int i = 0; i < 10; i++)
	{
		GameData::buttons.push_back(new Number_Button(i));
	}

}