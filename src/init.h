#ifndef INIT_H
#define INIT_H

#include "defs.h"

extern App app;
extern Entity type[TOTAL_INGREDIENT];
extern Entity cabbage;
extern Entity mushrooms;
extern Entity bean_sprouts;
extern Entity meat;

extern int g_game_running;

void init_sdl(void);
void InitIngredient(void);

void handle_events(void);
void update_game(void);
void render_game(void);
void cleanup_sdl(void);

void render_game(void);


#endif
