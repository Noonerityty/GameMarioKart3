#include "PiranhaBullet.h"



void CPiranhaBullet::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	x += vx * dt;
	y += vy * dt;

	CGameObject::Update(dt, coObjects);
	CCollision::GetInstance()->Process(this, dt, coObjects);
}

void CPiranhaBullet::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x;
	t = y;
	r = x + PIRANHA_BULLET_BBOX_WIDTH;
	b = y + PIRANHA_BULLET_BBOX_HEIGHT;
}

void CPiranhaBullet::Render()
{
	CAnimations::GetInstance()->Get(115001)->Render(x, y);
}