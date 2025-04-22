#include "QuestionBlock.h"
#include "Sprite.h"
#include "Sprites.h"
#include "PlayScene.h"
#include "Textures.h"
#include "Game.h"
#include "Coin.h"
void CQuestionBlock::OnCollisionWithMario(LPCOLLISIONEVENT e)
{
	
	
		if (!isBouncing && !isEmpty && e->ny > 0)
		{
			isBouncing = true;
			isEmpty = true; // Mark the block as empty after bouncing
			bounceStartTime = GetTickCount();
			startY = y; // Store the starting Y position for bouncing
			if (itemType == 0)
			{
				//Tạo coin nảy
				CCoin* coin = new CCoin(this->x, this->y, 1);
				
				CPlayScene* scene = dynamic_cast<CPlayScene*>(CGame::GetInstance()->GetCurrentScene());
				if (scene)
				{
					coin->SetState(COIN_STATE_JUMP);
					scene->AddObject(coin);
				
				}
				
				
			}
		}
	
}
void CQuestionBlock::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	if (isBouncing)
	{
		if (GetTickCount() - bounceStartTime < 120) // Bounce for 300 ms
		{
			DebugOutTitle(L"Bounce time: %d", GetTickCount() - bounceStartTime);
			this->y = startY - 5 * sin((GetTickCount() - bounceStartTime) * 0.005); // Simple sine wave for bouncing effect
		}
		else
		{
			isBouncing = false; // Stop bouncing after the time is up
			y = startY; // Reset to original position
		}
	}
	CGameObject::Update(dt, coObjects);
	CCollision::GetInstance()->Process(this, dt, coObjects);
}
void CQuestionBlock::Render()
{
	int id = -1;
	CAnimations* ani = CAnimations::GetInstance();
	CSprites* sprites = CSprites::GetInstance();
	if (isEmpty)
	{
		id = emptyBlock;
		sprites->Get(id)->Draw(x, y);
	}
	else
	{
		id = ID_ANI_QUESTION_BLOCK;
		ani->Get(id)->Render(x, y);
	}
}
void CQuestionBlock::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x - QUESTION_BLOCK_BBOX_WIDTH  / 2;
	t = y - QUESTION_BLOCK_BBOX_HEIGHT / 2;
	r = l + QUESTION_BLOCK_BBOX_WIDTH;
	b = t + QUESTION_BLOCK_BBOX_HEIGHT;
}