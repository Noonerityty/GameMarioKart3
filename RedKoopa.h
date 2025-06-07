#pragma once
#include "Koopa.h"

#define KOOPA_RED_ANI_WALKING_LEFT 125101
#define KOOPA_RED_ANI_WALKING_RIGHT 125104
#define KOOPA_RED_ANI_SHELL_IDLE 125102
#define KOOPA_RED_ANI_SHELL_MOVING 125103
#define KOOPA_RED_ANI_SHELL_EXIT 125105

class CRedKoopa : public CKoopa
{
public:
	CRedKoopa(float x, float y) : CKoopa(x, y)
	{
		this->ax = 0;
		this->ay = KOOPA_GRAVITY;
		isShell = false;
		SetState(KOOPA_STATE_WALKING);
		isActive = true;
	}
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects) override;
	void Render() override;

};