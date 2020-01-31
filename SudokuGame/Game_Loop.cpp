#include "Game_Loop.h"
#include "GameData.h"
#include "Level_ID.h"
#include "Level_Handler.h"
#include "Process_Input_Events.h"
#include "Update.h"
#include "Render.h"
#include "Window.h"
#include "Window_Events.h"
#include <SDL.h>
#include <atomic>
#include <iostream>


extern int window_width;
extern int window_height;
extern std::atomic<bool> isRunning;


void Game_Loop()
{
	const unsigned FPS = 60;
	const unsigned FrameDelay = 1000 / FPS;
	long int TimeStart = 0, TimeFinish = 0;
	SDL_Event e;
	Window window("Sudoku", window_width, window_height);
	SDL_Renderer* renderer = SDL_CreateRenderer(window.get(), -1, SDL_RENDERER_ACCELERATED);

	/*Game Start*/
	while (isRunning)
	{


		while (SDL_PollEvent(&e) != 0)
		{

			TimeStart = SDL_GetTicks();

			Window_Events(e, window);
			Process_Input_Events(e);
			Level_Handler(renderer);
			Update();
			Render(renderer);

			TimeFinish = SDL_GetTicks() - TimeStart;
			if (FrameDelay > TimeFinish)
			{
				SDL_Delay(FrameDelay - TimeFinish);
			}

		}
	}

	SDL_DestroyRenderer(renderer);
	GameData::Destroy();
}