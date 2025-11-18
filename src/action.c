#include "defs.h" 
#include "action.h" // ActIngredients 함수 선언 포함

void ActIngredients(Ingredient ingredients[], int count) {
    // GRAVITY 상수는 defs.h에 #define GRAVITY 0.5 와 같이 정의되어야 합니다.
    const double GRAVITY = 0.5; 

    for (int i = 0; i < count; i++) {
        // 활성화된 재료만 업데이트
        if (ingredients[i].is_active && !ingredients[i].is_cut) {
            
            // 1. 중력 적용: y축 속도(v_y) 증가 (위로 쏘았으므로 v_y는 점점 양수 방향으로 바뀝니다)
            ingredients[i].v_y += GRAVITY; 
            
            // 2. 위치 업데이트 (v_x는 변함 없이, v_y는 중력 적용됨)
            ingredients[i].pos.x += (int)ingredients[i].v_x;
            ingredients[i].pos.y += (int)ingredients[i].v_y;
            
            // (화면 밖으로 나갔을 때 비활성화 로직 추가 예정)
        }
    }
}
