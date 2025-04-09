#pragma once
#include "GameObject.h"

class CSinglePlatform : public CGameObject
{
protected:
	// Unit: cell 
	float cellWidth;
	float cellHeight;
	bool isCloud;
	int spriteID;
public:
	CSinglePlatform(float x, float y,
		float cell_width, float cell_height, bool iscloud ,int sprite_id) :CGameObject(x, y)
	{
		this->cellWidth = cell_width;
		this->cellHeight = cell_height;
		this->isCloud = iscloud;
		this->spriteID = sprite_id;
	}

	void Render();
	void Update(DWORD dt) {}
	void GetBoundingBox(float& l, float& t, float& r, float& b);
	int IsDirectionColliable(float nx, float ny);

};	