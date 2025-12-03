

#include "utils.h" // (파일 맨 위에 이 줄이 없다면 추가해주세요)
#include "defs.h"

// CheckSlice 함수의 실제 구현 내용
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
                App.game.score += 10; // 점수 추가
            }
        }
    }
}
