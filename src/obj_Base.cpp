#include "obj_Base.h"

SDL_Texture* Obj::mTexture = nullptr;

Obj::Obj(int x, int y, SDL_Renderer* renderer){
    cout << "Create Obj" << endl;
}

Obj::~Obj() {
    cout << "Delete Obj" << endl;
}

void Obj::update() {
}

void Obj::render(SDL_Renderer* renderer) const {
    SDL_SetRenderDrawColor(g_renderer, 255, 255, 255, 255); // 캐릭터 기본 색상
    SDL_RenderClear(g_renderer);


    SDL_RenderPresent(g_renderer);
}