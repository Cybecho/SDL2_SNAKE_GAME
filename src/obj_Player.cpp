#include "obj_Player.h"
#include "GameLogic.h"

SDL_Texture* Player::mTexture = nullptr;

Player::Player(int x, int y, int defineType, SDL_Renderer* renderer) : Obj(x, y, renderer) {
    mType = defineType;
    if (mType != Head) {
        g_score += mScore; // Head�� �ƴ� ��쿡�� ���� �߰�
    }
    cout << "Create Player , x : " << mX << " | y : " << mY << "|| Type : " << mType << endl;
}

Player::~Player() {
    g_score -= mScore; // Player ��ü �Ҹ� �� score���� mScore ����
    cout << "Delete Player" << endl;
}

void Player::update() {
    // ���� ��ġ ����
    mPrevX = mX;
    mPrevY = mY;

    Obj::update(); // �θ� Ŭ������ update() �Լ� ȣ���Ͽ� mRect ������Ʈ

    if (mDir == UP) { mY -= PLAYER_SIZE; }
    else if (mDir == DOWN) { mY += PLAYER_SIZE; }
    else if (mDir == LEFT) { mX -= PLAYER_SIZE; }
    else if (mDir == RIGHT) { mX += PLAYER_SIZE; }
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