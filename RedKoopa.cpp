#include "RedKoopa.h"
#include "SinglePlatform.h"
#include "QuestionBlock.h"
void CRedKoopa::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CKoopa::Update(dt, coObjects);

    if (state == KOOPA_STATE_WALKING)
    {
        // Kiểm tra nếu Koopa sắp rơi khỏi platform
        float checkDistance = 5.0f; // Khoảng cách kiểm tra phía trước
        float edgeX = (vx > 0) ? x + checkDistance : x - checkDistance;
        float edgeY = y + KOOPA_BBOX_HEIGHT; // Kiểm tra ở chân Koopa

        // Tìm các object tại vị trí mép platform
        bool hasGroundAhead = false;
        for (auto obj : *coObjects)
        {
            if (dynamic_cast<CSinglePlatform*>(obj) || dynamic_cast<CQuestionBlock*>(obj))
            {
                float objLeft, objTop, objRight, objBottom;
                obj->GetBoundingBox(objLeft, objTop, objRight, objBottom);

                // Kiểm tra xem có platform phía trước Koopa không
                if (edgeY >= objTop && edgeY <= objBottom)
                {
                    if ((vx > 0 && edgeX <= objRight && edgeX >= objLeft) ||
                        (vx < 0 && edgeX >= objLeft && edgeX <= objRight))
                    {
                        hasGroundAhead = true;
                        break;
                    }
                }
            }
        }

        // Nếu không có platform phía trước => Quay đầu
        if (!hasGroundAhead)
        {
            vx = -vx; // Đảo chiều di chuyển
        }
    }


}

void CRedKoopa::Render()
{
	int aniId = KOOPA_RED_ANI_WALKING_LEFT;
	switch (state)
	{
	case KOOPA_STATE_WALKING:
		if (vx > 0)
			aniId = KOOPA_RED_ANI_WALKING_RIGHT;
		else
			aniId = KOOPA_RED_ANI_WALKING_LEFT;
		break;
	case KOOPA_STATE_SHELL_IDLE:
		aniId = KOOPA_RED_ANI_SHELL_IDLE;
		break;
	case KOOPA_STATE_SHELL_MOVING:
		aniId = KOOPA_RED_ANI_SHELL_MOVING;
		break;
	case KOOPA_STATE_SHELL_EXIT:
		aniId = KOOPA_RED_ANI_SHELL_EXIT;
		break;
	}
	CAnimations::GetInstance()->Get(aniId)->Render(x, y);
}