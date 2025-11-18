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
#define GRAVITY 0.5


// 구조체 정의 
typedef struct {
    SDL_Window *g_window;
    SDL_Renderer *g_renderer;
    TTF_Font *font;

} APP;


// 게임 내에서 움직이는 물체 (훠궈 재료, 신발)를 구현하기 위한 구조체
typedef struct {
    SDL_Texture *texture; // 텍스쳐 (그림파일) [cite: 532]
    SDL_Rect pos;         // 객체의 좌표, 위치, 너비, 높이를 저장하는 구조체 [cite: 533, 534]
    
    double v_x;           // x방향 속도벡터 [cite: 536]
    double v_y;           // y방향 속도벡터 (중력 적용) [cite: 537]
    double angle;         // 객체의 회전 각도 (선택 사항)

    IngredientType type;  // 재료의 종류 (고기, 신발 등)
    bool is_active;       // 현재 활성화되어 날아가는 중인지
    bool is_cut;          // 베였는지 여부
    
} Ingredient;

// 게임 내에 문자열을 표시할 경우 문자열을 나타내는 구조체 (스코어보드) [cite: 543]
typedef struct {
    SDL_Rect pos;       // 좌표와 위치 [cite: 550, 551]
    SDL_Color color;    // 글씨 색깔 [cite: 552]
    SDL_Surface *surface; // 폰트 렌더링을 위해 필요한 구조체 [cite: 553]
    SDL_Texture *texture; // 문자열을 저장한 텍스처 [cite: 554]
} Text;

#endif
