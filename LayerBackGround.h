#pragma once
#include "GameObject.h"



class CLayerBackGround : public CGameObject
{
protected:

	float cellWidth;
	float cellHeight;

	int spriteID;
public:
	CLayerBackGround(float x, float y,
		float cell_width, float cell_height, int sprite_id) :CGameObject(x, y)
	{
		this->cellWidth = cell_width;
		this->cellHeight = cell_height;
		this->spriteID = sprite_id;
	}

	void Render();
	void Update(DWORD dt) {}
	void GetBoundingBox(float& l, float& t, float& r, float& b);
	int IsDirectionColliable(float nx, float ny);

};