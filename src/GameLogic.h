#pragma once
#define WINDOW_SIZE 500						// 윈도우 사이즈
#define PLAYER_SIZE 10						// 캐릭터 사이즈
#define ARR_SIZE WINDOW_SIZE / PLAYER_SIZE	// 배열 사이즈 (윈도우 사이즈 / 캐릭터 사이즈)

#include "Include.h"

//! 필수 함수
void InitGame();
void HandleEvents();
void Update();
void Render();
void ClearGame();

//! 전역 변수
extern bool g_flag_running;
extern SDL_Renderer* g_renderer;
extern Uint32 g_frame_per_sec;
extern int g_blockCount;
extern int SPACE[ARR_SIZE][ARR_SIZE]; // 맵 사이즈

//! static 변수
static int LEFT_SPACE = ARR_SIZE; // 0이 될 경우 게임 클리어
// LEFT_SPACE - Player_SIZE == 0 일 경우 게임클리어
