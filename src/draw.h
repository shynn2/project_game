#ifndef DRAW_H
#define DRAW_H

#include "defs.h"


// 1. 화면 제어
void ClearWindow(App *app);
void ShowWindow(App *app);

// 2. 그리기 (Render)
// 게임 화면 전체를 그리는 함수
// score_text와 life_text는 main에서 관리하는 텍스트 객체입니다.
void DrawGame(App *app, TextObject *score_text, TextObject *life_text);

// 재료 하나를 그리는 함수
void RenderEntity(App *app, Ingredient *ing);

// 점수판(텍스트)을 그리는 함수
void RenderScoreBoard(App *app, TextObject *text_obj);

// 3. 텍스트 업데이트 (Update)
// 문자열을 텍스처로 변환하여 TextObject에 저장하는 함수
void UpdateScoreBoard(App *app, TextObject *text_obj, char *str, SDL_Color color);


#endif
