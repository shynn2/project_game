#ifndef INIT_H
#define INIT_H

#include "defs.h"

extern App app;
extern Ingredient type[MIN_INGREDIENT];
extern Ingredient mushroom;
extern Ingredient cabbage;
extern Ingredient meat;
extern Ingredient beanSprouts;



extern int g_game_running;

void init_sdl(void);
void InitIngredient(void);

void handle_events(void);
void update_game(void);
void render_game(void);
void InitTrail(void);
void cleanup_sdl(void);

void render_game(void);


#endif
