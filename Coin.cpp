#include "Coin.h"

void CCoin::Render()
{
	if (state == COIN_STATE_JUMP)
	{
		CAnimations* animations = CAnimations::GetInstance();
		animations->Get(ID_ANI_COIN_JUMP)->Render(x, y);
	}
	else
	{
		CAnimations* animations = CAnimations::GetInstance();
		animations->Get(ID_ANI_COIN_IDLE)->Render(x, y);
	}

	//RenderBoundingBox();
}

void CCoin::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x - COIN_BBOX_WIDTH / 2;
	t = y - COIN_BBOX_HEIGHT / 2;
	r = l + COIN_BBOX_WIDTH;
	b = t + COIN_BBOX_HEIGHT;
}

void CCoin::SetState(int state)
{
	switch (state)
	{
		case COIN_STATE_JUMP:
		{
			vx = 0;
			vy = -COIN_JUMP_SPEED;
			
			
			break;
		}
		default:
		{
			vx = 0;
			vy = 0;
		}
			break;
	}

}
void CCoin::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	if (state == COIN_STATE_JUMP)
	{
		// vy chịu tác động của trọng lực theo thời gian
		vy += GRAVITY * dt;

		// Tính toán vị trí mới của coin
		y += vy * dt;
		// Kiểm tra nếu coin đã rơi xuống dưới một khoảng cách nhất định
		if (vy > 0 &&  !isFalling)
		{
			isFalling = true;
		}

		if (y > startY)
		{
			this->Delete();
			return;
		}
		

	}
	CGameObject::Update(dt, coObjects);
	CCollision::GetInstance()->Process(this, dt, coObjects);
}
