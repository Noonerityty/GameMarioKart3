#pragma once
#include "GameObject.h"

#define BUTTON_BBOX_WIDTH 16
#define BUTTON_BBOX_HEIGHT 16

#define BUTTON_BBOX_ACTIVATED_WIDTH 8
#define BUTTON_BBOX_ACTIVATED_HEIGHT 8


#define BUTTON_ID_ANI_UNACTIVATED 185000
#define BUTTON_ID_ANI_ACTIVATED 185001

#define BUTTON_DESTROY_TIMEOUT 200


class CButton : public CGameObject
{
protected:
	bool isActivated;
	bool isOffsetYAfterActivated = false;
	
public:
	CButton(float x, float y) : CGameObject(x, y), isActivated(false) {}

	void Render();
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects) ;
	void GetBoundingBox(float& l, float& t, float& r, float& b) ;
	
	void Activate() {isActivated = true;}
	bool IsActivated() const { return isActivated; }
	virtual int IsBlocking() override { return 1; }
	virtual int IsCollidable() override { return 1; }
};