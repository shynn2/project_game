#include "init.h"

// SDL 시스템 초기화하고 창과 렌더러를 생성
int init_sdl() {
    // 1. SDL 초기화 (비디오 시스템만)
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("SDL 초기화 에러: %s\n", SDL_GetError());
        return 0;
    }

    // 2. 창 (Window) 생성
    app.g_window = SDL_CreateWindow(
        "훠궈 요리사", 
        SDL_WINDOWPOS_UNDEFINED, 
        SDL_WINDOWPOS_UNDEFINED, 
        SCREEN_WIDTH, 
        SCREEN_HEIGHT, 
        SDL_WINDOW_SHOWN
    );
    if (app.g_window == NULL) {
        printf("창 생성 에러: %s\n", SDL_GetError());
        return 0;
    }

    // 렌더러(Renderer) 생성
    app.g_renderer = SDL_CreateRenderer(
        app.g_window, 
        -1, 
        SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC // 하드웨어 가속 사용 및 V-Sync (수직 동기화) 켜기
    );
    if (app.g_renderer == NULL) {
        printf("렌더러 생성 에러: %s\n", SDL_GetError());
        return 0;
    }

    return 1;
}



// 게임 루프 내부 함수 정의-사용자 입력 및 시스템 이벤트를 처리
void handle_events() {
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
void update_game() {
    // 2단계에서 구현할 재료의 위치 이동 및 물리 로직, 충돌 판정 등이 여기에 들어갑니다.
}

/**
 * 화면을 지우고, 객체들을 그린 후, 화면을 갱신합니다.
 */
void render_game() {
    // 1. 화면 지우기 (검은색으로)
    SDL_SetRenderDrawColor(app.g_renderer, 0, 0, 0, 255);
    SDL_RenderClear(app.g_renderer);

    // 2. 재료, 점수, UI 등을 그리는 코드가 여기에 들어갑니다.
    // 예: SDL_RenderDrawRect(g_renderer, ...);

    // 3. 렌더링 결과를 최종적으로 화면에 표시
    SDL_RenderPresent(app.g_renderer);
}

// ====================================================================
// --- 3. 종료 처리 함수 정의 ---
// ====================================================================


// SDL 객체를 파괴 시스템을 종료
void cleanup_sdl() {
    if (app.g_renderer) {
        SDL_DestroyRenderer(app.g_renderer);
    }
    if (app.g_window) {
        SDL_DestroyWindow(app.g_window);
    }

    SDL_Quit();
}
