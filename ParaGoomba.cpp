#include "ParaGoomba.h"

void CParaGoomba::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	vy += ay * dt;
	vx += ax * dt;

	switch (state)
	{
	case PARAGOOMBA_STATE_WALKING_WING:
		isWinged = true;
		if (GetTickCount64() - stateStart > PARAGOOMBA_WALKING_WING_TIME)
		{
			SetState(PARAGOOMBA_STATE_JUMPNG);
		}
		break;
	case PARAGOOMBA_STATE_JUMPNG:
		isWinged = true;
		if (jumpCount < PARAGOOMBA_SMALL_JUMP_COUNT)
		{
			jumpCount++;
			vy = PARAGOOMBA_SMALL_JUMP_Y;
			
		}
		else
		{
			jumpCount = 0;
			vy = PARAGOOMBA_BIG_JUMP_Y;
		}
		SetState(PARAGOOMBA_STATE_WALKING_WING);
		break;
	case PARAGOOMBA_STATE_WALKING_NO_WING:
		isWinged = false;
		break;
	case PARAGOOMBA_STATE_DIE:
		if (isWinged)
		{
			isWinged = false;
			SetState(PARAGOOMBA_STATE_WALKING_NO_WING);

		}
		else
		{
			isWinged = false;
			if (GetTickCount64() - die_start > PARAGOOMBA_DIE_TIMEOUT)
			{
				isDeleted = true;
				return;
			}
		}
		break;
	}




	//if (isWinged)
	//{
	//	if (GetTickCount64() - lastJumpTime > PARAGOOMBA_JUMP_TIME)
	//	{
	//		if (jumpCount < PARAGOOMBA_SMALL_JUMP_COUNT)
	//		{
	//			jumpCount++;
	//			vy = PARAGOOMBA_SMALL_JUMP_Y;
	//		}
	//		else
	//		{
	//			jumpCount = 0;
	//			vy = PARAGOOMBA_BIG_JUMP_Y;
	//		}
	//		lastJumpTime = GetTickCount64();
	//		isJumping = true;
	//	}


	//}
	//if (isJumping && vy == 0)
	//{
	//	isJumping = false;
	//}
	CGameObject::Update(dt, coObjects);
	CCollision::GetInstance()->Process(this, dt, coObjects);
}
void CParaGoomba::Render()
{
	int aniId;
	//if (state != GOOMBA_STATE_DIE)
	//{
	//	if (isWinged)
	//	{
	//		if (isJumping)
	//		{
	//			aniId = ID_ANI_PARAGOOMBA_JUMPING;
	//		}
	//		else
	//		{
	//			aniId = ID_ANI_PARAGOOMBA_WALKING_WING;
	//		}
	//	}
	//	else
	//	{
	//		aniId = ID_ANI_PARAGOOMBA_WALKING_NO_WING;
	//	}
	//}
	//else
	//{
	//	aniId = ID_ANI_PARAGOOMBA_DIE;
	//}
	switch (state)
	{
	case PARAGOOMBA_STATE_WALKING_WING:
		aniId = ID_ANI_PARAGOOMBA_WALKING_WING;
		break;
	case PARAGOOMBA_STATE_JUMPNG:
		aniId = ID_ANI_PARAGOOMBA_JUMPING;
		break;
	case PARAGOOMBA_STATE_WALKING_NO_WING:
		aniId = ID_ANI_PARAGOOMBA_WALKING_NO_WING;
		break;
	case PARAGOOMBA_STATE_DIE:
		aniId = ID_ANI_PARAGOOMBA_DIE;
		break;
	}

	CAnimations::GetInstance()->Get(aniId)->Render(x, y);
}

void CParaGoomba::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case PARAGOOMBA_STATE_WALKING_WING:
		vx = -GOOMBA_WALKING_SPEED;
		stateStart = GetTickCount64();
		isWinged = true;
		break;
	case PARAGOOMBA_STATE_JUMPNG:
		isWinged = true;
		break;
	case PARAGOOMBA_STATE_WALKING_NO_WING:
		vx = -GOOMBA_WALKING_SPEED;
		isWinged = false;
		break;
	case PARAGOOMBA_STATE_DIE:
		die_start = GetTickCount64();
		vx = 0;
		vy = 0;
		ay = 0;
		break;

	}
}
void CParaGoomba::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	if (state == GOOMBA_STATE_DIE)
	{
		l = x;
		t = y;
		r = l + PARAGOOMBA_WING_BBOX_WIDTH/2;
		b = t + PARAGOOMBA_WING_BBOX_HEIGHT_DIE/2;
	}
	else if (isWinged)
	{
		l = x;
		t = y;
		r = l + PARAGOOMBA_WING_BBOX_WIDTH/2;
		b = t + PARAGOOMBA_WING_BBOX_HEIGHT/2;
	}
	else
	{
		l = x;
		t = y;
		r = l + PARAGOOMBA_WING_BBOX_WIDTH/2;
		b = t + PARAGOOMBA_NOWING_BBOX_HEIGHT/2;
	}
}
