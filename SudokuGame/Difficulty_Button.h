#ifndef DIFFICULTY_BUTTON
#define DIFFICULTY_BUTTON

#include "Button.h"
#include <SDL.h>

enum 
{
	EASY,
	MEDIUM,
	HARD
};

class Difficulty_Button : public Button
{
public:
	Difficulty_Button(int);
	int get_difficulty_type();
	void action() override;
	void set_size(int, int) override;
	void Load_Image(SDL_Renderer*&) override;
	void render(SDL_Renderer*&) override;
	void update() override;

private:
	int difficulty_type;
};

#endif