
#include <algorithm>
#include "debug.h"

#include "Mario.h"
#include "Game.h"
#include "Sprite.h"


#include "Goomba.h"
#include "Coin.h"
#include "Portal.h"
#include "QuestionBlock.h"
#include "Mushroom.h"
#include "Piranha.h"
#include "PiranhaBullet.h"
#include "Leaf.h"
#include "ParaKoopa.h"
#include "TailRacoon.h"
#include "Button.h"
#include "Tunnel.h"

#include "Collision.h"

void CMario::Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects)
{
	//Diều chỉnh tốc độ rơi để đánh đuôi hơn

	vy += ay * dt;
	vx += ax * dt;

	
	

	//if (state == MARIO_STATE_DIE)
	//{
	//	// Chỉ cập nhật vị trí khi chết, bỏ qua các logic khác
	//	vx += ax * dt;
	//	vy += ay * dt;
	//	DebugOut(L"[INFO] Update in DIE state: vx = %f, vy = %f, heldKoopa = %p\n", vx, vy, heldKoopa);
	//	return; // Thoát sớm để tránh xử lý logic không cần thiết
	//}

	if (abs(vx) > abs(maxVx)) vx = maxVx;
	if (timer >= 0 && state != MARIO_STATE_DIE)
	{
		ULONGLONG currentTime = GetTickCount64();
		/*timer1s += dt;
		if (timer1s >= 1000)
		{
			TimerEvent();
			timer1s -= 1000;
		}*/
		if (currentTime - timer1s >= 1000)
		{
			Timer1sEvent();
			timer1s = currentTime; // Reset timer1s to current time
		}

	}
	
	if (isStunned)
	{
		vx = 0;
		vy = 0;
		if (GetTickCount64() - stunned_start > MARIO_STUNNED_TIME)
		{
			isStunned = false;
			
		}
		
		return;

	
	}



	//DebugOut(L"[INFO] Mario state: %d, level: %d, isTailAttacking: %d, isHolding: %d, isKickingKoopa: %d\n", state, level, isTailAttacking, isHolding, isKickingKoopa);


	if (isKickingKoopa)
	{
		/*ULONGLONG timer = GetTickCount64();*/
		if (GetTickCount64() - kick_time_out > MARIO_KICK_TIME && isKickingKoopa == true)
		{
			isKickingKoopa = false;
		}
	}
	if (heldKoopa != NULL && isHolding)
	{
		float offsetX = 0;
		float offsetY = 0;

		offsetX = (nx > 0) ? 8.0f : -8.0f;
		if (level != MARIO_LEVEL_SMALL)
		{
			offsetY = 4.0f;
		}
		else
		{
			offsetY = -2.0f;

		}
		float koopaX = x + offsetX;
		float koopaY = y + offsetY;

		heldKoopa->SetPosition(koopaX, koopaY);
		// Kiểm tra nếu Koopa chuyển sang trạng thái WALKING
		if (heldKoopa->GetState() == KOOPA_STATE_WALKING)
		{
			ProcessMarioDie();
			isHolding = false;
		
		}
	}
	//p_Meter
	if (abs(vx) >= MARIO_RUNNING_SPEED - 0.05)
	{
		p_meter += MARIO_P_METER_CHARGE_RATE * dt;
		if (p_meter > MARIO_P_METER_MAX)
		{
			p_meter = MARIO_P_METER_MAX;
			if (level == MARIO_LEVEL_RACOON)
			{
				/*if (CGame::GetInstance()->IsKeyDown(DIK_S))
				{
					canFly = true;
				}*/
				canFly = true; 
				isTailAttacking = false; // Reset tail attack when running fast
			}
		}
	}
	else
	{
		if (p_meter > 0)
		{
			p_meter -= MARRIO_P_METER_DECREASE_RATE * dt;
			if (p_meter < 0) p_meter = 0;
			canFly = false; // Không thể bay nếu không chạy
		}
	}

	DebugOut(L"ISTUNNELDOOR: %d\n", isTunnelDoor);
	//if (isSliding)
	//{
	//	ULONGLONG currentTime = GetTickCount64();

	//	if (slidePhase == 1 && currentTime - slideStartTime < 500)
	//	{
	//		// Giai đoạn 1: Trượt xuống
	//		vx = 0;
	//		ax = 0;
	//		ay = 0;
	//		float process = (float)currentTime / 500;
	//		y = startY - 32 * process;
	//	}
	//	else if (slidePhase == 1 && currentTime - slideStartTime >= 500)
	//	{
	//		slidePhase = 2; // Chuyển sang giai đoạn 2
	//		slideStartTime = currentTime; // Reset thời gian bắt đầu trượt
	//		DebugOut(L"[INFO] Mario finished sliding phase 1, now in phase 2\n");
	//	}
	//	else if (slidePhase == 2 && currentTime - slideStartTime < 500)
	//	{
	//		// Giai đoạn 2: Trượt xuống và dừng lại
	//		vx = 0;
	//		ax = 0;
	//		ay = 0;
	//		float process = (float)currentTime / 500;
	//		x = 10;
	//		y = startY - 32 * process;
	//	}
	//	else if (slidePhase == 2 && currentTime - slideStartTime >= 500)
	//	{
	//		isSliding = false; // Kết thúc trượt
	//	}
	//}
	
	InputTunnelDoor();
	OutputTunnelDoor();
	
	
	//else
	//{
	//	// Kích hoạt trượt lần 1
	//	if (isTunnelDoor && CGame::GetInstance()->IsKeyDown(DIK_DOWN) && isOnPlatform && level == MARIO_LEVEL_RACOON && !isSitting && !isHolding && !isTailAttacking)
	//	{
	//		isSliding = true;
	//		slideStartTime = GetTickCount64();
	//		startY = y;
	//		slidePhase = 1;
	//		vx = 0;
	//		ax = 0;
	//		ay = 0;
	//		DebugOut(L"[INFO] Mario started sliding phase 1 at y = %f\n", y);
	//	}
	//}


	if (level == MARIO_LEVEL_RACOON)
	{
		
		

		if (isTailAttacking)
		{
			if (GetTickCount64() - tailAttackStartTime > MARIO_TAIL_ATTACK_FRAME_TIME && !tailCreated)
			{
				TailAttackEvent();
				tailCreated = true;
			}
			if (GetTickCount64() - tailAttackStartTime > MArio_TAIL_ATTACK_TIMEOUT)
			{
				isTailAttacking = false;
				tailCreated = false; // Reset tailCreated when tail attack ends
			}

			if (!isOnPlatform)
			{
				vy = 0.01f; // Giữ Mario đứng yên trong trạng thái tấn công đuôi
				ay = MARIO_FLYING_GRAVITY;
			}


		}
		else
		{
			ay = MARIO_GRAVITY;
		}
		
		if (isFlying)
		{
			if (jumpPressed && !jumpPressedLastFrame)
			{
				vy = MARRIO_FLYING_BOOST;
				ay = MARIO_FLYING_GRAVITY;
				lastSpamFly = GetTickCount64();
			}

			if (GetTickCount64() - lastSpamFly > MARIO_SPAM_FLY_TIME)
			{
				isFlying = false;
			}
		}
		else
		{
			ay = MARIO_GRAVITY;
		}
		


		if (jumpPressed && !jumpPressedLastFrame && vy > 0)
		{
			vy = min(vy, 0.05);
			ay = MARIO_FLYING_GRAVITY;
		}
		else
		{
			ay = MARIO_GRAVITY;
		}


	}
	
	//if (isFlying && level == MARIO_LEVEL_RACOON)
	//{

	//	if (jumpPressed && !jumpPressedLastFrame)
	//	{
	//		vy = -1;
	//		/*ay = MARIO_FLYING_GRAVITY;*/
	//		lastSpamFly = GetTickCount64();
	//	}

	//	if (GetTickCount64() - lastSpamFly > MARIO_SPAM_FLY_TIME)
	//	{
	//		isFlying = false;
	//	}
	//}
	//else
	//{
	//	if (jumpPressed && !jumpPressedLastFrame && vy > 0)
	//	{
	//		vy = min(vy, 0.05);
	//	}
	//	
	//}


	if (y < MARIO_MAX_FLYING_HEIGHT && vy < 0)
	{
		y = MARIO_MAX_FLYING_HEIGHT;
		vy = 0.0f;
	}
	/*DebugOut(L"[INFO] Mario position: x = %f, y = %f, vx = %f, vy = %f\n", x, y, vx, vy);*/
	/*DebugOut(L"[DEBUG] dt = %d, p_meter = %f\n", dt, p_meter);*/
	// reset untouchable timer if untouchable time has passed
	if ( GetTickCount64() - untouchable_start > MARIO_UNTOUCHABLE_TIME) 
	{
		untouchable_start = 0;
		untouchable = 0;
	}

	

	jumpPressedLastFrame = jumpPressed;
	CGameObject::Update(dt, coObjects);

	CCollision::GetInstance()->Process(this, dt, coObjects);
}

