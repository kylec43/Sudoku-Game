#include "Game_Figure.h"
#include "Tile.h"
#include "Level_ID.h"
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <iostream>
#include <string>

unsigned Tile::tile_id = 0;
bool Tile::tile_images_loaded = false;
SDL_Texture* Tile::render_number_texture[9];


Tile::Tile(const int posx, const int posy, const int sizew, const int sizeh)
			:
			current_number(0),
			tile({}),
			tile_color(),
			selected(false),
			read_only(false),
			number_render_size({})
{
	tile_id++;
	id = tile_id;
	x = posx;
	y = posy;
	tile = { posx, posy, sizew, sizeh };



}


/*Set tile size*/
void Tile::set_size(const int width, const int height) 
{
	tile.w = width;
	tile.h = height;
	number_render_size.w = width/2;
	number_render_size.h = height/2;
}


void Tile::set_height(const int height)
{
	tile.h = height;
	number_render_size.h = height / 2;
}



void Tile::set_width(const int width)
{
	tile.w = width;
	number_render_size.w = width / 2;

}

void Tile::set_x(const int posx)
{
	x = posx;
	tile.x = x;
	number_render_size.x = tile.x - (number_render_size.w / 2) + tile.w / 2;
}



void Tile::set_y(const int posy)
{
	y = posy;
	tile.y = y;
	number_render_size.y = tile.y - (number_render_size.w / 2) + tile.h / 2;
}


/*Set tile position*/
void Tile::set_position(const int posx, const int posy)
{
	x = posx;
	y = posy;
	tile.x = x;
	tile.y = y;

	number_render_size.x = tile.x - (number_render_size.w / 2) + tile.w / 2;
	number_render_size.y = tile.y - (number_render_size.w / 2) + tile.h / 2;
}


/*Set Current Number*/
Tile& Tile::operator=(const int n) 
{
	current_number = n;
	return *this;
}


/*Checks if ID's are not equal*/
bool Tile::operator!=(const Tile& other_tile) 
{
	return (id != other_tile.id) ? true : false;
}


/*Checks if ID's are equal*/
bool Tile::operator==(const Tile& other_tile)
{
	return (id == other_tile.id) ? true : false;
}

int Tile::get_number()
{
	return current_number;
}

bool Tile::is_read_only()
{
	return read_only;
}




/*Load Tile Images*/
void Tile::load_tile_images(SDL_Renderer*& renderer) {
	SDL_Surface* images[9];
	std::string numbers_path("images/sprites/numbers/");
	for (int i = 0; i < 9; i++)
	{
		images[i] = IMG_Load((numbers_path + std::to_string(i + 1) + ".png").c_str());
		if (images[i] == NULL)
		{
			std::cerr << "Failled loading image for Tiles: " << SDL_GetError() << std::endl;
		}
	}

	for (int i = 0; i < 9; i++)
	{
		render_number_texture[i] = SDL_CreateTextureFromSurface(renderer, images[i]);
		SDL_FreeSurface(images[i]);
	}

	tile_images_loaded = true;
}



bool Tile::mouse_over_tile(const int mouse_x, const int mouse_y)
{
	if (mouse_x > x + 2 && mouse_x < x - 2 + tile.w && mouse_y > y + 2 && mouse_y < y - 2  + tile.h) {
		return true;
	}

	return false;
}


void Tile::set_color(const int color)
{
	if (selected == false)
	{
		tile_color = color;
	}
}


bool Tile::is_selected() 
{
	if (selected == true) 
	{
		return true;
	}
	else 
	{
		return false;
	}
}


void Tile::set_selected(bool flag) 
{
	selected = flag;
}



void Tile::set_number(int n) 
{
	if (read_only == false)
	{
		current_number = n;
	}
}




void Tile::render(SDL_Renderer*& renderer) 
{
	/*Load Images if they have not been loaded yet*/
	if (!tile_images_loaded)
	{
		load_tile_images(renderer);
	}

	/*Render tile background*/
	if (read_only == true && selected == false)
	{
		SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xe6, 0xFF);
		SDL_RenderFillRect(renderer, &tile);
	}
	else if (read_only == true && selected == true)
	{
		SDL_SetRenderDrawColor(renderer, 0xFF, 0xc8, 0x00, 0xFF);
		SDL_RenderFillRect(renderer, &tile);
	}
	else if (tile_color == COLOR_WHITE) 
	{
		SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
		SDL_RenderFillRect(renderer, &tile);
	}
	else if(tile_color == COLOR_LIGHT_GREY)
	{
		SDL_SetRenderDrawColor(renderer, 0xC0, 0xC0, 0xC0, 0xFF);
		SDL_RenderFillRect(renderer, &tile);
	}
	else if (tile_color == COLOR_DARK_GREY) 
	{
		SDL_SetRenderDrawColor(renderer, 0x86, 0x88, 0x8A, 0xFF);
		SDL_RenderFillRect(renderer, &tile);
	}


	/*Render Number*/
	if (current_number != 0) 
	{
		SDL_RenderCopy(renderer, render_number_texture[current_number - 1], NULL, &number_render_size);
	}
}


void Tile::update() 
{

}


Tile::~Tile()
{

}