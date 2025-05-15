#pragma once
#include "GameObject.h"

#define	PIRANHA_SPEED	0.03f
#define PIRANHA_BBOX_WIDTH  17
#define PIRANHA_BBOX_HEIGHT 33
#define	PIRANHA_SAFE_ZONE_X 40
#define PIRANHA_ACTIVE_ZONE_X 200
#define PIRANHA_WAIT_TIME 1500

#define PIRANHA_ANIMATION_LEFT_BELOW 105001
#define PIRANHA_ANIMATION_LEFT_ABOVE 105002
#define PIRANHA_ANIMATION_RIGHT_BELOW 105003
#define PIRANHA_ANIMATION_RIGHT_ABOVE 105004

#define	PIRANHA_SPRITES_LEFT_BELOW	100000
#define	PIRANHA_SPRITES_LEFT_ABOVE	100002
#define	PIRANHA_SPRITES_RIGHT_BELOW	100004
#define	PIRANHA_SPRITES_RIGHT_ABOVE	100006


#define PIRANHA_STATE_HIDDEN 777
#define PIRANHA_STATE_RISING 778
#define PIRANHA_STATE_SHOWING 779
#define PIRANHA_STATE_SHOOTING 780
#define PIRANHA_STATE_FALLING 781
#define PIRANHA_STATE_DIE 782

#define PIRANHA_HIDE_TIME 1000
#define PIRANHA_RISE_TIME 500
#define PIRANHA_SHOW_TIME 1500
#define PIRANHA_SHOOT_TIME 500
#define PIRANHA_FALL_TIME 500

#define PIRANHA_BULLET_SPEED_X_NARROW 0.09f
#define PIRANHA_BULLET_SPEED_Y_NARROW 0.04f
#define PIRANHA_BULLET_SPEED_X_WIDE 0.075f
#define PIRANHA_BULLET_SPEED_Y_WIDE 0.07f


class CPiranha : public CGameObject
{
protected:
	float startY;
	DWORD state_start;
	float shootX;
	float shootY;
	int marioPosition;
public:
	CPiranha(float x, float y) : CGameObject(x, y)
	{
		startY = y;
		state = PIRANHA_STATE_HIDDEN;
	}
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void Render();
	void SetState(int state);
	void GetBoundingBox(float& l, float& t, float& r, float& b);
	void RenderBoudingBox();
	virtual int IsBlocking() { return 0; }
	virtual int IsCollidable() { return 1; }
	
	int GetMarioRegion();
	float DistanceMario();
	bool IsMarioActiveZone();
	void Shoot();
	

};