#pragma once
#include "GameObject.h"

#include "Animation.h"
#include "Animations.h"

#include "debug.h"


#include "Koopa.h"



#define MARIO_WALKING_SPEED		0.1f
#define MARIO_RUNNING_SPEED		0.2f

#define MARIO_ACCEL_WALK_X	0.0005f
#define MARIO_ACCEL_RUN_X	0.0007f

#define MARIO_JUMP_SPEED_Y		0.5f
#define MARIO_JUMP_RUN_SPEED_Y	0.6f

#define MARIO_GRAVITY			0.002f

#define MARIO_JUMP_DEFLECT_SPEED  0.4f

#define MARIO_STATE_DIE				-10
#define MARIO_STATE_IDLE			0
#define MARIO_STATE_WALKING_RIGHT	100
#define MARIO_STATE_WALKING_LEFT	200

#define MARIO_STATE_JUMP			300
#define MARIO_STATE_RELEASE_JUMP    301

#define MARIO_STATE_RUNNING_RIGHT	400
#define MARIO_STATE_RUNNING_LEFT	500

#define MARIO_STATE_SIT				600
#define MARIO_STATE_SIT_RELEASE		601


#pragma region ANIMATION_ID

#define ID_ANI_MARIO_IDLE_RIGHT 400
#define ID_ANI_MARIO_IDLE_LEFT 401

#define ID_ANI_MARIO_WALKING_RIGHT 500
#define ID_ANI_MARIO_WALKING_LEFT 501

#define ID_ANI_MARIO_RUNNING_RIGHT 600
#define ID_ANI_MARIO_RUNNING_LEFT 601

#define ID_ANI_MARIO_JUMP_WALK_RIGHT 700
#define ID_ANI_MARIO_JUMP_WALK_LEFT 701

#define ID_ANI_MARIO_JUMP_RUN_RIGHT 800
#define ID_ANI_MARIO_JUMP_RUN_LEFT 801

#define ID_ANI_MARIO_SIT_RIGHT 900
#define ID_ANI_MARIO_SIT_LEFT 901

#define ID_ANI_MARIO_BRACE_RIGHT 1000
#define ID_ANI_MARIO_BRACE_LEFT 1001

#define ID_ANI_MARIO_HOLD_KOOPA_LEFT 1180
#define ID_ANI_MARIO_HOLD_KOOPA_RIGHT 1181

#define ID_ANI_MARIO_HOLD_KOOPA_LEFT_IDLE 1182
#define ID_ANI_MARIO_HOLD_KOOPA_RIGHT_IDLE 1183

#define ID_ANI_MARIO_KICK_KOOPA_LEFT 1184
#define ID_ANI_MARIO_KICK_KOOPA_RIGHT 1185

#define ID_ANI_MARIO_DIE 999

// SMALL MARIO
#define ID_ANI_MARIO_SMALL_IDLE_RIGHT 1100
#define ID_ANI_MARIO_SMALL_IDLE_LEFT 1102

#define ID_ANI_MARIO_SMALL_WALKING_RIGHT 1200
#define ID_ANI_MARIO_SMALL_WALKING_LEFT 1201

#define ID_ANI_MARIO_SMALL_RUNNING_RIGHT 1300
#define ID_ANI_MARIO_SMALL_RUNNING_LEFT 1301

#define ID_ANI_MARIO_SMALL_BRACE_RIGHT 1400
#define ID_ANI_MARIO_SMALL_BRACE_LEFT 1401

#define ID_ANI_MARIO_SMALL_JUMP_WALK_RIGHT 1500
#define ID_ANI_MARIO_SMALL_JUMP_WALK_LEFT 1501

#define ID_ANI_MARIO_SMALL_JUMP_RUN_RIGHT 1600
#define ID_ANI_MARIO_SMALL_JUMP_RUN_LEFT 1601

#define ID_ANI_MARIO_SMALL_HOLD_KOOPA_LEFT 1700
#define ID_ANI_MARIO_SMALL_HOLD_KOOPA_RIGHT 1701
#define ID_ANI_MARIO_SMALL_HOLD_KOOPA_LEFT_IDLE 1702
#define ID_ANI_MARIO_SMALL_HOLD_KOOPA_RIGHT_IDLE 1703
#define ID_ANI_MARIO_SMALL_KICK_KOOPA_LEFT 1704
#define ID_ANI_MARIO_SMALL_KICK_KOOPA_RIGHT 1705

//RACOON MARIO
#define ID_ANI_MARIO_RACOON_IDLE_RIGHT 1800
#define ID_ANI_MARIO_RACOON_IDLE_LEFT 1801

#define ID_ANI_MARIO_RACOON_WALKING_RIGHT 1805
#define ID_ANI_MARIO_RACOON_WALKING_LEFT 1806

#define ID_ANI_MARIO_RACOON_RUNNING_RIGHT 1810
#define ID_ANI_MARIO_RACOON_RUNNING_LEFT 1811

#define ID_ANI_MARIO_RACOON_BRACE_RIGHT 1815
#define ID_ANI_MARIO_RACOON_BRACE_LEFT 1816

#define ID_ANI_MARIO_RACOON_JUMP_WALK_RIGHT 1820
#define ID_ANI_MARIO_RACOON_JUMP_WALK_LEFT 1821

#define ID_ANI_MARIO_RACOON_JUMP_RUN_RIGHT 1825
#define ID_ANI_MARIO_RACOON_JUMP_RUN_LEFT 1826

#define ID_ANI_MARIO_RACOON_HOLD_KOOPA_RIGHT 1830
#define ID_ANI_MARIO_RACOON_HOLD_KOOPA_LEFT 1831

