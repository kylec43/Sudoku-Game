#include "Sudoku_Solver.h"
#include "GameData.h"
#include <vector>
#include <utility>
#include <iostream>
#include <deque>
#include <algorithm>

Sudoku_Solver::Sudoku_Solver() 
							  : row(0), 
								collumn(0), 
								multiple_solutions(false), 
								puzzle{}, 
								tiles{}, 
								solution{}, 
								solution_count(0), 
								clues()
{

}



void Sudoku_Solver::set_board(int(&new_tiles)[9][9]) 
{
	row = 0;
	collumn = 0;
	multiple_solutions = false;
	solution_count = 0;
	clues.clear();
	for (int i = 0; i < 9; i++) 
	{
		for (int j = 0; j < 9; j++) 
		{
			solution[i][j] = 0;
			puzzle[i][j] = new_tiles[i][j];
			tiles[i][j] = new_tiles[i][j];
			if (tiles[i][j] != 0)
			{
				clues.push_back(std::make_pair(i, j));
			}
		}
	}


	while (std::find(clues.begin(), clues.end(), std::make_pair(row, collumn)) != clues.end())
	{
		if (collumn == 8)
		{
			row++;
			collumn = 0;
		}
		else
		{
			collumn++;
		}
	}

}



void Sudoku_Solver::solve() 
{
	if (is_full()) 
	{
		++solution_count;
		if (solution_count > 1) 
		{
			multiple_solutions = true;
			return;
		}
		set_solution();
	}
	else 
	{
		for (int i = 1; i < 10; i++) 
		{
			if (can_put_on_board(i)) 
			{
				int pos_row = row;
				int pos_collumn = collumn;
				add(i);
				solve();
				if (multiple_solutions == true) 
				{
					return;
				}
				remove(i);
			}
		}
	}
}


void Sudoku_Solver::set_solution() 
{
	for (int i = 0; i < 9; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			solution[i][j] = tiles[i][j];
		}
	}
}


bool Sudoku_Solver::is_full() 
{

	for (int i = 0; i < 9; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			if (tiles[i][j] == 0) 
			{
				return false;
			}
		}
	}
	return true;
}


bool Sudoku_Solver::can_put_on_board(int n) 
{

		/*Check Collumn*/
	for (int i = 0; i < 9; i++)
	{
		if (i != row) 
		{
			if (tiles[i][collumn] == n)
			{
				return false;
			}
		}
	}




		/*Check Row*/
	for (int i = 0; i < 9; i++)
	{
		if (i != collumn) 
		{
			if (tiles[row][i] == n)
			{
				return false;
			}
		}
	}



		/*Check Box*/
		int box_position_row = 0;
		int box_position_collumn = 0;

		/*Get box row*/
		if (row % 3 == 0)
		{
			box_position_row = row;
		}
		else if ((row + 1) % 3 == 0)
		{
			box_position_row = row - 2;
		}
		else if ((row - 1) % 3 == 0)
		{
			box_position_row = row - 1;
		}


		/*Get box collumn*/
		if (collumn % 3 == 0)
		{
			box_position_collumn = collumn;
		}
		else if ((collumn + 1) % 3 == 0)
		{
			box_position_collumn = collumn - 2;
		}
		else if ((collumn - 1) % 3 == 0)
		{
			box_position_collumn = collumn - 1;
		}

	/*	for (int i = 0; i < 9; i++) {
			for (int j = 0; j < 9; j++) {
				std::cout << tiles[i][j] << " ";
			}
			std::cout << std::endl;
		}
		std::cout << std::endl;
		std::cout << std::endl << std::endl;
		*/
		for (int i = 0; i < 3; i++)
		{
			if (i != 0) 
			{
				if (tiles[box_position_row][box_position_collumn + i] == n)
				{
					return false;
				}
			}
			if (tiles[box_position_row + 1][box_position_collumn + i] == n)
			{
				return false;
			}
			if (tiles[box_position_row + 2][box_position_collumn + i] == n)
			{
				return false;
			}
		}
	return true;
}



void Sudoku_Solver::add(int n)
{
	tiles[row][collumn] = n;


	if (collumn == 8)
	{
		row++;
		collumn = 0;
	}
	else
	{
		collumn++;
	}

	while (std::find(clues.begin(), clues.end(), std::make_pair(row, collumn)) != clues.end())
	{
		if (collumn == 8)
		{
			row++;
			collumn = 0;
		}
		else
		{
			collumn++;
		}
	}
}


void Sudoku_Solver::remove(int n)
{

	if (collumn == 0)
	{
		row--;
		collumn = 8;
	}
	else
	{
		collumn--;
	}

	while (std::find(clues.begin(), clues.end(), std::make_pair(row, collumn)) != clues.end())
	{
		if (collumn == 0)
		{
			row--;
			collumn = 8;
		}
		else
		{
			collumn--;
		}
	}

	tiles[row][collumn] = 0;

}


int Sudoku_Solver::solutions()
{
	return solution_count;
}


void Sudoku_Solver::print_solution()
{
	for (int i = 0; i < 9; i++) 
	{
		for (int j = 0; j < 9; j++) 
		{
			std::cout << solution[i][j] << " ";
		}
		std::cout << std::endl;
	}
	std::cout << std::endl << std::endl;
}


int (&Sudoku_Solver::get_solution())[9][9]
{
	return solution;
}


void Sudoku_Solver::send_solution_to_game_data()
{
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
			GameData::puzzles.back()[i][j] = solution[i][j];
		}
	}
}