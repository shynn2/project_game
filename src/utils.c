/**
 * @file      utils.c
 * @brief     게임 로직에 필요한 수학적 계산 및 충돌 감지 유틸리티 구현
 */

#include "utils.h"

// 점(Point)이 사각형(Rect) 안에 있는지 확인
// 마우스 커서가 재료 위에 있는지(슬라이스 판정) 확인할 때 사용합니다.
int CheckPointInRect(int x, int y, const SDL_Rect *rect) {
    if ((x >= rect->x) && (x < (rect->x + rect->w)) &&
        (y >= rect->y) && (y < (rect->y + rect->h))) {
        return 1; // 충돌 (안에 있음)
    }
    return 0; // 충돌 안 함
}

// 재료가 화면 밖(특히 바닥)으로 나갔는지 확인
// 재료가 바닥으로 떨어졌을 때(목숨 차감 등)를 감지합니다.
int CheckOutBound(Ingredient *ing) {
    // 화면 아래쪽(SCREEN_HEIGHT)보다 더 아래로 내려갔는지 확인
    // (완전히 사라지게 하기 위해 여유분 50픽셀 정도를 둡니다)
    if (ing->y > SCREEN_HEIGHT + 50) {
        return 1; // 화면 밖으로 나감
    }
    
    // (선택 사항) 좌우나 위쪽으로 너무 멀리 날아간 경우도 제거하고 싶다면 아래 주석 해제
    /*
    if (ing->x < -100 || ing->x > SCREEN_WIDTH + 100 || ing->y < -500) {
        return 1;
    }
    */

    return 0; // 아직 화면 안에 있거나 유효한 범위임
}

// 정수 난수 생성 (min 이상 max 미만)
// 재료 타입 결정(0~5) 등에 사용합니다.
int RandInt(int min, int max) {
    if (min >= max) return min;
    return (rand() % (max - min)) + min;
}

// 실수 난수 생성 (min 이상 max 미만)
double RandDouble(double min, double max) {
    if (min >= max) return min;
    // 0.0 ~ 1.0 사이의 실수 난수 생성 후 범위에 맞게 변환
    double scale = (double)rand() / (double)RAND_MAX;
    return min + scale * (max - min);
}

// Degree -> Radian 변환
double DegToRad(double degrees) {
    return degrees * (M_PI / 180.0);
}
