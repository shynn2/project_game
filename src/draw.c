#include "draw.h"


// 1. 화면 지우기
void ClearWindow(App *app) {
    // 검은색(R:0, G:0, B:0)으로 설정
    SDL_SetRenderDrawColor(app->g_renderer, 0, 0, 0, 255);
    // 화면 전체를 지움
    SDL_RenderClear(app->g_renderer);
}

// 2. 화면 보여주기
void ShowWindow(App *app) {
    // 렌더러에 그려진 내용을 화면에 송출
    SDL_RenderPresent(app->g_renderer);
}

// 3. 게임 전체 그리기
void DrawGame(App *app, TextObject *score_text, TextObject *life_text) {
    
    // A. 모든 재료 그리기
    // MAX_INGREDIENTS 만큼 반복하면서 활성화된 재료만 그림
    for (int i = 0; i < MAX_INGREDIENTS; i++) {
        // App -> Game -> Ingredients 배열 접근
        Ingredient *ing = &app->game.ingredients[i];
        
        // 화면에 살아있는(is_active) 재료만 그린다
        if (ing->is_active) {
            RenderEntity(app, ing);
        }
    }

    // B. UI(점수, 목숨) 그리기
    RenderScoreBoard(app, score_text);
    RenderScoreBoard(app, life_text);
}

// 4. 개별 재료 그리기
void RenderEntity(App *app, Ingredient *ing) {
    // 텍스처가 없으면 그리지 않음 (안전장치)
    if (ing->texture == NULL) return;

    SDL_Rect dest;
    
    // 구조체의 float 좌표를 int로 변환 (SDL은 int 좌표를 씀)
    dest.x = (int)ing->x;
    dest.y = (int)ing->y;
    dest.w = ing->w;
    dest.h = ing->h;

    // 화면에 복사 (회전 없이 정방향)
    SDL_RenderCopy(app->g_renderer, ing->texture, NULL, &dest);
}

// 5. 텍스트 그리기
void RenderScoreBoard(App *app, TextObject *text_obj) {
    // 텍스처가 존재할 때만 그림
    if (text_obj->texture != NULL) {
        SDL_RenderCopy(app->g_renderer, text_obj->texture, NULL, &text_obj->rect);
    }
}

// 6. 텍스트 내용 업데이트 (가장 중요한 함수!)
void UpdateScoreBoard(App *app, TextObject *text_obj, char *str, SDL_Color color) {
    
    // A. 기존 텍스처가 있다면 삭제 (메모리 누수 방지)
    if (text_obj->texture != NULL) {
        SDL_DestroyTexture(text_obj->texture);
        text_obj->texture = NULL;
    }

    // 폰트가 로드되지 않았다면 중단
    if (app->font == NULL) return;

    // B. 폰트와 문자열을 이용해 Surface(임시 비트맵) 생성
    SDL_Surface *surface = TTF_RenderText_Solid(app->font, str, color);
    
    if (surface == NULL) {
        printf("Text Render Error: %s\n", TTF_GetError());
        return;
    }

    // C. Surface를 Texture(GPU 이미지)로 변환
    text_obj->texture = SDL_CreateTextureFromSurface(app->g_renderer, surface);
    
    if (text_obj->texture == NULL) {
        printf("Texture Create Error: %s\n", SDL_GetError());
        SDL_FreeSurface(surface);
        return;
    }

    // D. 만들어진 이미지의 크기를 TextObject의 rect에 저장
    text_obj->rect.w = surface->w;
    text_obj->rect.h = surface->h;
    
    // (x, y 위치는 main함수에서 초기화할 때 정해둔 것을 그대로 씀)

    // E. 임시로 만든 Surface는 이제 필요 없으니 삭제
    SDL_FreeSurface(surface);
}
