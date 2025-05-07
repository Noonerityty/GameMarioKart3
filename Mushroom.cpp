#include "Mushroom.h"
#include "debug.h"
void CMushroom::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	vx += ax * dt;
	vy += ay * dt;
	if (state == MUSHROOM_STATE_IDLE)
	{

		// Tính thời gian đã trôi qua kể từ khi spawn
        DWORD timer = GetTickCount64() - spawntime;
        
        // Giai đoạn 1: Trồi lên hoàn toàn trong 300ms
        if (timer < 300)
        {
            float progress = (float)timer / 300.0f; // Từ 0.0 đến 1.0
            y = startY - MUSHROOM_BBOX_HEIGHT * progress;
        }
        // Giai đoạn 2: Giữ nguyên vị trí đỉnh thêm 100ms
        else if (timer < 400)
        {
            y = startY - MUSHROOM_BBOX_HEIGHT;
        }
        // Chuyển sang trạng thái di chuyển
        else
        {
            SetState(MUSHROOM_STATE_MOVING);
        }
	}
	else if (state == MUSHROOM_STATE_DIE)
	{
		this->Delete();
	}

	CGameObject::Update(dt, coObjects);
	CCollision::GetInstance()->Process(this, dt, coObjects);
	

}
void CMushroom::OnNoCollision(DWORD dt)
{
	x += vx * dt;
	y += vy * dt;
}
void CMushroom::OnCollisionWith(LPCOLLISIONEVENT e)
{

	if (!e->obj->IsBlocking()) return; // Ignore collision with blocking objects
	if (dynamic_cast<CMushroom*>(e->obj)) return; // Ignore collision with other mushrooms
	
	if (e->ny != 0)
	{
		//vy = 0; // Stop falling
		if (e->ny < 0) // Va chạm từ trên xuống (đứng trên vật)
		{
			vy = 0;
			y += e->ny * 0.4f; // Điều chỉnh vị trí để đứng chính xác trên bề mặt
		}

	}
	else if (e->nx != 0)
	{
		vx = -vx; // Reverse direction on horizontal collision
	}


}
void CMushroom::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x - MUSHROOM_BBOX_WIDTH / 2;
	top = y - MUSHROOM_BBOX_HEIGHT / 2;
	right = left + MUSHROOM_BBOX_WIDTH;
	bottom = top + MUSHROOM_BBOX_HEIGHT;
}

void CMushroom::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case MUSHROOM_STATE_IDLE:
		spawntime = GetTickCount64();
		vx = 0;
		ay = 0;
		break;
	case MUSHROOM_STATE_MOVING:
		vx = MUSHROOM_SPEED_X;
		ay = MUSHROOM_GRAVITY;
		break;
	case MUSHROOM_STATE_DIE:
		vx = 0;
		vy = 0;
		break;
	default:
		break;
	}
}
void CMushroom::Render()
{
	CSprites::GetInstance()->Get(ID_TEX_MUSHROOM)->Draw(x, y);
}