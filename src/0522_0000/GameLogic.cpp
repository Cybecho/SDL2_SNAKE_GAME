// GameLogic.cpp
#include "GameLogic.h"

//! SDL 텍스트 관련 함수
SDL_Texture* text_score_;
SDL_Rect text_score_rect_;
TTF_Font* game_font_;

//! 배경 이미지 (rect로 solid색상을 구현)
SDL_Rect g_bg_source_rect;
SDL_Rect g_bg_destination_rect;

//! Game Ready Texture
SDL_Texture* g_ready_texture = nullptr;
SDL_Rect g_ready_rect;

//! Game Over Texture
SDL_Texture* g_game_over_texture = nullptr;
SDL_Rect g_game_over_rect;

//! Game Clear Texture
SDL_Texture* g_game_clear_texture = nullptr;
SDL_Rect g_game_clear_rect;

//! 게임 객체 연결리스트
list<Player*> g_Player;
list<Item*> g_Item;
list<trap_Item*> g_TrapItem;
list<cheat_Item*> g_CheatItem;

//!************************** extern 변수 초기화 **************************
bool g_game_started = false;    // 게임 시작 여부
bool g_game_over = false;       // 게임 오버 여부
bool g_game_clear = false;      // 게임 클리어 여부 (추가)
bool g_game_paused = false;     // 게임 일시정지 여부
int g_input;                    // 플레이어 입력  
int g_score;                    // 점수

//!************************** 기본 게임 상태 함수 **************************

void InitGame() {
    g_flag_running = true;
    srand(time(NULL));

    g_input = -1;
    g_score = 0; // 점수 초기화

    //! 배경 색상 설정
    g_bg_source_rect = { 0, 0, WINDOW_SIZE, WINDOW_SIZE };
    g_bg_destination_rect = { 0, 0, WINDOW_SIZE, WINDOW_SIZE };

    g_game_started = false;
    g_game_over = false;

    //! Game Ready Texture
    g_ready_texture = LoadTexture("../../res/GameReady.png", g_renderer, g_ready_rect, WINDOW_SIZE / 2 - 50, WINDOW_SIZE / 2 - 50, 100, 100);

    //! Game Over Texture
    g_game_over_texture = LoadTexture("../../res/GameOver.png", g_renderer, g_game_over_rect, WINDOW_SIZE / 2 - 75, WINDOW_SIZE / 2 - 50, 150, 100);

    //! Game Clear Texture
    g_game_clear_texture = LoadTexture("../../res/GameClear.png", g_renderer, g_game_clear_rect, WINDOW_SIZE / 2 - 75, WINDOW_SIZE / 2 - 50, 150, 100);

    //! Player 객체 생성
    CreatePlayer();

    //! Item 객체 생성
    CreateItem();
}

void HandleEvents() {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT) {
            g_flag_running = false;
        }
        else if (event.type == SDL_KEYDOWN && !g_game_started && !g_game_over && !g_game_clear) {
            g_game_started = true;
        }
        //~ GameReady로 전환 시 플레이어 위치 초기화 및 방향 초기화
        else if (event.type == SDL_MOUSEBUTTONDOWN && event.button.button == SDL_BUTTON_LEFT && (g_game_over || g_game_clear)) {
            ResetGame();
        }
        else if (event.type == SDL_KEYDOWN && g_game_started && !g_game_over && !g_game_clear) {
            switch (event.key.keysym.sym) {
            case SDLK_LEFT: if (g_input != RIGHT && !g_game_paused) { g_input = LEFT; } break;
            case SDLK_RIGHT: if (g_input != LEFT && !g_game_paused) { g_input = RIGHT; } break;
            case SDLK_UP: if (g_input != DOWN && !g_game_paused) { g_input = UP; } break;
            case SDLK_DOWN: if (g_input != UP && !g_game_paused) { g_input = DOWN; } break;
            case SDLK_SPACE: g_game_clear = true; g_game_paused = true;  break;
            case SDLK_p: g_game_paused = !g_game_paused; break;
            default: break;
            }
        }
    }
}

