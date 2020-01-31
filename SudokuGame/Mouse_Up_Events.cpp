#include "Mouse_Up_Events.h"
#include "GameData.h"
#include "Sudoku_Board.h"
#include <SDL.h>


void Mouse_Up_Events(SDL_Event& e) {
	
	Sudoku_Board* board = GameData::sudoku_board;

	if (board != NULL)
	{
		board->drag_board(false);
	}
}