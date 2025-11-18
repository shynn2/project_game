#ifndef ACTION_H
#define ACTION_H

#include "defs.h" 
#include "input.h" // 입력 상태(마우스 움직임)를 참조해야 할 수 있음

// 모든 객체의 상태를 업데이트하고 충돌을 확인하는 메인 액션 함수
void ActGame(void);

// 훠궈 재료들의 움직임(물리, 중력)을 업데이트하는 함수
void ActIngredients(Ingredient ingredients[], int count);

// 베기 로직(마우스 이동)에 따른 충돌 감지 및 점수/목숨 처리 함수
void CheckSlice(Ingredient ingredients[], int count);

// 게임 오버 상태일 때의 로직 (R키 눌러 재시작 등)
void ActGameOver(void); 

// (선택) 충돌 감지 여부를 확인하는 유틸리티 함수 선언 (예: utils.c에 정의되어 있지만 필요하다면 여기에 선언)
int CheckCollisionObjects(SDL_Rect *rect_a, SDL_Rect *rect_b);

#endif // ACTION_H