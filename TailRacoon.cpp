#include "TailRacoon.h"

#include "Koopa.h"
#include "Goomba.h"
#include "QuestionBlock.h"
#include "Mario.h"

void CTailRacoon::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x - TAIL_RACOON_BBOX_WIDTH / 2;
	t = y - TAIL_RACOON_BBOX_HEIGHT / 2;
	r = l + TAIL_RACOON_BBOX_WIDTH;
	b = t + TAIL_RACOON_BBOX_HEIGHT;
	/*DebugOut(L"[TAIL BBOX] l: %f, t: %f, r: %f, b: %f\n", l, t, r, b);*/
}

void CTailRacoon::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	// Check if the tail racoon has lived long enough
	if (GetTickCount64() - startTime > lifeTime)
	{
		this->Delete();
	}

	// Update position and handle collisions
	float marioX, marioY;
	int direction;
	float oldX = x;
	float oldY = y;
	mario->GetDirection(direction);
	mario->GetPosition(marioX, marioY);

	this->x = marioX + (direction > 0 ? MARIO_TAIL_ATTACK_OFFSET_X : -MARIO_TAIL_ATTACK_OFFSET_X);
	this->y = marioY + MARIO_TAIL_ATTACK_OFFSET_Y;

	vx = (this->x - oldX) / dt;
	vy = (this->y - oldY) / dt;
	//if (vx < 0.4 && vy < 0.4)
	//{
	//	vx = (direction > 0 ? 0.4f : -0.4f); // Giữ vận tốc giả
	//}

	float tl, tt, tr, tb; // Tail bounding box
	GetBoundingBox(tl, tt, tr, tb);

	for (auto obj : *coObjects)
	{
		if (dynamic_cast<CQuestionBlock*>(obj))
		{
			float bl, bt, br, bb; // Block bounding box
			obj->GetBoundingBox(bl, bt, br, bb);

			// Check if tail's bounding box overlaps with block's bounding box
			if (tl < br && tr > bl && tt < bb && tb > bt)
			{
				OnCollisionWithQuestionBlock(new CCollisionEvent(0, 0, 0, 0, 0, obj, this));
			}
		}
	}

	CGameObject::Update(dt, coObjects);
	CCollision::GetInstance()->Process(this, dt, coObjects);
}
				
void CTailRacoon::OnCollisionWith(LPCOLLISIONEVENT e)
{
	if (dynamic_cast<CMario*>(e->obj))
	{
		// Ignore collision with Mario
		return;
	}
	
	if (dynamic_cast<CKoopa*>(e->obj))
	{
		OnCollisionWithKoopa(e);
		
	}
	else if (dynamic_cast<CGoomba*>(e->obj))
	{
		OnCollisionWithGoomba(e);
	}
	else if (dynamic_cast<CQuestionBlock*>(e->obj))
	{
		OnCollisionWithQuestionBlock(e);
		DebugOut(L"[TAIL] Collision Detected\n");
		
	}
}

void CTailRacoon::OnCollisionWithKoopa(LPCOLLISIONEVENT e)
{
	CKoopa* koopa = dynamic_cast<CKoopa*>(e->obj);
	if (koopa->GetState() != KOOPA_STATE_DIE)
	{
		koopa->SetState(KOOPA_STATE_DIE);
	}
}

void CTailRacoon::OnCollisionWithGoomba(LPCOLLISIONEVENT e)
{
	CGoomba* goomba = dynamic_cast<CGoomba*>(e->obj);
	if (goomba->GetState() != GOOMBA_STATE_DIE)
	{
		goomba->SetState(GOOMBA_STATE_DIE);
	}
}
void CTailRacoon::OnCollisionWithQuestionBlock(LPCOLLISIONEVENT e)
{
	CQuestionBlock* questionBlock = dynamic_cast<CQuestionBlock*>(e->obj);
	questionBlock->TriggerQuestionBlock();
}