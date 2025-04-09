#include "SinglePlatform.h"

void CSinglePlatform::Render()
{
	//Render 1 sprite cua platform
	CSprites* sprites = CSprites::GetInstance();
	sprites->Get(this->spriteID)->Draw(x, y);
}
void CSinglePlatform::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	//Render 1 sprite cua platform
	l = x - this->cellWidth / 2;
	t = y - this->cellHeight / 2;
	r = l + this->cellWidth;
	b = t + this->cellHeight;
}
int CSinglePlatform::IsDirectionColliable(float nx, float ny)
{
	if (this->isCloud)
	{
		if (nx == 0 && ny == -1) return 1;
		else return 0;
	}
	else
	{
		if (nx == 0 && ny == -1) return 1;
		else return 1;
	}
}
