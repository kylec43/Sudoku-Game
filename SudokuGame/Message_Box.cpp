#include "Message_Box.h"
#include "OK_Button.h"
#include "Button.h"
#include "Quit_Button.h"
#include "New_Game_Button.h"
#include "Resume_Button.h"
#include "Save_Button.h"
#include <SDL.h>
#include <utility>
#include <iostream>
#include <SDL_image.h>

extern int mouse_x;
extern int mouse_y;
extern int window_width;
extern int window_height;

bool is_over_button(Button*);

Message_Box::Message_Box(int type): Box(), Frame_Top(), Frame_Sides(), Frame_Bottom(), 
									image_loaded(false), frame_texture(NULL),
									ok_button(NULL), new_game_button(NULL), resume_button(NULL), 
									save_button(NULL), box_type(NULL)
{


	if (type == MESSAGE_BOX_OK)
	{
		ok_button = new OK_Button();
		box_type = MESSAGE_BOX_OK;
	}
	else if (type == MESSAGE_BOX_OPTIONS)
	{
		new_game_button = new New_Game_Button();
		resume_button = new Resume_Button();
		quit_button = new Quit_Button();
		save_button = new Save_Button();
		box_type = MESSAGE_BOX_OPTIONS;
	}

}


Button* Message_Box::get_button(int type)
{
	if (type == BUTTON_OK)
	{
		return ok_button;
	}
	else if (type == BUTTON_NEW_GAME)
	{
		return new_game_button;
	}
	else if (type == BUTTON_RESUME)
	{
		return resume_button;
	}
	else if (type == BUTTON_QUIT)
	{
		return quit_button;
	}
	else if (type == BUTTON_SAVE)
	{
		return save_button;
	}
	else
	{
		return NULL;
	}
}



bool Message_Box::Mouse_Over_Button(int type)
{

		switch (type) 
		{
			case BUTTON_OK:
				return mouse_is_over_button(ok_button);
				break;

			case BUTTON_NEW_GAME:
				return mouse_is_over_button(new_game_button);
				break;

			case BUTTON_RESUME:
				return mouse_is_over_button(resume_button);
				break;

			case BUTTON_QUIT:
				return mouse_is_over_button(quit_button);
				break;

			case BUTTON_SAVE:
				return mouse_is_over_button(save_button);
		}
		
		return false;
		
}


void Message_Box::Set_Button_Image(int b_type, int focus_type)
{

	switch (b_type)
	{
		case BUTTON_OK:
			ok_button->Set_Image(focus_type);
			break;

		case BUTTON_NEW_GAME:
			new_game_button->Set_Image(focus_type);
			break;

		case BUTTON_RESUME:
			resume_button->Set_Image(focus_type);

		case BUTTON_QUIT:
			quit_button->Set_Image(focus_type);

		case BUTTON_SAVE:
			save_button->Set_Image(focus_type);
	}
}




void Message_Box::load_image(SDL_Renderer*& renderer)
{
	SDL_Surface* image = IMG_Load("images/textures/message_box_frame.jpg");

	if (image == NULL)
	{
		std::cerr << "Error Loading Message Box Frame Image: " << SDL_GetError() << std::endl;
	}
	frame_texture = SDL_CreateTextureFromSurface(renderer, image);
	SDL_FreeSurface(image);
	image = NULL;

	image_loaded = true;
}


int Message_Box::get_x()
{
	return x;
}

int Message_Box::get_y()
{
	return y;
}

int Message_Box::get_w()
{
	return width;
}

int Message_Box::get_h()
{
	return height;
}


int Message_Box::get_type()
{
	return box_type;
}



