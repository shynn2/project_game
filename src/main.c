#include "main.h"
#include "draw.h"
#include "action.h"
#include "input.h"

// 전역 변수 실체화 (defs.h에 선언된 것들)
App app;
// 게임 내 모든 재료 관리 배열
// Ingredient ingredients[MAX_INGREDIENTS]; (defs.h나 Game 구조체 안에 있다면 주석 처리)

// 텍스트 객체 (점수판, 목숨)
TextObject score_text;
TextObject life_text;

int g_game_running = 1;

int main(void) {
    srand(time(NULL));

    // 1. 초기화 (init.c의 함수 사용)
    init_sdl();
    InitIngredient(); // 재료 및 텍스처 로딩

    // 텍스트 객체 초기화 (색상 설정 등)
    SDL_Color black = {0, 0, 0, 255};
    SDL_Color red = {255, 0, 0, 255};
    
    // (초기 텍스트 렌더링은 루프 안에서 하거나 여기서 한 번 해줄 수 있음)
    // UpdateScoreBoard(&app, &score_text, "Score: 0", black);
    // UpdateScoreBoard(&app, &life_text, "Lives: 3", red);

    // 2. 게임 루프
    while (g_game_running) {
        Uint32 start_tick = SDL_GetTicks();

        // 2A. 입력 처리 (input.c의 함수 사용)
        handle_events(); 

        // 2B. 게임 로직 (action.c의 함수 사용)
        // 재료들의 물리 움직임 계산
        ActIngredients(app.game.ingredients, MAX_INGREDIENTS);
        
        // (점수나 목숨이 바뀌었을 때 텍스트 업데이트 로직 추가 가능)
        char score_str[32];
        char life_str[32];
        sprintf(score_str, "Score: %d", app.game.score);
        sprintf(life_str, "Lives: %d", app.game.health);
        
        UpdateScoreBoard(&app, &score_text, score_str, black);
        UpdateScoreBoard(&app, &life_text, life_str, red);

        // 텍스트 위치 잡기
        score_text.rect.x = SCREEN_WIDTH - score_text.rect.w - 20;
        score_text.rect.y = 20;
        life_text.rect.x = SCREEN_WIDTH - life_text.rect.w - 20;
        life_text.rect.y = 50;

        // 2C. 그리기 (draw.c의 함수 사용)
        ClearWindow(&app); // 화면 지우기
        DrawGame(&app, &score_text, &life_text); // 재료 및 UI 그리기
        ShowWindow(&app); // 화면 표시

        // 프레임 제한 (60 FPS)
        Uint32 frame_ticks = SDL_GetTicks() - start_tick;
        if (frame_ticks < 1000 / FPS) {
            SDL_Delay(1000 / FPS - frame_ticks);
        }
    }

    // 3. 종료 (init.c의 함수 사용)
    cleanup_sdl();

    return 0;
}

#endif


