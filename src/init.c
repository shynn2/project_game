#include <stdlib.h>
#include "init.h"

#if 0
// SDL 시스템 초기화하고 창과 렌더러를 생성
void init_sdl(void) {
    // SDL 초기화(비디오 시스템)
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("SDL 초기화 에러: %s\n", SDL_GetError());
        exit(1);
    }

    // 창 (Window) 생성, 오류 시 프로그램 종료
    app.g_window = SDL_CreateWindow(
        "훠궈 요리사", 
        SDL_WINDOWPOS_UNDEFINED, 
        SDL_WINDOWPOS_UNDEFINED, 
        SCREEN_WIDTH, 
        SCREEN_HEIGHT, 
        0
    ); // 마지막 인자는 SDL_WINDOW_SHOWN 으로 해도 무관

    if (app.g_window == NULL) {
        printf("창 생성 에러: %s\n", SDL_GetError());
        SDL_Quit();
        exit(1);
    }

    // 렌더러(Renderer) 생성
    app.g_renderer = SDL_CreateRenderer(app.g_window, -1, SDL_RENDERER_ACCELERATED);

    if (app.g_renderer == NULL) {
        printf("렌더러 생성 에러: %s\n", SDL_GetError());
        SDL_DestroyWindow(app.g_window);
        SDL_Quit();
        exit(1);
    }
    
    IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG);

    return;
    
}



// 게임 루프 내부 함수 정의-사용자 입력 및 시스템 이벤트를 처리
void handle_events(void) {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT) { // 창의 'X' 버튼 클릭 시
            g_game_running = 0;
        }
        if (event.type == SDL_KEYDOWN) {
            if (event.key.keysym.sym == SDLK_ESCAPE) { // ESC 키 누를 시
                g_game_running = 0;
            }
        }
        // 마우스 입력, 슬라이스 궤적 추적 등은 여기에 추가됩니다.
    }
}

/**
 * 게임의 논리와 상태를 업데이트합니다. (현재는 비어있음)
 */
void update_game(void) {
    // 2단계에서 구현할 재료의 위치 이동 및 물리 로직, 충돌 판정 등이 여기에 들어갑니다.
}

/**
 * 화면을 지우고, 객체들을 그린 후, 화면을 갱신합니다.
 */
/*void render_game(void) {
    // 1. 화면 지우기 (검은색으로)
    SDL_SetRenderDrawColor(app.g_renderer, 0, 0, 0, 255);
    SDL_RenderClear(app.g_renderer);

    // 2. 재료, 점수, UI 등을 그리는 코드가 여기에 들어갑니다.
    // 예: SDL_RenderDrawRect(g_renderer, ...);

    // 3. 렌더링 결과를 최종적으로 화면에 표시
    SDL_RenderPresent(app.g_renderer);
}*/

// ====================================================================
// --- 3. 종료 처리 함수 정의 ---
// ====================================================================


// SDL 객체를 파괴 시스템을 종료
void cleanup_sdl(void) {
    if (app.g_renderer) {
        SDL_DestroyRenderer(app.g_renderer);
    }
    if (app.g_window) {
        SDL_DestroyWindow(app.g_window);
    }

    SDL_Quit();
}



void InitIngredient(void) {
    
    return;
}


void render_game(void) {
    // 1. 화면 지우기 (검은색으로)
    SDL_SetRenderDrawColor(app.g_renderer, 0, 0, 0, 255);
    SDL_RenderClear(app.g_renderer);

    // --- ▼ 2. (추가!) 양배추 그리기 ▼ ---
    

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

    return;
}

void InitMemorySet(void) {
    // 구조체 메모리를 0으로 초기화 (예제 스타일)
    memset(&app, 0, sizeof(App));
    memset(&score_text, 0, sizeof(TextObject));
    memset(&health_text, 0, sizeof(TextObject));

    return;
}

void InitGameData(void) {
    // 게임 변수 초기화 (예제의 InitPlayer, InitBullet 역할)
    app.game.score = 0;
    app.game.health = MAX_HEALTH;
    app.game.game_over = 0;

    // 모든 재료 슬롯 비활성화
    for (int i = 0; i < MAX_INGREDIENTS; i++) {
        app.game.ingredients[i].is_active = 0;
        app.game.ingredients[i].texture = NULL;
    }


    return;
}


void InitScoreBoard(void) {
    // 점수 텍스트 위치 설정
    score_text.rect.x = 20;
    score_text.rect.y = 20;
    score_text.texture = NULL;

    // 목숨 텍스트 위치 설정
    health_text.rect.x = SCREEN_WIDTH - 150; // 오른쪽 상단
    health_text.rect.y = 20;
    health_text.texture = NULL;

    return;
}

void QuitSDL(int flag) {
    // 1. 텍스트 텍스처 해제
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

    // 3. SDL 시스템 해제
    if (app.g_renderer) SDL_DestroyRenderer(app.g_renderer);
    if (app.g_window) SDL_DestroyWindow(app.g_window);

    QuitTTF();
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

#endif
