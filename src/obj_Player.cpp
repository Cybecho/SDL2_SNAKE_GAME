#include "obj_Player.h"

SDL_Texture* Player::mTexture = nullptr;

Player::Player(int x, int y, int defineType, SDL_Renderer* renderer) : Obj(x, y, renderer) {
    mType = defineType;
    cout << "Create Player , x : " << mX << " | y : " << mY << "|| Type : " << mType << endl;
}

Player::~Player() {
    cout << "Delete Player" << endl;
}

void Player::update() {
    // 이전 위치 저장
    mPrevX = mX;
    mPrevY = mY;

    if (mDir == UP) { mY -= PLAYER_SIZE; }
    else if (mDir == DOWN) { mY += PLAYER_SIZE; }
	else if (mDir == LEFT) { mX -= PLAYER_SIZE; }
	else if (mDir == RIGHT) { mX += PLAYER_SIZE; }
    
    Obj::update(); // 부모 클래스의 update() 함수 호출하여 mRect 업데이트
}

//! 각 드라이브 객체에 생성
void Player::render(SDL_Renderer* renderer) const {
    if(mType == Head) {
		SDL_SetRenderDrawColor(renderer, 255 , 0, 0, 255); // 머리라면 빨간색
	} else {
		SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255); // 몸통이라면 흰색
	}
    
    SDL_RenderFillRect(renderer, &mRect);
}