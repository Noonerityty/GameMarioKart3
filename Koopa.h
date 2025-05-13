#pragma once
#include "GameObject.h"
#include "Goomba.h"

#define KOOPA_WALKING_SPEED 0.05f
#define KOOPA_SHELL_MOVING_SPEED 0.13f
#define KOOPA_GRAVITY 0.002f

#define KOOPA_BBOX_WIDTH 15
#define KOOPA_BBOX_HEIGHT 25
#define KOOPA_BBOX_SHELL_HEIGHT 15
#define KOOPA_BBOX_SHELL_WIDTH 15

#define KOOPA_STATE_WALKING 100
#define KOOPA_STATE_SHELL_IDLE 101
#define KOOPA_STATE_SHELL_MOVING 102
#define KOOPA_STATE_SHELL_PRE_MOVING 104
#define KOOPA_STATE_SHELL_EXIT 103

#define KOOPA_STATE_DIE 200

#define KOOPA_SHELLING_TIMEOUT 5000
#define KOOPA_DIE_TIMEOUT 500
#define KOOPA_SHELL_EXIT_TIMEOUT 500
#define KOOPA_SHELL_PREDAMGE_TIMEOUT 70


#define KOOPA_ANI_WALKING 125001
#define KOOPA_ANI_SHELL_IDLE 125002
#define KOOPA_ANI_SHELL_MOVING 125003


class CKoopa : public CGameObject
{
protected:
	float ax;
	float ay;
	bool isShell;
	bool takeDamge;
	ULONGLONG state_start;
	float marioX;
	void OnCollisionWithOtherKoopa(LPCOLLISIONEVENT e);
	void OnCollisionWithGoomba(LPCOLLISIONEVENT e);
public:
	CKoopa(float x, float y) : CGameObject(x, y)
	{
		this->ax = 0;
		this->ay = KOOPA_GRAVITY;
		
		isShell = false;
		SetState(KOOPA_STATE_WALKING);
	}
	void Render();
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void GetBoundingBox(float& l, float& t, float& r, float& b);
	void SetState(int state);
	void OnNoCollision(DWORD dt);
	void OnCollisionWith(LPCOLLISIONEVENT e);
	void GetMarioX(float marioX) { this->marioX = marioX; }
	bool GetTakeDamgeFromKoopa() { return takeDamge; }
	virtual int IsCollidable() { return 1; }
	virtual int IsBlocking() { return 0; }
};
