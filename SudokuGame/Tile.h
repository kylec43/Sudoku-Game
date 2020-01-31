#ifndef TILE
#define TILE

#include "Game_Figure.h"
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <string>


enum {
	COLOR_WHITE,
	COLOR_LIGHT_GREY,
	COLOR_DARK_GREY,
	COLOR_IDK
};

class Tile : public Game_Figure {
public:
	Tile(const int posx = 0, const int posy = 0, const int sizew = 0, const int sizeh = 0);
	void set_size(const int, const int);
	void set_width(const int);
	void set_height(const int);
	void set_x(const int);
	void set_y(const int);
	void set_position(const int, const int);
	Tile& operator=(const int);
	bool operator!=(const Tile&);
	bool operator==(const Tile&);
	void load_tile_images(SDL_Renderer*&);
	bool mouse_over_tile(const int, const int);
	void set_color(const int);
	void set_number(int);
	int get_number();
	bool is_selected();
	bool is_read_only();
	void set_selected(bool);
	void render(SDL_Renderer*&) override;
	void update() override;
	~Tile();

private:
	friend class Sudoku_Board;

	static unsigned tile_id;
	unsigned id;

	int current_number;
	SDL_Rect tile;
	int tile_color;
	bool selected;
	bool read_only;

	static SDL_Texture* render_number_texture[9];

	/*Checks if images are loaded*/
	static bool tile_images_loaded;

	SDL_Rect number_render_size;

};

#endif