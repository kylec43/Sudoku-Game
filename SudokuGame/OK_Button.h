#ifndef OK_BUTTON
#define OK_BUTTON

#include "Button.h"
#include <SDL.h>

class OK_Button : public Button
{
public:
	OK_Button();
	void action() override;
	void set_size(int, int) override;
	void Load_Image(SDL_Renderer*&) override;
	void render(SDL_Renderer*&) override;
	void update() override;
};

#endif