#pragma once

#include "Include.h"
#include "obj_Base.h"
#include "obj_Player.h"
#include "obj_Item.h"

//! 객체 리스트
extern list<Player*> g_Player;
extern list<Item*> g_Item;

//! 필수 함수
void InitGame();
void HandleEvents();
void Update();
void Render();
void ClearGame();

//! 렌더링 관련 함수
void RenderReadyTexture();
void RenderGameOverTexture();
void RenderGameClearTexture();

//! 게임 상태
extern bool g_flag_running;
extern SDL_Renderer* g_renderer;
extern Uint32 g_frame_per_sec;
extern bool g_game_started;
extern bool g_game_over;
extern bool g_game_clear;
extern SDL_Texture* g_ready_texture;
extern SDL_Rect g_ready_rect;
extern SDL_Texture* g_game_over_texture;
extern SDL_Rect g_game_over_rect;
extern SDL_Texture* g_game_clear_texture;
extern SDL_Rect g_game_clear_rect;

//! static 변수
static int LEFT_SPACE = ARR_SIZE * ARR_SIZE; // 남은 공간은 1씩 줄어들고, 0이 되면 게임 클리어
// LEFT_SPACE - Player_SIZE == 0 이 되면 게임클리어