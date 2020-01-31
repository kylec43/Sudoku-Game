#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <iostream>
#include <thread>
#include <fstream>
#include <Windows.h>
#include <atomic>
#include "Board_Loader.h"
#include "Level_ID.h"
#include "Game_Loop.h"
#include <mutex>
#include <ShlObj_core.h>

int window_width = 0;
int window_height = 0;
int window_x = 0;
int window_y = 0;
int screen_resolution_width = 0;
int screen_resolution_height = 0;
int mouse_x = 0;
int mouse_y = 0;
std::atomic<bool> generate_board = false;
std::atomic<bool> generate_saved_board = false;
bool save_exists = false;
std::atomic<bool> isRunning = true;
std::atomic<int> difficulty_level = -1;
std::atomic<int> level = LEVEL_MAIN_MENU;
std::mutex Lock_GameData_Puzzles;



int main(int argc, char* args[]) 
{
	bool debug_game = false;

	/*Hide The Console*/
	if (!debug_game)
	{
		HWND consoleWindow = GetConsoleWindow();
		ShowWindow(consoleWindow, SW_HIDE);
	}

	/*Initialize SDL2*/
	if (SDL_Init(SDL_INIT_EVERYTHING) == -1) {
		std::cerr << "SDL Initialization Error: " << SDL_GetError() << std::endl;
	}

	if (!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG)) {
		std::cerr << "SDL Image PNG Initialization Error: " << SDL_GetError() << std::endl;
	}

	if (TTF_Init() == -1) {
		std::cerr << "TTF Initialization Error: " << SDL_GetError() << std::endl;
	}

	/*Get Screen Resolution*/
	SDL_DisplayMode DM;
	SDL_GetCurrentDisplayMode(0, &DM);
	screen_resolution_width = DM.w;
	screen_resolution_height = DM.h;
	window_width = DM.w;
	window_height = DM.h;


	/*Check if a save file exists*/
	char documents_path[MAX_PATH];
	SHGetFolderPath(NULL, CSIDL_PERSONAL, NULL, SHGFP_TYPE_CURRENT, documents_path);
	std::string path = documents_path;
	path = path + "/SudokuGame/";
	std::fstream file(path + "sudoku_save_file");
	if (file.is_open())
	{
		save_exists = true;
		file.close();
	}

	std::thread Start_Game(Game_Loop);
	std::thread Puzzle_Generation(board_loader);
	Start_Game.join();
	Puzzle_Generation.join();

	return 0;
}