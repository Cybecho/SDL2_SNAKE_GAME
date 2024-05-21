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

//! ������ ���� �Լ�
void RenderReadyTexture();
void RenderGameOverTexture();
void RenderGameClearTexture();

//! ���� ����
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

//! static ����
static int LEFT_SPACE = ARR_SIZE * ARR_SIZE; // ���� ������ 1�� �پ���, 0�� �Ǹ� ���� Ŭ����
// LEFT_SPACE - Player_SIZE == 0 �� �Ǹ� ����Ŭ����