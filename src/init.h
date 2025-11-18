#ifndef INIT_H
#include "defs.h"

extern APP app;


int init_sdl();
void handle_events();
void update_game();
void render_game();
void cleanup_sdl();


#endif
