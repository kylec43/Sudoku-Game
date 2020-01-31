#include "GameData.h"
#include "Background.h"
#include "Sudoku_Board.h"
#include "Button.h"
#include "Message_Handler.h"
#include "Message_Box.h"
#include <atomic>
#include <mutex>

extern std::mutex Lock_GameData_Puzzles;

Background* GameData::background = NULL;
Sudoku_Board* GameData::sudoku_board = NULL;
Message_Handler* GameData::message_handler = NULL;
std::vector <std::array<std::array<int, 9>, 9>> GameData::puzzles{};
std::vector<Button*> GameData::buttons = {};

void GameData::Destroy() 
{

	for (auto m : buttons) {
		delete m;
		m = NULL;
	}
	buttons.clear();


	delete background;
	background = NULL;

	delete sudoku_board;
	sudoku_board = NULL;

	delete message_handler;
	message_handler = NULL;

	Lock_GameData_Puzzles.lock();
	puzzles.clear();
	Lock_GameData_Puzzles.unlock();
}