void Update() {
    if (!g_game_paused) {
        // Player와 Item 업데이트
        for (auto player : g_Player) {
            if (player->getType() == Head) { // Head 타입의 Player만 입력 방향 설정
                player->setDir(g_input);
            }
            player->update();
        }
    }
    for (auto item : g_Item) {
        item->update();
    }

    // Player와 Item 충돌 감지
    for (auto player : g_Player) {                  //~ 모든 Player 객체들에 대해
        for (auto item : g_Item) {                  //~ 모든 Player당 Item 객체들에 대해
            if (player->getType() == Head &&        //~ 현재 Player 객체가 Head 타입이고
                player->getX() == item->getX() &&   //~ 현재 Player 객체의 X 위치와
                player->getY() == item->getY())     //~ 현재 Player 객체의 Y 위치가 Item 객체의 위치와 같을 경우
            {
                //~ 충돌한 Item 객체 소멸
                g_Item.remove(item);
                delete item;

                // 새로운 꼬리 Player 객체 생성
                CreateNewTail(player);

                // 새로운 Item 객체 생성
                CreateNewItem();

                break;
            }
        }
    }

    // 꼬리 Player 객체 움직임 처리
    for (auto it = ++g_Player.begin(); it != g_Player.end(); ++it) {    // Head를 제외한 Player 객체들은
        Player* prevPlayer = *(prev(it));                               // 이전 Player 객체의 위치로 이동
        Player* currentPlayer = *it;                                    // 이전 Player 객체의 위치를 저장
        currentPlayer->setX(prevPlayer->getPrevX());                    // X 재 Player 객체의 위치를 이전 Player 객체의 위치로 설정
        currentPlayer->setY(prevPlayer->getPrevY());                    // Y 현재 Player 객체의 위치를 이전 Player 객체의 위치로 설정
    }

    CheckGameOver();
}

void Render() {
    SDL_SetRenderDrawColor(g_renderer, 0, 0, 0, 255);
    SDL_RenderClear(g_renderer);
    RenderScore();

    if (!g_game_started) {
        RenderReadyTexture();
    }
    else {
        for (auto player : g_Player) {
            player->render(g_renderer);
        }

        for (auto item : g_Item) {
            item->render(g_renderer);
        }

        if (g_game_over) {
            RenderGameOverTexture();
        }
        else if (g_game_clear) {
            RenderGameClearTexture();
        }
    }
    SDL_RenderPresent(g_renderer);

}

void ClearGame() {
    // Player와 Item 메모리 해제
    for (auto player : g_Player) {
        delete player;
    }
    g_Player.clear();

    for (auto item : g_Item) {
        delete item;
    }
    g_Item.clear();

    TTF_CloseFont(game_font_);
    SDL_DestroyTexture(g_ready_texture);
    SDL_DestroyTexture(g_game_over_texture);
    SDL_DestroyTexture(g_game_clear_texture);
}

//!************************** 게임 로직 관련 함수 **************************

void CreatePlayer() {
    Player* player = new Player((WINDOW_SIZE / 2 + PLAYER_SIZE), (WINDOW_SIZE / 2 + PLAYER_SIZE), Head, g_renderer);
    g_Player.push_back(player);
}

void CreateItem() {
    int itemX, itemY;
    do {
        itemX = rand() % WINDOW_SIZE / 10 * 10;
        itemY = rand() % WINDOW_SIZE / 10 * 10;
    } while (itemX == g_Player.front()->getX() && itemY == g_Player.front()->getY());

    Item* item = new Item(itemX, itemY, g_renderer);
    g_Item.push_back(item);
}

void ResetGame() {
    g_game_over = false;
    g_game_clear = false;
    g_game_started = false;
    g_game_paused = false;

    // 꼬리 부분 제거
    auto it = ++g_Player.begin();
    while (it != g_Player.end()) {
        Player* tail = *it;
        it = g_Player.erase(it);
        delete tail;
    }

    ClearGame();
    InitGame();
}

void CreateNewTail(Player* player) {
    Player* newTail = new Player(player->getPrevX(), player->getPrevY(), BODY, g_renderer);
    g_Player.push_back(newTail);
    cout << "Size : " << g_Player.size() << " / " << ARR_SIZE * ARR_SIZE << " | Score :  " << g_score << endl;
}

