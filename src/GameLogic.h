#pragma once
#define WINDOW_SIZE 500						// ������ ������
#define PLAYER_SIZE 10						// ĳ���� ������
#define ARR_SIZE WINDOW_SIZE / PLAYER_SIZE	// �迭 ������ (������ ������ / ĳ���� ������)

#include "Include.h"

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
static int LEFT_SPACE = ARR_SIZE; // 0�� �� ��� ���� Ŭ����
// LEFT_SPACE - Player_SIZE == 0 �� ��� ����Ŭ����
