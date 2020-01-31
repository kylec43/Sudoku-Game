#include <SDL.h>
#include "Difficulty_Select.h"
#include "Background.h"
#include "Difficulty_Button.h"
#include "Message_Handler.h"
#include "Level_ID.h"
#include "GameData.h"
extern int window_width;
extern int window_height;

void Difficulty_Select(SDL_Renderer*& renderer)
{
	GameData::background = (new Background(renderer, "images/backgrounds/mountains.bmp"));
	GameData::message_handler = (new Message_Handler(LEVEL_DIFFICULTY_SELECT, 100));
	GameData::buttons.push_back(new Difficulty_Button(EASY));
	GameData::buttons.push_back(new Difficulty_Button(MEDIUM));
	GameData::buttons.push_back(new Difficulty_Button(HARD));

}