#ifndef NEW_GAME_BUTTON
#define NEW_GAME_BUTTON

#include "Button.h"
#include <SDL.h>

class New_Game_Button : public Button
{
public:
	New_Game_Button();
	void action() override;
	void set_size(int, int) override;
	void Load_Image(SDL_Renderer*&) override;
	void render(SDL_Renderer*&) override;
	void update() override;
};

#endif