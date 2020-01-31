#include "Mouse_Dragging_Events.h"
#include "GameData.h"
#include "Sudoku_Board.h"
#include "Tile.h"
#include "Complete_Button.h"
#include "Message_Box.h"
#include "Message_Handler.h"
#include "Event_Helper_Functions.h"
#include <SDL.h>
#include <iostream>

extern int mouse_x;
extern int mouse_y;

void Mouse_Dragging_Events(SDL_Event& e) {

	SDL_GetMouseState(&mouse_x, &mouse_y);

	if (!message_box_open())
	{

		/*For Sudoku Board Tiles*/
		Sudoku_Board* board = GameData::sudoku_board;
		if (board != NULL)
		{
			for (int i = 0; i < 9; i++)
			{
				for (Tile& tile : board->get_tiles()[i])
				{
					if (tile.mouse_over_tile(mouse_x, mouse_y))
					{
						tile.set_color(COLOR_LIGHT_GREY);
					}
					else
					{
						tile.set_color(COLOR_WHITE);
					}

				}
			}
		}
		/*For Buttons*/
		for (auto button : GameData::buttons)
		{
			if (button->Mouse_Over_Button(mouse_x, mouse_y))
			{
				button->Set_Image(FOCUSED_IMAGE);
			}
			else
			{
				button->Set_Image(UNFOCUSED_IMAGE);
			}
		}


	}

	/*For Messenge Box Buttons */
	Message_Box* message_box = NULL;
	Message_Handler* message_handler = GameData::message_handler;
	if (message_handler != NULL)
	{
		message_box = message_handler->get_message_box();
	}
	if (message_box != NULL)
	{

		switch (message_box->get_type())
		{

		case MESSAGE_BOX_OK:
			if (message_box->Mouse_Over_Button(BUTTON_OK))
			{
				message_box->Set_Button_Image(BUTTON_OK, FOCUSED_IMAGE);
			}
			else
			{
				message_box->Set_Button_Image(BUTTON_OK, UNFOCUSED_IMAGE);
			}
			break;

		case MESSAGE_BOX_OPTIONS:
			if (message_box->Mouse_Over_Button(BUTTON_NEW_GAME))
			{
				message_box->Set_Button_Image(BUTTON_NEW_GAME, FOCUSED_IMAGE);
			}
			else
			{
				message_box->Set_Button_Image(BUTTON_NEW_GAME, UNFOCUSED_IMAGE);
			}

			if (message_box->Mouse_Over_Button(BUTTON_RESUME))
			{
				message_box->Set_Button_Image(BUTTON_RESUME, FOCUSED_IMAGE);
			}
			else
			{
				message_box->Set_Button_Image(BUTTON_RESUME, UNFOCUSED_IMAGE);
			}

			if (message_box->Mouse_Over_Button(BUTTON_QUIT))
			{
				message_box->Set_Button_Image(BUTTON_QUIT, FOCUSED_IMAGE);
			}
			else
			{
				message_box->Set_Button_Image(BUTTON_QUIT, UNFOCUSED_IMAGE);
			}

			if (message_box->Mouse_Over_Button(BUTTON_SAVE))
			{
				message_box->Set_Button_Image(BUTTON_SAVE, FOCUSED_IMAGE);
			}
			else
			{
				message_box->Set_Button_Image(BUTTON_SAVE, UNFOCUSED_IMAGE);
			}
			break;

		}
	}
}