void CMario::OnNoCollision(DWORD dt)
{
	x += vx * dt;
	y += vy * dt;
	isOnPlatform = false;
	//DebugOut(L"[INFO] Mario on no platform\n");
}

void CMario::OnCollisionWith(LPCOLLISIONEVENT e)
{
	if (e->ny != 0 && e->obj->IsBlocking())
	{
		vy = 0;
		if (e->ny < 0) isOnPlatform = true;
	/*	DebugOut(L"[INFO] Mario on platform\n");*/
	}
	else 
	if (e->nx != 0 && e->obj->IsBlocking())
	{
		vx = 0;
	}

	if (dynamic_cast<CGoomba*>(e->obj))
		OnCollisionWithGoomba(e);
	else if (dynamic_cast<CCoin*>(e->obj))
		OnCollisionWithCoin(e);
	else if (dynamic_cast<CPortal*>(e->obj))
		OnCollisionWithPortal(e);
	else if (dynamic_cast<CQuestionBlock*>(e->obj))
		OnCollisionWithQuestionBlock(e);
	else if (dynamic_cast<CMushroom*>(e->obj))
		OnCollisionWithMushroom(e);
	else if (dynamic_cast<CPiranha*>(e->obj))
		OnCollisionWithPiranha(e);
	else if (dynamic_cast<CPiranhaBullet*>(e->obj))
		OnCollisionWithPiranhaBullet(e);
	else if (dynamic_cast<CKoopa*>(e->obj))
		OnCollisionWithKoopa(e);
	else if (dynamic_cast<CLeaf*>(e->obj))
		OnCollisionWithLeaf(e);
	else if (dynamic_cast<CButton*>(e->obj))
		OnCollisionWithButton(e);
	else if (dynamic_cast<CTunnel*> (e->obj))
		OnCollisionWithTunnel(e);
	



}



