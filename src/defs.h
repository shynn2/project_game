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

// 재료 종류 (ID)
#define TYPE_MUSHROOM 0
#define TYPE_FUZHU  1
#define TYPE_CABBAGE   2
#define TYPE_BEEF    3 //4점짜리
#define TYPE_SHOES     4 // 함정 (목숨깎여)
#define TYPE_ROCK     5 // 함정 (목숨 깎임)
#define NUM_TEXTURES  6 // 이미지 총 개수
#define FPS 60
#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 720
#define GRAVITY 0.5f



// APP (창, 렌더러, 마우스 상태)
typedef struct {
    SDL_Renderer *renderer;
    SDL_Window *window;
    TTF_Font *font;
    
    // 마우스 상태 (슬라이스 기능을 위해 필요)
    int mouse_x;
    int mouse_y;
    int mouse_down; // 클릭 중인가? (1:Yes, 0:No)
} App;

// 재료 정보
typedef struct {
    float x, y;       // 현재 위치 (float으로 해야 부드러움)
    float dx, dy;     // 이동 속도 (dx:가로, dy:세로)
    int w, h;         // 크기
    int type;         // 재료 종류 (버섯인지 고기인지)
    int active;       // 1: 화면에 살아있음, 0: 죽음(재사용 대기)
    int is_sliced;    // 1: 이미 칼로 베임, 0: 안 베임
    SDL_Texture *texture; // 재료 그림
} Ingredient;

// Text 점수판, 목숨표에 사용
typedef struct {
    int x, y;
    SDL_Color color;
    SDL_Texture *texture;
    SDL_Surface *surface;
    SDL_Rect pos;
} Text;

//공유 자원

extern App app;
extern Ingredient ingredients[MAX_INGREDIENTS]; // 재료들을 모아둔 배열
extern SDL_Texture* ingredient_textures[NUM_TEXTURES]; // 로딩된 이미지 원본들
extern int score;     // 현재 점수
extern int lives;     // 남은 목숨
extern int high_score; // 최고 점수

#endif
