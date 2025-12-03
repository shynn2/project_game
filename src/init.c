#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "init.h"
#include "action.h"
#include "draw.h"
#include "input.h"

Ingredient mushroom, cabbage, meat, beanSprouts, shoes, stone;
TextObject score_text, life_text;
// [추가] 게임 오버용 텍스트 객체
TextObject gameover_text, restart_text;

void InitTrail(void) {
    app.trail_head = 0;
    for (int i = 0; i < TRAIL_LENGTH; i++) {
        app.trail_points[i].x = -1;
        app.trail_points[i].y = -1;
    }
}

void InitIngredient(void) {
    #define LOAD_TEX(obj, path) \
        obj.texture = IMG_LoadTexture(app.g_renderer, path); \
        if (!obj.texture) printf("Failed to load %s: %s\n", path, IMG_GetError());

    LOAD_TEX(cabbage, "./gfx/cabbage.png");
    LOAD_TEX(meat, "./gfx/meat.png");
    LOAD_TEX(mushroom, "./gfx/mushrooms.png");
    LOAD_TEX(beanSprouts, "./gfx/bean_sprouts.png");
    LOAD_TEX(shoes, "./gfx/shoes.png");
    stone.texture = shoes.texture;
}

void init_sdl(void) {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) exit(1);
    if (TTF_Init() < 0) exit(1);
    int imgFlags = IMG_INIT_PNG | IMG_INIT_JPG;
    if (!(IMG_Init(imgFlags) & imgFlags)) exit(1);

    app.font = TTF_OpenFont(FONT_PATH, FONTSIZE);
    

    // 3. 렌더링 결과를 최종적으로 화면에 표시
    SDL_RenderPresent(app.g_renderer);
}

#endif

extern TextObject health_text;

#if 1
void InitSDL(void) {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("[ERROR] in InitSDL(): %s\n", SDL_GetError());
        exit(1);
    }

    app.g_window = SDL_CreateWindow(
        "Huoguo Chef",
        SDL_WINDOWPOS_UNDEFINED,
        SDL_WINDOWPOS_UNDEFINED,
        SCREEN_WIDTH,
        SCREEN_HEIGHT,
        0);

    if (!app.g_window) {
        printf("[ERROR] in CreateWindow: %s\n", SDL_GetError());
        exit(1);
    }

    app.g_window = SDL_CreateWindow("Hotpot Chef", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, 0);
    app.g_renderer = SDL_CreateRenderer(app.g_window, -1, SDL_RENDERER_ACCELERATED);
    
    if (!app.g_renderer) {
        printf("[ERROR] in CreateRenderer: %s\n", SDL_GetError());
        exit(1);
    }

    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
        printf("[ERROR] Mix_OpenAudio: %s\n", Mix_GetError());
        exit(1);
    }

    // 이미지 라이브러리 초기화
    if (IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG) == 0) {
        printf("[ERROR] in InitIMG: %s\n", IMG_GetError());
        exit(1);
    }

    return;
}

// 2. InitAudio 함수 추가 (파일 불러오기) - 파일 맨 아래나 적절한 곳에 추가
void InitAudio(void) {
    // 배경음악 로드 (mp3 권장)
    bgm = Mix_LoadMUS("./assets/bgm.mp3"); 
    if (bgm == NULL) {
        printf("[WARNING] Failed to load BGM: %s\n", Mix_GetError());
    }

    // 효과음 로드 (wav 권장)
    effect_slice = Mix_LoadWAV("./assets/slice.wav");
    if (effect_slice == NULL) {
        printf("[WARNING] Failed to load Effect: %s\n", Mix_GetError());
    }
}

void InitTTF(void) {
    if (TTF_Init() < 0) {
        printf("[ERROR] in InitTTF(): %s\n", TTF_GetError());
        exit(1);
    }

    // 폰트 로드 (경로 확인 필수)
    app.font = TTF_OpenFont("./assets/font.ttf", FONTSIZE);

    if (!app.font) {
        printf("[ERROR] Failed to load font: %s\n", TTF_GetError());
        exit(1);
    }

    app.font = TTF_OpenFont("./ttf/LiberationSans-Regular.ttf", FONTSIZE);
    
    InitIngredient();
    InitTrail();
    
    score_text.texture = NULL;
    life_text.texture = NULL;
    gameover_text.texture = NULL;
    restart_text.texture = NULL;

    // [추가] 고정 텍스트 미리 생성 (게임 오버, 재시작)
    SDL_Color red = {255, 50, 50, 255};
    SDL_Color white = {255, 255, 255, 255};
    UpdateScoreBoard(&app, &gameover_text, "GAME OVER", red);
    UpdateScoreBoard(&app, &restart_text, "Press 'R' to Restart", white);

    // 위치 설정 (화면 중앙)
    gameover_text.rect.x = (SCREEN_WIDTH - gameover_text.rect.w) / 2;
    gameover_text.rect.y = SCREEN_HEIGHT / 2 - 50;
    restart_text.rect.x = (SCREEN_WIDTH - restart_text.rect.w) / 2;
    restart_text.rect.y = SCREEN_HEIGHT / 2 + 10;
}

void update_game(void) {
    ActGame();
}

void render_game(void) {
    ClearWindow(&app);

    // 점수 및 목숨 업데이트 (매 프레임)
    char score_str[64];
    char life_str[64];
    SDL_Color white = {255, 255, 255, 255};
    SDL_Color red = {255, 50, 50, 255};

    sprintf(score_str, "Score: %d", app.game.score);
    sprintf(life_str, "Lives: %d", app.game.lives);

    UpdateScoreBoard(&app, &score_text, score_str, white);
    UpdateScoreBoard(&app, &life_text, life_str, red);

    score_text.rect.x = 20; score_text.rect.y = 20;
    life_text.rect.x = 20; life_text.rect.y = 50;

    // [수정] DrawGame에 모든 텍스트 객체 전달
    DrawGame(&app, &score_text, &life_text, &gameover_text, &restart_text);

    ShowWindow(&app);
}

void cleanup_sdl(void) {
    if (cabbage.texture) SDL_DestroyTexture(cabbage.texture);
    if (meat.texture) SDL_DestroyTexture(meat.texture);
    if (mushroom.texture) SDL_DestroyTexture(mushroom.texture);
    if (beanSprouts.texture) SDL_DestroyTexture(beanSprouts.texture);
    if (shoes.texture) SDL_DestroyTexture(shoes.texture);
    
    if (score_text.texture) SDL_DestroyTexture(score_text.texture);
    if (health_text.texture) SDL_DestroyTexture(health_text.texture);
    if (bgm) Mix_FreeMusic(bgm);
    if (effect_slice) Mix_FreeChunk(effect_slice);
    Mix_CloseAudio();
    
    // 2. 재료 텍스처 해제 (남아있는 재료가 있다면)
    for (int i = 0; i < MAX_INGREDIENTS; i++) {
        if (app.game.ingredients[i].texture) {
            SDL_DestroyTexture(app.game.ingredients[i].texture);
        }
    }

    if (app.font) TTF_CloseFont(app.font);
    if (app.g_renderer) SDL_DestroyRenderer(app.g_renderer);
    if (app.g_window) SDL_DestroyWindow(app.g_window);

    TTF_Quit();
    IMG_Quit();
    SDL_Quit();

    exit(flag);

    return;
}

void QuitTTF(void) {
    if (app.font) {

        TTF_CloseFont(app.font);
        app.font = NULL;
    }
    TTF_Quit();

    return;
}
