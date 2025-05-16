#pragma once
#include "GameObject.h"

#define LEAF_GRAVITY 0.00005f
#define LEAF_BBOX_WIDTH 15
#define LEAF_BBOX_HEIGHT 13

#define LEAF_ANI_LEFT 135001
#define LEAF_ANI_RIGHT 135002

#define LEAF_STATE_RISING 677
#define LEAF_STATE_FALLING 678
#define LEAF_STATE_DIE 679

#define LEAF_SPEED_X 0.05f
#define LEAF_SPEED_Y 0.08f

#define LEAF_X_RANGE 15.0f

class CLeaf : public CGameObject
{
protected:
	float ax;
	float ay;
	float startY;
	ULONGLONG spawntime;
	int direction = -1;
	float OffsetX = 0;
	
public:
	CLeaf(float x, float y) : CGameObject(x, y)
	{
		ax = 0;
		ay = LEAF_GRAVITY;
		startY = y;
		spawntime = GetTickCount64();
		
	
	}

	void Render();
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void GetBoundingBox(float& l, float& t, float& r, float& b);
	 int IsBlocking() override{ return 0; }
	int IsCollidable() override { return 1; }
	void SetState(int state);
	void OnNoCollision(DWORD dt);
	void OnCollisionWith(LPCOLLISIONEVENT e);

};