#include "obj_Item.h"

SDL_Texture* Item::mTexture = nullptr;

Item::Item(int x, int y, SDL_Renderer* renderer) : Obj(x, y, renderer) {
    mType = ITEM;
    cout << "Create Item , x : " << mX << " | y : " << mY << "|| Type : " << mType << endl;
}

Item::~Item() {
    cout << "Delete Item" << endl;
}

void Item::update() {

}

//! 각 드라이브 객체에 생성
void Item::render(SDL_Renderer* renderer) const {
    SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255); // 아이템 이라면 파란색으로

    SDL_RenderFillRect(renderer, &mRect);
}