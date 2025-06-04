#pragma once
#include "GameObject.h"

#define	PIRANHA_SPEED	0.03f
#define PIRANHA_BBOX_WIDTH  17
#define PIRANHA_BBOX_HEIGHT 33
#define	PIRANHA_SAFE_ZONE_X 40
#define PIRANHA_ACTIVE_ZONE_X 200
#define PIRANHA_WAIT_TIME 3500

//Red Piranha

#define PIRANHA_ANI_LEFT_BELOW_MOVING 105001
#define PIRANHA_ANI_LEFT_ABOVE_MOVING 105002
#define PIRANHA_ANI_RIGHT_BELOW_MOVING 105003
#define PIRANHA_ANI_RIGHT_ABOVE_MOVING 105004

#define	PIRANHA_ANI_LEFT_BELOW_IDLE	105050
#define	PIRANHA_ANI_LEFT_ABOVE_IDLE	105051
#define	PIRANHA_ANI_RIGHT_BELOW_IDLE	105052
#define	PIRANHA_ANI_RIGHT_ABOVE_IDLE	105053

//Green Piranha

#define PIRANHA_ANI_LEFT_BELOW_MOVING_GREEN 105104
#define PIRANHA_ANI_LEFT_ABOVE_MOVING_GREEN 105105
#define PIRANHA_ANI_RIGHT_BELOW_MOVING_GREEN 105106
#define PIRANHA_ANI_RIGHT_ABOVE_MOVING_GREEN 105107


#define	PIRANHA_ANI_LEFT_BELOW_IDLE_GREEN	105100
#define	PIRANHA_ANI_LEFT_ABOVE_IDLE_GREEN	105101
#define	PIRANHA_ANI_RIGHT_BELOW_IDLE_GREEN	105102
#define	PIRANHA_ANI_RIGHT_ABOVE_IDLE_GREEN	105103

//Melee Piranha
#define PIRANHA_ANI_MELEE 105200


#define PIRANHA_STATE_HIDDEN 777
#define PIRANHA_STATE_RISING 778
#define PIRANHA_STATE_SHOWING 779
#define PIRANHA_STATE_SHOOTING 780
#define PIRANHA_STATE_FALLING 781
#define PIRANHA_STATE_DIE 782

#define PIRANHA_HIDE_TIME 3000
#define PIRANHA_RISE_TIME 500
#define PIRANHA_SHOW_TIME 1500
#define PIRANHA_SHOOT_TIME 500
#define PIRANHA_FALL_TIME 500

#define PIRANHA_BULLET_SPEED_X_NARROW 0.09f
#define PIRANHA_BULLET_SPEED_Y_NARROW 0.04f
#define PIRANHA_BULLET_SPEED_X_WIDE 0.075f
#define PIRANHA_BULLET_SPEED_Y_WIDE 0.07f


#define PIRANHA_TYPE_RED 1
#define PIRANHA_TYPE_GREEN 2
#define PIRANHA_TYPE_MELEE 3
class CPiranha : public CGameObject
{
protected:
	float startY;
	DWORD state_start;
	float shootX;
	float shootY;
	int marioPosition;
	int type;

	int GetAniIdRedPiranha();
	int GetAnIdGreenPiranha();
	int GetAniIdMeleePiranha();

public:
	CPiranha(float x, float y, int type) : CGameObject(x, y)
	{
		startY = y;
		state = PIRANHA_STATE_HIDDEN;
		this->type = type;
	}
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void Render();
	void SetState(int state);
	void GetBoundingBox(float& l, float& t, float& r, float& b);
	/*void RenderBoudingBox();*/
	virtual int IsBlocking() { return 0; }
	virtual int IsCollidable() { return 1; }
	
	int GetMarioRegion();
	float DistanceMario();
	bool IsMarioActiveZone();
	void Shoot();
	

};