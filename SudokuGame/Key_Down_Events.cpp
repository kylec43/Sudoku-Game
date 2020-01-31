#include "Key_Down_Events.h"
#include "Event_Helper_Functions.h"
#include <SDL.h>

void Key_Down_Events(SDL_Event& e) {


	switch (e.key.keysym.sym)
	{
	
		case SDLK_0:
			set_tile_number(0);
			break;

		case SDLK_1:
			set_tile_number(1);
			break;

		case SDLK_2:
			set_tile_number(2);
			break;

		case SDLK_3:
			set_tile_number(3);
			break;

		case SDLK_4:
			set_tile_number(4);
			break;

		case SDLK_5:
			set_tile_number(5);
			break;

		case SDLK_6:
			set_tile_number(6);
			break;

		case SDLK_7:
			set_tile_number(7);
			break;

		case SDLK_8:
			set_tile_number(8);
			break;

		case SDLK_9:
			set_tile_number(9);
			break;

		case SDLK_u:
			unselect_tile();
			break;

		case SDLK_SPACE:
			increment_tile();
			break;

		case SDLK_UP:
			change_selected_tile(SDLK_UP);
			break;

		case SDLK_DOWN:
			change_selected_tile(SDLK_DOWN);
			break;

		case SDLK_RIGHT:
			change_selected_tile(SDLK_RIGHT);
			break;

		case SDLK_LEFT:
			change_selected_tile(SDLK_LEFT);
			break;

	}
}