#pragma once

#include "GameObject.h"
#include "Mario.h"

#define TAIL_RACOON_BBOX_WIDTH 14
#define TAIL_RACOON_BBOX_HEIGHT 8

class CTailRacoon : public CGameObject
{
protected:
	float lifeTime;
	ULONGLONG startTime;
	CMario* mario;
	void OnCollisionWithKoopa(LPCOLLISIONEVENT e);
	void OnCollisionWithGoomba(LPCOLLISIONEVENT e);
	void OnCollisionWithQuestionBlock(LPCOLLISIONEVENT e);
public:
	CTailRacoon(float x, float y, CMario* mario) : CGameObject(x, y)
	{
		lifeTime = 200;
		startTime = GetTickCount64();
		this->mario = mario;

	}
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void Render() { RenderBoundingBox(); }

	virtual int IsBlocking() { return 0; }
	virtual int IsCollidable() { return 1; }

	void OnCollisionWith(LPCOLLISIONEVENT e);
	void GetBoundingBox(float& l, float& t, float& r, float& b);
};

