#pragma once
#include "Include.h"

enum Type { Head, BODY, ITEM}; // ��ü�� Ÿ���� ��Ÿ���� ������

class Obj {
public:
    Obj() {} // �⺻ ������ �߰�
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

    //! ���� ��ü���� ������ �޾ƿ� �����Լ� 
    virtual string getType() const = 0; //~ �̰ɷ� Player ���� Item���� ����

protected:
    //! ��ġ ����
    int mX;     // ���� x��ǥ
    int mY;     // ���� y��ǥ
    int mPrevX; // ���� x��ǥ
    int mPrevY; // ���� y��ǥ
    int mPos[ARR_SIZE][ARR_SIZE]; // 2���� �迭�� ��ǥ�� �޾ƿ� �� �ְ� ��
    int mDir; // ���� (���� �ڽ��� Head�� ��ġ�ϴ� mDir�� ������ ��ӹ���)
    

    //! ���� ����
    int mType;          // ��ü�� Ÿ�� (Head, Body, Item)
    bool isWall;        // ���ΰ�? 
    bool isItem;        // ������ Ÿ���ΰ�? (�ƴ϶�� ����)
    bool isClear;       // ���� �ʾҰ�, ���̻� �������� ���� �� ������
    bool isHead = 0;    // �Ӹ��ΰ�? 1�̶�� �Ӹ�, �Ӹ���� Head, �����̶�� Body

    //! ������ ����
    int mFrame;
    int mFrameCount;
    int mFrameDelay;
    int mFrameTimer;
    Uint32 mCreateTime;
    
    //! �ؽ�ó ����
    SDL_Rect mRect; // �������� ��ġ
    static SDL_Texture* mTexture;
};