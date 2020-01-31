#include "Sudoku_Board.h"
#include "Level_ID.h"
#include "GameData.h"
#include <SDL.h>
#include <iostream>
#include <atomic>
#include <mutex>

extern std::atomic<bool> generate_board;
extern int window_width;
extern int window_height;
extern int window_x;
extern int window_y;
extern int screen_resolution_width;
extern int screen_resolution_height;
extern int mouse_x;
extern int mouse_y;
extern std::mutex Lock_GameData_Puzzles;

Sudoku_Board::Sudoku_Board(int posx, int posy, int thickness) 
						  : board_frame({}),
							board_frame_thickness(thickness),
							drag_bar({}),
							divider_thickness(3),
							solution {},
							tiles{{}},
							tile_w(0),
							tile_h(0),
							drag_state(false),
							puzzle_loaded(false),
							board_images_loaded(false),
							board_frame_texture(NULL),
							drag_bar_texture(NULL)


{
	generate_board = true;

	/*Because of integer division, a multiple of 9 needs to be found for the precision of the tile positions*/
	int find_multiple_9 = 0;
	while (true)
	{
		find_multiple_9 += 9;
		if (find_multiple_9 >= board_frame_thickness)
		{
			board_frame_thickness = find_multiple_9;
			break;
		}
	}
	
	x = posx;
	y = posy;

	update_frame_size();
	update_sizes_and_positions();

}



void Sudoku_Board::update_frame_size()
{
	int w = window_width / 2;
	int h = window_width / 2;
	if (w > screen_resolution_height*0.70) 
	{
		w = screen_resolution_height * 0.70;
		h = screen_resolution_height * 0.70;
	}

	/*Because of integer division, a multiple of 9 needs to be found for the precision of the tile positions*/
	int find_multiple_9 = 0;
	bool found_w = false;
	bool found_h = false;
	while (true)
	{
		find_multiple_9 += 9;
		if (find_multiple_9 >= w && !found_w)
		{
			w = find_multiple_9;
			found_w = true;
		}

		if (find_multiple_9 >= h && !found_h)
		{
			h = find_multiple_9;
			found_h = true;
		}

		if (found_w && found_h)
		{
			break;
		}
	}

	/*If the Board is out of view, put it in a visible position*/
	if (x + window_x + w < window_x)
	{
		x = 0;
	}
	else if (x + window_x > window_x + window_width)
	{
		x = 0 + window_width - w;
	}

	if (y + window_y > window_y + window_height)
	{
		y = 0 + window_height - h;
	}
	else if (y + window_y - board_frame_thickness < window_y)
	{
		y = board_frame_thickness;
	}
	/*Set border outline Size and Position*/
	board_frame.w = w;
	board_frame.h = h;
	board_frame.x = x;
	board_frame.y = y;
}



/*Load Texture for drag_bar*/
void Sudoku_Board::load_board_images(SDL_Renderer*& renderer) 
{
	SDL_Surface* image = IMG_Load("images/textures/board_drag_bar_texture.jpg");
	if (image == NULL) 
	{
		std::cerr << "Error Loading Drag Bar Image: " << SDL_GetError() << std::endl;
	}

	drag_bar_texture = SDL_CreateTextureFromSurface(renderer, image);
	SDL_FreeSurface(image);
	
	image = IMG_Load("images/textures/board_frame_texture.jpg");
	if (image == NULL)
	{
		std::cerr << "Error Loading Board Frame Image: " << SDL_GetError() << std::endl;
	}
	board_frame_texture = SDL_CreateTextureFromSurface(renderer, image);
	SDL_FreeSurface(image);
}




