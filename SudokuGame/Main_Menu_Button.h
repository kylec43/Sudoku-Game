#ifndef MAIN_MENU_BUTTON
#define MAIN_MENU_BUTTON

#include "Button.h"
#include <SDL.h>

class Main_Menu_Button : public Button
{
public:
	Main_Menu_Button(int);
	void action() override;
	void set_size(int, int) override;
	void Load_Image(SDL_Renderer*&) override;
	void render(SDL_Renderer*&) override;
	void update() override;
};

#endif