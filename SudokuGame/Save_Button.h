#ifndef SAVE_BUTTON
#define SAVE_BUTTON

#include "Button.h"
#include <SDL.h>resu

class Save_Button : public Button
{
public:
	Save_Button();
	bool save();
	bool board_is_saved();
	void action() override;
	int get_value() override;
	void set_size(int, int) override;
	void Load_Image(SDL_Renderer*&) override;
	void render(SDL_Renderer*&) override;
	void update() override;
private:
	bool board_saved;
};

#endif