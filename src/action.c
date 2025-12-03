#include "utils.h"
#include "action.h" 


// [추가 1] main.c(main.h)에 있는 효과음 변수를 가져옵니다.
extern App app;
extern Mix_Chunk *effect_slice; // 효과음 변수 가져오기

//재료 변수 가져오기
extern Ingredient cabbage;
extern Ingredient meat;
extern Ingredient mushroom;
extern Ingredient beanSprouts;
extern Ingredient shoes;
extern Ingredient stone;



#define SPAWN_INTERVAL 40 //스폰 간격
#define LAUNCH_SPEED_MIN 13.0f //재료 발사 속도 최소
#define LAUNCH_SPEED_MAX 18.0f //재료 발사 속도 최대

static int spawn_timer = 0;



// 기존 ActIngredients 함수...
void ActIngredients(Ingredient ingredients[], int count) { 

    for (int i = 0; i < count; i++) {
        if (ingredients[i].is_active && !ingredients[i].is_sliced) {
            ingredients[i].dy += GRAVITY; 
            ingredients[i].pos.x += (int)ingredients[i].dx;
            ingredients[i].pos.y += (int)ingredients[i].dy;
        }
    }
}

// CheckSlice 구현
void CheckSlice(Ingredient ingredients[], int count, int x1, int y1, int x2, int y2) {
    // 너무 짧은 움직임(클릭 등)은 무시
    if (abs(x1 - x2) < 5 && abs(y1 - y2) < 5) return;

    for (int i = 0; i < count; i++) {
        // 활성화되어 있고 안 잘린 재료만 확인
        if (ingredients[i].is_active && !ingredients[i].is_sliced) {
            
            // 선분과 사각형 충돌 확인
            if (CheckLineRectHit(x1, y1, x2, y2, &ingredients[i].pos)) {
                
                // 베기 성공!
                ingredients[i].is_sliced = 1; 
                app.game.score += 10; // 점수 추가

                // [추가 2] 효과음 재생 (채널 -1: 자동 할당, 반복 0: 한 번 재생)
                if (effect_slice != NULL) {
                    Mix_PlayChannel(-1, effect_slice, 0);
                }
            }
        }
    }
}
