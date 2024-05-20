#include "Include.h"
#include "GameLogic.h"

Mix_Chunk* wave1_;
Mix_Music* music1_;

SDL_Texture* text_score_;
SDL_Rect text_score_rect_;
TTF_Font* game_font_;

SDL_Rect g_bg_source_rect;
SDL_Rect g_bg_destination_rect;

void InitGame() {
    g_flag_running = true;

    g_bg_source_rect = { 0, 0, WINDOW_SIZE, WINDOW_SIZE };
    g_bg_destination_rect = { 0, 0, WINDOW_SIZE, WINDOW_SIZE };
}

void HandleEvents() {
    SDL_Event event;

    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_SPACE) {
            // 스페이스바를 누르면?
        }
    }
}

void Update() {
}

void Render() {
    SDL_SetRenderDrawColor(g_renderer, 0, 0, 0, 0); // 배경색 설정
    SDL_RenderClear(g_renderer);



    SDL_RenderPresent(g_renderer);
}

//! 게임 종료 시 메모리 꼭! 해제
void ClearGame() {

    Mix_FreeMusic(music1_);
    Mix_FreeChunk(wave1_);

    TTF_CloseFont(game_font_);
}