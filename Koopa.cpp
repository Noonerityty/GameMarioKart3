#include "Koopa.h"
#include"debug.h"
#include "Textures.h"
#include "Game.h"

void CKoopa::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	if (state == KOOPA_STATE_SHELL_IDLE || state == KOOPA_STATE_SHELL_MOVING || state == KOOPA_STATE_SHELL_EXIT)
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
	isOnPlatform = false;
}

void CKoopa::OnCollisionWith(LPCOLLISIONEVENT e)
{
	if(!e->obj->IsBlocking())
	{
		OnCollisionWithOtherKoopa(e);
		OnCollisionWithGoomba(e);
		return;
	}
	if (e->ny != 0)
	{
		vy = 0;
		if (e->ny < 0)
		{
			isOnPlatform = true;
		}
	}
	else if (e->nx != 0 )
	{
		vx = -vx;

	}

	

}

void CKoopa::OnCollisionWithOtherKoopa(LPCOLLISIONEVENT e)
{
	CKoopa* koopa = dynamic_cast<CKoopa*>(e->obj);
	if (koopa == nullptr || koopa == this) return;
	if (state == KOOPA_STATE_SHELL_MOVING)
	{
		if (koopa->GetState() != KOOPA_STATE_SHELL_MOVING)
		{
			koopa->SetState(KOOPA_STATE_DIE);
			
		}
		else
		{
			SetState(KOOPA_STATE_DIE);
			
		}
	}
	else if (koopa->GetState() == KOOPA_STATE_SHELL_MOVING)
	{
		SetState(KOOPA_STATE_DIE);
		
	}

		
}
void CKoopa::OnCollisionWithGoomba(LPCOLLISIONEVENT e)
{
	CGoomba* goomba = dynamic_cast<CGoomba*>(e->obj);
	if (goomba == nullptr) return;
	if (state == KOOPA_STATE_SHELL_MOVING)
	{
		if (goomba->GetState() != GOOMBA_STATE_DIE)
		{
			goomba->SetState(GOOMBA_STATE_DIE);
		}
		
	}
	

}

void CKoopa::SetState(int state)
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
		break;
	case KOOPA_STATE_SHELL_IDLE:
		vx = 0;
		isShell = true;
		takeDamge = false;
		state_start = GetTickCount64();
		break;
	case KOOPA_STATE_SHELL_MOVING:
		state_start = GetTickCount64();
		if (marioX > x)
			vx = -KOOPA_SHELL_MOVING_SPEED;
		else
			vx = KOOPA_SHELL_MOVING_SPEED;
		isShell = true;
		takeDamge = false;
		break;
	case KOOPA_STATE_SHELL_EXIT:
		vx = 0;
		isShell = true;
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
	if (state == KOOPA_STATE_SHELL_MOVING && GetTickCount64() - state_start > KOOPA_SHELL_PREDAMGE_TIMEOUT)
	{
		takeDamge = true;
	}

	CGameObject::Update(dt, coObjects);
	CCollision::GetInstance()->Process(this, dt, coObjects);
}

void CKoopa::Render()
{
	RenderBoundingBox();
	int aniId;
	switch (state)
	{
	case KOOPA_STATE_WALKING:
		if (vx > 0)
			aniId = KOOPA_ANI_WALKING_RIGHT;
		else
			aniId = KOOPA_ANI_WALKING_LEFT;
		break;
	case KOOPA_STATE_SHELL_IDLE:
		aniId = KOOPA_ANI_SHELL_IDLE;
		break;
	case KOOPA_STATE_SHELL_MOVING:
		aniId = KOOPA_ANI_SHELL_MOVING;
		break;
	case KOOPA_STATE_SHELL_EXIT:
		aniId = KOOPA_ANI_SHELL_EXIT;
		break;
	default:
		break;
	}
	CAnimations::GetInstance()->Get(aniId)->Render(x, y);
}
void CKoopa::RenderBoundingBox()
{
	D3DXVECTOR3 p(x, y, 0);
	RECT rect;

	LPTEXTURE bbox = CTextures::GetInstance()->Get(ID_TEX_BBOX);

	float l, t, r, b;

	GetBoundingBox(l, t, r, b);
	rect.left = 0;
	rect.top = 0;
	rect.right = (int)r - (int)l;
	rect.bottom = (int)b - (int)t;

	float cx, cy;
	CGame::GetInstance()->GetCamPos(cx, cy);

	/*float yy = y - this->cellHeight / 2 + rect.bottom / 2;*/

	CGame::GetInstance()->Draw(x - cx, y - cy, bbox, nullptr, BBOX_ALPHA, rect.right - 1, rect.bottom - 1);
}