void Sudoku_Board::update_sizes_and_positions() {
	/*Set Drag Bar size and position*/
	drag_bar.h = board_frame_thickness * 1.5;
	drag_bar.w = board_frame.w;
	drag_bar.x = board_frame.x;
	drag_bar.y = board_frame.y - drag_bar.h;


	/*Set Size and Position of board surface*/
	board_surface.h = board_frame.h - (board_frame_thickness * 2);
	board_surface.w = board_frame.w - (board_frame_thickness * 2);
	board_surface.x = board_frame.x + board_frame_thickness;
	board_surface.y = board_frame.y + board_frame_thickness;





	const float thicker_line_multiple = 2; //Determines how much thicker the dividers are.

	/*Set Size and position of vertical dividers*/
	int space_between_lines = board_surface.w / 9;
	for (int i = 0; i < 8; i++)
	{
		vertical_dividers[i].y = board_surface.y;
		vertical_dividers[i].h = board_surface.h;

		if ((i + 1) % 3 != 0)
		{
			vertical_dividers[i].w = divider_thickness;
			vertical_dividers[i].x = (board_surface.x + (space_between_lines * (i + 1))) - (divider_thickness / 2);
		}
		else
		{
			vertical_dividers[i].w = divider_thickness * thicker_line_multiple;
			vertical_dividers[i].x = (board_surface.x + (space_between_lines * (i + 1))) - ((divider_thickness * thicker_line_multiple) / 2);
		}
	}


	/*Set Size and position of horizontal dividers*/
	space_between_lines = board_surface.h / 9;
	for (int i = 0; i < 8; i++)
	{
		horizontal_dividers[i].x = board_surface.x;
		horizontal_dividers[i].w = board_surface.w;

		if ((i + 1) % 3 != 0)
		{
			horizontal_dividers[i].h = divider_thickness;
			horizontal_dividers[i].y = (board_surface.y + (space_between_lines * (i + 1))) - (divider_thickness / 2);
		}
		else
		{
			horizontal_dividers[i].h = divider_thickness * thicker_line_multiple;
			horizontal_dividers[i].y = (board_surface.y + (space_between_lines * (i + 1))) - ((divider_thickness * thicker_line_multiple) / 2);
		}
	}





	/*Set Size of Position in order to draw the horizontal outline of the surface*/
	surface_outline_horizontal.first.w = board_surface.w + (divider_thickness * thicker_line_multiple);
	surface_outline_horizontal.first.h = divider_thickness * thicker_line_multiple;
	surface_outline_horizontal.first.x = board_surface.x - (divider_thickness * thicker_line_multiple);
	surface_outline_horizontal.first.y = board_surface.y - (divider_thickness * thicker_line_multiple);

	surface_outline_horizontal.second.w = board_surface.w + (divider_thickness * thicker_line_multiple);
	surface_outline_horizontal.second.h = divider_thickness * thicker_line_multiple;
	surface_outline_horizontal.second.x = board_surface.x - (divider_thickness * thicker_line_multiple);
	surface_outline_horizontal.second.y = board_surface.y + board_surface.h - (divider_thickness * thicker_line_multiple);

	/*Set Size of Position in order to draw the vertical outline of the surface*/
	surface_outline_vertical.first.w = divider_thickness * thicker_line_multiple;
	surface_outline_vertical.first.h = board_surface.h;
	surface_outline_vertical.first.x = board_surface.x - (divider_thickness * thicker_line_multiple);
	surface_outline_vertical.first.y = board_surface.y;

	surface_outline_vertical.second.w = divider_thickness * thicker_line_multiple;
	surface_outline_vertical.second.h = board_surface.h;
	surface_outline_vertical.second.x = board_surface.x + board_surface.w - (divider_thickness * thicker_line_multiple);
	surface_outline_vertical.second.y = board_surface.y;



	/*Set Size and position of Tiles*/
	tile_w = board_surface.w / 9;
	tile_h = board_surface.h / 9;
	int space_between_tiles_w = board_surface.w/9;
	int space_between_tiles_h = board_surface.h/9;
	for (int i = 0; i < 9; i++)
	{
		for (int k = 0; k < 9; k++)
		{
			tiles[i][k].set_size(tile_w, tile_h);
			tiles[i][k].set_position(board_surface.x + (space_between_tiles_w * k), board_surface.y + (space_between_tiles_h * i));


		}
	}



	/*Set Size of Position in order to draw the horizontal outline of the board*/
	horizontal_lines_frame.first.x = board_frame.x;
	horizontal_lines_frame.first.y = board_frame.y;
	horizontal_lines_frame.first.w = board_frame.w;
	horizontal_lines_frame.first.h = board_frame_thickness;

	horizontal_lines_frame.second.x = board_frame.x;
	horizontal_lines_frame.second.y = board_frame.y + board_frame.h - board_frame_thickness;
	horizontal_lines_frame.second.w = board_frame.w;
	horizontal_lines_frame.second.h = board_frame_thickness;

	/*Set Size of Position in order to draw the vertical outline of the board*/
	vertical_lines_frame.first.x = board_frame.x;
	vertical_lines_frame.first.y = board_frame.y + board_frame_thickness;
	vertical_lines_frame.first.w = board_frame_thickness;
	vertical_lines_frame.first.h = board_frame.h - board_frame_thickness;

	vertical_lines_frame.second.x = board_frame.x + board_frame.w - board_frame_thickness;
	vertical_lines_frame.second.y = board_frame.y + board_frame_thickness;
	vertical_lines_frame.second.w = board_frame_thickness;
	vertical_lines_frame.second.h = board_frame.h - board_frame_thickness;
}



