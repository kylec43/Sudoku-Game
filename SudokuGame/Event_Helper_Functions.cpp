#include "Event_Helper_Functions.h"
#include "GameData.h"
#include "Message_Handler.h"
#include "Sudoku_Board.h"
#include "Tile.h"
#include <iostream>

extern int mouse_x;
extern int mouse_y;

bool message_box_open()
{
	bool msg_box_is_open = false;
	Message_Handler* message_handler = GameData::message_handler;
	if (message_handler != NULL)
	{
		if (message_handler->get_message_box() != NULL)
		{
			msg_box_is_open = true;
		}
	}
	return msg_box_is_open;
}

void unselect_tile()
{

	if (!message_box_open())
	{

		Sudoku_Board*& board = GameData::sudoku_board;

		if (board != NULL)
		{
			for (int i = 0; i < 9; i++)
			{
				for (int j = 0; j < 9; j++)
				{
					if (board->get_tiles()[i][j].is_selected())
					{
						board->get_tiles()[i][j].set_selected(false);
						board->get_tiles()[i][j].set_color(COLOR_WHITE);
					}
				}
			}
		}

	}
}


void set_tile_number(int n)
{

	if (!message_box_open())
	{

		Sudoku_Board*& board = GameData::sudoku_board;

		if (board != NULL)
		{
			for (int i = 0; i < 9; i++)
			{
				for (int j = 0; j < 9; j++)
				{

					Tile& tile = GameData::sudoku_board->get_tiles()[i][j];
					if (tile.is_selected())
					{
						tile.set_number(n);
					}
				}
			}
		}

	}
}


void increment_tile()
{

	if (!message_box_open())
	{

		Sudoku_Board*& board = GameData::sudoku_board;

		if (board != NULL)
		{
			for (int i = 0; i < 9; i++)
			{
				for (int j = 0; j < 9; j++)
				{
					Tile& tile = GameData::sudoku_board->get_tiles()[i][j];
					if (tile.is_selected())
					{
						if (tile.get_number() == 9)
						{
							tile.set_number(0);
						}
						else
						{
							tile.set_number(tile.get_number() + 1);
						}
					}
				}
			}
		}

	}
}