#define ID_ANI_MARIO_RACOON_HOLD_KOOPA_RIGHT_IDLE 1832
#define ID_ANI_MARIO_RACOON_HOLD_KOOPA_LEFT_IDLE 1833

#define ID_ANI_MARIO_RACOON_KICK_KOOPA_RIGHT 1834
#define ID_ANI_MARIO_RACOON_KICK_KOOPA_LEFT 1835

#define ID_ANI_MARIO_RACOON_SIT_RIGHT 1836
#define ID_ANI_MARIO_RACOON_SIT_LEFT 1837

#define ID_ANI_MARIO_RACOON_FLYING_RIGHT 1838
#define ID_ANI_MARIO_RACOON_FLYING_LEFT 1839

#define ID_ANI_MARIO_RACOON_TAIL_ATTACK_IDLE_RIGHT 1840
#define ID_ANI_MARIO_RACOON_TAIL_ATTACK_IDLE_LEFT 1841

#define ID_ANI_MARIO_RACOON_TAIL_ATTACK_MOVING_RIGHT 1842
#define ID_ANI_MARIO_RACOON_TAIL_ATTACK_MOVING_LEFT 1843

#pragma endregion

#define GROUND_Y 160.0f




#define	MARIO_LEVEL_SMALL	1
#define	MARIO_LEVEL_BIG		2
#define MARIO_LEVEL_RACOON	3

#define MARIO_BIG_BBOX_WIDTH  14 // 14
#define MARIO_BIG_BBOX_HEIGHT 24 //24
#define MARIO_BIG_SITTING_BBOX_WIDTH  14
#define MARIO_BIG_SITTING_BBOX_HEIGHT 16

#define MARIO_SIT_HEIGHT_ADJUST ((MARIO_BIG_BBOX_HEIGHT-MARIO_BIG_SITTING_BBOX_HEIGHT)/2)

#define MARIO_SMALL_BBOX_WIDTH  13
#define MARIO_SMALL_BBOX_HEIGHT 12


#define MARIO_UNTOUCHABLE_TIME 2500
#define MARIO_STUNNED_TIME 1000
#define MARIO_KICK_TIME 100
#define MARIO_SPAM_FLY_TIME 200


#define MARIO_P_METER_MAX 1.0f
#define MARIO_P_METER_CHARGE_RATE 0.0005f
#define MARRIO_P_METER_DECREASE_RATE 0.0007f


#define MARRIO_FLYING_BOOST -0.25f
#define MARIO_FLYING_GRAVITY 0.0005f
#define MARIO_MAX_FLYING_HEIGHT -242


//TAIL RACOON
#define MARIO_TAIL_ATTACK_OFFSET_X  10
#define MARIO_TAIL_ATTACK_OFFSET_Y  6
#define MARIO_TAIL_ATTACK_FRAME_TIME 100
#define MArio_TAIL_ATTACK_TIMEOUT 500


class CMario : public CGameObject
{
	BOOLEAN isSitting;
	float maxVx;
	float ax;				// acceleration on x 
	float ay;				// acceleration on y 

	int level; 
	int untouchable; 
	ULONGLONG untouchable_start;
	ULONGLONG stunned_start;
	ULONGLONG kick_time_out;
	ULONGLONG lastSpamFly;
	ULONGLONG tailAttackStartTime;
	BOOLEAN isOnPlatform;
	int coin; 
	bool isStunned = false;
	CKoopa* heldKoopa = NULL;
	bool isHolding = false;
	bool isKickingKoopa = false;
	bool isTailAttacking;
	bool tailCreated;
	bool isFlying;          
	float p_meter;          
	bool canFly;            
	bool jumpPressed;
	bool jumpPressedLastFrame;

	void OnCollisionWithGoomba(LPCOLLISIONEVENT e);
	void OnCollisionWithCoin(LPCOLLISIONEVENT e);
	void OnCollisionWithPortal(LPCOLLISIONEVENT e);
	void OnCollisionWithQuestionBlock(LPCOLLISIONEVENT e);
	void OnCollisionWithMushroom(LPCOLLISIONEVENT e);
	void OnCollisionWithPiranha(LPCOLLISIONEVENT e);
	void OnCollisionWithPiranhaBullet(LPCOLLISIONEVENT e);
	void OnCollisionWithKoopa(LPCOLLISIONEVENT e);
	void OnCollisionWithLeaf(LPCOLLISIONEVENT e);
	
	int GetAniIdBig();
	int GetAniIdSmall();
	int GetAniIdRacoon();

public:
	CMario(float x, float y) : CGameObject(x, y)
	{
		isSitting = false;
		maxVx = 0.0f;
		ax = 0.0f;
		ay = MARIO_GRAVITY; 
		lastSpamFly = 0;
		canFly = false;
		level = 3;
		untouchable = 0;
		untouchable_start = -1;
		isOnPlatform = false;
		coin = 0;
          
	}
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void Render();
	void SetState(int state);

	int IsCollidable()
	{ 
		return (state != MARIO_STATE_DIE); 
	}

	int IsBlocking() { return (state != MARIO_STATE_DIE && untouchable==0); }

	void OnNoCollision(DWORD dt);
	void OnCollisionWith(LPCOLLISIONEVENT e);
	void SetJumpInput(bool pressed) { jumpPressed = pressed; }
	void SetLevel(int l);
	void StartUntouchable() { untouchable = 1; untouchable_start = GetTickCount64(); }
	void StartStunned() { if(!isStunned) isStunned = true; stunned_start = GetTickCount64(); }
	void ReleaseKoopa();
	void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	void ProcessMarioDie();

	void StartTailAttack();
	void TailAttackEvent();

	bool isHoldingKoopa() { return isHolding; }
	int GetLevel() { return level; }
	bool GetIsSitting() { return isSitting; }
	
};