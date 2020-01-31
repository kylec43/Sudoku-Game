#include "Process_Input_Events.h"
#include "Key_Down_Events.h"
#include "Mouse_Down_Events.h"
#include "Mouse_Up_Events.h"
#include "Mouse_Dragging_Events.h"
#include <SDL.h>

enum 
{
	MOUSE_DOWN = true,
	MOUSE_UP = false
};


void Process_Input_Events(SDL_Event& e) 
{
	switch (e.type)
	{
		case SDL_KEYDOWN:
			Key_Down_Events(e);
			break;

		case SDL_MOUSEBUTTONDOWN:
			Mouse_Down_Events(e);
			break;

		case SDL_MOUSEBUTTONUP:
			Mouse_Up_Events(e);
			break;

		case SDL_MOUSEMOTION:
			Mouse_Dragging_Events(e);
			break;
	}
}