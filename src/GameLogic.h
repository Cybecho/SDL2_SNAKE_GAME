#pragma once

#include "Include.h"
#include "obj_Base.h"
#include "obj_Player.h"
#include "obj_Item.h"

//! ���� ����Ʈ
extern list<Player*> g_Player;
extern list<Item*> g_Item;

//! �ʼ� �Լ�
void InitGame();
void HandleEvents();
void Update();
void Render();
void ClearGame();

//! ���� ����
extern bool g_flag_running;
extern SDL_Renderer* g_renderer;
extern Uint32 g_frame_per_sec;
extern int g_blockCount;
extern int SPACE[ARR_SIZE][ARR_SIZE]; // �� ������

//! static ����
static int LEFT_SPACE = ARR_SIZE*ARR_SIZE; // ���̸� ���������� 1�� �پ���, 0�� �� ��� ���� Ŭ����
// LEFT_SPACE - Player_SIZE == 0 �� ��� ����Ŭ����