// GameLogic.cpp
#include "GameLogic.h"

//! SDL 사운드 관련 변수
Mix_Chunk* wave1_;

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

//! extern 변수 초기화
bool g_game_started = false;    // 게임 시작 여부
bool g_game_over = false;       // 게임 오버 여부
bool g_game_clear = false;      // 게임 클리어 여부 (추가)
int g_input;                    // 플레이어 입력  

void InitGame() {
    g_flag_running = true;
    srand(time(NULL));

    g_input = -1;

    //! 배경 색상 설정
    g_bg_source_rect = { 0, 0, WINDOW_SIZE, WINDOW_SIZE };
    g_bg_destination_rect = { 0, 0, WINDOW_SIZE, WINDOW_SIZE };

    g_game_started = false;
    g_game_over = false;

    //! Game Ready Texture
    SDL_Surface* ready_surface = IMG_Load("../../res/GameReady.png");
    g_ready_texture = SDL_CreateTextureFromSurface(g_renderer, ready_surface);
    SDL_FreeSurface(ready_surface);
    g_ready_rect = { WINDOW_SIZE / 2 - 50, WINDOW_SIZE / 2 - 50, 100, 100 };

    //! Game Over Texture
    SDL_Surface* game_over_surface = IMG_Load("../../res/GameOver.png");
    g_game_over_texture = SDL_CreateTextureFromSurface(g_renderer, game_over_surface);
    SDL_FreeSurface(game_over_surface);
    g_game_over_rect = { WINDOW_SIZE / 2 - 75, WINDOW_SIZE / 2 - 50, 150, 100 };

    //! Game Clear Texture
    SDL_Surface* game_clear_surface = IMG_Load("../../res/GameClear.png");
    g_game_clear_texture = SDL_CreateTextureFromSurface(g_renderer, game_clear_surface);
    SDL_FreeSurface(game_clear_surface);
    g_game_clear_rect = { WINDOW_SIZE / 2 - 75, WINDOW_SIZE / 2 - 50, 150, 100 };

    //! Player 객체 생성
    Player* player = new Player( (WINDOW_SIZE/2 + PLAYER_SIZE) , (WINDOW_SIZE / 2+PLAYER_SIZE) , Head , g_renderer);
    g_Player.push_back(player);

    //! Item 객체 생성
    int itemX, itemY;
    do {
        itemX = rand() % WINDOW_SIZE / 10 * 10;
        itemY = rand() % WINDOW_SIZE / 10 * 10;
    } while (itemX == player->getX() && itemY == player->getY());

    Item* item = new Item(itemX, itemY, g_renderer);
    g_Item.push_back(item);
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
        else if (event.type == SDL_MOUSEBUTTONDOWN && event.button.button == SDL_BUTTON_LEFT && (g_game_over || g_game_clear)) {
            g_game_over = false;
            g_game_clear = false;
            g_game_started = false;
            ClearGame();
            InitGame();
        }
        else if (event.type == SDL_KEYDOWN && g_game_started && !g_game_over) {
            switch (event.key.keysym.sym) {
            case SDLK_LEFT: if (g_input != RIGHT) { g_input = LEFT; } break;
            case SDLK_RIGHT:if (g_input != LEFT) { g_input = RIGHT; } break;
            case SDLK_UP: if (g_input != DOWN) { g_input = UP; } break;
            case SDLK_DOWN: if (g_input != UP) { g_input = DOWN; } break;
            case SDLK_SPACE: g_input = -1; break;
            default: break; }
        }
    }
}

void Update() {
    // Player와 Item 업데이트
    for (auto player : g_Player) {
        if (player->getType() == Head) { // Head 타입의 Player만 입력 방향 설정
            player->setDir(g_input);
        }
        player->update();
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
                Player* newTail = new Player(player->getX(), player->getY(), BODY, g_renderer);
                g_Player.push_back(newTail);
                cout << "Size : " << g_Player.size() << " / " << ARR_SIZE * ARR_SIZE << endl;

                // 새로운 Item 객체 생성
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

    //~ 게임 오버 조건 처리
    Player* head = g_Player.front();

    // 조건 1: g_Player 크기가 ARR_SIZE*ARR_SIZE와 같을 경우
    if (g_Player.size() == ARR_SIZE * ARR_SIZE) {
        cout << "Game Clear!" << endl;
        g_game_clear = true;
    }
    // 조건 2: Player가 다른 Player 객체에 닿았을 경우
    for (auto it = ++g_Player.begin(); it != g_Player.end(); ++it) {
        Player* body = *it;
        if (head->getX() == body->getX() && head->getY() == body->getY()) {
            cout << "Game Over - Collided with body" << endl;
            g_game_over = true;
            break;
        }
    }

    // 조건 3: Player가 벽에 닿았을 경우
    if (head->getX() < 0 || head->getX() >= WINDOW_SIZE || head->getY() < 0 || head->getY() >= WINDOW_SIZE) {
        cout << "Game Over - Collided with wall" << endl;
        g_game_over = true;
    }

    // 게임 오버 상태일 때 플레이어 위치 초기화 및 방향 초기화
    if (g_game_over) {
        head->setX(WINDOW_SIZE / 2 + PLAYER_SIZE);
        head->setY(WINDOW_SIZE / 2 + PLAYER_SIZE);
        head->setDir(-1);

        // 꼬리 부분 제거
        auto it = ++g_Player.begin();
        while (it != g_Player.end()) {
            Player* tail = *it;
            it = g_Player.erase(it);
            delete tail;
        }
    }
}


void Render() {
    SDL_SetRenderDrawColor(g_renderer, 0, 0, 0, 255);
    SDL_RenderClear(g_renderer);

    if (!g_game_started) {
        RenderReadyTexture();
    }
    else {
        if (g_game_over) {
            RenderGameOverTexture();
        }
        else if (g_game_clear) {
            RenderGameClearTexture();
        }
        else {
            for (auto player : g_Player) {
                player->render(g_renderer);
            }

            for (auto item : g_Item) {
                item->render(g_renderer);
            }
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

    Mix_FreeChunk(wave1_);
    TTF_CloseFont(game_font_);
    SDL_DestroyTexture(g_ready_texture);
    SDL_DestroyTexture(g_game_over_texture);
    SDL_DestroyTexture(g_game_clear_texture);
}

void RenderReadyTexture() {
    SDL_RenderCopy(g_renderer, g_ready_texture, nullptr, &g_ready_rect);
}

void RenderGameOverTexture() {
    SDL_RenderCopy(g_renderer, g_game_over_texture, nullptr, &g_game_over_rect);
}

void RenderGameClearTexture() {
    SDL_RenderCopy(g_renderer, g_game_clear_texture, nullptr, &g_game_clear_rect);
}