void CMario::OnCollisionWithKoopa(LPCOLLISIONEVENT e)
{
	CKoopa* koopa = dynamic_cast<CKoopa*>(e->obj);
	
	if (e->ny < 0)
	{
		score += 100;
		if (koopa->GetState() == KOOPA_STATE_WALKING)
		{
			koopa->SetState(KOOPA_STATE_SHELL_IDLE);
			vy = -MARIO_JUMP_DEFLECT_SPEED;
		}
		if (koopa->GetState() == KOOPA_STATE_WALKING_WING || koopa->GetState() == KOOPA_STATE_JUMPING)
		{
			CParaKoopa* paraKoopa = dynamic_cast<CParaKoopa*>(koopa);
			if (paraKoopa)
			{
				paraKoopa->SetState(KOOPA_STATE_WALKING);
				vy = -MARIO_JUMP_DEFLECT_SPEED;
				DebugOut(L"[INFO] Mario hit ParaKoopa with wing. Now walking.\n");
			}
		}
		else if(koopa->GetState() == KOOPA_STATE_SHELL_IDLE && isHolding == false)
		{
			koopa->GetMarioX(x);
			koopa->SetState(KOOPA_STATE_SHELL_MOVING);
			vy = -MARIO_JUMP_DEFLECT_SPEED;
			
		}
		else if (koopa->GetState() == KOOPA_STATE_SHELL_MOVING)
		{
			koopa->SetState(KOOPA_STATE_SHELL_IDLE);
			vy = -MARIO_JUMP_DEFLECT_SPEED;
		}
	}
	else if (koopa->GetState() == KOOPA_STATE_SHELL_IDLE)
	{
		if (e->ny == 0)
		{
			if (CGame::GetInstance()->IsKeyDown(DIK_A) && isSitting == false)
			{
				heldKoopa = koopa;
				isHolding = true;
				
			}
			else if(isHolding == false)
			{
				koopa->GetMarioX(x);
				isKickingKoopa = true;
				koopa->SetState(KOOPA_STATE_SHELL_MOVING);

			}

			
		}
	}
	else if(koopa->GetTakeDamgeFromKoopa())
	{
		if (untouchable == 0 || isStunned)
		{
			if (koopa->GetState() != KOOPA_STATE_DIE)
			{
				ProcessMarioDie();
			}
		}
	}
}

void CMario::ReleaseKoopa()
{
	score += 200;
	if (heldKoopa && isHolding)
	{
		heldKoopa->SetState(KOOPA_STATE_SHELL_MOVING);
		heldKoopa = NULL;
		isHolding = false;
		isKickingKoopa = true;
		kick_time_out = GetTickCount64();
	}
}
void CMario::OnCollisionWithPiranhaBullet(LPCOLLISIONEVENT e)
{
	CPiranhaBullet* piranhaBullet = dynamic_cast<CPiranhaBullet*>(e->obj);
	if (untouchable == 0 || isStunned)
	{
		
		
		ProcessMarioDie();
		
	}
}

void CMario::OnCollisionWithPiranha(LPCOLLISIONEVENT e)
{
	CPiranha* piranha = dynamic_cast<CPiranha*>(e->obj);
	if (e->ny < 0)
	{

	}
	else
	{
		if (untouchable == 0 || isStunned)
		{
			if (piranha->GetState() != PIRANHA_STATE_DIE && piranha->GetState() != PIRANHA_STATE_HIDDEN)
			{
				ProcessMarioDie();
			}
		}
	}
}

void CMario::OnCollisionWithGoomba(LPCOLLISIONEVENT e)
{
	CGoomba* goomba = dynamic_cast<CGoomba*>(e->obj);

	// jump on top >> kill Goomba and deflect a bit 
	if (e->ny < 0)
	{
		score += 100;
		if (goomba->GetState() != GOOMBA_STATE_DIE)
		{
			goomba->SetState(GOOMBA_STATE_DIE);
			vy = -MARIO_JUMP_DEFLECT_SPEED;
		}
	}
	else 
	{
		if (untouchable == 0 || isStunned)
		{
			if (goomba->GetState() != GOOMBA_STATE_DIE)
			{
				ProcessMarioDie();
			}
		}
	}
}

