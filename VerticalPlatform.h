#include "GameObject.h"

class CVerticalPlatform : public CGameObject
{
protected:
	int length;				
	float cellWidth;
	float cellHeight;
	int spriteIdBegin, spriteIdMiddle, spriteIdEnd;
public:
	CVerticalPlatform(float x, float y, int cellWidth, int cellHeight, int length, int spriteIdBegin, int spriteIdMidedle, int spriteIdEnd)
		: CGameObject(x, y)
	{
		this->length = length;
		this->cellWidth = cellWidth;
		this->cellHeight = cellHeight;
		this->spriteIdBegin = spriteIdBegin;
		this->spriteIdMiddle = spriteIdMidedle;
		this->spriteIdEnd = spriteIdEnd;
	}
	void Render();
	void Update(DWORD dt) {}
	void GetBoundingBox(float& l, float& t, float& r, float& b);
	void RenderBoundingBox();
};