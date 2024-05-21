#include "obj_Base.h"

SDL_Texture* Obj::mTexture = nullptr;

Obj::Obj(int x, int y, SDL_Renderer* renderer) : mX(x), mY(y) {
    mRect = { x, y, PLAYER_SIZE, PLAYER_SIZE };
    // cout << "Create Obj" << endl;
}

Obj::~Obj() {
    // cout << "Delete Obj" << endl;
}

void Obj::update() {
	mRect.x = mX;
	mRect.y = mY;
}