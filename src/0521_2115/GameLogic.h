#pragma once

#include "Include.h"
#include "obj_Base.h"
#include "obj_Player.h"
#include "obj_Item.h"

//! ��ü ����Ʈ
extern list<Player*> g_Player;
extern list<Item*> g_Item;

//! �ʼ� �Լ�
void InitGame();
void HandleEvents();
void Update();
void Render();
void ClearGame();

//! ���� ���� ���� �Լ�
void CreatePlayer();
void CreateItem();
void ResetGame();
void CreateNewTail(Player* player);
void CreateNewItem();
void CheckGameOver();


//! ���� ����
extern int g_score; // extern ���� ����

//! ������ ���� �Լ�
SDL_Texture* LoadTexture(const char* path, SDL_Renderer* renderer, SDL_Rect& rect, int x, int y, int w, int h);
void RenderReadyTexture();
void RenderGameOverTexture();
void RenderGameClearTexture();
void RenderScore();

//! SDL �ؽ�ó
extern SDL_Texture* g_ready_texture;
extern SDL_Rect g_ready_rect;
extern SDL_Texture* g_game_over_texture;
extern SDL_Rect g_game_over_rect;
extern SDL_Texture* g_game_clear_texture;
extern SDL_Rect g_game_clear_rect;

//! ���� ����
extern bool g_flag_running;
extern SDL_Renderer* g_renderer;
extern Uint32 g_frame_per_sec;

//! ���� ���� ����
extern bool g_game_started;
extern bool g_game_over;
extern bool g_game_clear;
extern bool g_game_paused;

//! ���� ������ ����
extern Uint32 g_last_trap_item_time;  // ���������� trap_Item�� ������ �ð�
extern Uint32 g_last_cheat_item_time; // ���������� cheat_Item�� ������ �ð�
extern bool g_is_cheat_item_active;   // cheat_Item�� Ȱ��ȭ �������� ����