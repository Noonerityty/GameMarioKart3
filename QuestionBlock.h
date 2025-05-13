#include "GameObject.h"
#include "PlayScene.h"
#include "Coin.h"
#include "Mushroom.h"
#include "Koopa.h"
#include "Mario.h"

#include "debug.h"
#define ID_ANI_QUESTION_BLOCK 86000
#define emptyBlock 85001
#define QUESTION_BLOCK_BBOX_WIDTH 15
#define QUESTION_BLOCK_BBOX_HEIGHT 15

class CQuestionBlock : public CGameObject
{
protected:
	bool isBouncing;
	bool isEmpty;
	float startY;
	DWORD bounceStartTime;
	int itemType; // 0: coin, 1: mushroom
public:
	CQuestionBlock(float x, float y, int type) : CGameObject(x, y)
	{
		isBouncing = false;
		isEmpty = false;
		startY = y;
		bounceStartTime = 0;
		itemType = type;// Default to coin
	}

	void Render();
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void GetBoundingBox(float& l, float& t, float& r, float& b);
	void SetItemType(int type) { itemType = type; }
	int GetItemType() { return itemType; }
	void OnCollisionWith(LPCOLLISIONEVENT e);
	void TriggerQuestionBlock();
	virtual int IsBlocking() { return 1; }
	virtual int IsCollidable() { return 1; }
};
