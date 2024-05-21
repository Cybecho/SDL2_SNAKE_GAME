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
void RenderReadyText();
void RenderGameOverText();

//! ���� ����
extern bool g_flag_running;
extern SDL_Renderer* g_renderer;
extern Uint32 g_frame_per_sec;
extern bool g_game_started;
extern bool g_game_over;
extern SDL_Texture* g_ready_text_texture;
extern SDL_Rect g_ready_text_rect;
extern SDL_Texture* g_game_over_text_texture;
extern SDL_Rect g_game_over_text_rect;

//! static ����
static int LEFT_SPACE = ARR_SIZE * ARR_SIZE; // ���� ������ 1�� �پ���, 0�� �Ǹ� ���� Ŭ����
// LEFT_SPACE - Player_SIZE == 0 �� �Ǹ� ����Ŭ����