#pragma once
#include "GameObject.h"
#include "PlayScene.h"


#include "debug.h"
#define ID_ANI_QUESTION_BLOCK 86000
#define ID_ANI_QUESTION_BLOCK_SIMPLE_BRICK 86100


#define emptyBlock 86101
#define QUESTION_BLOCK_BBOX_WIDTH 15
#define QUESTION_BLOCK_BBOX_HEIGHT 15

#define QUESTION_NLOCK_ITEM_TYPE_SIMPLE_BRICK 99

class CQuestionBlock : public CGameObject
{
protected:
	bool isBouncing;
	bool isEmpty;
	float startY;
	DWORD bounceStartTime;
	int itemType; // 0: coin, 1: mushroom
	bool isSimplebrick;
	bool isDeletedQBlock = false; // Flag to check if the block is deleted
	int typeBlock;
	//bool isSimpleBrickBreak;
public:
	CQuestionBlock(float x, float y, int type, int typeBlock) : CGameObject(x, y)
	{
		isBouncing = false;
		isEmpty = false;
		startY = y;
		bounceStartTime = 0;
		itemType = type;// Default to coin
		this->typeBlock = typeBlock;
		if (type == 99)
		{
			isSimplebrick = true;
		}
		else
		{
			isSimplebrick = false;
		}
	}

	void Render();
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void GetBoundingBox(float& l, float& t, float& r, float& b);
	void SetItemType(int type) { itemType = type; }
	int GetItemType() { return itemType; }
	void OnCollisionWith(LPCOLLISIONEVENT e);
	void TriggerQuestionBlock();
	virtual int IsBlocking() { if (isDeletedQBlock) return 0; else return 1; }
	virtual int IsCollidable() { if (isDeletedQBlock) return 0; return 1; }
	void ConvertToCoin();
	int GetItemTypeOfQuestionBlock() { return itemType; }
	void SetDeletedQBlock() { isDeletedQBlock = true; }
	bool IsDeletedQBlock() { return isDeletedQBlock; }
};
