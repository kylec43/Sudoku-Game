#include <SDL.h>
#include "Window_Events.h"
#include "Complete_Button.h"
#include "GameData.h"
#include "Window.h"
#include <iostream>
#include <atomic>

extern int window_width;
extern int window_height;
extern int window_x;
extern int window_y;
extern bool window_maximized;
extern std::atomic<bool> isRunning;

void Window_Events(SDL_Event& e, Window& window)
{

	switch(e.type)
	{
		case SDL_QUIT:
			isRunning = false;
			break;

		case SDL_WINDOWEVENT:
			switch (e.window.event)
			{

				case SDL_WINDOWEVENT_RESIZED:
					SDL_GetWindowSize(window.get(), &window_width, &window_height);
					break;

				case SDL_WINDOWEVENT_MOVED:
				SDL_GetWindowPosition(window.get(), &window_x, &window_y);
				break;
			}
			break;
	}
}