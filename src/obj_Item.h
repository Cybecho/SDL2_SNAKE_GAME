#pragma once
#include "Include.h"
#include "Obj_Base.h"

class Item : public Obj {
public:
    Item(int x, int y, SDL_Renderer* renderer);
    virtual ~Item();
    void render(SDL_Renderer* renderer) const;

    //! 현재 객체 타입 반환
    int getType() const { return mType; }

protected:
    static SDL_Texture* mTexture;
};

class trap_Item : public Obj {
public:
    trap_Item(int x, int y, SDL_Renderer* renderer);
    virtual ~trap_Item();
    void render(SDL_Renderer* renderer) const;

    //! 현재 객체 타입 반환
    int getType() const { return mType; }

protected:
    static SDL_Texture* mTexture;
};

class cheat_Item : public Obj {
public:
	cheat_Item(int x, int y, SDL_Renderer* renderer);
	virtual ~cheat_Item();
	void render(SDL_Renderer* renderer) const;

	//! 현재 객체 타입 반환
    int getType() const { return mType; }
protected:
    static SDL_Texture* mTexture;
};