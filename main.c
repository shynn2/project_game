#include <stdio.h>
#include <SDL2/SDL.h>

#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 720

// 전역 SDL 변수 (다른 함수에서도 접근 가능하도록 전역으로 선언)
SDL_Window *g_window = NULL;
SDL_Renderer *g_renderer = NULL;
int g_game_running = 1;

// --- 함수 선언 ---
int init_sdl();
void handle_events();
void update_game();
void render_game();
void cleanup_sdl();

int main(int argc, char* argv[]) {
    // 1. 초기화 (Initialization)
    if (!init_sdl()) {
        printf("게임 초기화 실패 \n");
        return 1;
    }

    // 2. 게임 루프 (The Game Loop)
    while (g_game_running) {
        
        // 2A. 이벤트 처리 (입력 및 종료 감지)
        handle_events(); 
        
        // 2B. 게임 상태 업데이트 (재료 이동, 충돌, 점수 로직)
        update_game(); 
        
        // 2C. 렌더링 (화면 그리기)
        render_game(); 
        
        // 프레임 속도 제어 (선택 사항: 60 FPS 목표)
        SDL_Delay(1000 / 60); 
    }

    // 3. 종료 처리 (Cleanup)
    cleanup_sdl();
    return 0;
}

// ====================================================================
// --- 1. 초기화 및 생성 함수 정의 ---
// ====================================================================

/**
 * SDL 시스템을 초기화하고 창과 렌더러를 생성합니다.
 */
int init_sdl() {
    // 1. SDL 초기화 (비디오 시스템만)
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("SDL 초기화 에러: %s\n", SDL_GetError());
        return 0;
    }

    // 2. 창 (Window) 생성
    g_window = SDL_CreateWindow(
        "훠궈 요리사", 
        SDL_WINDOWPOS_UNDEFINED, 
        SDL_WINDOWPOS_UNDEFINED, 
        SCREEN_WIDTH, 
        SCREEN_HEIGHT, 
        SDL_WINDOW_SHOWN
    );
    if (g_window == NULL) {
        printf("창 생성 에러: %s\n", SDL_GetError());
        return 0;
    }

    // 3. 렌더러 (Renderer) 생성 (그림 그리기 도구)
    g_renderer = SDL_CreateRenderer(
        g_window, 
        -1, 
        SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC // 하드웨어 가속 사용 및 V-Sync (수직 동기화) 켜기
    );
    if (g_renderer == NULL) {
        printf("렌더러 생성 에러: %s\n", SDL_GetError());
        return 0;
    }

    return 1; // 성공적으로 초기화됨
}

// ====================================================================
// --- 2. 게임 루프 내부 함수 정의 ---
// ====================================================================

/**
 * 사용자 입력 및 시스템 이벤트를 처리합니다.
 */
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
    SDL_SetRenderDrawColor(g_renderer, 0, 0, 0, 255);
    SDL_RenderClear(g_renderer);

    // 2. 재료, 점수, UI 등을 그리는 코드가 여기에 들어갑니다.
    // 예: SDL_RenderDrawRect(g_renderer, ...);

    // 3. 렌더링 결과를 최종적으로 화면에 표시
    SDL_RenderPresent(g_renderer);
}

// ====================================================================
// --- 3. 종료 처리 함수 정의 ---
// ====================================================================

/**
 * SDL 객체를 파괴하고 시스템을 종료합니다.
 */
void cleanup_sdl() {
    // 렌더러와 창을 파괴합니다.
    if (g_renderer) {
        SDL_DestroyRenderer(g_renderer);
    }
    if (g_window) {
        SDL_DestroyWindow(g_window);
    }
    
    // SDL 시스템 종료
    SDL_Quit();
}
