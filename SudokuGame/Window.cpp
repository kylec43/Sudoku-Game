#include "Window.h"
#include <iostream>
#include <string>
#include <SDL.h>
extern int window_width;
extern int window_height;

Window::Window(const std::string& TITLE, const int WIDTH, const int HEIGHT) : window(NULL), width(WIDTH), height(HEIGHT)
{

	width = width * 0.6;

	int find_multiple_4 = 0;
	while (true)
	{
		find_multiple_4 += 4;

		if (find_multiple_4 >= width)
		{
			width = find_multiple_4;
			height = width * 0.75;
			break;
		}
	}

	window = SDL_CreateWindow(TITLE.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);

	window_width = width;
	window_height = height;

	if (window == NULL) {
		std::cerr << "Window Creation Error: " << SDL_GetError() << std::endl;
	}

}


SDL_Window*& Window::get() 
{
	return window;
}


Window::~Window()
{
	SDL_DestroyWindow(window);
	window = NULL;
}