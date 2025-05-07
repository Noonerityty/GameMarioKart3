#pragma once
#include "GameObject.h"
#include "Mario.h"
#include "Sprites.h"
#define MUSHROOM_GRAVITY 0.002f
#define MUSHROOM_BBOX_WIDTH 16
#define MUSHROOM_BBOX_HEIGHT 15
#define MUSHROOM_SPEED_X 0.05f

#define ID_TEX_MUSHROOM 90000

#define MUSHROOM_STATE_MOVING 1
#define MUSHROOM_STATE_IDLE 0
#define MUSHROOM_STATE_DIE 2

class CMushroom : public CGameObject
{
protected:
	float ax;
	float ay;
	float startY;
	ULONGLONG spawntime;
public:
	CMushroom(float x, float y) : CGameObject(x, y)
	{
		ax = 0;
		ay = MUSHROOM_GRAVITY;
		startY = y;
	}

	void Render();
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void GetBoundingBox(float& l, float& t, float& r, float& b);
	virtual int IsBlocking() { return 0; }
	virtual int IsCollidable() { return 1; }
	void OnCollisionWith(LPCOLLISIONEVENT e);
	void SetState(int state);
	void OnNoCollision(DWORD dt);
};