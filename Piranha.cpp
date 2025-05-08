#include "Piranha.h"
#include "Mario.h"
#include "PlayScene.h"
#include "PiranhaBullet.h"




struct ShootDirection
{
	float vx, vy;
};
ShootDirection shootDirections[4][2] =
{
	{{-PIRANHA_BULLET_SPEED_X_NARROW, -PIRANHA_BULLET_SPEED_Y_NARROW}, {-PIRANHA_BULLET_SPEED_X_WIDE,-PIRANHA_BULLET_SPEED_Y_WIDE } },// Mario ở trái trên
	{{PIRANHA_BULLET_SPEED_X_NARROW, -PIRANHA_BULLET_SPEED_Y_NARROW}, {PIRANHA_BULLET_SPEED_X_WIDE,-PIRANHA_BULLET_SPEED_Y_WIDE } },// Mario ở phải trên
	{{-PIRANHA_BULLET_SPEED_X_NARROW, PIRANHA_BULLET_SPEED_Y_NARROW}, {-PIRANHA_BULLET_SPEED_X_WIDE,PIRANHA_BULLET_SPEED_Y_WIDE } },// Mario ở trái dưới
	{{PIRANHA_BULLET_SPEED_X_NARROW, PIRANHA_BULLET_SPEED_Y_NARROW}, {PIRANHA_BULLET_SPEED_X_WIDE,PIRANHA_BULLET_SPEED_Y_WIDE } },// Mario ở phải dưới

};

void CPiranha::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	//if (state == PIRANHA_STATE_HIDDEN)
	//{
	//	DWORD timer = GetTickCount64() - state_start;
	//	if (timer > PIRANHA_HIDE_TIME)
	//	{
	//		float process = (float)timer / PIRANHA_HIDE_TIME;
	//		y = startY - PIRANHA_BBOX_HEIGHT * process;
	//	}
	//	else
	//	{

	//	}
	//}

	marioPosition = GetMarioRegion();
	DWORD timer = GetTickCount64() - state_start;
	switch (state)
	{
		case PIRANHA_STATE_HIDDEN:
		{
			y = startY;
			/*float distance = DistanceMario();*/
			if (IsMarioActiveZone())
			{
				
				if (timer > PIRANHA_HIDE_TIME)
				{

					SetState(PIRANHA_STATE_RISING);
				}
			}
			


			break;
		}
		case PIRANHA_STATE_RISING:
		{
			
			if (timer < PIRANHA_RISE_TIME)
			{
				float process = (float)timer / PIRANHA_RISE_TIME;
				y = startY - PIRANHA_BBOX_HEIGHT * process;
			}
			else
			{
				SetState(PIRANHA_STATE_SHOWING);
			}

			break;

		}
		case PIRANHA_STATE_SHOWING:
		{
			y = startY - PIRANHA_BBOX_HEIGHT;
			if (timer > PIRANHA_SHOW_TIME)
			{
				SetState(PIRANHA_STATE_SHOOTING);
			}
			break;
		}
		case PIRANHA_STATE_SHOOTING:
		{
			if(timer > PIRANHA_SHOOT_TIME)
			{
				SetState(PIRANHA_STATE_FALLING);
			}
			break;
		}
		case PIRANHA_STATE_FALLING:
		{
			if (timer < PIRANHA_FALL_TIME)
			{
				float process = (float)timer / PIRANHA_FALL_TIME;
				y = (startY - PIRANHA_BBOX_HEIGHT) + PIRANHA_BBOX_HEIGHT * process;
			}
			else
			{
				SetState(PIRANHA_STATE_HIDDEN);
			}

			break;
		}
		
		
	}
}

//void CPiranha::TrackingMarioAbove()
//{
//	CScene* currentScene = CGame::GetInstance()->GetCurrentScene();
//	CPlayScene* playscene = dynamic_cast<CPlayScene*>(currentScene);
//	CMario* mario = (CMario*)playscene->GetPlayer();
//	float marioX, marioY;
//	mario->GetPosition(marioX, marioY);
//	bool newIsMarioAbove = (marioY < this->y);
//	if (newIsMarioAbove != isMarioAbove)
//	{
//		isMarioAbove = newIsMarioAbove;
//	}
//}
int CPiranha::GetMarioRegion()
{
	CScene* currentScene = CGame::GetInstance()->GetCurrentScene();
	CPlayScene* playscene = dynamic_cast<CPlayScene*>(currentScene);
	CMario* mario = (CMario*)playscene->GetPlayer();
	if (mario == NULL)
		return -1;
	float marioX, marioY;
	mario->GetPosition(marioX, marioY);
	if (marioX <= this->x && marioY <= this->y)
	{
		return 0; //Mario ở trái trên
	}
	else if (marioX > this->x && marioY < this->y)
	{
		return 1; //Mario ở phải trên
	}
	else if (marioX < this->x && marioY > this->y)
	{
		return 2; //Mario ở trái dưới
	}
	else if (marioX >= this->x && marioY >= this->y)
	{
		return 3; //Mario ở phải dưới
	}

}
bool CPiranha::IsMarioActiveZone()
{
	CScene* currentScene = CGame::GetInstance()->GetCurrentScene();
	CPlayScene* playscene = dynamic_cast<CPlayScene*>(currentScene);
	CMario* mario = (CMario*)playscene->GetPlayer();
	if (mario == NULL)
		return false;
	float marioX, marioY;
	mario->GetPosition(marioX, marioY);
	float dx = abs(marioX - this->x);
	if (dx < PIRANHA_ACTIVE_ZONE_X && dx > PIRANHA_SAFE_ZONE_X)
	{
		return true;
	}
	return false;
}


