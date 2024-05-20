#pragma once
#include "Include.h"
#include "Obj_Base.h"

class Player : public Obj {
public:
    Player(int x, int y, int defineType, SDL_Renderer* renderer);
    virtual ~Player();
    void update();
    void render(SDL_Renderer* renderer) const;

    //! ���� ��ü Ÿ�� ��ȯ
    int getType() const { return mType; }

protected:
    static SDL_Texture* mTexture;
};