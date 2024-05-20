// obj_VFX.h
#pragma once
#include "Include.h"

class Obj {
public:
    Obj(int x, int y, SDL_Renderer* renderer);
    virtual ~Obj();
    void update();
    void render(SDL_Renderer* renderer) const;

    //! ���� ��ü���� ������ �޾ƿ� �����Լ� 
    //! �̰ɷ� Player ���� Item���� ����
    virtual string getType() const = 0;

private:
    int mX;
    int mY;
    int mFrame;
    int mFrameCount;
    int mFrameDelay;
    int mFrameTimer;
    Uint32 mCreateTime;
    static SDL_Texture* mTexture;
};