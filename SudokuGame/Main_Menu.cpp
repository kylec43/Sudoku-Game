#include <SDL.h>
#include "Main_Menu.h"
#include "Background.h"
#include "Main_Menu_Button.h"
#include "Message_Handler.h"
#include "GameData.h"
#include "Level_ID.h"
extern int window_width;
extern int window_height;

void MainMenu(SDL_Renderer*& renderer)
{
	GameData::background = (new Background(renderer, "images/backgrounds/mountains.bmp"));
	GameData::message_handler = new Message_Handler(LEVEL_MAIN_MENU, 100);
	GameData::buttons.push_back(new Main_Menu_Button(BUTTON_CONTINUE));
	GameData::buttons.push_back(new Main_Menu_Button(BUTTON_START));
	GameData::buttons.push_back(new Main_Menu_Button(BUTTON_EXIT));

}