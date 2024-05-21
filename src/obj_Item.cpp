#include "obj_Item.h"

//! ************************** positive Item **************************
SDL_Texture* Item::mTexture = nullptr;
Item::Item(int x, int y, SDL_Renderer* renderer) : Obj(x, y, renderer) {
    mType = ITEM;
    cout << "Create Item , x : " << mX << " | y : " << mY << "|| Type : " << mType << endl;
}
Item::~Item() {
    cout << "Delete Item" << endl;
}
void Item::render(SDL_Renderer* renderer) const {
    SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255); // 아이템 이라면 파란색으로

    SDL_RenderFillRect(renderer, &mRect);
}

//! ************************** negative Item **************************
SDL_Texture* trap_Item::mTexture = nullptr;
trap_Item::trap_Item(int x, int y, SDL_Renderer* renderer) : Obj(x, y, renderer) {
	mType = ITEM;
	cout << "Create trap_Item , x : " << mX << " | y : " << mY << "|| Type : " << mType << endl;
}
trap_Item::~trap_Item() {
	cout << "Delete trap_Item" << endl;
}
void trap_Item::render(SDL_Renderer* renderer) const {
	SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255); // 함정 아이템 이라면 초록색으로

	SDL_RenderFillRect(renderer, &mRect);
}

//! ************************** cheat Item **************************
SDL_Texture* cheat_Item::mTexture = nullptr;
cheat_Item::cheat_Item(int x, int y, SDL_Renderer* renderer) : Obj(x, y, renderer) {
	mType = ITEM;
	cout << "Create cheat_Item , x : " << mX << " | y : " << mY << "|| Type : " << mType << endl;
}
cheat_Item::~cheat_Item() {
	cout << "Delete cheat_Item" << endl;
}
void cheat_Item::render(SDL_Renderer* renderer) const {
	SDL_SetRenderDrawColor(renderer, 255, 127, 0, 255); // 치트 아이템 이라면 주황색으로

	SDL_RenderFillRect(renderer, &mRect);
}