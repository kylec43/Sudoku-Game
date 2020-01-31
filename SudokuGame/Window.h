#ifndef WINDOW
#define WINDOW

#include <string>
#include <SDL.h>


class Window 
{
public:
	Window(const std::string&, const int, const int);
	SDL_Window*& get();
	~Window();


private:
	SDL_Window* window;
	int width;
	int height;
};

#endif