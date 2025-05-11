#include "Goomba.h"

#define PARAGOOMBA_JUMP_TIME 300
#define PARAGOOMBA_SMALL_JUMP_Y -0.25
#define PARAGOOMBA_BIG_JUMP_Y -0.45

#define PARAGOOMBA_SMALL_JUMP_COUNT 3

#define ID_ANI_PARAGOOMBA_WALKING_WING 5002
#define ID_ANI_PARAGOOMBA_JUMPING 5003
#define ID_ANI_PARAGOOMBA_WALKING_NO_WING 5004
#define ID_ANI_PARAGOOMBA_DIE 5005

#define PARAGOOMBA_STATE_WALKING_WING 150
#define PARAGOOMBA_STATE_JUMPNG 155
#define PARAGOOMBA_STATE_WALKING_NO_WING 160
#define PARAGOOMBA_STATE_DIE 200

#define PARAGOOMBA_WALKING_WING_TIME 600
#define	PARAGOOMBA_DIE_TIMEOUT 500

#define PARAGOOMBA_WING_BBOX_WIDTH 16
#define PARAGOOMBA_WING_BBOX_HEIGHT 19
#define PARAGOOMBA_NOWING_BBOX_HEIGHT 14
#define PARAGOOMBA_WING_BBOX_HEIGHT_DIE 7

class CParaGoomba : public CGoomba
{
	bool isWinged;
	bool isJumping;
	int jumpCount;
	ULONGLONG lastJumpTime;
	ULONGLONG stateStart;
public:
	CParaGoomba(float x, float y) : CGoomba(x, y)
	{
		this->ax = 0;
		this->ay = GOOMBA_GRAVITY;
		die_start = -1;
		isWinged = true;
		isJumping = false;
		lastJumpTime = 0;
		jumpCount = 0;
		SetState(PARAGOOMBA_STATE_WALKING_WING);
	}
	void Render();
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void GetBoundingBox(float& l, float& t, float& r, float& b);
	void SetState(int state);
};