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
    // ���� ��ġ ����
    mPrevX = mX;
    mPrevY = mY;

    if (mDir == UP) { mY -= PLAYER_SIZE; }
    else if (mDir == DOWN) { mY += PLAYER_SIZE; }
	else if (mDir == LEFT) { mX -= PLAYER_SIZE; }
	else if (mDir == RIGHT) { mX += PLAYER_SIZE; }
    
    Obj::update(); // �θ� Ŭ������ update() �Լ� ȣ���Ͽ� mRect ������Ʈ
}

//! �� ����̺� ��ü�� ����
void Player::render(SDL_Renderer* renderer) const {
    if(mType == Head) {
		SDL_SetRenderDrawColor(renderer, 255 , 0, 0, 255); // �Ӹ���� ������
	} else {
		SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255); // �����̶�� ���
	}
    
    SDL_RenderFillRect(renderer, &mRect);
}