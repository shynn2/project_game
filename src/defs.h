#ifndef DEFS_H
#define DEFS_H


// 표준 라이브러리
#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// SDL2 라이브러리
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>

// 상수 정의 
#define FPS 60 //프레임
#define BUFSIZE 1024 

#define SCREEN_WIDTH 1280 //화면 크기
#define SCREEN_HEIGHT 720  

#define INGREDIENTS_WIDTH 80   
#define INGREDIENTS_HEIGHT 80   //재료 크기
#define INGREDIENTS_SPEED 10 //재료 속도

#define MIN_INGREDIENT 3  // 화면에 나타나는 재료의 최소 개수
#define MAX_INGREDIENTS 50  // 화면에 나타나는 재료의 최대 개수
#define MAX_HEALTH 3 // 목숨 개수는 3

#define GRAVITY 0.3f //중력
#define FONTSIZE 20  //폰트 사이즈

// 폰트 파일 이름을 상수로 정의 (경로 변경 시 여기만 바꾸면 됨)
#define FONT_PATH "./LiberationSans-Regular.ttf" 

#define TRAIL_LENGTH 10  //마우스 궤적 길이

typedef enum {
    MUSHROOM, 
    CABBAGE, 
    BEANSPROUTS, 
    MEAT, 
    SHOES, 
    STONE
} TypeIngredient;  //재료 타입 열거

// 텍스트 객체 구조체
typedef struct {
    SDL_Texture *texture; // 글자 이미지 데이터
    SDL_Rect rect;        // 위치(x, y)와 크기(w, h) 정보
} TextObject;


typedef struct {
    float x, y;        //위치
    float dx, dy;        //속도 (dx: x축 변화량, dy: y축 변화량)
    int type;           // TypeIngredient 0~3:식재료, 4:돌, 5:신발
    int is_enemy;      // 1: 닿으면 목숨 깎임, 0: 획득
    int is_active;     //  1: 현재 화면에 존재함, 0: 비활성
    int is_sliced;     // 1: 베어짐, 0: 안 베어짐

    int w, h;            //  크기
    SDL_Texture *texture; // 이미지

// 재료 구조체
typedef struct {
    float x, y;         // 위치 (물리 연산을 위해 float 사용)
    float dx, dy;       // 속도 (dx: x축 변화량, dy: y축 변화량)
    int type;           // TypeIngredient 값 (0~3:식재료, 4:신발, 5:돌)
    int is_enemy;       // 1: 닿으면 목숨 깎임(함정), 0: 점수 획득
    int is_active;      // 1: 현재 화면에 존재함, 0: 비활성
    int is_sliced;      // 1: 베어짐, 0: 안 베어짐

    int w, h;           // 크기
    SDL_Texture *texture; // 이미지 텍스처
} Ingredient;

// 게임 상태 구조체
typedef struct {
    int score;          // 현재 점수
    int lives;          // 남은 목숨
    int game_over;      // 게임 종료 여부

    // 게임 내 모든 재료 관리 배열
    Ingredient ingredients[MAX_INGREDIENTS];
} Game;

// 애플리케이션 구조체
typedef struct {
    SDL_Window *g_window;
    SDL_Renderer *g_renderer;
    TTF_Font *font;

    Game game; // 게임 상태 포함

    // 마우스 슬라이스 궤적 저장용
    SDL_Point trail_points[TRAIL_LENGTH];
    int trail_head; // 순환 버퍼 인덱스

    // 마우스 상태 추가
    int mouse_x;
    int mouse_y;
    int mouse_down;
    Game game;

    // 마우스 슬라이스 궤적 저장용
    SDL_Point trail_points[TRAIL_LENGTH]; 
    int trail_head; // 배열의 현재 위치 (순환 버퍼용)

    // 마우스 상태 추가
    int mouse_x;
    int mouse_y;
    int mouse_down;
} App;


#endif
