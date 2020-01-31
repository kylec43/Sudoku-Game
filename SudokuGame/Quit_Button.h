#ifndef QUIT_BUTTON
#define QUIT_BUTTON

#include "Button.h"
#include <SDL.h>

class Quit_Button : public Button
{
public:
	Quit_Button();
	void action() override;
	void set_size(int, int) override;
	void Load_Image(SDL_Renderer*&) override;
	void render(SDL_Renderer*&) override;
	void update() override;
};

#endif