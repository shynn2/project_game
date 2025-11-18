#include <stdio.h>
#include <SDL2/SDL.h>

#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 720

int g_game_running = 1;



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


