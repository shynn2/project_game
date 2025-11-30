#include <stdlib.h>
#include "init.h"

// SDL 시스템 초기화하고 창과 렌더러를 생성
void init_sdl(void) {
    // SDL 초기화(비디오 시스템)
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("SDL 초기화 에러: %s\n", SDL_GetError());
        exit(1);
    }
/*
void InitTTF(void) {
    if (TTF_Init() < 0) {
        printf("[ERROR] in InitTTF(): %s", SDL_GetError());
        exit(1);
    }

    app.font = TTF_OpenFont("./ttf/LiberationSans-Regular.ttf", 20);

    return;
}

    void QuitTTF(void) {
    TTF_CloseFont(app.font);
    TTF_Quit();

    return;
}
*/
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

// [구현] 마우스 슬라이스 궤적 초기화
void InitTrail(void) {
    app.trail_head = 0;
    for (int i = 0; i < TRAIL_LENGTH; i++) {
        // -1은 '아직 점이 찍히지 않음'을 의미 (유효하지 않은 좌표)
        app.trail_points[i].x = -1;
        app.trail_points[i].y = -1;
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
    cabbage.texture = IMG_LoadTexture(app.g_renderer, "./gfx/cabbage.png");
    cabbage.pos.x = SCREEN_WIDTH / 2;
    cabbage.pos.y = SCREEN_HEIGHT / 2;
    // player.health = 1;
    SDL_QueryTexture(cabbage.texture, NULL, NULL, &(cabbage.pos.w),
                     &(cabbage.pos.h));

    return;
}


void render_game(void) {
    // 1. 화면 지우기 (검은색으로)
    SDL_SetRenderDrawColor(app.g_renderer, 0, 0, 0, 255);
    SDL_RenderClear(app.g_renderer);

    // --- ▼ 2. (추가!) 양배추 그리기 ▼ ---
    // (cabbage.texture가 NULL이 아닐 때만 그리는 것이 안전합니다)
    if (cabbage.texture != NULL) {
        SDL_RenderCopy(
            app.g_renderer,     // 1. 사용할 렌더러
            cabbage.texture,    // 2. 그릴 텍스처 (양배추)
            NULL,               // 3. 텍스처의 어느 부분을 그릴지 (NULL = 전체)
            &cabbage.pos        // 4. 화면 어디에(x,y) 어떤 크기(w,h)로 그릴지
        );
    }
    // --- ▲ ---------------------- ▲ ---

    // 3. 렌더링 결과를 최종적으로 화면에 표시
    SDL_RenderPresent(app.g_renderer);
}