void Message_Box::render(SDL_Renderer*& renderer)
{

	if (!image_loaded)
	{
		load_image(renderer);
	}

	/*Render Background*/
	SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x96, 0xFF);
	SDL_RenderFillRect(renderer, &Box);


	/*Render frame*/
	SDL_RenderCopy(renderer, frame_texture, NULL, &Frame_Top);
	SDL_RenderCopy(renderer, frame_texture, NULL, &Frame_Bottom);
	SDL_RenderCopy(renderer, frame_texture, NULL, &Frame_Sides.first);
	SDL_RenderCopy(renderer, frame_texture, NULL, &Frame_Sides.second);


	/*Render Buttons depending on the box_type*/
	switch(box_type)
	{

		case MESSAGE_BOX_OK:
			ok_button->render(renderer);
			break;

		case MESSAGE_BOX_OPTIONS:
			new_game_button->render(renderer);
			resume_button->render(renderer);
			quit_button->render(renderer);
			save_button->render(renderer);
			break;
	}

}


void Message_Box::update()
{

	switch (box_type)
	{

		case MESSAGE_BOX_OK:

			/*Update Box Size and Position*/
			width = window_width / 3;
			height = window_width / 6;
			if (width > 800)
			{
				width = 800;
				height = 400;
			}
			x = window_width / 2 - width / 2;
			y = window_height / 2 - height / 2;
			Box = { x,y,width, height };

			/*Update Button Sizes and Positions*/
			ok_button->set_size(width / 4, width / 6);
			ok_button->set_position(x + width / 2 - ok_button->get_width() / 2, y + height * 0.8 - ok_button->get_height() / 2);
			break;

		case MESSAGE_BOX_OPTIONS:

			/*Update Box Size and Position*/
			width = window_width / 2;
			height = window_width / 2;
			if (width > 800)
			{
				width = 800;
				height = 800;
			}
			x = window_width / 2 - width / 2;
			y = window_height / 2 - height / 2;
			Box = { x,y,width, height };

			/*Update Button Sizes and Positions*/
			resume_button->set_size(width * 0.45, width * 0.15);
			resume_button->set_position(x + width / 2 - resume_button->get_width() / 2, y + height * 0.25 - resume_button->get_height() / 2);

			save_button->set_size(width * 0.45, width * 0.15);
			save_button->set_position(x + width / 2 - save_button->get_width() / 2, y + height * 0.45 - save_button->get_height() / 2);

			new_game_button->set_size(width * 0.45, width * 0.15);
			new_game_button->set_position(x + width / 2 - new_game_button->get_width() / 2, y + height * 0.65 - new_game_button->get_height() / 2);

			quit_button->set_size(width * 0.45, width * 0.14);
			quit_button->set_position(x + width / 2 - quit_button->get_width() / 2, y + height * 0.85 - quit_button->get_height() / 2);
	}


	/*Set Size and Position of Frame Sides*/
	Frame_Sides.first.w = width / 50;
	Frame_Sides.first.h = height;
	Frame_Sides.first.x = x - Frame_Sides.first.w;
	Frame_Sides.first.y = y;

	Frame_Sides.second.w = width / 50;
	Frame_Sides.second.h = height;
	Frame_Sides.second.x = x + width;
	Frame_Sides.second.y = y;


	/*Set Size and Position of Frame*/
	Frame_Top.w = width + (Frame_Sides.first.w * 2);
	Frame_Top.h = height / 20;
	Frame_Top.x = x - Frame_Sides.first.w;
	Frame_Top.y = y - Frame_Top.h;

	/*Set Size and Position of Bottom Frame*/
	Frame_Bottom.w = Frame_Top.w;
	Frame_Bottom.h = Frame_Sides.first.w;
	Frame_Bottom.x = Frame_Top.x;
	Frame_Bottom.y = y + height;

}


Message_Box::~Message_Box()
{
	SDL_DestroyTexture(frame_texture);
	frame_texture = NULL;

	delete ok_button;
	ok_button = NULL;

	delete new_game_button;
	new_game_button = NULL;

	delete resume_button;
	resume_button = NULL;

	delete quit_button;
	quit_button = NULL;

	delete save_button;
	save_button = NULL;

}


bool Message_Box::mouse_is_over_button(Button* button)
{
	if (button != NULL)
	{
		if (mouse_x >= button->get_x() &&
			mouse_x <= button->get_x() + button->get_width() &&
			mouse_y >= button->get_y() &&
			mouse_y <= button->get_y() + button->get_height())
		{
			return true;
		}
	}
	else
	{
		return false;
	}

	return false;
}