void CMario::OnCollisionWithCoin(LPCOLLISIONEVENT e)
{
	e->obj->Delete();
	coin++;
	score += 200;
}
void CMario::OnCollisionWithMushroom(LPCOLLISIONEVENT e)
{
	CMushroom* mushroom = dynamic_cast<CMushroom*>(e->obj);
	if (mushroom->GetState() != MUSHROOM_STATE_DIE)
	{
		score += 1000;
		if (level == MARIO_LEVEL_SMALL)
		{
			SetLevel(MARIO_LEVEL_BIG);
			mushroom->SetState(MUSHROOM_STATE_DIE);
			
			StartStunned();
			StartUntouchable();
		}
		else
		{
			mushroom->SetState(MUSHROOM_STATE_DIE);
		}
	}
}

void CMario::OnCollisionWithLeaf(LPCOLLISIONEVENT e)
{
	//SetLevel(MARIO_LEVEL_RACOON);
		CLeaf* leaf = dynamic_cast<CLeaf*>(e->obj);
	if (leaf->GetState() != LEAF_STATE_DIE)
	{
		score += 1000;
		if (level == MARIO_LEVEL_SMALL || level == MARIO_LEVEL_BIG)
		{
			SetLevel(MARIO_LEVEL_RACOON);
			leaf->SetState(LEAF_STATE_DIE);
			/*StartStunned();*/
			StartStunned();
			StartUntouchable();
		}
		else
		{
			leaf->SetState(LEAF_STATE_DIE);
		}
	}
}

void CMario::OnCollisionWithTunnel(LPCOLLISIONEVENT e)
{
	CTunnel* tunnel1 = dynamic_cast<CTunnel*>(e->obj);
	if (tunnel1)
	{
		
		if (tunnel1->GetNumberDoor() == 1 && isOnPlatform)
		{
			isTunnelDoor = 1;
			

		}
		else if (tunnel1->GetNumberDoor() == 2 && e->ny > 0)
		{
			isTunnelDoor = 2;
		}
	}
}

void CMario::OnCollisionWithQuestionBlock(LPCOLLISIONEVENT e)
{
	CQuestionBlock* qblock = dynamic_cast<CQuestionBlock*>(e->obj);
	//if (qblock->GetItemType() == QUESTION_NLOCK_ITEM_TYPE_SIMPLE_BRICK)
	//{
	//	if (e->ny > 0)
	//	{
	//		this->Delete();
	//	}
	//}
	if (e->ny > 0)
	{
		qblock->TriggerQuestionBlock();
		score += 50;
	}
	/*DebugOut(L"[INFO] Mario hit question block\n");*/
	/*if(qblock->GetItemType() == 0)
	coin++;*/

}

void CMario::OnCollisionWithButton(LPCOLLISIONEVENT e)
{
	CButton* button = dynamic_cast<CButton*>(e->obj);
	if (e->ny < 0 && !button->IsActivated())
	{
		button->Activate();
		CPlayScene* playScene = dynamic_cast<CPlayScene*>(CGame::GetInstance()->GetCurrentScene());
		if (playScene)
		{
			
			for (auto obj : playScene->GetQuestionBlocks())
			{
				
				CQuestionBlock* qBlock = dynamic_cast<CQuestionBlock*>(obj);
				if (qBlock == NULL) continue; // Kiểm tra nếu obj là CQuestionBlock
				if (qBlock && qBlock->IsDeletedQBlock())
				{
					continue;
				}
				if (qBlock && qBlock->GetItemTypeOfQuestionBlock() == QUESTION_NLOCK_ITEM_TYPE_SIMPLE_BRICK) 
				{
					qBlock->ConvertToCoin(); // Chuyển đổi thành coin
				}
				
			}
		}
	}
}

void CMario::OnCollisionWithPortal(LPCOLLISIONEVENT e)
{
	CPortal* p = (CPortal*)e->obj;
	CGame::GetInstance()->InitiateSwitchScene(p->GetSceneId());
}

