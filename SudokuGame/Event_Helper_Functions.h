#ifndef EVENT_HELPER_FUNCTIONS
#define EVENT_HELPER_FUNCTIONS

class Tile;

void set_tile_number(int);
void unselect_tile();
void unselect_all_tiles(Tile*&);
Tile* tile_is_selected();
Tile* mouse_over_tile();
bool message_box_open();
void increment_tile();
void change_selected_tile(int);
#endif