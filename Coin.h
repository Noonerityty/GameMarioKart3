#pragma once

#include "GameObject.h"
#include "Animation.h"
#include "Animations.h"
#define ID_ANI_COIN_IDLE 11000
#define ID_ANI_COIN_JUMP 11001

#define	COIN_WIDTH 10
#define COIN_BBOX_WIDTH 10
#define COIN_BBOX_HEIGHT 16
#define COIN_STATE_JUMP 1
#define COIN_JUMP_SPEED 0.6f
#define COIN_JUMP_HEIGHT 80
#define GRAVITY 0.002f

class CCoin : public CGameObject {
protected:

	float startY;
	bool isFalling;

public:
	CCoin(float x, float y, int state) : CGameObject(x, y) { this->state = state; startY = y; }
	void Render();
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void GetBoundingBox(float& l, float& t, float& r, float& b);
	int IsBlocking() { return 0; }
	virtual int IsCollidable() { return 1; }
	void SetState(int state);
};