void Sudoku_Board::update_positions() 
{
	drag_bar.x = board_frame.x;
	drag_bar.y = board_frame.y - drag_bar.h;

	board_surface.x = board_frame.x + board_frame_thickness;
	board_surface.y = board_frame.y + board_frame_thickness;


	const float thicker_line_multiple = 2; //Determines how much thicker the dividers are.

	/*Set Size and position of vertical dividers*/
	int space_between_lines = board_surface.w/9;
	for (int i = 0; i < 8; i++)
	{
		vertical_dividers[i].y = board_surface.y;

		if ((i + 1) % 3 != 0)
		{
			vertical_dividers[i].x = (board_surface.x + (space_between_lines * (i + 1))) - (divider_thickness / 2);
		}
		else
		{
			vertical_dividers[i].x = (board_surface.x + (space_between_lines * (i + 1))) - ((divider_thickness * thicker_line_multiple) / 2);
		}
	}


	/*Set Size and position of horizontal dividers*/
	space_between_lines = board_surface.h/9;
	for (int i = 0; i < 8; i++)
	{
		horizontal_dividers[i].x = board_surface.x;

		if ((i + 1) % 3 != 0)
		{
			horizontal_dividers[i].y = (board_surface.y + (space_between_lines * (i + 1))) - (divider_thickness / 2);
		}
		else
		{
			horizontal_dividers[i].y = (board_surface.y + (space_between_lines * (i + 1))) - ((divider_thickness * thicker_line_multiple) / 2);
		}
	}





	/*Set Size of Position in order to draw the horizontal outline of the surface*/
	surface_outline_horizontal.first.x = board_surface.x - (divider_thickness * thicker_line_multiple);
	surface_outline_horizontal.first.y = board_surface.y - (divider_thickness * thicker_line_multiple);

	surface_outline_horizontal.second.x = board_surface.x - (divider_thickness * thicker_line_multiple);
	surface_outline_horizontal.second.y = board_surface.y + board_surface.h - (divider_thickness * thicker_line_multiple);

	/*Set Size of Position in order to draw the vertical outline of the surface*/
	surface_outline_vertical.first.x = board_surface.x - (divider_thickness * thicker_line_multiple);
	surface_outline_vertical.first.y = board_surface.y;

	surface_outline_vertical.second.x = board_surface.x + board_surface.w - (divider_thickness * thicker_line_multiple);
	surface_outline_vertical.second.y = board_surface.y;


	int space_between_tiles_w = board_surface.w / 9;
	int space_between_tiles_h = board_surface.h / 9;
	for (int i = 0; i < 9; i++)
	{
		for (int k = 0; k < 9; k++)
		{
			tiles[i][k].set_size(tile_w, tile_h);
			tiles[i][k].set_position(board_surface.x + (space_between_tiles_w * k), board_surface.y + (space_between_tiles_h * i));
		}
	}

	/*Set Size of Position in order to draw the horizontal outline of the board*/
	horizontal_lines_frame.first.x = board_frame.x;
	horizontal_lines_frame.first.y = board_frame.y;

	horizontal_lines_frame.second.x = board_frame.x;
	horizontal_lines_frame.second.y = board_frame.y + board_frame.h - board_frame_thickness;

	/*Set Size of Position in order to draw the vertical outline of the board*/
	vertical_lines_frame.first.x = board_frame.x;
	vertical_lines_frame.first.y = board_frame.y + board_frame_thickness;

	vertical_lines_frame.second.x = board_frame.x + board_frame.w - board_frame_thickness;
	vertical_lines_frame.second.y = board_frame.y + board_frame_thickness;
}




/*Checks if mouse position is over the drag bar*/
bool Sudoku_Board::mouse_over_drag_bar(const int posx, const int posy) 
{
	mouse_distance_x = posx - x;
	mouse_distance_y = posy - y;
	if (posx >= drag_bar.x && posx <= (drag_bar.x + drag_bar.w) && posy >= drag_bar.y && posy <= drag_bar.y + drag_bar.h) 
	{
		return true;
	}
	
	return false;
}


void Sudoku_Board::drag_board(bool flag) 
{
	drag_state = flag;
}



Tile(&Sudoku_Board::get_tiles())[9][9]
{
	return tiles;
}

int Sudoku_Board::get_difficulty() 
{
	return difficulty;
}

void Sudoku_Board::set_difficulty(int d) 
{
	difficulty = d;
}