//
// Get animation ID for small Mario
//
int CMario::GetAniIdSmall()
{
	int aniId = -1;
	if (!isOnPlatform)
	{
		if (abs(ax) == MARIO_ACCEL_RUN_X)
		{
			if (nx >= 0)
				aniId = ID_ANI_MARIO_SMALL_JUMP_RUN_RIGHT;
			else
				aniId = ID_ANI_MARIO_SMALL_JUMP_RUN_LEFT;
		}
		else
		{
			if (nx >= 0)
				aniId = ID_ANI_MARIO_SMALL_JUMP_WALK_RIGHT;
			else
				aniId = ID_ANI_MARIO_SMALL_JUMP_WALK_LEFT;
		}
	}
	else
		if (isSitting)
		{

			if (nx > 0)
				aniId = ID_ANI_MARIO_SIT_RIGHT;
			else
				aniId = ID_ANI_MARIO_SIT_LEFT;
		}
		else if (isHolding)
		{
			if (vx == 0)
			{
				if (nx > 0)
					aniId = ID_ANI_MARIO_SMALL_HOLD_KOOPA_RIGHT_IDLE;
				else
					aniId = ID_ANI_MARIO_SMALL_HOLD_KOOPA_LEFT_IDLE;

			}
			else if (vx > 0)
			{
					aniId = ID_ANI_MARIO_SMALL_HOLD_KOOPA_RIGHT;
			}
			else
			{
				aniId = ID_ANI_MARIO_SMALL_HOLD_KOOPA_LEFT;
			}

			//if (nx > 0)
			//	aniId = ID_ANI_MARIO_HOLD_KOOPA_RIGHT;
			//else
			//	aniId = ID_ANI_MARIO_HOLD_KOOPA_LEFT;
		}
		else if (isKickingKoopa)
		{
			if (vx > 0)
			{
				aniId = ID_ANI_MARIO_SMALL_KICK_KOOPA_RIGHT;

			}
			else if (vx < 0)
			{
				aniId = ID_ANI_MARIO_SMALL_KICK_KOOPA_LEFT;
			}
			
			DebugOut(L">>> Mario DIE >>> \n");
		}
		else
			if (vx == 0)
			{
				if (nx > 0) aniId = ID_ANI_MARIO_SMALL_IDLE_RIGHT;
				else aniId = ID_ANI_MARIO_SMALL_IDLE_LEFT;
			}
			else if (vx > 0)
			{
				if (ax < 0)
					aniId = ID_ANI_MARIO_SMALL_BRACE_RIGHT;
				else if (ax == MARIO_ACCEL_RUN_X)
					aniId = ID_ANI_MARIO_SMALL_RUNNING_RIGHT;
				else if (ax == MARIO_ACCEL_WALK_X)
					aniId = ID_ANI_MARIO_SMALL_WALKING_RIGHT;
			}
			else // vx < 0
			{
				if (ax > 0)
					aniId = ID_ANI_MARIO_SMALL_BRACE_LEFT;
				else if (ax == -MARIO_ACCEL_RUN_X)
					aniId = ID_ANI_MARIO_SMALL_RUNNING_LEFT;
				else if (ax == -MARIO_ACCEL_WALK_X)
					aniId = ID_ANI_MARIO_SMALL_WALKING_LEFT;
			}

	if (aniId == -1) aniId = ID_ANI_MARIO_SMALL_IDLE_RIGHT;

	return aniId;
}


//
// Get animdation ID for big Mario
//
int CMario::GetAniIdBig()
{
	int aniId = -1;
	if (!isOnPlatform)
	{
		if (abs(ax) == MARIO_ACCEL_RUN_X)
		{
			if (nx >= 0)
				aniId = ID_ANI_MARIO_JUMP_RUN_RIGHT;
			else
				aniId = ID_ANI_MARIO_JUMP_RUN_LEFT;
		}
		else
		{
			if (nx >= 0)
				aniId = ID_ANI_MARIO_JUMP_WALK_RIGHT;
			else
				aniId = ID_ANI_MARIO_JUMP_WALK_LEFT;
		}
	}
	else
		if (isSitting)
		{
			if (nx > 0)
				aniId = ID_ANI_MARIO_SIT_RIGHT;
			else
				aniId = ID_ANI_MARIO_SIT_LEFT;
		}
		else if (isHolding)
		{
			if (vx == 0)
			{
				if (nx > 0)
					aniId = ID_ANI_MARIO_HOLD_KOOPA_RIGHT_IDLE;
				else
					aniId = ID_ANI_MARIO_HOLD_KOOPA_LEFT_IDLE;

			}
			else if (vx > 0)
			{
				aniId = ID_ANI_MARIO_HOLD_KOOPA_RIGHT;
			}
			else
			{
				aniId = ID_ANI_MARIO_HOLD_KOOPA_LEFT;
			}

		}
		else if (isKickingKoopa)
		{
			if (vx > 0)
			{
				aniId = ID_ANI_MARIO_KICK_KOOPA_RIGHT;

			}
			else if (vx < 0)
			{
				aniId = ID_ANI_MARIO_KICK_KOOPA_LEFT;
			}
		
			
		}
		
		else
			if (vx == 0)
			{
				if (nx > 0) aniId = ID_ANI_MARIO_IDLE_RIGHT;
				else aniId = ID_ANI_MARIO_IDLE_LEFT;
			}
			else if (vx > 0)
			{
				if (ax < 0)
					aniId = ID_ANI_MARIO_BRACE_RIGHT;
				else if (ax == MARIO_ACCEL_RUN_X)
					aniId = ID_ANI_MARIO_RUNNING_RIGHT;
				else if (ax == MARIO_ACCEL_WALK_X)
					aniId = ID_ANI_MARIO_WALKING_RIGHT;
			}
			else // vx < 0
			{
				if (ax > 0)
					aniId = ID_ANI_MARIO_BRACE_LEFT;
				else if (ax == -MARIO_ACCEL_RUN_X)
					aniId = ID_ANI_MARIO_RUNNING_LEFT;
				else if (ax == -MARIO_ACCEL_WALK_X)
					aniId = ID_ANI_MARIO_WALKING_LEFT;
			}

	if (aniId == -1) aniId = ID_ANI_MARIO_IDLE_RIGHT;

	return aniId;
}

