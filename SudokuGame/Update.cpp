#include "Update.h"
#include "Sudoku_Board.h"
#include "GameData.h"
#include "Message_Handler.h"
#include "Button.h"
void Update() {

	if (GameData::sudoku_board != NULL)
	{
		GameData::sudoku_board->update();
	}

	if (GameData::message_handler != NULL)
	{
		GameData::message_handler->update();
	}

	for (auto m : GameData::buttons)
	{
		m->update();
	}
}