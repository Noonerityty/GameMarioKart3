#include "Leaf.h"
#include "debug.h"
#include "Mario.h"
#include "QuestionBlock.h"
#include "SinglePlatform.h"
void CLeaf::OnNoCollision(DWORD dt)
{
	x += direction * vx * dt;
	y += vy * dt;
}
void CLeaf::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x - LEAF_BBOX_WIDTH / 2;
	t = y - LEAF_BBOX_HEIGHT / 2;
	r = l + LEAF_BBOX_WIDTH;
	b = t + LEAF_BBOX_HEIGHT;
}

void CLeaf::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	//ULONGLONG timer = GetTickCount64();
	
	vector<LPGAMEOBJECT> marioOnly;
	for (auto obj : *coObjects)
	{
		if (dynamic_cast<CMario*>(obj))
			marioOnly.push_back(obj);
	}
	if (state == LEAF_STATE_RISING)
	{
		
		if (y <= startY - 40)
		{
			SetState(LEAF_STATE_FALLING);
		}
	}
	else if (state == LEAF_STATE_FALLING)
	{
		vy += ay * dt;
		OffsetX += abs(direction * vx * dt);
		if (OffsetX > LEAF_X_RANGE)
		{
			direction = -direction;
			OffsetX = 0;
		}
	}
	else if (state == LEAF_STATE_DIE)
	{
		this->Delete();
	}



	CGameObject::Update(dt, coObjects);
	CCollision::GetInstance()->Process(this, dt, &marioOnly);
}

void CLeaf::OnCollisionWith(LPCOLLISIONEVENT e)
{
	
	//if (dynamic_cast<CLeaf*>(e->obj)) return; // Ignore collision with other leaves
	//if (dynamic_cast<CQuestionBlock*>(e->obj)) return; // Ignore collision with question blocks
	//if (dynamic_cast<CSinglePlatform*>(e->obj)) return; // Ignore collision with single platforms

	//DebugOut(L"[LEAF] Mario hit leaf\n");


	if (dynamic_cast<CMario*>(e->obj))
	{
		if (state != LEAF_STATE_DIE)
		{
			state = LEAF_STATE_DIE;
		}
		CMario* mario = dynamic_cast<CMario*>(e->obj);
		mario->SetLevel(MARIO_LEVEL_RACOON);
	}
	if (!e->obj->IsBlocking()) return; // Ignore collision with blocking objects
	

}

void CLeaf::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case LEAF_STATE_RISING:
		vx = 0;
		vy = -LEAF_SPEED_Y;
		ay = 0;
		break;
	case LEAF_STATE_FALLING:
		vx = LEAF_SPEED_X;
		vy = 0;
		ay = LEAF_GRAVITY;
		break;
	case LEAF_STATE_DIE:
		vx = 0;
		vy = 0;
		this->Delete();
		break;
	default:
		break;


	}

}

void CLeaf::Render()
{
	int aniId = LEAF_ANI_LEFT;
	if (direction == 1)
		aniId = LEAF_ANI_RIGHT;
	CAnimations::GetInstance()->Get(aniId)->Render(x, y);

}