void CPiranha::SetState(int state)
{
	CGameObject::SetState(state);
	state_start = GetTickCount64();
	switch (state)
	{
	case PIRANHA_STATE_HIDDEN:
		
		break;
	case PIRANHA_STATE_RISING:
		break;
	case PIRANHA_STATE_SHOOTING:
		Shoot();
		break;

	}
}
void CPiranha::Render()
{
	RenderBoudingBox();
	switch(state)
	{
		case PIRANHA_STATE_HIDDEN:
		{
			CSprites::GetInstance()->Get(100000)->Draw(x, y);
			break;
		}
		case PIRANHA_STATE_RISING:
		case PIRANHA_STATE_FALLING:
		{
			if (marioPosition == 0)
			{
				CAnimations::GetInstance()->Get(PIRANHA_ANIMATION_LEFT_ABOVE)->Render(x, y);
			}
			else if(marioPosition == 1)
			{
				CAnimations::GetInstance()->Get(PIRANHA_ANIMATION_RIGHT_ABOVE)->Render(x, y);
			}
			else if (marioPosition == 2)
			{
				CAnimations::GetInstance()->Get(PIRANHA_ANIMATION_LEFT_BELOW)->Render(x, y);
			}
			else if (marioPosition == 3)
			{
				CAnimations::GetInstance()->Get(PIRANHA_ANIMATION_RIGHT_BELOW)->Render(x, y);
			}

			break;
		}
		case PIRANHA_STATE_SHOWING:
		case PIRANHA_STATE_SHOOTING:
		{
			if (marioPosition == 0)
			{
				CSprites::GetInstance()->Get(PIRANHA_SPRITES_LEFT_ABOVE)->Draw(x, y);
			}
			else if(marioPosition == 1)
			{
				CSprites::GetInstance()->Get(PIRANHA_SPRITES_RIGHT_ABOVE)->Draw(x, y);
			}
			else if (marioPosition == 2)
			{
				CSprites::GetInstance()->Get(PIRANHA_SPRITES_LEFT_BELOW)->Draw(x, y);
			}
			else if (marioPosition == 3)
			{
				CSprites::GetInstance()->Get(PIRANHA_SPRITES_RIGHT_BELOW)->Draw(x, y);
			}

			
			break;
		}

		
	default:
		break;
	}
	//if (state == PIRANHA_STATE_HIDDEN)
	//{
	//	CSprites::GetInstance()->Get(100000)->Draw(x, y);
	//}
	//else if (state == PIRANHA_STATE_RISING || (state == PIRANHA_STATE_SHOWING && isMarioAbove == true))
	//{
	//	CAnimations::GetInstance()->Get(105001)->Render(x, y);
	//}
	//else if (state == PIRANHA_STATE_RISING || (state == PIRANHA_STATE_SHOWING && isMarioAbove == false))
	//{
	//	CSprites::GetInstance()->Get(100000)->Draw(x, y);
	//}

}
float CPiranha::DistanceMario()
{
	
	CScene* currentScene = CGame::GetInstance()->GetCurrentScene();
	CPlayScene* playscene = dynamic_cast<CPlayScene*>(currentScene);
	CMario* mario = (CMario*)playscene->GetPlayer();
	if (mario == NULL)
		return 0;
	float marioX, marioY;
	mario->GetPosition(marioX, marioY);
	float dx = marioX - this->x;
	float dy = marioY - this->y;
	return sqrt(dx * dx + dy * dy);
}
void CPiranha::Shoot()
{
	int region = GetMarioRegion();
	float distance = DistanceMario();
	int type = (distance < 80.0f) ? 1 : 0; // Narrow or wide bullet
	float vx = shootDirections[region][type].vx;
	float vy = shootDirections[region][type].vy;
	CPiranhaBullet* bullet = new CPiranhaBullet(x, y- 9, vx, vy);
	CScene* currentScene = CGame::GetInstance()->GetCurrentScene();
	CPlayScene* playscene = dynamic_cast<CPlayScene*>(currentScene);
	playscene->AddObject(bullet);

}
void CPiranha::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x - PIRANHA_BBOX_WIDTH / 2;
	t = y - PIRANHA_BBOX_HEIGHT / 2;
	r = l + PIRANHA_BBOX_WIDTH;
	b = t + PIRANHA_BBOX_HEIGHT;
}

void CPiranha::RenderBoudingBox()
{
	D3DXVECTOR3 p(x, y, 0);
	RECT rect;

	LPTEXTURE bbox = CTextures::GetInstance()->Get(ID_TEX_BBOX);

	float l, t, r, b;

	GetBoundingBox(l, t, r, b);
	rect.left = 0;
	rect.top = 0;
	rect.right = (int)r - (int)l;
	rect.bottom = (int)b - (int)t;

	float cx, cy;
	CGame::GetInstance()->GetCamPos(cx, cy);

	/*float yy = y - this->cellHeight / 2 + rect.bottom / 2;*/

	CGame::GetInstance()->Draw(x - cx, y - cy, bbox, nullptr, BBOX_ALPHA, rect.right - 1, rect.bottom - 1);
}
