#pragma once
#include "Include.h"

enum Type { Head, BODY, ITEM}; // 객체의 타입을 나타내는 열거형

class Obj {
public:
    Obj() {} // 기본 생성자 추가
    Obj(int x, int y, SDL_Renderer* renderer);
    virtual ~Obj();
    void update();
    virtual void render(SDL_Renderer* renderer) const = 0;

    //! getter, setter
    void setX(int x) { mX = x; }
    void setY(int y) { mY = y; }
    void setPos(int x, int y) { mPos[x][y]; }
    void setDir(int dir) { mDir = dir; }
	int getX() const { return mX; }
    int getY() const { return mY; }
    int getPrevX() const { return mPrevX; }
    int getPrevY() const { return mPrevY; }
    int getPos(int x, int y) const { return mPos[x][y]; }
    int getDir() const { return mDir; }

    //! 하위 객체들의 정보를 받아올 가상함수 
    virtual string getType() const = 0; //~ 이걸로 Player 인지 Item인지 구분

protected:
    //! 위치 관련
    int mX;     // 현재 x좌표
    int mY;     // 현재 y좌표
    int mPrevX; // 이전 x좌표
    int mPrevY; // 이전 y좌표
    int mPos[ARR_SIZE][ARR_SIZE]; // 2차원 배열로 좌표를 받아올 수 있게 함
    int mDir; // 방향 (현재 자신의 Head에 위치하는 mDir의 내용을 상속받음)
    

    //! 상태 관련
    int mType;          // 객체의 타입 (Head, Body, Item)
    bool isWall;        // 벽인가? 
    bool isItem;        // 아이템 타입인가? (아니라면 몸통)
    bool isClear;       // 죽지 않았고, 더이상 아이템이 나올 수 없을때
    bool isHead = 0;    // 머리인가? 1이라면 머리, 머리라면 Head, 몸통이라면 Body

    //! 프레임 관련
    int mFrame;
    int mFrameCount;
    int mFrameDelay;
    int mFrameTimer;
    Uint32 mCreateTime;
    
    //! 텍스처 관련
    SDL_Rect mRect; // 렌더링할 위치
    static SDL_Texture* mTexture;
};