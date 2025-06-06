#include "Hud.h"
#include "Game.h"

void CHud::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	// Update the HUD based on the player's state
	if (player != nullptr)
	{
		coins = player->GetCoin();
		timer = player->GetTimer();
		lives = player->GetLives();
		p_meter = player->GetPMeter();

		CGame* game = CGame::GetInstance();
		float cam_x, cam_y;
		game->GetCamPos(cam_x, cam_y);

		// Update HUD position based on camera position
		x = static_cast<int>(cam_x + 120);
		y = static_cast<int>(cam_y + game->GetBackBufferHeight() - 20);

	}
}

void CHud::Render()
{
	CSprites* sprites = CSprites::GetInstance();

	sprites->Get(HUD_UI_BAR_SPRITE)->Draw(x, y);
	RenderNumber(coins, x + HUD_OFFSET_X_COIN, y + HUD_OFFSET_Y_COIN, 2);
	RenderNumber(max(timer, 0), x + HUD_OFFSET_X_TIMER, y + HUD_OFFSET_Y_TIMER, 3);
	RenderPowerMeter(x + HUD_OFFSET_X_P_METER, y + HUD_OFFSET_Y_P_METER);
	RenderNumber(score, x + HUD_OFFSET_X_SCORE, y + HUD_OFFSET_Y_SCORE, 7);
	RenderNumber(lives, x + HUD_OFFSET_X_LIVES, y + HUD_OFFSET_Y_LIVES, 2);
	RenderNumber(world, x + HUD_OFFSET_X_WORLD, y + HUD_OFFSET_Y_WORLD, 1);

}

void CHud::RenderNumber(int number, float x, float y, int width)
{

	char  buffer[8]; // Buffer to hold the formatted number
	sprintf_s(buffer, 8, "%0*d", width, number); // Format number with leading zero
	float currentX = x;
	//for (char digit : buffer)
	//{
	//	int spriteId = ID_SPRITE_NUMBER_0 + (digit - '0'); // Convert char to corresponding sprite ID
	//	CSprites::GetInstance()->Get(spriteId)->Draw(currentX, y);
	//	currentX += 8; 
	//}
	for (int i = 0; i < width && buffer[i] != '\0'; i++)
	{
		int digit = buffer[i] - '0'; // Convert char to corresponding digit
		int spriteId = ID_SPRITE_NUMBER_0 + digit; // Get the sprite ID for the digit
		CSprites::GetInstance()->Get(spriteId)->Draw(currentX, y);
		currentX += 8; // Move to the next position
	}
}

void CHud::RenderPowerMeter(float x, float y)
{
	CSprites* sprites = CSprites::GetInstance();
	float offset_X = 8.0f;
	float offset_X_Last = 12;
	float currentX = x;
	float valuePerSegment = (1.0f/ P_METER_MAX_SEGMENTS);

	int segment = static_cast<int>(player->GetPMeter() /valuePerSegment);
	DebugOut(L"[DEBUG] pMeter = %f, valuePerSegment = %f, segment = %d\n", player->GetPMeter(), valuePerSegment, segment);
	for (int i = 0; i < P_METER_MAX_SEGMENTS; i++)
	{
		int spriteId;
		if (i == P_METER_MAX_SEGMENTS - 1)
		{
			spriteId = (i <= segment) ? P_METER_SPRITE_LAST_FULL : P_METER_SPRITE_LAST_EMPTY;
			currentX += offset_X_Last; 
		}
		else
		{
			spriteId = (i < segment) ? P_METER_SPRITE_FULL : P_METER_SPRITE_EMPTY;
			currentX += offset_X;
		}
		sprites->Get(spriteId)->Draw(currentX, y);
	}


}