int CMario::GetAniIdRacoon()
{
	int aniId = -1;
	if (isTailAttacking)
	{
		if (vx == 0)
		{
			if (nx > 0)
			{
				aniId = ID_ANI_MARIO_RACOON_TAIL_ATTACK_IDLE_RIGHT;
			}
			else
			{
				aniId = ID_ANI_MARIO_RACOON_TAIL_ATTACK_IDLE_LEFT;
			}
		}
		else if(vx > 0)
		{
			aniId = ID_ANI_MARIO_RACOON_TAIL_ATTACK_MOVING_RIGHT;
		}
		else if (vx < 0)
		{
			aniId = ID_ANI_MARIO_RACOON_TAIL_ATTACK_MOVING_LEFT;
		}
	}
	else if (isFlying)
	{
		if (nx >= 0)
			aniId = ID_ANI_MARIO_RACOON_FLYING_RIGHT;
		else
			aniId = ID_ANI_MARIO_RACOON_FLYING_LEFT;
	}
	else if (!isOnPlatform)
	{
		if (abs(ax) == MARIO_ACCEL_RUN_X)
		{
			if (nx >= 0)
				aniId = ID_ANI_MARIO_RACOON_JUMP_RUN_RIGHT;
			else
				aniId = ID_ANI_MARIO_RACOON_JUMP_RUN_LEFT;
		}
		else
		{
			if (nx >= 0)
				aniId = ID_ANI_MARIO_RACOON_JUMP_WALK_RIGHT;
			
			else
				aniId = ID_ANI_MARIO_RACOON_JUMP_WALK_LEFT;
		}
	}
	else
		if (isSitting)
		{
			if (nx > 0)
				aniId = ID_ANI_MARIO_RACOON_SIT_RIGHT;
			else
				aniId = ID_ANI_MARIO_RACOON_SIT_LEFT;
		}
		else if (isHolding)
		{
			if (vx == 0)
			{
				if (nx > 0)
					aniId = ID_ANI_MARIO_RACOON_HOLD_KOOPA_RIGHT_IDLE;
				else
					aniId = ID_ANI_MARIO_RACOON_HOLD_KOOPA_LEFT_IDLE;

			}
			else if (vx > 0)
			{
				aniId = ID_ANI_MARIO_RACOON_HOLD_KOOPA_RIGHT;
			}
			else
			{
				aniId = ID_ANI_MARIO_RACOON_HOLD_KOOPA_LEFT;
			}

		}

		else if (isKickingKoopa)
		{
			if (vx > 0)
			{
				aniId = ID_ANI_MARIO_RACOON_KICK_KOOPA_RIGHT;

			}
			else if (vx < 0)
			{
				aniId = ID_ANI_MARIO_RACOON_KICK_KOOPA_LEFT;
			}
			
		}
		else
		{
			if (vx == 0)
				if (nx > 0) aniId = ID_ANI_MARIO_RACOON_IDLE_RIGHT;
				else aniId = ID_ANI_MARIO_RACOON_IDLE_LEFT;
			else if (vx > 0)
			{
				if (ax < 0)
					aniId = ID_ANI_MARIO_RACOON_BRACE_RIGHT;
				else if (abs(ax) == MARIO_ACCEL_RUN_X)
					aniId = ID_ANI_MARIO_RACOON_RUNNING_RIGHT;
				else
					aniId = ID_ANI_MARIO_RACOON_WALKING_RIGHT;
			}
			else if(vx < 0)
			{
				if (ax > 0)
					aniId = ID_ANI_MARIO_RACOON_BRACE_LEFT;
				else if (abs(ax) == MARIO_ACCEL_RUN_X)
					aniId = ID_ANI_MARIO_RACOON_RUNNING_LEFT;
				else
					aniId = ID_ANI_MARIO_RACOON_WALKING_LEFT;
			}
		}


	if (aniId == -1)
	{
		aniId =ID_ANI_MARIO_RACOON_IDLE_RIGHT;
	}

	return aniId;
}

void CMario::Render()
{
	CAnimations* animations = CAnimations::GetInstance();
	int aniId = -1;

	if (state == MARIO_STATE_DIE)
		aniId = ID_ANI_MARIO_DIE;
	else
	{
			 if (level == MARIO_LEVEL_RACOON)
				aniId = GetAniIdRacoon();
			else if (level == MARIO_LEVEL_BIG)
				aniId = GetAniIdBig();
			else if (level == MARIO_LEVEL_SMALL)
				aniId = GetAniIdSmall();
	}

	/*DebugOut(L"[DEBUG] Render Mario state: %d, level: %d, aniId: %d\n", isKickingKoopa	, level, aniId);*/
	
	animations->Get(aniId)->Render(x, y);

	//RenderBoundingBox();
	
	DebugOutTitle(L"Coins: %d", coin);
}

