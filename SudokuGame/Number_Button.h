#ifndef NUMBER_BUTTON
#define NUMBER_BUTTON

#include "Button.h"
#include <SDL.h>

class Number_Button : public Button
{
public:
	Number_Button(int n = 0);
	void action() override;
	void set_size(int, int) override;
	int get_value() override;
	void Load_Image(SDL_Renderer*&) override;
	void render(SDL_Renderer*&) override;
	void update() override;

private:
	int number;
};

#endif