#pragma once
#include "Include.h"
#include "Obj_Base.h"

class Item : public Obj {
public:
    Item(int x, int y, SDL_Renderer* renderer);
    virtual ~Item();
    void update();
    void render(SDL_Renderer* renderer) const;

    //! ���� ��ü Ÿ�� ��ȯ
    string getType() const { return "Item"; }

protected:
    static SDL_Texture* mTexture;
};