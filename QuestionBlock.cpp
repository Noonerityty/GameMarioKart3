#include "QuestionBlock.h"


void CQuestionBlock::TriggerQuestionBlock()
{
	isBouncing = true;
	isEmpty = true; // Mark the block as empty after bouncing
	bounceStartTime = GetTickCount64();
	startY = y; // Store the starting Y position for bouncing
	if (itemType == 0)
	{
		//Tạo coin nảy
		CCoin* coin = new CCoin(this->x, this->y, 1);
		CScene* currentScene = CGame::GetInstance()->GetCurrentScene();
		CPlayScene* playscene = dynamic_cast<CPlayScene*>(currentScene);

		if (playscene)
		{
			coin->SetState(COIN_STATE_JUMP);
			playscene->AddObject(coin);

		}


	}
	else if (itemType == 1)
	{
		//Tạo nấm nảy
		CMushroom* mushroom = new CMushroom(this->x, this->y);
		CPlayScene* scene = dynamic_cast<CPlayScene*>(CGame::GetInstance()->GetCurrentScene());
		if (scene)
		{
			mushroom->SetState(MUSHROOM_STATE_IDLE);
			scene->AddObject(mushroom);
		}
	}
}

void CQuestionBlock::OnCollisionWith(LPCOLLISIONEVENT e)
{
	
	CKoopa* koopa = dynamic_cast<CKoopa*>(e->obj);
		if (koopa != NULL && koopa->GetState() == KOOPA_STATE_SHELL_MOVING && e->nx != 0 && !isBouncing && !isEmpty)
		{
			TriggerQuestionBlock();
			
		
		}
	CMario* mario = dynamic_cast<CMario*>(e->obj);
		if (mario != NULL && !isBouncing && !isEmpty && e->ny > 0)
		{
			TriggerQuestionBlock();
		
		}
	 

	
}
void CQuestionBlock::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	if (isBouncing)
	{
		if (GetTickCount64() - bounceStartTime < 120)
		{
			this->y = startY - 5 * sin((GetTickCount64() - bounceStartTime) * 0.005); // Simple sine wave for bouncing effect
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