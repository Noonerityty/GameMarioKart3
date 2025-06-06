
#include "QuestionBlock.h"
#include "Coin.h"
#include "Mushroom.h"
#include "Koopa.h"
#include "Mario.h"
#include "debug.h"
#include "Leaf.h"
#include "TailRacoon.h"
#include "Button.h"

void CQuestionBlock::TriggerQuestionBlock()
{
	if (isBouncing || isEmpty) return; // Prevent triggering if already bouncing or empty
	isBouncing = true;
	isEmpty = true; // Mark the block as empty after bouncing
	bounceStartTime = GetTickCount64();
	startY = y; // Store the starting Y position for bouncing
	CScene* currentScene = CGame::GetInstance()->GetCurrentScene();
	CPlayScene* playscene = dynamic_cast<CPlayScene*>(currentScene);
	if (itemType == 0)
	{
		//Tạo coin nảy
		CCoin* coin = new CCoin(this->x, this->y, 1);


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
		
		if (playscene)
		{
			mushroom->SetState(MUSHROOM_STATE_IDLE);
			playscene->AddObject(mushroom);
		}
	}
	else if (itemType == 2)
	{
		CLeaf* leaf = new CLeaf(this->x, this->y);
		if (playscene)
		{
			leaf->SetState(LEAF_STATE_RISING);
			playscene->AddObject(leaf);
		}
	}
	else if (itemType == 98)
	{
		CButton* button = new CButton(this->x, this->y - 16);
		if (playscene)
		{
			playscene->AddObject(button);
		}
	}
	else if (itemType == QUESTION_NLOCK_ITEM_TYPE_SIMPLE_BRICK)
	{
		SetDeletedQBlock(); 
	}
}

void CQuestionBlock::OnCollisionWith(LPCOLLISIONEVENT e)
{
	
	CKoopa* koopa = dynamic_cast<CKoopa*>(e->obj);
		if (koopa != NULL && koopa->GetState() == KOOPA_STATE_SHELL_MOVING && e->nx != 0)
		{
			TriggerQuestionBlock();
		}
		else if (dynamic_cast<CTailRacoon*>(e->obj) != NULL )
		{
			TriggerQuestionBlock();
			
		}
		
	
}
void CQuestionBlock::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	/*if (itemType == 99)
	{
		isSimplebrick = true;
	}*/

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
	if (isDeletedQBlock)
		return; // If the block is deleted, do not render it


	if (typeBlock == 1)
	{
		if(!isEmpty)
		id = ID_ANI_QUESTION_BLOCK_SIMPLE_BRICK;
		else
		id = emptyBlock;
	}
	else
	{
		if (!isEmpty)
			id = ID_ANI_QUESTION_BLOCK;
		else
			id = emptyBlock;
	}
	ani->Get(id)->Render(x, y);
	/*else if (itemType == 98 || itemType == 97)
	{

	}
	else if (isSimplebrick)
	{
		id = ID_ANI_QUESTION_BLOCK_SIMPLE_BRICK;
		ani->Get(id)->Render(x, y);
	}
	else if (isEmpty)
	{
		id = emptyBlock;
		sprites->Get(id)->Draw(x, y);
	}
	else
	{

		id = ID_ANI_QUESTION_BLOCK;
		ani->Get(id)->Render(x, y);
	}*/
}
void CQuestionBlock::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	if (isDeletedQBlock)
	{
		l = t = r = b = 0; // No bounding box if the block is deleted
		return;
	}

	l = x - QUESTION_BLOCK_BBOX_WIDTH  / 2;
	t = y - QUESTION_BLOCK_BBOX_HEIGHT / 2;
	r = l + QUESTION_BLOCK_BBOX_WIDTH;
	b = t + QUESTION_BLOCK_BBOX_HEIGHT;
}

void CQuestionBlock::ConvertToCoin()
{
	if (!isSimplebrick && isDeletedQBlock)
		return;
	CScene* currentScene = CGame::GetInstance()->GetCurrentScene();
	CPlayScene* playscene = dynamic_cast<CPlayScene*>(currentScene);
	if (playscene)
	{
		CCoin* coin = new CCoin(this->x, this->y, 0);
		playscene->AddObject(coin);
	}
	SetDeletedQBlock(); // Mark the block as deleted

}