void CMario::SetState(int state)
{
	// DIE is the end state, cannot be changed! 
	if (this->state == MARIO_STATE_DIE) return; 

	switch (state)
	{
	case MARIO_STATE_RUNNING_RIGHT:
		if (isSitting) break;
		maxVx = MARIO_RUNNING_SPEED;
		ax = MARIO_ACCEL_RUN_X;
		nx = 1;
		break;
	case MARIO_STATE_RUNNING_LEFT:
		if (isSitting) break;
		maxVx = -MARIO_RUNNING_SPEED;
		ax = -MARIO_ACCEL_RUN_X;
		nx = -1;
		break;
	case MARIO_STATE_WALKING_RIGHT:
		if (isSitting) break;
		maxVx = MARIO_WALKING_SPEED;
		ax = MARIO_ACCEL_WALK_X;
		nx = 1;
		break;
	case MARIO_STATE_WALKING_LEFT:
		if (isSitting) break;
		maxVx = -MARIO_WALKING_SPEED;
		ax = -MARIO_ACCEL_WALK_X;
		nx = -1;
		break;
	case MARIO_STATE_JUMP:
		if (isSitting) break;
		if (isOnPlatform)
		{
			if (canFly)
			{
				isFlying = true;

				canFly = false; // Reset flying ability after jump
				p_meter = 0; // Reset power meter after flying

			}
			else
			{
				if (abs(this->vx) == MARIO_RUNNING_SPEED)
					vy = -MARIO_JUMP_RUN_SPEED_Y * 1.2;
				else
					vy = -MARIO_JUMP_SPEED_Y * 1.1;
			}


			
		}
		break;

	case MARIO_STATE_RELEASE_JUMP:
		if (vy < 0) vy += MARIO_JUMP_SPEED_Y / 2 /* normal la 2*/;
		break;

	case MARIO_STATE_SIT:
		if (isOnPlatform && level != MARIO_LEVEL_SMALL)
		{
			state = MARIO_STATE_IDLE;
			isSitting = true;
			vx = 0; vy = 0.0f;
			y +=MARIO_SIT_HEIGHT_ADJUST;
		}
		break;

	case MARIO_STATE_SIT_RELEASE:
		if (isSitting)
		{
			isSitting = false;
			state = MARIO_STATE_IDLE;
			y -= MARIO_SIT_HEIGHT_ADJUST;
		}
		break;

	case MARIO_STATE_IDLE:
		ax = 0.0f;
		vx = 0.0f;
		break;

	case MARIO_STATE_DIE:
		vy = -MARIO_JUMP_DEFLECT_SPEED;
		vx = 0;
		ax = 0;

		break;
	}

	CGameObject::SetState(state);
}

void CMario::GetBoundingBox(float &left, float &top, float &right, float &bottom)
{
	if (level==MARIO_LEVEL_BIG)
	{
		if (isSitting)
		{
			left = x - MARIO_BIG_SITTING_BBOX_WIDTH / 2;
			top = y - MARIO_BIG_SITTING_BBOX_HEIGHT / 2;
			right = left + MARIO_BIG_SITTING_BBOX_WIDTH;
			bottom = top + MARIO_BIG_SITTING_BBOX_HEIGHT;
		}
		else 
		{
			left = x - MARIO_BIG_BBOX_WIDTH/2;
			top = y - MARIO_BIG_BBOX_HEIGHT/2;
			right = left + MARIO_BIG_BBOX_WIDTH;
			bottom = top + MARIO_BIG_BBOX_HEIGHT;
		}
	}
	else if (level == MARIO_LEVEL_RACOON)
	{
		if (isSitting)
		{
			left = x - 10;
			top = y - 8;
			right = left + 20;
			bottom = top + 16;
		}
		else
		{
			left = x - 10;
			top = y - 12;
			right = left + 20;
			bottom = top + 24;
		}

	}
	else
	{
		left = x - MARIO_SMALL_BBOX_WIDTH/2;
		top = y - MARIO_SMALL_BBOX_HEIGHT/2;
		right = left + MARIO_SMALL_BBOX_WIDTH;
		bottom = top + MARIO_SMALL_BBOX_HEIGHT;
	}
}

void CMario::SetLevel(int l)
{
	// Adjust position to avoid falling off platform
	if (state == MARIO_STATE_DIE) return;
	if (this->level == MARIO_LEVEL_SMALL)
	{
		y -= (MARIO_BIG_BBOX_HEIGHT - MARIO_SMALL_BBOX_HEIGHT) / 2;
	}
	level = l;
}

void CMario::ProcessMarioDie()
{
	//if (state == MARIO_STATE_DIE)
	//	return;
	//if (timer <= 0)
	//{/*
	//	SetLevel(MARIO_LEVEL_SMALL);*/
	//	SetState(MARIO_STATE_DIE);
	//	//StartUntouchable();
	//}
	if(level == MARIO_LEVEL_RACOON)
	{
		SetLevel(MARIO_LEVEL_BIG);
	}
	else if (level == MARIO_LEVEL_BIG)
	{
		SetLevel(MARIO_LEVEL_SMALL);
	}
	else
	{
		SetState(MARIO_STATE_DIE);
	}
	StartUntouchable();

}

void CMario::StartTailAttack()
{

	if (isTailAttacking || p_meter >= MARIO_P_METER_MAX - 0.05)
		return;
	
	isTailAttacking = true;
	tailAttackStartTime = GetTickCount64();
	tailCreated = false;
}

