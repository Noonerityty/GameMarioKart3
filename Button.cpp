#include "Button.h"


void CButton::Render()
{
	CAnimations* animations = CAnimations::GetInstance();
	if (isActivated)
		animations->Get(BUTTON_ID_ANI_ACTIVATED)->Render(x, y);
	else
		animations->Get(BUTTON_ID_ANI_UNACTIVATED)->Render(x, y);
	//RenderBoundingBox();
}

void CButton::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	if (isActivated && !isOffsetYAfterActivated)
	{
		y += /*BUTTON_BBOX_ACTIVATED_HEIGHT/2 +*/ BUTTON_BBOX_HEIGHT/2; // Adjust y position when activated
		
		isOffsetYAfterActivated = true; 
		
		
	}
	
	
	CGameObject::Update(dt, coObjects);
	CCollision::GetInstance()->Process(this, dt, coObjects);
}

void CButton::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	if (!isActivated)
	{
		l = x - BUTTON_BBOX_WIDTH / 2;
		t = y - BUTTON_BBOX_HEIGHT / 2;
		r = l + BUTTON_BBOX_WIDTH;
		b = t + BUTTON_BBOX_HEIGHT;
		
	}
	else
	{
		l = x - BUTTON_BBOX_ACTIVATED_WIDTH / 2;
		t = y - BUTTON_BBOX_ACTIVATED_HEIGHT / 2;
		r = l + BUTTON_BBOX_ACTIVATED_WIDTH;
		b = t + BUTTON_BBOX_ACTIVATED_HEIGHT;

	}
}