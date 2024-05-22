#include "Include.h"
#include "GameLogic.h"

SDL_Window *g_window;
SDL_Renderer *g_renderer;
bool g_flag_running;
Uint32 g_last_time_ms;
Uint32 g_frame_per_sec = GAME_FRAME;

int main(int argc, char *argv[])
{

    // Initializing SDL library
    SDL_Init(SDL_INIT_EVERYTHING);

    TTF_Init();

    g_window = SDL_CreateWindow("201921408 SBU", 100, 100, WINDOW_SIZE, WINDOW_SIZE, 0);
    g_renderer = SDL_CreateRenderer(g_window, -1, 0);

    InitGame();

    g_last_time_ms = SDL_GetTicks();

    while (g_flag_running)
    {

        Uint32 cur_time_ms = SDL_GetTicks();

        if (cur_time_ms - g_last_time_ms < (1000 / g_frame_per_sec))
            continue;

        HandleEvents();
        Update();
        Render();

        g_last_time_ms = cur_time_ms;
    }

    SDL_DestroyRenderer(g_renderer);
    SDL_DestroyWindow(g_window);

    ClearGame();
    TTF_Quit();
    SDL_Quit();

    return 0;
}