#include "Render.h"
#include "GameData.h"
#include "Background.h"
#include "Sudoku_Board.h"
#include "Complete_Button.h"
#include "Message_Handler.h"
#include "Message_Box.h"
#include <SDL.h>


void Render(SDL_Renderer*& renderer) 
{

	if (GameData::background != NULL)
	{
		GameData::background->render(renderer);
	}

	if (GameData::sudoku_board != NULL)
	{
		GameData::sudoku_board->render(renderer);
	}

	for (auto m : GameData::buttons) {
		m->render(renderer);
	}

	if (GameData::message_handler != NULL)
	{
		GameData::message_handler->render(renderer);
	}

	SDL_RenderPresent(renderer);
}