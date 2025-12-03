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

extern Ingredient cabbage;
extern Ingredient meat;
extern Ingredient mushroom;
extern Ingredient beanSprouts;
extern Ingredient shoes;
extern Ingredient stone;

#define SPAWN_INTERVAL 40
#define LAUNCH_SPEED_MIN 13.0f
#define LAUNCH_SPEED_MAX 18.0f

static int spawn_timer = 0;

void ActGame(void) {
    if (app.game.game_over) return;

    spawn_timer++;
    if (spawn_timer > SPAWN_INTERVAL) {
        SpawnIngredient();
        spawn_timer = 0;
    }

    ActIngredients(app.game.ingredients, MAX_INGREDIENTS);
}

void SpawnIngredient(void) {
    int idx = -1;
    for (int i = 0; i < MAX_INGREDIENTS; i++) {
        if (!app.game.ingredients[i].is_active) {
            idx = i;
            break;
        }
    }
    if (idx == -1) return;

    Ingredient *ing = &app.game.ingredients[idx];

    ing->is_active = 1;
    ing->is_sliced = 0;
    
    // [중요] 크기를 상수로 강제 고정 (8x8)
    ing->w = INGREDIENTS_WIDTH; 
    ing->h = INGREDIENTS_HEIGHT;

    int center_x = SCREEN_WIDTH / 2;
    int offset_x = RandInt(-50, 51);
    ing->x = (float)(center_x + offset_x);
    ing->y = (float)SCREEN_HEIGHT;

    double angle_deg = RandDouble(60.0, 120.0);
    double angle_rad = DegToRad(angle_deg);
    double speed = RandDouble(LAUNCH_SPEED_MIN, LAUNCH_SPEED_MAX);

    ing->dx = (float)(speed * cos(angle_rad));
    ing->dy = (float)(-speed * sin(angle_rad));

    ing->type = RandInt(0, 6);

    switch (ing->type) {
        case MUSHROOM: ing->texture = mushroom.texture; ing->is_enemy = 0; break;
        case CABBAGE: ing->texture = cabbage.texture; ing->is_enemy = 0; break;
        case MEAT: ing->texture = meat.texture; ing->is_enemy = 0; break;
        case BEANSPROUTS: ing->texture = beanSprouts.texture; ing->is_enemy = 0; break;
        case SHOES: ing->texture = shoes.texture; ing->is_enemy = 1; break;
        case STONE: ing->texture = shoes.texture; ing->is_enemy = 1; break; 
        default: ing->texture = cabbage.texture; ing->is_enemy = 0; break;
    }

    // [중요] SDL_QueryTexture 코드를 완전히 제거했습니다.
    // 이제 이미지가 아무리 커도 8x8 크기로 찌그러져서 나옵니다.
}

void ActIngredients(Ingredient *ingredients, int count) {
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

void CheckSlice(Ingredient *ingredients, int count, int x1, int y1, int x2, int y2) {
    if (app.game.game_over) return;

    int hit_indices[MAX_INGREDIENTS];
    int hit_count = 0;
    int has_enemy = 0;

    for (int i = 0; i < count; i++) {
        Ingredient *ing = &ingredients[i];

        if (ing->is_active && !ing->is_sliced) {
            SDL_Rect rect = { (int)ing->x, (int)ing->y, ing->w, ing->h };

            if (CheckLineRectHit(x1, y1, x2, y2, &rect)) {
                hit_indices[hit_count++] = i;
                if (ing->is_enemy) has_enemy = 1;
            }
        }
    }

    if (hit_count > 0) {
        if (has_enemy) {
            app.game.lives--;
            if (app.game.lives <= 0) app.game.game_over = 1;
        } else {
            for (int k = 0; k < hit_count; k++) {
                int idx = hit_indices[k];
                Ingredient *target = &ingredients[idx];
                target->is_sliced = 1;
                app.game.score += 10;
                target->dy = -5.0f;
            }
        }
    }
}

void ActGameOver(void) {}

// [추가] 게임 재시작 로직
void ResetGame(void) {
    app.game.score = 0;
    app.game.lives = 3;
    app.game.game_over = 0;
    
    // 모든 재료 제거
    for (int i = 0; i < MAX_INGREDIENTS; i++) {
        app.game.ingredients[i].is_active = 0;
    }
}