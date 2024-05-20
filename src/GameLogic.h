#pragma once

#include "Include.h"
#include "obj_Base.h"
#include "obj_Player.h"
#include "obj_Item.h"

//! 연결 리스트
extern list<Player*> g_Player;
extern list<Item*> g_Item;

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
static int LEFT_SPACE = ARR_SIZE*ARR_SIZE; // 먹이를 먹을때마다 1씩 줄어들며, 0이 될 경우 게임 클리어
// LEFT_SPACE - Player_SIZE == 0 일 경우 게임클리어