void CreateNewItem() {
    int newItemX, newItemY;
    bool isValidPosition;
    do {
        newItemX = rand() % WINDOW_SIZE / 10 * 10;
        newItemY = rand() % WINDOW_SIZE / 10 * 10;
        isValidPosition = true;
        for (auto p : g_Player) {
            if (newItemX == p->getX() && newItemY == p->getY()) {
                isValidPosition = false;
                break;
            }
        }
    } while (!isValidPosition);

    Item* newItem = new Item(newItemX, newItemY, g_renderer);
    g_Item.push_back(newItem);
}

void CheckGameOver() {
    Player* head = g_Player.front();

    // 조건 1: g_Player 크기가 ARR_SIZE*ARR_SIZE와 같을 경우 (게임 클리어)
    if (g_Player.size() == ARR_SIZE * ARR_SIZE) {
        cout << "Game Clear!" << endl;
        g_game_clear = true;
    }
    // 조건 2: Player가 다른 Player 객체에 닿았을 경우 (게임 오버)
    for (auto it = ++g_Player.begin(); it != g_Player.end(); ++it) {
        Player* body = *it;
        if (head->getX() == body->getX() && head->getY() == body->getY()) {
            cout << "Game Over - Collided with body" << endl;
            g_game_over = true;
            g_game_paused = true; // 게임 오버 시 일시 정지 상태로 설정
            break;
        }
    }

    // 조건 3: Player가 벽에 닿았을 경우 (게임 오버)
    if (head->getX() < 0 || head->getX() >= WINDOW_SIZE || head->getY() < 0 || head->getY() >= WINDOW_SIZE) {
        cout << "Game Over - Collided with wall" << endl;
        g_game_over = true;
        g_game_paused = true; // 게임 오버 시 일시 정지 상태로 설정
    }
}

//!************************** 렌더링 관련 함수 **************************

SDL_Texture* LoadTexture(const char* path, SDL_Renderer* renderer, SDL_Rect& rect, int x, int y, int w, int h) {
    SDL_Surface* surface = IMG_Load(path);
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_SetTextureBlendMode(texture, SDL_BLENDMODE_BLEND);
    SDL_FreeSurface(surface);
    rect = { x, y, w, h };
    return texture;
}

void RenderReadyTexture() {
    SDL_SetRenderDrawBlendMode(g_renderer, SDL_BLENDMODE_BLEND); // 블렌드 모드로 설정해야 뒷 배경이 보임
    SDL_RenderCopy(g_renderer, g_ready_texture, nullptr, &g_ready_rect);
}

void RenderGameOverTexture() {
    SDL_SetRenderDrawBlendMode(g_renderer, SDL_BLENDMODE_BLEND); // 블렌드 모드로 설정해야 뒷 배경이 보임
    SDL_RenderCopy(g_renderer, g_game_over_texture, nullptr, &g_game_over_rect);
}

void RenderGameClearTexture() {
    SDL_SetRenderDrawBlendMode(g_renderer, SDL_BLENDMODE_BLEND); // 블렌드 모드로 설정해야 뒷 배경이 보임
    SDL_RenderCopy(g_renderer, g_game_clear_texture, nullptr, &g_game_clear_rect);
}

void RenderScore() {
    SDL_Color textColor = { 255, 255, 255, 255 };
    string scoreText = "Score: " + string(10 - to_string(g_score).length(), '0') + to_string(g_score);

    // 폰트 로드
    TTF_Font* scoreFont = TTF_OpenFont("../../res/FFFFORWA.TTF", 16);
    if (scoreFont == nullptr) {
        cout << "Failed to load font: " << TTF_GetError() << endl;
        return;
    }

    SDL_Surface* textSurface = TTF_RenderText_Solid(scoreFont, scoreText.c_str(), textColor);
    SDL_Texture* textTexture = SDL_CreateTextureFromSurface(g_renderer, textSurface);
    int textWidth = textSurface->w;
    int textHeight = textSurface->h;
    SDL_Rect textRect = { WINDOW_SIZE - textWidth - 10, 10, textWidth, textHeight }; // 오른쪽 상단에 위치
    SDL_RenderCopy(g_renderer, textTexture, nullptr, &textRect);

    // 사용한 자원 해제
    SDL_FreeSurface(textSurface);
    SDL_DestroyTexture(textTexture);
    TTF_CloseFont(scoreFont);
}