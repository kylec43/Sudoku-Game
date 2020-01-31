#ifndef SUDOKU_BOARD
#define SUDOKU_BOARD

#include "Game_Figure.h"
#include "Tile.h"
#include <SDL.h>
#include<utility>
class Window;

enum 
{
	BOARD_INCOMPLETE,
	BOARD_ERROR,
	BOARD_COMPLETE
};


class Sudoku_Board : public Game_Figure {
public:
	Sudoku_Board(int posx = 0, int posy = 0, int thickness = 18);
	void load_board_images(SDL_Renderer*&);
	void update_frame_size();
	void update_sizes_and_positions();
	void update_positions();
	bool mouse_over_drag_bar(const int, const int);
	void drag_board(bool);
	Tile(&get_tiles())[9][9];
	int get_difficulty();
	void set_difficulty(int);
	int is_complete();
	Tile& tile_index(int, int);
	int& solution_index(int, int);
	void Load_Puzzle();
	void render(SDL_Renderer*&) override;
	void update() override;
	~Sudoku_Board();

private:
	int difficulty;

	SDL_Rect board_frame;
	std::pair<SDL_Rect, SDL_Rect> vertical_lines_frame;
	std::pair<SDL_Rect, SDL_Rect> horizontal_lines_frame;
	int board_frame_thickness;
	SDL_Texture* board_frame_texture;


	SDL_Rect board_surface;
	std::pair<SDL_Rect, SDL_Rect> surface_outline_horizontal;
	std::pair<SDL_Rect, SDL_Rect> surface_outline_vertical;

	SDL_Rect horizontal_dividers[8];
	SDL_Rect vertical_dividers[8];
	const int divider_thickness;

	SDL_Rect drag_bar;
	SDL_Texture* drag_bar_texture;
	bool board_images_loaded;

	std::pair<SDL_Rect, SDL_Rect> vertical_lines;
	std::pair<SDL_Rect, SDL_Rect> horizontal_lines;

	int solution[9][9];
	Tile tiles[9][9];
	float tile_w;
	float tile_h;

	/*Determines weather board will move with the mouse*/
	bool drag_state;
	int mouse_distance_x;
	int mouse_distance_y;

	bool puzzle_loaded;
};

#endif