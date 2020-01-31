#ifndef COMPLETE_BUTTON
#define COMPLETE_BUTTON

#include "Button.h"
#include <SDL.h>

class Complete_Button : public Button 
{
public:
	Complete_Button();
	void action() override;
	void set_size(int, int) override;
	void Load_Image(SDL_Renderer*&) override;
	void render(SDL_Renderer*&) override;
	void update() override;
};

#endif