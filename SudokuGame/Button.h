#ifndef BUTTON
#define BUTTON

#include "Game_Figure.h"

enum {
	UNFOCUSED_IMAGE,
	FOCUSED_IMAGE,
	BUTTON_COMPLETE,
	BUTTON_DIFFICULTY,
	BUTTON_OK,
	BUTTON_MAIN_MENU,
	BUTTON_EXIT,
	BUTTON_OPTIONS,
	BUTTON_NEW_GAME,
	BUTTON_RESUME,
	BUTTON_QUIT,
	BUTTON_SAVE,
	BUTTON_START,
	BUTTON_CONTINUE,
	BUTTON_NUMBER
};

/*Note: All buttons have static positions*/
class Button : public Game_Figure {

public:

	Button();
	int get_x();
	int get_y();
	int get_width();
	int get_height();
	int get_type();
	void Set_Image(int);
	bool Mouse_Over_Button(int mouse_x, int mouse_y);
	void set_display(bool);
	virtual void action() = 0;
	void set_position(int, int);
	virtual int get_value(); /*gets a value from button if needed, mainly for Number_Button and Save_Button*/
	virtual void set_size(int, int) = 0;
	virtual void Load_Image(SDL_Renderer*&) = 0;
	virtual void render(SDL_Renderer*&) = 0;
	virtual void update() = 0;
	~Button();

protected:
	int width;
	int height;
	int image_type;
	SDL_Texture* textures[2];
	SDL_Rect button;
	bool image_loaded;
	int button_type;
	bool display;
};

#endif