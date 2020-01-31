#ifndef GAMEDATA
#define GAMEDATA

#include <vector>
#include <array>
#include <deque>
#include <atomic>
class Sudoku_Board;
class Background;
class Complete_Button;
class Message_Handler;
class Message_Box;
class Button;

class GameData {
public:
	static Background* background;
	static Sudoku_Board* sudoku_board;
	static std::vector<Button*> buttons;
	static Message_Handler* message_handler;


	static std::vector < std::array<std::array<int, 9>, 9>> puzzles;
	static void Destroy();
};

#endif
