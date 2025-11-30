#ifndef DEFS_H
#define DEFS_H


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

#define FPS 60 //프레임
#define BUFSIZE 1024 

#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 720  

#define INGREDIENTS_WIDTH 8      
#define INGREDIENTS_HEIGHT 8     
#define INGREDIENTS_SPEED 6

#define MIN_INGREDIENT 2  // 화면에 나타나는 재료의 최소 개수
#define MAX_INGREDIENTS 50  // 화면에 나타나는 재료의 최대 개수 

#define GRAVITY 0.5f
#define FONTSIZE 20       

#define TRAIL_LENGTH 10

typedef enum {MUSHROOM, CABBAGE, MEAT, BEANSPROUTS, SHOES, STONE} TypeIngredient;


// 구조체 정의 
typedef struct {
    SDL_Window *g_window;
    SDL_Renderer *g_renderer;
    TTF_Font *font;

    Game game;
    // [추가] 마우스 슬라이스 궤적 저장용
    SDL_Point trail_points[TRAIL_LENGTH]; 
    int trail_head; // 배열의 현재 위치 (순환 버퍼용)

} App;

typedef struct {
    int score;          // 현재 점수
    int lives;          // 남은 목숨 (여기 들어갑니다!)
    int game_over;     // 게임 종료 여부
    
    // 게임 내 모든 재료들을 여기서 관리
    Ingredient ingredients[MAX_INGREDIENTS]; 
} Game;


typedef struct {
    float x, y;
    float dx, dy;
    int type;           // 0~3:식재료, 4:돌, 5:신발
    int is_enemy;      // 1: 닿으면 목숨 깎임, 0: 획득
    int is_active;     // 현재 화면에 살아있는가?
    int is_sliced;     // 베어졌는가?

    int w, h;            //  크기
    SDL_Texture *texture; // 이미지

} Ingredient;


typedef struct {
    SDL_Texture *texture; // 글자 이미지 데이터 (가장 중요)
    SDL_Rect rect;        // 위치(x, y)와 크기(w, h) 정보
} TextObject;

#endif
