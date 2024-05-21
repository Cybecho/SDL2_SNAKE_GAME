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

//! 게임 로직 관련 함수
void CreatePlayer();
void CreateItem();
void ResetGame();
void CreateNewTail(Player* player);
void CreateNewItem();
void CheckGameOver();

//! 렌더링 관련 함수
SDL_Texture* LoadTexture(const char* path, SDL_Renderer* renderer, SDL_Rect& rect, int x, int y, int w, int h);
void RenderReadyTexture();
void RenderGameOverTexture();
void RenderGameClearTexture();
void RenderScore();

//! 게임 상태
extern bool g_flag_running;
extern SDL_Renderer* g_renderer;
extern Uint32 g_frame_per_sec;
extern bool g_game_started;
extern bool g_game_over;
extern bool g_game_clear;
extern bool g_game_paused;
extern SDL_Texture* g_ready_texture;
extern SDL_Rect g_ready_rect;
extern SDL_Texture* g_game_over_texture;
extern SDL_Rect g_game_over_rect;
extern SDL_Texture* g_game_clear_texture;
extern SDL_Rect g_game_clear_rect;
extern int g_score; // extern 변수 선언