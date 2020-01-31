#ifndef MESSAGE_HANDLER
#define MESSAGE_HANDLER

#include "Game_Figure.h"
#include <vector>
#include <string>
#include <SDL_ttf.h>
#include <SDL.h>
#include <chrono>
class Message_Box;

enum {
	TXT_INCOMPLETE,
	TXT_BOARD_ERROR,
	TXT_COMPLETE,
	TXT_DIFFICULTY_SELECT,
	TXT_MAIN_MENU,
	TXT_OPTIONS,
	TXT_SAVE_SUCCESSFUL,
	TXT_SAVE_UNSUCCESSFUL
};


class Message_Handler : public Game_Figure
{
public:
	Message_Handler(int, int font_size = 72);
	void Load_Textures(SDL_Renderer*&);
	void Set_Text(int);
	void Set_Display(bool);
	void Destroy_Message_Box();
	Message_Box* get_message_box();
	void render(SDL_Renderer*&) override;
	void update() override;
	~Message_Handler();

private:
	std::vector<SDL_Texture*> messages;
	TTF_Font* Sans;
	SDL_Rect text_box;
	SDL_Color color;
	int text_message;
	bool display;
	bool images_loaded;
	Message_Box* Box;
	const int current_level;

};


#endif