void Sudoku_Board::Load_Puzzle()
{
	Lock_GameData_Puzzles.lock();
	for (int i = 0; i < 9; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			/*Loads the puzzle. If the current number is negative then the puzzle was loaded from a save file and determines that it is not read_only*/
			tiles[i][j] = GameData::puzzles.front()[i][j];
			if (tiles[i][j].current_number != 0 && tiles[i][j].current_number > 0)
			{
				tiles[i][j].read_only = true;
				tiles[i][j].selected = false;
			}

			if (tiles[i][j].current_number < 0)
			{
				tiles[i][j].current_number *= -1;
			}
		}
	}



	for (int i = 0; i < 9; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			solution[i][j] = GameData::puzzles.back()[i][j];
		}
	}
	GameData::puzzles.clear();
	Lock_GameData_Puzzles.unlock();

}


int Sudoku_Board::is_complete()
{
	bool invalid_answer = false;
	for (int i = 0; i < 9; i++) 
	{
		for (int j = 0; j < 9; j++)
		{
			if (tiles[i][j].current_number == 0) 
			{
				return BOARD_INCOMPLETE;
			}
			if (tiles[i][j].current_number != solution[i][j])
			{
				invalid_answer = true;
			}
		}
	}
	if (invalid_answer == true) 
	{
		return BOARD_ERROR;
	}
	else 
	{
		return BOARD_COMPLETE;
	}
}

Tile& Sudoku_Board::tile_index(int i, int j)
{
	return tiles[i][j];
}

int& Sudoku_Board::solution_index(int i, int j)
{
	return solution[i][j];
}



void Sudoku_Board::render(SDL_Renderer*& renderer) 
{	
	/*Load Images if they have not been loaded yet*/
	if (!board_images_loaded)
	{
		load_board_images(renderer);
		board_images_loaded = true;

	}

	/*Render Board frame*/
	SDL_SetRenderDrawColor(renderer, 0xD5, 0xC4, 0xA1, 0xFF);
	SDL_RenderCopy(renderer, board_frame_texture, NULL, &horizontal_lines_frame.first);
	SDL_RenderCopy(renderer, board_frame_texture, NULL, &horizontal_lines_frame.second);
	SDL_RenderCopy(renderer, board_frame_texture, NULL, &vertical_lines_frame.first);
	SDL_RenderCopy(renderer, board_frame_texture, NULL, &vertical_lines_frame.second);

	/*Render Tiles*/
	for (int i = 0; i < 9; i++) {
		for (Tile& t : tiles[i]) {
			t.render(renderer);
		}
	}



	/*Render Horizontal Dividers Black*/
	SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0xFF);
	for (int i = 0; i<8; i++) 
	{
		if ((i + 1) % 3 != 0) {
			SDL_RenderFillRect(renderer, &horizontal_dividers[i]);
		}
		else {
			SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0xFF);
			SDL_RenderFillRect(renderer, &horizontal_dividers[i]);
			SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0x3c);
		}
	}

	/*Render Vertical Dividers Black*/
	for (int i = 0; i < 8; i++)
	{
		if ((i + 1) % 3 != 0) {
			SDL_RenderFillRect(renderer, &vertical_dividers[i]);
		}
		else {
			SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0xFF);
			SDL_RenderFillRect(renderer, &vertical_dividers[i]);
			SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0xFF);
		}
	}

	/*Render Surface Outline*/
	SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0xFF);
	SDL_RenderFillRect(renderer, &surface_outline_horizontal.first);
	SDL_RenderFillRect(renderer, &surface_outline_horizontal.second);
	SDL_RenderFillRect(renderer, &surface_outline_vertical.first);
	SDL_RenderFillRect(renderer, &surface_outline_vertical.second);

	/*Render Drag Bar*/
	SDL_RenderCopy(renderer, drag_bar_texture, NULL, &drag_bar);

}


void Sudoku_Board::update() 
{
	if (drag_state == true) 
	{
		x = mouse_x - mouse_distance_x;
		y = mouse_y - mouse_distance_y;
		board_frame.x = x;
		board_frame.y = y;
		update_positions();
	}
	else
	{
		update_frame_size();
		update_sizes_and_positions();

	}


	if (!puzzle_loaded)
	{
		Lock_GameData_Puzzles.lock();
		int size = GameData::puzzles.size();
		Lock_GameData_Puzzles.unlock();

		if (size != 0)
		{
			Load_Puzzle();
			puzzle_loaded = true;

		}
	}
}



Sudoku_Board::~Sudoku_Board() {

	for (SDL_Texture*& texture : Tile::render_number_texture)
	{
		SDL_DestroyTexture(texture);
		texture = NULL;
	}
		Tile::tile_images_loaded = false;

		SDL_DestroyTexture(drag_bar_texture);
		drag_bar_texture = NULL;

		SDL_DestroyTexture(board_frame_texture);
		board_frame_texture = NULL;
}
