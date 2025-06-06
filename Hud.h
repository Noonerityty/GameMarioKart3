#pragma once
#include "GameObject.h"
#include "Mario.h"

#define HUD_UI_BAR_SPRITE 170001

#define ID_SPRITE_NUMBER_0 170800
#define ID_SPRITE_NUMBER_1 170801
#define ID_SPRITE_NUMBER_2 170802
#define ID_SPRITE_NUMBER_3 170803
#define ID_SPRITE_NUMBER_4 170804
#define ID_SPRITE_NUMBER_5 170805
#define ID_SPRITE_NUMBER_6 170806
#define ID_SPRITE_NUMBER_7 170807
#define ID_SPRITE_NUMBER_8 170808
#define ID_SPRITE_NUMBER_9 170809

#define HUD_OFFSET_X_COIN 17
#define HUD_OFFSET_Y_COIN -3
#define HUD_OFFSET_X_TIMER 9
#define HUD_OFFSET_Y_TIMER 5
#define HUD_OFFSET_X_SCORE -63
#define HUD_OFFSET_Y_SCORE 5
#define HUD_OFFSET_X_LIVES -86
#define HUD_OFFSET_Y_LIVES 5

#define HUD_OFFSET_X_WORLD  -78
#define HUD_OFFSET_Y_WORLD  -3

#define HUD_OFFSET_X_P_METER -71
#define HUD_OFFSET_Y_P_METER -4

#define P_METER_MAX_SEGMENTS 7

#define P_METER_SPRITE_FULL 170900
#define P_METER_SPRITE_EMPTY 170901
#define	P_METER_SPRITE_LAST_FULL 170902
#define P_METER_SPRITE_LAST_EMPTY 170903


class CHud : public CGameObject
{
protected:
	CMario* player;
	int coins;
	int lives;	
	float p_meter;
	int timer;
	int world;
	int score;
public:
	CHud(CMario* mario)
	{
		player = mario;
		coins = 0;
		lives = 3; // Default lives
		p_meter = 0.0f; // Default power meter
		timer = 0; // Default time
		world = 1; // Default world
		score = 0; // Default points

	}

	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void Render();
	void GetBoundingBox(float& l, float& t, float& r, float& b) override
	{
		l = t = r = b = 0; // No bounding box for HUD
	}

	void RenderNumber(int number, float x, float y, int width);
	void RenderPowerMeter(float x, float y);
};
