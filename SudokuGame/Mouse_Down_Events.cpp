#include "Mouse_Down_Events.h"
#include "GameData.h"
#include "Sudoku_Board.h"
#include "Complete_Button.h"
#include "Difficulty_Button.h"
#include "Message_Box.h"
#include "OK_Button.h"
#include "Message_Handler.h"
#include "Event_Helper_Functions.h"
#include "Level_ID.h"
#include <SDL.h>
#include <iostream>
#include <atomic>

extern int mouse_x;
extern int mouse_y;
extern bool save_exists;
extern std::atomic<int> level;
extern std::atomic<bool> isRunning;

void Mouse_Down_Events(SDL_Event& e) {

	if (!message_box_open())
	{

		/*For all Board Events*/
		Sudoku_Board* board = GameData::sudoku_board;
		Tile* tile = NULL;

		if (board != NULL)
		{

			/*If mouse is over the drag bar allow the board to move with the mouse************************/
			if (board->mouse_over_drag_bar(mouse_x, mouse_y))
			{
				board->drag_board(true);
			}

			/*If mouse is down over a board tile, if tile is NULL, the mouse is not over a tile*/
			else if ((tile = mouse_over_tile()) != NULL)
			{
				unselect_all_tiles(tile);

				/*If tile is already selected unselect it*/
				if (tile->is_selected())
				{
					tile->set_selected(false);
					tile->set_color(COLOR_LIGHT_GREY);
				}
				else
				{
					tile->set_color(COLOR_DARK_GREY);
					tile->set_selected(true);
				}
			}

		}


		/*For button events*/
		for (auto button : GameData::buttons)
		{

			Message_Handler* message_handler = GameData::message_handler;

			if (message_handler != NULL)
			{
				Tile* tile = NULL;
				if (button->Mouse_Over_Button(mouse_x, mouse_y))
				{
					switch (button->get_type())
					{

					case BUTTON_COMPLETE:

						/*Check if the board is complete and Display a message box depending on if it is complete or not*/
						if (button->Mouse_Over_Button(mouse_x, mouse_y))
						{

							int completion = board->is_complete();
							if (completion == BOARD_COMPLETE)
							{
								message_handler->Set_Text(TXT_COMPLETE);
								message_handler->Set_Display(true);
							}
							else if (completion == BOARD_INCOMPLETE)
							{
								message_handler->Set_Text(TXT_INCOMPLETE);
								message_handler->Set_Display(true);

							}
							else if (completion == BOARD_ERROR)
							{
								message_handler->Set_Text(TXT_BOARD_ERROR);
								message_handler->Set_Display(true);
							}
						}
						break;

					case BUTTON_DIFFICULTY:
						/*Play the game with the selected difficulty level from button->action*/
						if (button->Mouse_Over_Button(mouse_x, mouse_y))
						{
							for (auto hide_button = GameData::buttons.begin(); hide_button != GameData::buttons.end(); hide_button++)
							{
								(*hide_button)->set_display(false);
							}
							button->action();
						}
						break;

					case BUTTON_START:

						/*Go to LEVEL_DIFFICULTY from button->action*/
						if (button->Mouse_Over_Button(mouse_x, mouse_y))
						{
							for (auto hide_button = GameData::buttons.begin(); hide_button != GameData::buttons.end(); hide_button++)
							{
								(*hide_button)->set_display(false);
							}
							button->action();
						}
						break;


					case BUTTON_EXIT:
						if (button->Mouse_Over_Button(mouse_x, mouse_y))
						{
							isRunning = false;
						}
						break;


					case BUTTON_CONTINUE:
						/*If a save file exists, load the save by using button->action*/
						if (save_exists == true)
						{
							if (button->Mouse_Over_Button(mouse_x, mouse_y))
							{
								for (auto hide_button = GameData::buttons.begin(); hide_button != GameData::buttons.end(); hide_button++)
								{
									(*hide_button)->set_display(false);
								}
								button->action();
							}
						}
						break;

					case BUTTON_OPTIONS:

						/*Open Options Message Box*/
						if (button->Mouse_Over_Button(mouse_x, mouse_y))
						{
							message_handler->Set_Text(TXT_OPTIONS);
							message_handler->Set_Display(true);
						}
						break;


					case BUTTON_NUMBER:

						/*If Mouse is over a number_button set the selected tile to that number*/
						if (button->Mouse_Over_Button(mouse_x, mouse_y))
						{
							if ((tile = tile_is_selected()) != NULL)
								tile->set_number(button->get_value());
						}
						break;
					}
				}
			}
		}
	}

	/*For Message Box Buttons*/
	Message_Handler* message_handler = GameData::message_handler;
	Message_Box* m = NULL;
	if (message_handler != NULL)
	{
		m = message_handler->get_message_box();
	}

		/*If a message box exists*/
	if (m != NULL)
	{
		/*Do button->action if mouse is pressed over the button*/
		if (m->Mouse_Over_Button(BUTTON_OK))
		{
			message_handler->Destroy_Message_Box();
		}
		else if (m->Mouse_Over_Button(BUTTON_NEW_GAME))
		{
			m->get_button(BUTTON_NEW_GAME)->action();
		}
		else if (m->Mouse_Over_Button(BUTTON_RESUME))
		{
			message_handler->Destroy_Message_Box();
		}
		else if (m->Mouse_Over_Button(BUTTON_QUIT))
		{
			m->get_button(BUTTON_QUIT)->action();
		}
		else if (m->Mouse_Over_Button(BUTTON_SAVE))
		{
			m->get_button(BUTTON_SAVE)->action();
			if (m->get_button(BUTTON_SAVE)->get_value() == true)
			{
				message_handler->Destroy_Message_Box();
				message_handler->Set_Text(TXT_SAVE_SUCCESSFUL);
				message_handler->Set_Display(true);
			}
			else
			{
				message_handler->Destroy_Message_Box();
				message_handler->Set_Text(TXT_SAVE_UNSUCCESSFUL);
				message_handler->Set_Display(true);
			}
		}
	}

}