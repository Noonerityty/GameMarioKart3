#include "LayerBackGround.h"

void CLayerBackGround::Render()
{
	//Render 1 sprite cua platform
	CSprites* sprites = CSprites::GetInstance();
	sprites->Get(this->spriteID)->Draw(x, y);
}

void CLayerBackGround::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	//Render 1 sprite cua platform
	l = x - this->cellWidth / 2;
	t = y - this->cellHeight / 2;
	r = l + this->cellWidth;
	b = t + this->cellHeight;
}
int CLayerBackGround::IsDirectionColliable(float nx, float ny)
{
 return 0;
}