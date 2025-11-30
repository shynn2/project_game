#ifndef INIT_H
#define INIT_H

#include "defs.h"

extern App app;
extern App app;

extern TextObject score_text;

extern TextObject health_text;

extern char text_buffer[BUFSIZE];

extern Mix_Music *bgm = NULL;
extern Mix_Chunk *effect_slice = NULL;

extern int g_game_running;

void init_sdl(void);
void InitIngredient(void);

void handle_events(void);
void update_game(void);
void render_game(void);
void cleanup_sdl(void);



#endif
