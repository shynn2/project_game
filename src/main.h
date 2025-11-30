#ifndef MAIN_H
#define MAIN_H

#include "defs.h"

#include "init.h"
#include "input.h"
#include "action.h"
#include "draw.h"
#include "sound.h"

APP app;
TextObject score_text;

TextObject health_text;

char text_buffer[BUFSIZE];

Mix_Music *bgm = NULL;
Mix_Chunk *effect_slice = NULL;



#endif 
