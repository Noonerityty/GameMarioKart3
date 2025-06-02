#pragma once
#include "GameObject.h"
#include "Koopa.h"

#define PARAKOOPA_BBOX_WIDTH 15
#define PARAKOOPA_BBOX_HEIGHT 26

#define	KOOPA_STATE_WALKING_WING 120
#define KOOPA_STATE_JUMPING 125


#define KOOPA_WALKING_WING_TIMEOUT 600


#define KOOPA_ANI_WALKING_WING_LEFT 125502
#define KOOPA_ANI_WALKING_WING_RIGHT 125501

#define KOOPA_JUMPING_Y -0.35f

class CParaKoopa : public CKoopa
{
protected:
	bool isWinged;
	bool willJump;
	
	ULONGLONG lastJumpTime;
	ULONGLONG stateStart;
public:
	CParaKoopa(float x, float y) : CKoopa(x, y)
	{
		this->ax = 0;
		this->ay = KOOPA_GRAVITY;
		isWinged = true;
		
		lastJumpTime = 0;
		
		stateStart = GetTickCount64();
		SetState(KOOPA_STATE_WALKING_WING);
	}
	void Render() override;
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects) override;
	void GetBoundingBox(float& l, float& t, float& r, float& b) override;
	void SetState(int state) override;
};
