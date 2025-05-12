#include "Koopa.h"

void CKoopa::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	if (state == KOOPA_STATE_SHELL_IDLE || state == KOOPA_STATE_SHELL_MOVING)
	{
		left = x - KOOPA_BBOX_SHELL_WIDTH / 2;
		top = y - KOOPA_BBOX_SHELL_HEIGHT / 2;
		right = left + KOOPA_BBOX_SHELL_WIDTH;
		bottom = top + KOOPA_BBOX_SHELL_HEIGHT;
	}
	else
	{
		left = x - KOOPA_BBOX_WIDTH / 2;
		top = y - KOOPA_BBOX_HEIGHT / 2;
		right = left + KOOPA_BBOX_WIDTH;
		bottom = top + KOOPA_BBOX_HEIGHT;
	}
}

void CKoopa::OnNoCollision(DWORD dt)
{
	x += vx * dt;
	y += vy * dt;
}

void CKoopa::OnCollisionWith(LPCOLLISIONEVENT e)
{
	if (!e->obj->IsBlocking()) return;
	if (dynamic_cast<CKoopa*>(e->obj))
	{
		CKoopa* koopa = dynamic_cast<CKoopa*>(e->obj);
		if (koopa->GetState() != KOOPA_STATE_SHELL_MOVING)
		{
			return;
		}
		else
		{
			koopa->SetState(KOOPA_STATE_DIE);
		}
	}

	if (e->ny != 0)
	{
		vy = 0;
	}
	else if (e->nx != 0)
	{
		vx = -vx;
	}
}

void CKoopa::SetState(int state)
{
	CGameObject::SetState(state);

	switch (state)
	{
	case KOOPA_STATE_WALKING:
		vx = -KOOPA_WALKING_SPEED;
		isShell = false;
		break;
	case KOOPA_STATE_SHELL_IDLE:
		vx = 0;
		isShell = true;
		state_start = GetTickCount64();
		break;
	case KOOPA_STATE_SHELL_MOVING:
		if (marioX > x)
			vx = KOOPA_WALKING_SPEED;
		else
			vx = -KOOPA_WALKING_SPEED;
		isShell = true;
		break;
	case KOOPA_STATE_SHELL_EXIT:
		vx = 0;
		isShell = false;
		state_start = GetTickCount64();
		break;
	case KOOPA_STATE_DIE:
		state_start = GetTickCount64();
		vx = 0;
		vy = 0;
		ay = 0;
		break;
	}
}

void CKoopa::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	vx += ax * dt;
	vy += ay * dt;
	if (state == KOOPA_STATE_DIE && GetTickCount64() - state_start > KOOPA_DIE_TIMEOUT)
	{
		isDeleted = true;
		return;
	}

	if (state == KOOPA_STATE_SHELL_IDLE && GetTickCount64() - state_start > KOOPA_SHELLING_TIMEOUT)
	{
		SetState(KOOPA_STATE_SHELL_EXIT);
	}

	if (state == KOOPA_STATE_SHELL_EXIT && GetTickCount64() - state_start > KOOPA_SHELL_EXIT_TIMEOUT)
	{
		SetState(KOOPA_STATE_WALKING);
	}

	CGameObject::Update(dt, coObjects);
	CCollision::GetInstance()->Process(this, dt, coObjects);
}

void CKoopa::Render()
{
	int aniId = KOOPA_ANI_WALKING;
	switch (state)
	{
	case KOOPA_STATE_WALKING:
		aniId = KOOPA_ANI_WALKING;
		break;
	case KOOPA_STATE_SHELL_IDLE:
		aniId = KOOPA_ANI_SHELL_IDLE;
		break;
	default:
		break;
	}
	CAnimations::GetInstance()->Get(aniId)->Render(x, y);
}