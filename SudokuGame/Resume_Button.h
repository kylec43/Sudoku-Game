#ifndef RESUME_BUTTON
#define RESUME_BUTTON

#include "Button.h"
#include <SDL.h>

class Resume_Button : public Button
{
public:
	Resume_Button();
	void action() override;
	void set_size(int, int) override;
	void Load_Image(SDL_Renderer*&) override;
	void render(SDL_Renderer*&) override;
	void update() override;
};

#endif