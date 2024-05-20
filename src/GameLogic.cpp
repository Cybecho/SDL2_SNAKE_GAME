// GameLogic.cpp
#include "GameLogic.h"

Mix_Chunk* wave1_;
Mix_Music* music1_;

SDL_Texture* text_score_;
SDL_Rect text_score_rect_;
TTF_Font* game_font_;

SDL_Rect g_bg_source_rect;
SDL_Rect g_bg_destination_rect;

list<Player*> g_Player;
list<Item*> g_Item;

int g_input;

void InitGame() {
    g_flag_running = true;
    srand(time(NULL));

    g_input = -1;

    //! 배경 색상 설정
    g_bg_source_rect = { 0, 0, WINDOW_SIZE, WINDOW_SIZE };
    g_bg_destination_rect = { 0, 0, WINDOW_SIZE, WINDOW_SIZE };

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

void HandleEvents()
{
    SDL_Event event;
    while (SDL_PollEvent(&event))
    {
        if (event.type == SDL_QUIT)
        {
            g_flag_running = false;
        }
        else if (event.type == SDL_KEYDOWN)
        {
            switch (event.key.keysym.sym)
            {
            case SDLK_LEFT: if (g_input != RIGHT)   { g_input = LEFT; } break;
            case SDLK_RIGHT:if (g_input != LEFT)    { g_input = RIGHT;} break;
            case SDLK_UP: if (g_input != DOWN)      { g_input = UP; }   break;
            case SDLK_DOWN: if (g_input != UP)      { g_input = DOWN; } break;
            case SDLK_SPACE: g_input = -1; break; // Space 키 입력 시 방향 입력 초기화
            default: break;
            }
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
        g_flag_running = false;
    }

    // 조건 2: Player가 다른 Player 객체에 닿았을 경우
    for (auto it = ++g_Player.begin(); it != g_Player.end(); ++it) {
        Player* body = *it;
        if (head->getX() == body->getX() && head->getY() == body->getY()) {
            cout << "Game Over - Collided with body" << endl;
            //~g_flag_running = false;
            break;
        }
    }

    // 조건 3: Player가 벽에 닿았을 경우
    if (head->getX() < 0 || head->getX() >= WINDOW_SIZE || head->getY() < 0 || head->getY() >= WINDOW_SIZE) {
        cout << "Game Over - Collided with wall" << endl;
        //~ g_flag_running = false;
    }
}


void Render() {
    SDL_SetRenderDrawColor(g_renderer, 0, 0, 0, 0); // 배경색 설정
    SDL_RenderClear(g_renderer);

    // Player와 Item 렌더링
    for (auto player : g_Player) {
        player->render(g_renderer);
    }

    for (auto item : g_Item) {
        item->render(g_renderer);
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

    Mix_FreeMusic(music1_);
    Mix_FreeChunk(wave1_);

    TTF_CloseFont(game_font_);
}