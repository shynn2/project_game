#include "input.h"
#include "action.h" // CheckSlice 함수를 쓰기 위해 필요

// 전역 변수 참조 (defs.h에 선언된 변수들)
extern App app;
extern int g_game_running;

// 초기화가 필요한 경우를 위해 (게임 재시작 등)
//InitGame 있다면 게임 재시작 함수가 있따면 !! extern void InitGame(void); 

void handle_events(void) {
    SDL_Event event;

    while (SDL_PollEvent(&event)) {
        
        // 1. 종료 이벤트 (X 버튼)
        if (event.type == SDL_QUIT) {
            g_game_running = 0;
        }

        // 2. 키보드 이벤트
        if (event.type == SDL_KEYDOWN) {
            // ESC 누르면 종료
            if (event.key.keysym.sym == SDLK_ESCAPE) {
                g_game_running = 0;
            }
            // 게임 오버 상태에서 R 키 누르면 재시작
            /*if (app.game.game_over && event.key.keysym.sym == SDLK_r) {
                // InitGame(); // 재시작 함수가 있다면 호출
                // 임시로 변수만 초기화
                app.game.score = 0;
                app.game.lives = 3;
                app.game.game_over = 0;
            }*/
        }

        // 3. 마우스 이동 이벤트 (핵심 로직!)
        if (event.type == SDL_MOUSEMOTION) {
            int prev_x = app.mouse_x;
            int prev_y = app.mouse_y;

            // 현재 마우스 위치 업데이트
            app.mouse_x = event.motion.x;
            app.mouse_y = event.motion.y;

            // [잔상 효과] 궤적 배열에 현재 위치 저장 (순환 버퍼)
            app.trail_head = (app.trail_head + 1) % TRAIL_LENGTH;
            app.trail_points[app.trail_head].x = app.mouse_x;
            app.trail_points[app.trail_head].y = app.mouse_y;

            // [슬라이스 판정] 마우스가 눌린 상태로 이동했으면 베기 시도
            if (app.mouse_down) {
                // action.c 에 있는 CheckSlice 호출
                // (이전 위치와 현재 위치를 잇는 선분이 재료를 베었는지 확인)
                CheckSlice(app.game.ingredients, MAX_INGREDIENTS, prev_x, prev_y, app.mouse_x, app.mouse_y);
            } //마우스 버튼을 누르고 있다면 app.mouse_down이 1이됨 따라서 true --> 조건문 실행
        }

        // 4. 마우스 버튼 이벤트
        if (event.type == SDL_MOUSEBUTTONDOWN) {
            app.mouse_down = 1;
        }
        if (event.type == SDL_MOUSEBUTTONUP) {
            app.mouse_down = 0;
        }
    }
}
