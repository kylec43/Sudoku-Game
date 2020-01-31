#ifndef MESSAGE_BOX
#define MESSAGE_BOX

#include <utility>
#include "Game_Figure.h"
#include "Button.h"
#include <SDL.h>
class Message_Handler;
class OK_Button;
class New_Game_Button;
class Resume_Button;
class Quit_Button;
class Save_Button;


enum 
{
	MESSAGE_BOX_OK,
	MESSAGE_BOX_OPTIONS
};


class Message_Box: public Game_Figure
{
public:
	Message_Box(int);
	void load_image(SDL_Renderer*&);
	bool Mouse_Over_Button(int);
	bool mouse_is_over_button(Button*);
	void Set_Button_Image(int, int);
	int get_x();
	int get_y();
	int get_w();
	int get_h();
	int get_type();
	Button* get_button(int);

	void render(SDL_Renderer*&) override;
	void update() override;
	~Message_Box();

private:
	friend class Message_Handler;
	int width;
	int height;
	SDL_Rect Box;
	SDL_Rect Frame_Top;
	std::pair<SDL_Rect, SDL_Rect> Frame_Sides;
	SDL_Rect Frame_Bottom;
	SDL_Texture* frame_texture;

	int box_type;
	OK_Button* ok_button;
	New_Game_Button* new_game_button;
	Resume_Button* resume_button;
	Quit_Button* quit_button;
	Save_Button* save_button;

	bool image_loaded;
};

#endif