#pragma once
#include "GameObject.h"

#include "GameObject.h"


#define TUNNEL_BBOX_WIDTH 16
#define TUNNEL_BBOX_HEIGHT 16

class CTunnel : public CGameObject
{
protected:
	int numberDoor;
public:
	CTunnel(float x, float y, int numberDoor) : CGameObject(x, y)
	{
		this->numberDoor = numberDoor;
	}

	void Render() { RenderBoundingBox(); }
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void GetBoundingBox(float& l, float& t, float& r, float& b);
	
	int GetNumberDoor() { return numberDoor; }
	virtual int IsBlocking() { return 0; }
	virtual int IsCollidable() { return 1; }
};
