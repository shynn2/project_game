#include <stdio.h>
#include <time.h>

#include "main.h"


int g_game_running = 1;

int main(void) {

    int tmpcnt = 0;

    srand(time(NULL));

    // 1. 초기화 (Initialization)
    init_sdl();
    

        

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


