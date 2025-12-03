#ifndef INIT_H
#define INIT_H

#include "defs.h"

// 전역 변수 (외부 참조)
extern App app;
extern int g_game_running;

// [init.h 파일 수정]

// ... (기존 extern 선언들 아래에 추가)
extern Mix_Music *bgm;
extern Mix_Chunk *effect_slice;

// 1. 시스템 초기화
void InitSDL(void);
void InitTTF(void);
void InitMemorySet(void);
void InitAudio(void); // <--- [추가!] 오디오 로딩 함수 선언

// ... (나머지는 그대로)

// 2. 게임 데이터 초기화
void InitGameData(void);   // 예제의 InitPlayer + InitBullet 역할 (데이터 리셋)
void ActIngredient(void);
void InitScoreBoard(void); // 점수판 및 목숨 텍스트 초기화


// 3. 종료 처리
void QuitSDL(int flag);
void QuitTTF(void);

#endif // INIT_H