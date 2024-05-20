#pragma once
#include "Include.h"
#include "Obj_Base.h"

class Player : public Obj {
public:
    Player(int x, int y, int defineType, SDL_Renderer* renderer);
    virtual ~Player();
    void update();
    void render(SDL_Renderer* renderer) const;

    //! 현재 객체 타입 반환
    string getType() const { return "Player"; }

protected:
    static SDL_Texture* mTexture;
};