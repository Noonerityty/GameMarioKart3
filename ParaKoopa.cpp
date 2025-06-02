#include "ParaKoopa.h"
#include "debug.h"


void CParaKoopa::SetState(int state)
{
	CGameObject::SetState(state);

	switch (state)
	{
	case KOOPA_STATE_WALKING:
		if (isShell) {
			y -= (KOOPA_BBOX_HEIGHT - KOOPA_BBOX_SHELL_HEIGHT) / 2.0f; //Để tránh khi chuyển boudingbox mai rùa thành boudingbox đã chui ra thì bị rớt xuông do lồng vào block phía dưới

		}
		vx = -KOOPA_WALKING_SPEED;
		isShell = false;
		takeDamge = true;
		isWinged = false;
		break;
	case KOOPA_STATE_WALKING_WING:
		vx = -KOOPA_WALKING_SPEED;
		isWinged = true;
		isShell = false;
		takeDamge = true;
		willJump = true;
		stateStart = GetTickCount64();
		break;
	case KOOPA_STATE_JUMPING:
		// CHỈ khởi tạo giá trị cho state mới
		willJump = true; // Cho phép thực hiện nhảy
		state_start = GetTickCount64(); // Bắt đầu đếm thời gian cho JUMPING
		break;
	case KOOPA_STATE_SHELL_IDLE:
		vx = 0;
		isShell = true;
		takeDamge = false;
		state_start = GetTickCount64();
		isWinged = false;
		break;
	case KOOPA_STATE_SHELL_MOVING:
		state_start = GetTickCount64();
		if (marioX > x)
			vx = -KOOPA_SHELL_MOVING_SPEED;
		else
			vx = KOOPA_SHELL_MOVING_SPEED;
		isShell = true;
		takeDamge = false;
		isWinged = false;
		break;
	
	case KOOPA_STATE_SHELL_EXIT:
		vx = 0;
		isShell = true;
		isWinged = false;
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

void CParaKoopa::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	

	vx += ax * dt;
	vy += ay * dt;

	if (state == KOOPA_STATE_DIE && GetTickCount64() - state_start > KOOPA_DIE_TIMEOUT)
	{
		isDeleted = true;
		return;
	}

	if (state == KOOPA_STATE_WALKING_WING && GetTickCount64() - state_start > KOOPA_WALKING_WING_TIMEOUT)
	{
		SetState(KOOPA_STATE_JUMPING);
	}

	if (state == KOOPA_STATE_JUMPING)
	{
		if (willJump)
		{
			
			vy = KOOPA_JUMPING_Y;
			willJump = false;
		/*	state_start = GetTickCount64();*/
		}
		if (GetTickCount64() - state_start > 500)
		SetState(KOOPA_STATE_WALKING_WING);
	}
	if (state == KOOPA_STATE_SHELL_IDLE && GetTickCount64() - state_start > KOOPA_SHELLING_TIMEOUT)
	{
		SetState(KOOPA_STATE_SHELL_EXIT);
	}


	if (state == KOOPA_STATE_SHELL_EXIT && GetTickCount64() - state_start > KOOPA_SHELL_EXIT_TIMEOUT)
	{
		SetState(KOOPA_STATE_WALKING);
	}
	if (state == KOOPA_STATE_SHELL_MOVING && GetTickCount64() - state_start > KOOPA_SHELL_PREDAMGE_TIMEOUT)
	{
		takeDamge = true;
	}

	CGameObject::Update(dt, coObjects);
	CCollision::GetInstance()->Process(this, dt, coObjects);
}

void CParaKoopa::Render()
{
	int ani = -1;
	if (state == KOOPA_STATE_WALKING)
	{
		if (vx > 0) ani = KOOPA_ANI_WALKING_RIGHT;
		else if (vx < 0) ani = KOOPA_ANI_WALKING_LEFT;
	}
	else if (state == KOOPA_STATE_SHELL_IDLE)
	{
		ani = KOOPA_ANI_SHELL_IDLE;
	}
	else if (state == KOOPA_STATE_SHELL_MOVING)
	{
		ani = KOOPA_ANI_SHELL_MOVING;
	}
	else if (state == KOOPA_STATE_SHELL_EXIT)
	{
		ani = KOOPA_ANI_SHELL_EXIT;
	}
	else if (state == KOOPA_STATE_WALKING_WING || state == KOOPA_STATE_JUMPING)
	{
		if (vx > 0) ani = KOOPA_ANI_WALKING_WING_RIGHT;
		else if (vx < 0) ani = KOOPA_ANI_WALKING_WING_LEFT;
	}

	if (ani != -1)
		CAnimations::GetInstance()->Get(ani)->Render(x, y);
}

void CParaKoopa::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	if (state == KOOPA_STATE_SHELL_IDLE || state == KOOPA_STATE_SHELL_MOVING || state == KOOPA_STATE_SHELL_EXIT )
	{
		left = x - KOOPA_BBOX_SHELL_WIDTH / 2;
		top = y - KOOPA_BBOX_SHELL_HEIGHT / 2;
		right = left + KOOPA_BBOX_SHELL_WIDTH;
		bottom = top + KOOPA_BBOX_SHELL_HEIGHT;
	}
	else if (state == KOOPA_STATE_WALKING_WING || state == KOOPA_STATE_JUMPING)
	{
		left = x - PARAKOOPA_BBOX_WIDTH / 2;
		top = y - PARAKOOPA_BBOX_HEIGHT / 2;
		right = left + PARAKOOPA_BBOX_WIDTH;
		bottom = top + PARAKOOPA_BBOX_HEIGHT;
	
	}
	else
	{

		left = x - KOOPA_BBOX_WIDTH / 2;
		top = y - KOOPA_BBOX_HEIGHT / 2;
		right = left + KOOPA_BBOX_WIDTH;
		bottom = top + KOOPA_BBOX_HEIGHT;
	}
	DebugOut(L"[DEBUG] ParaKoopa BBOX: x=%.2f, y=%.2f, L=%.2f, T=%.2f, R=%.2f, B=%.2f, state=%d\n",
		x, y, left, top, right, bottom, state);
}
