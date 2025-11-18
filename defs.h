#ifndef DEFS_H
#define INIT_H


// 상수 매크로 정의 
#include "ctype.h"
#include "math.h"
#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "time.h"

#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include "SDL2/SDL_ttf.h"
#include "SDL2/SDL_mixer.h"

#define FPS 60
#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 720


// 구조체 정의 
typedef struct {
    SDL_Window *g_window;
    SDL_Renderer *g_renderer;
    TTF_Font *font;

} APP;

typedef struct {
    
} INGREDIENTS;



#endif