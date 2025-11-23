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

#define FPS 60
#define BUFSIZE 1024

#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 720

#define PLAYER_WIDTH 
#define PLAYER_HEIGHT     

#define INGREDIENTS_WIDTH 8      
#define INGREDIENTS_HEIGHT 8     
#define INGREDIENTS_SPEED 6

#define TOTAL_INGREDIENT 6
#define NUM_INGREDIENTS_MIN   // 화면에 나타난는 재료의 최소 개수
#define NUM_INGREDIENTS_MAX   // 화면에 나타나는 재료의 최대 개수 

#define GRAVITY 0.5
#define FONTSIZE 20       

enum TypeIngredient {MUSHROOM, CABBAGE, MEAT, BEANSPROUTS, SHOES, ROCK};


/*define TYPE_MUSHROOM 0
#define TYPE_FUZHU  1
#define TYPE_CABBAGE   2
#define TYPE_BEEF    3 //4점짜리
#define TYPE_SHOES     4 // 함정 (목숨깎여)
#define TYPE_ROCK     5 // 함정 (목숨 깎임) */




// 구조체 정의 
typedef struct {
    SDL_Window *g_window;
    SDL_Renderer *g_renderer;
    TTF_Font *font;

    int mouse_x;
    int mouse_y;
    int mouse_down;

} App;

typedef struct {
    SDL_Rect pos;

    int ingredient_type[TOTAL_INGREDIENT]; 
    double angle;           // 지면과 재료의 각도?를 저장하는 변수
    double v_x;             // 재료의 x방향 속도벡터
    double v_y;             // 재료의 y방향 속도벡터

    int health;             // 플레이어의 체력 상태를 나타내는 변수 (생존1, 사망0)
             
    SDL_Texture *texture;   // 그림 파일의 텍스처를 이 변수에 저장

} Entity;


typedef struct {
    float x, y;       // 현재 위치 (float으로 해야 부드러움)
    float dx, dy;     // 이동 속도 (dx:가로, dy:세로)
    int w, h;         // 크기
    int type;         // 재료 종류 (버섯인지 고기인지)
    int active;       // 1: 화면에 살아있음, 0: 죽음(재사용 대기)
    int is_sliced;    // 1: 이미 칼로 베임, 0: 안 베임
    SDL_Texture *texture; // 재료 그림
} Ingredient;


typedef struct {

    int x, y;
    SDL_Rect pos;           /**< 직사각형 객체의 상태를 나타내기 위한 구조체
                                여기에 객체의 좌표, 위치 저장*/
    SDL_Color color;        /**< 글씨 색깔을 저장하는 구조체*/
    SDL_Surface *surface;   /**< 폰트 렌더링을 위해 필요한 구조체*/
    SDL_Texture *texture;   /**< 신기하다*/

} TEXT;



#endif
