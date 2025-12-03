#include "draw.h"

const SDL_Color COLOR_WHITE = {255, 255, 255, 255};
const SDL_Color COLOR_RED = {255, 50, 50, 255};

void ClearWindow(App *app) {
    SDL_SetRenderDrawColor(app->g_renderer, 30, 30, 30, 255);
    SDL_RenderClear(app->g_renderer);
}

void ShowWindow(App *app) {
    SDL_RenderPresent(app->g_renderer);
}

// [수정] 인자 추가됨
void DrawGame(App *app, TextObject *score, TextObject *life, TextObject *go, TextObject *restart) {
    
    // A. 재료 그리기
    for (int i = 0; i < MAX_INGREDIENTS; i++) {
        Ingredient *ing = &app->game.ingredients[i];
        if (ing->is_active) {
            RenderEntity(app, ing);
        }
    }

    // B. 마우스 궤적
    SDL_SetRenderDrawColor(app->g_renderer, 255, 255, 255, 255);
    for (int i = 0; i < TRAIL_LENGTH - 1; i++) {
        int idx1 = (app->trail_head + i) % TRAIL_LENGTH;
        int idx2 = (app->trail_head + i + 1) % TRAIL_LENGTH;
        if (app->trail_points[idx1].x != -1 && app->trail_points[idx2].x != -1) {
            SDL_RenderDrawLine(app->g_renderer, 
                app->trail_points[idx1].x, app->trail_points[idx1].y,
                app->trail_points[idx2].x, app->trail_points[idx2].y);
        }
    }

    // C. 점수판 및 생명 그리기 (항상 표시)
    RenderScoreBoard(app, score);
    RenderScoreBoard(app, life);

    // D. 게임 오버 화면
    if (app->game.game_over) {
        // 반투명 배경
        SDL_SetRenderDrawBlendMode(app->g_renderer, SDL_BLENDMODE_BLEND);
        SDL_SetRenderDrawColor(app->g_renderer, 0, 0, 0, 200);
        SDL_Rect screen_rect = {0, 0, SCREEN_WIDTH, SCREEN_HEIGHT};
        SDL_RenderFillRect(app->g_renderer, &screen_rect);
        SDL_SetRenderDrawBlendMode(app->g_renderer, SDL_BLENDMODE_NONE);

        // [추가] 텍스트 그리기 (중앙 정렬은 init.c에서 위치 잡음)
        RenderScoreBoard(app, go);
        RenderScoreBoard(app, restart);
    }
}

void RenderEntity(App *app, Ingredient *ing) {
    if (ing->texture == NULL) return;
    SDL_Rect dest;
    dest.x = (int)ing->x;
    dest.y = (int)ing->y;
    dest.w = ing->w;
    dest.h = ing->h;

    if (ing->is_sliced) {
        SDL_SetTextureColorMod(ing->texture, 150, 150, 150);
        SDL_SetTextureAlphaMod(ing->texture, 200);
    } else {
        SDL_SetTextureColorMod(ing->texture, 255, 255, 255);
        SDL_SetTextureAlphaMod(ing->texture, 255);
    }
    
    if (ing->is_enemy && !ing->is_sliced) {
        SDL_SetRenderDrawColor(app->g_renderer, 255, 0, 0, 255);
        SDL_RenderDrawRect(app->g_renderer, &dest);
    }
    SDL_RenderCopy(app->g_renderer, ing->texture, NULL, &dest);
}

void RenderScoreBoard(App *app, TextObject *text_obj) {
    if (text_obj->texture != NULL) {
        SDL_RenderCopy(app->g_renderer, text_obj->texture, NULL, &text_obj->rect);
    }
}

void UpdateScoreBoard(App *app, TextObject *text_obj, char *str, SDL_Color color) {
    if (app->font == NULL) return;
    if (text_obj->texture != NULL) {
        SDL_DestroyTexture(text_obj->texture);
        text_obj->texture = NULL;
    }
    SDL_Surface *surface = TTF_RenderText_Solid(app->font, str, color);
    if (surface == NULL) return;
    text_obj->texture = SDL_CreateTextureFromSurface(app->g_renderer, surface);
    if (text_obj->texture != NULL) {
        text_obj->rect.w = surface->w;
        text_obj->rect.h = surface->h;
    }
    SDL_FreeSurface(surface);
}