void change_selected_tile(int direction)
{
	bool tile_selected = false;
	Sudoku_Board*& board = GameData::sudoku_board;

	if (board != NULL)
	{
		switch (direction)
		{

		case SDLK_UP:
			tile_selected = false;
			for (int i = 0; i < 9; i++)
			{
				for (int j = 0; j < 9; j++)
				{
					if (board->get_tiles()[i][j].is_selected())
					{
						board->get_tiles()[i][j].set_selected(false);
						board->get_tiles()[i][j].set_color(COLOR_WHITE);
						if (i == 0)
						{
							board->get_tiles()[8][j].set_color(COLOR_DARK_GREY);
							board->get_tiles()[8][j].set_selected(true);
						}
						else
						{
							board->get_tiles()[i - 1][j].set_color(COLOR_DARK_GREY);
							board->get_tiles()[i - 1][j].set_selected(true);
						}
						tile_selected = true;
					}
					if (tile_selected) break;
				}
				if (tile_selected) break;
			}

			if (!tile_selected)
			{
				board->get_tiles()[0][0].set_color(COLOR_DARK_GREY);
				board->get_tiles()[0][0].set_selected(true);
			}
			break;



		case SDLK_DOWN:
			tile_selected = false;
			for (int i = 0; i < 9; i++)
			{
				for (int j = 0; j < 9; j++)
				{
					if (board->get_tiles()[i][j].is_selected())
					{
						board->get_tiles()[i][j].set_selected(false);
						board->get_tiles()[i][j].set_color(COLOR_WHITE);
						if (i == 8)
						{
							board->get_tiles()[0][j].set_color(COLOR_DARK_GREY);
							board->get_tiles()[0][j].set_selected(true);
						}
						else
						{
							board->get_tiles()[i + 1][j].set_color(COLOR_DARK_GREY);
							board->get_tiles()[i + 1][j].set_selected(true);
						}

						tile_selected = true;
					}

					if (tile_selected) break;
				}
				if (tile_selected) break;
			}

			if (!tile_selected)
			{
				Sudoku_Board*& board = GameData::sudoku_board;
				board->get_tiles()[0][0].set_color(COLOR_DARK_GREY);
				board->get_tiles()[0][0].set_selected(true);
			}
			break;



		case SDLK_RIGHT:
			tile_selected = false;
			for (int i = 0; i < 9; i++)
			{
				for (int j = 0; j < 9; j++)
				{
					if (board->get_tiles()[i][j].is_selected())
					{
						board->get_tiles()[i][j].set_selected(false);
						board->get_tiles()[i][j].set_color(COLOR_WHITE);
						if (j == 8)
						{
							board->get_tiles()[i][0].set_color(COLOR_DARK_GREY);
							board->get_tiles()[i][0].set_selected(true);
						}
						else
						{
							board->get_tiles()[i][j + 1].set_color(COLOR_DARK_GREY);
							board->get_tiles()[i][j + 1].set_selected(true);
						}
						tile_selected = true;
					}
					if (tile_selected) break;
				}
				if (tile_selected) break;
			}

			if (!tile_selected)
			{
				board->get_tiles()[0][0].set_color(COLOR_DARK_GREY);
				board->get_tiles()[0][0].set_selected(true);
			}
			break;



		case SDLK_LEFT:
			tile_selected = false;
			for (int i = 0; i < 9; i++)
			{
				for (int j = 0; j < 9; j++)
				{
					if (board->get_tiles()[i][j].is_selected())
					{
						board->get_tiles()[i][j].set_selected(false);
						board->get_tiles()[i][j].set_color(COLOR_WHITE);
						if (j == 0)
						{
							board->get_tiles()[i][8].set_color(COLOR_DARK_GREY);
							board->get_tiles()[i][8].set_selected(true);
						}
						else
						{
							board->get_tiles()[i][j - 1].set_color(COLOR_DARK_GREY);
							board->get_tiles()[i][j - 1].set_selected(true);
						}
						tile_selected = true;
					}
					if (tile_selected) break;
				}
				if (tile_selected) break;
			}

			if (!tile_selected)
			{
				Sudoku_Board*& board = GameData::sudoku_board;
				board->get_tiles()[0][0].set_color(COLOR_DARK_GREY);
				board->get_tiles()[0][0].set_selected(true);
			}
			break;
		}
	}
}


void unselect_all_tiles(Tile*& exempted_tile)
{

	if (GameData::sudoku_board != NULL)
	{
		for (int k = 0; k < 9; k++)
		{
			for (int f = 0; f < 9; f++)
			{

				Tile& tile_unselect = GameData::sudoku_board->get_tiles()[k][f];
				if (tile_unselect != *exempted_tile)
				{
					tile_unselect.set_selected(false);
					tile_unselect.set_color(COLOR_WHITE);
				}
			}
		}
	}

}


Tile* mouse_over_tile()
{

	if (GameData::sudoku_board != NULL)
	{
		for (int i = 0; i < 9; i++)
		{
			for (int j = 0; j < 9; j++)
			{

				Tile& tile_ref = GameData::sudoku_board->get_tiles()[i][j];
				Tile* tile = &tile_ref;
				if (tile->mouse_over_tile(mouse_x, mouse_y))
				{
					return tile;
				}
			}
		}
	}
	return NULL;
}


Tile* tile_is_selected()
{

	Sudoku_Board* board = GameData::sudoku_board;

	if (board != NULL)
	{
		for (int i = 0; i < 9; i++)
		{
			for (int j = 0; j < 9; j++)
			{

				if (board->get_tiles()[i][j].is_selected())
				{
					return &board->get_tiles()[i][j];
				}
			}
		}
	}

	return NULL;
}