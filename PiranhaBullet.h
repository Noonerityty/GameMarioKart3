#pragma once
#include "GameObject.h"


#define PIRANHA_BULLET_BBOX_WIDTH  7
#define PIRANHA_BULLET_BBOX_HEIGHT 7

class CPiranhaBullet : public CGameObject
{
	
public:
	CPiranhaBullet(float x, float y, float vx, float vy) : CGameObject(x, y)
	{
		this->vx = vx;
		this->vy = vy;
	}
	void Render();
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void GetBoundingBox(float& l, float& t, float& r, float& b);
	virtual int IsBlocking() { return 0; }
	virtual int IsCollidable() { return 1; }
};