void CMario::TailAttackEvent()
{

	float tailX;
	float tailY;
	if (nx > 0)
	{
		tailX = x + MARIO_TAIL_ATTACK_OFFSET_X; //10 
	}
	else
	{
		tailX = x - MARIO_TAIL_ATTACK_OFFSET_X;
	}
	tailY = y + MARIO_TAIL_ATTACK_OFFSET_Y; //6
	CScene* currentScene = CGame::GetInstance()->GetCurrentScene();
	CPlayScene* playscene = dynamic_cast<CPlayScene*>(currentScene);

	playscene->AddObject(new CTailRacoon(tailX, tailY, this));
	DebugOut(L"[INFO] Mario created tail at position: x = %f, y = %f\n", tailX, this->x);
	
}

void CMario::Timer1sEvent()
{
	if (state != MARIO_STATE_DIE && timer >= 0)
	{
		timer--;
		if (timer < 0)
		{
			ProcessMarioDie();
			DebugOut(L"[INFO] Timer reached zero, processing Mario die\n");
		}
	}
}

void CMario::InputTunnelDoor()
{
	if (isSliding && isTunnelDoor == 1)
	{
		ULONGLONG now = GetTickCount64();
		float elapsed = (float)(now - slideStartTime);
		if (slidePhase == 1)
		{
			if (elapsed < MARIO_TUNNEL_DOOR_TIME) // Giai đoạn 1: Trượt xuống từ từ trong 500ms
			{
				float process = elapsed / MARIO_TUNNEL_DOOR_TIME; // Tỉ lệ thời gian đã trôi qua (0 -> 1)
				y = startY + MARIO_TUNNEL_OFFSETY * process;    // Di chuyển y từ startY đến startY + 32
				vx = 0;
				ax = 0;
				ay = 0;
			}
			else // Kết thúc giai đoạn 1, chuyển sang giai đoạn 2
			{
				y = startY + MARIO_TUNNEL_OFFSETY; // Đảm bảo y đạt đến vị trí cuối cùng


				slidePhase = 2;
				slideStartTime = GetTickCount64(); // Reset thời gian cho giai đoạn 2

			}
		}
		else if (slidePhase == 2)

		{
			x = MARIO_X_TELEPORT_INPUT;
			y = MARIO_Y_TELEPORT_INPUT;
			startY = y;
			if (elapsed < MARIO_TUNNEL_DOOR_TIME)
			{

				float process = elapsed / MARIO_TUNNEL_DOOR_TIME; 
				y = startY + MARIO_TUNNEL_OFFSETY * process; 
				vx = 0;
				ax = 0;
				ay = 0;
			}
			else // Kết thúc giai đoạn trượt
			{

				y = startY + MARIO_TUNNEL_OFFSETY;
				isSliding = false;
				slidePhase = 0;
				vy = 0;
				isTunnelDoor = false;
			}
		}
	}
	else if (isTunnelDoor ==1 && CGame::GetInstance()->IsKeyDown(DIK_DOWN) && isOnPlatform && level == MARIO_LEVEL_RACOON && !isSitting && !isHolding && !isTailAttacking)
	{
		isSliding = true;
		slideStartTime = GetTickCount64();
		startY = y;
		slidePhase = 1;
		vx = 0;
		ax = 0;
		ay = 0;
		DebugOut(L"[INFO] Mario started sliding phase 1 at y = %f\n", y);
	}
}
void CMario::OutputTunnelDoor()
{
	if(isSliding && isTunnelDoor == 2)
	{
		ULONGLONG now = GetTickCount64();
		float elapsed = (float)(now - slideStartTime);
		if (slidePhase == 1)
		{
			if (elapsed < MARIO_TUNNEL_DOOR_TIME) // Giai đoạn 1: Trượt lên từ từ trong 500ms
			{
				float process = elapsed / MARIO_TUNNEL_DOOR_TIME; 
				y = startY - MARIO_TUNNEL_OFFSETY * process;    
				ax = 0;
				ay = 0;
			}
			else 
			{
				y = startY - MARIO_TUNNEL_OFFSETY; 
				slidePhase = 2;
				slideStartTime = GetTickCount64(); 
			}
		}
		else if (slidePhase == 2)
		{
			x = MARIO_X_TELEPORT_OUTPUT; 
			y = MARIO_Y_TELEPORT_OUTPUT; 
			startY = y; 
			if (elapsed < MARIO_TUNNEL_DOOR_TIME) 
			{
				float process = elapsed / MARIO_TUNNEL_DOOR_TIME; 
				y = startY - MARIO_TUNNEL_OFFSETY * process; 
				vx = 0;
				ax = 0;
				ay = 0;
			}
			else 
			{
				y = startY - MARIO_TUNNEL_OFFSETY; 
				isSliding = false;
				slidePhase = 0;
				vy = 0;
				isTunnelDoor = false;
			}
		}
	}
else
{
	// Kích hoạt trượt từ dưới lên
	if (isTunnelDoor  == 2  && level == MARIO_LEVEL_RACOON && !isSitting && !isHolding && !isTailAttacking)
	{
		isSliding = true;
		slideStartTime = GetTickCount64();
		startY = y;
		slidePhase = 1;
		vx = 0;
		ax = 0;
		ay = 0;
		DebugOut(L"[INFO] Mario started sliding phase 1 (upwards) at y = %f\n", y);
	}
	}
}

