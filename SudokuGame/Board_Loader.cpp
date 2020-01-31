#include "Board_Loader.h"
#include "GameData.h"
#include "Level_ID.h"
#include <random>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <thread>
#include <atomic>
#include <Windows.h>
#include <mutex>
#include <ShlObj_core.h> //GetFolderPath

extern std::atomic<bool> generate_board;
extern std::atomic<bool> generate_saved_board;
extern std::atomic<bool> isRunning;
extern std::atomic<int> difficulty_level;
extern std::atomic<int> level;
extern std::mutex Lock_GameData_Puzzles;

void board_loader()
{

	while (isRunning) 
	{

		while (generate_board == false)
		{
			std::this_thread::yield();
			if (isRunning == false)
			{
				break;
			}
		}

		if (isRunning == false) break;

		if (generate_saved_board == true)
		{
			send_saved_board_to_game_data();
			generate_board = false;
			generate_saved_board = false;
			continue;
		}

		send_pre_generated_board_to_game_data();
		generate_board = false;
	}
}


void send_saved_board_to_game_data()
{

	int puzzle_solution[9][9];
	int puzzle[9][9];

	char documents_path[MAX_PATH];
	SHGetFolderPath(NULL, CSIDL_PERSONAL, NULL, SHGFP_TYPE_CURRENT, documents_path);
	std::string path = documents_path;
	path = path + "/SudokuGame/";

	std::fstream file(path + "sudoku_save_file");
	if (!file.is_open())
	{
		std::cerr << "Unable to open save file" << std::endl;
	}


	std::string row;
	std::string number;
	int collumn_number = 0;
	int row_number = 0;
	bool get_puzzle = true;
	bool get_solution = false;
	while (std::getline(file, row))
	{
		if (row != "")
		{
			if (collumn_number == 9)
			{
				collumn_number = 0;
				row_number++;
			}

			std::istringstream numbers(row);
			while (numbers >> number)
			{
				if (get_puzzle == true)
				{
					puzzle[row_number][collumn_number] = std::stoi(number);
				}
				else if (get_solution == true)
				{
					puzzle_solution[row_number][collumn_number] = std::stoi(number);
				}
				collumn_number++;
			}
		}
		else
		{
			row_number = 0;
			collumn_number = 0;
			get_solution = true;
			get_puzzle = false;
		}
	}


	Lock_GameData_Puzzles.lock();
	GameData::puzzles.push_back({});
	for (int i = 0; i < 9; i++) {
		for (int j = 0; j < 9; j++)
		{
			GameData::puzzles.back()[i][j] = puzzle[i][j];
		}
	}

	GameData::puzzles.push_back({});
	for (int i = 0; i < 9; i++) {
		for (int j = 0; j < 9; j++)
		{
			GameData::puzzles.back()[i][j] = puzzle_solution[i][j];
		}
	}
	Lock_GameData_Puzzles.unlock();

}



void send_pre_generated_board_to_game_data()
{

	int puzzle_solution[9][9];
	int puzzle[9][9];
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<int> easy_board_dis(0, 4999);
	std::uniform_int_distribution<int> medium_board_dis(0, 1999);
	std::uniform_int_distribution<int> hard_board_dis(0, 499);
	std::fstream file;
	char documents_path[MAX_PATH];

	SHGetFolderPath(NULL, CSIDL_PERSONAL, NULL, SHGFP_TYPE_CURRENT, documents_path);

	std::string path = documents_path;
	path = path + "/SudokuGame/";
	int board_number = 0;
	if (difficulty_level == DIFFICULTY_EASY)
	{
		board_number = easy_board_dis(gen);
		path = path + "sudoku_boards/easy/easy_board" + std::to_string(board_number);
		file.open(path);
	}
	else if (difficulty_level == DIFFICULTY_MEDIUM)
	{
		board_number = medium_board_dis(gen);
		path = path + "sudoku_boards/medium/medium_board" + std::to_string(board_number);
		file.open(path);
	}
	else if (difficulty_level == DIFFICULTY_HARD)
	{
		board_number = hard_board_dis(gen);
		path = path + "sudoku_boards/hard/hard_board" + std::to_string(board_number);
		file.open(path);
	}

	if (!file.is_open())
	{
		std::cerr << "Unable to open pre generated board: LEVEL = " << difficulty_level << " board_number = " << board_number << std::endl;
	}


	std::string row;
	std::string number;
	int collumn_number = 0;
	int row_number = 0;
	bool get_puzzle = true;
	bool get_solution = false;
	while (std::getline(file, row))
	{
		if (row != "")
		{
			if (collumn_number == 9)
			{
				collumn_number = 0;
				row_number++;
			}

			std::istringstream numbers(row);
			while (numbers >> number)
			{
				if (get_puzzle == true)
				{
					puzzle[row_number][collumn_number] = std::stoi(number);
				}
				else if (get_solution == true)
				{
					puzzle_solution[row_number][collumn_number] = std::stoi(number);
				}
				collumn_number++;
			}
		}
		else
		{
			row_number = 0;
			collumn_number = 0;
			get_solution = true;
			get_puzzle = false;
		}
	}

	Lock_GameData_Puzzles.lock();
	GameData::puzzles.push_back({});
	for (int i = 0; i < 9; i++) {
		for (int j = 0; j < 9; j++)
		{
			GameData::puzzles.back()[i][j] = puzzle[i][j];
		}
	}

	GameData::puzzles.push_back({});
	for (int i = 0; i < 9; i++) {
		for (int j = 0; j < 9; j++)
		{
			GameData::puzzles.back()[i][j] = puzzle_solution[i][j];
		}
	}
	Lock_GameData_Puzzles.unlock();


}