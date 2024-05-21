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
void ResetGame();
void CheckGameOver();

//! 플레이어 관련 함수
void CreatePlayer();
void CreateNewTail(Player* player);

//! 아이템 관련 함수
void CreateItem();								// Item 컴파일 타임 중 생성 함수
void CreateNewItem();							// Item 런타임 중 생성 함수
void CreateTrapItem();							// trap_Item 생성 함수
void CreateCheatItem();							// cheat_Item 생성 함수

//! 플레이어와 아이템의 충돌 처리 함수
bool IsValidItemPosition(int itemX, int itemY);	// 아이템이 생성될 위치가 유효한지 확인
void HandleItemCollision(Player* player);		// 아이템과 플레이어의 충돌 처리


//! 게임 점수
extern int g_score; // extern 변수 선언

//! 렌더링 관련 함수
SDL_Texture* LoadTexture(const char* path, SDL_Renderer* renderer, SDL_Rect& rect, int x, int y, int w, int h);
void RenderReadyTexture();
void RenderGameOverTexture();
void RenderGameClearTexture();
void RenderScore();

//! SDL 텍스처
extern SDL_Texture* g_ready_texture;
extern SDL_Rect g_ready_rect;
extern SDL_Texture* g_game_over_texture;
extern SDL_Rect g_game_over_rect;
extern SDL_Texture* g_game_clear_texture;
extern SDL_Rect g_game_clear_rect;

//! 게임 상태
extern bool g_flag_running;
extern SDL_Renderer* g_renderer;
extern Uint32 g_frame_per_sec;

//! 게임 실행 상태
extern bool g_game_started;
extern bool g_game_over;
extern bool g_game_clear;
extern bool g_game_paused;

//! 게임 아이템 관련
extern Uint32 g_last_trap_item_time;  // 마지막으로 trap_Item이 생성된 시간
extern Uint32 g_last_cheat_item_time; // 마지막으로 cheat_Item이 생성된 시간
extern bool g_is_cheat_item_active;   // cheat_Item이 활성화 상태인지 여부