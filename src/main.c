#include <stdio.h>
#include <time.h>
#include "main.h"

// 전역 변수 실제 정의
App app;
int g_game_running = 1;

int main(int argc, char *argv[]) {
    // 랜덤 시드 설정
    srand((unsigned int)time(NULL));

    // 1. 초기화
    init_sdl();
    InitIngredient(); // 재료 및 텍스처 로딩
    InitAudio();

    // [추가!] 배경음악 재생 (-1은 무한 반복)
    if (bgm != NULL) {
        Mix_PlayMusic(bgm, -1);
    }
    
    // 텍스트 객체 초기화 (색상 설정 등)
    SDL_Color black = {0, 0, 0, 255};
    SDL_Color red = {255, 0, 0, 255};
    
    // (초기 텍스트 렌더링은 루프 안에서 하거나 여기서 한 번 해줄 수 있음)
    // UpdateScoreBoard(&app, &score_text, "Score: 0", black);
    // UpdateScoreBoard(&app, &life_text, "Lives: 3", red);

    // 2. 게임 루프
    while (g_game_running) {
        handle_events(); 
        update_game(); 
        render_game(); 
        SDL_Delay(1000 / 60); 
    }

    // 3. 종료
    cleanup_sdl();
    return 0;
}