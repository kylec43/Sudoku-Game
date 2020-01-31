#ifndef OPTIONS_BUTTON
#define OPTIONS_BUTTON

#include "Button.h"
#include <SDL.h>

class Options_Button : public Button
{
public:
	Options_Button();
	void action() override;
	void set_size(int, int) override;
	void Load_Image(SDL_Renderer*&) override;
	void render(SDL_Renderer*&) override;
	void update() override;
};

#endif