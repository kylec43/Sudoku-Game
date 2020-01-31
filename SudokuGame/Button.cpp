#include "Button.h"


Button::Button() : width(0), height(0), image_type(0), textures{ NULL, NULL }, button(), image_loaded(false), button_type(0), display(true)
{
	x = 0;
	y = 0;
}

void Button::set_display(bool flag)
{
	display = flag;
}

int Button::get_type()
{
	return button_type;
}

int Button::get_x()
{
	return x;
}

int Button::get_y()
{
	return y;
}

int Button::get_width()
{
	return width;
}

int Button::get_height()
{
	return height;
}

void  Button::set_position(int posx, int posy)
{
	x = posx;
	y = posy;
	button.x = x;
	button.y = y;
}

void Button::Set_Image(int image)
{
	if (image == FOCUSED_IMAGE)
	{
		image_type = FOCUSED_IMAGE;
	}
	else if (image == UNFOCUSED_IMAGE)
	{
		image_type = UNFOCUSED_IMAGE;
	}
}


bool Button::Mouse_Over_Button(int mouse_x, int mouse_y)
{
	if (mouse_x >= x && mouse_x <= x + width && mouse_y >= y && mouse_y <= y + height)
	{
		return true;
	}
	else
	{
		return false;
	}
}

int Button::get_value()
{
	return 0;
}


Button::~Button()
{
	for (auto m : textures)
	{
		SDL_DestroyTexture(m);
	}
}