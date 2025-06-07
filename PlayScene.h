#pragma once
#include "Game.h"
#include "Textures.h"
#include "Scene.h"
#include "GameObject.h"
#include "Brick.h"
#include "Mario.h"
#include "Goomba.h"
#include "Hud.h"
//#include "Koopas.h"


class CPlayScene: public CScene
{
protected: 
	// A play scene has to have player, right? 
	CMario* player;
	CHud* hud;
	vector<LPGAMEOBJECT> enemies;
	vector<LPGAMEOBJECT> piranhas;
	vector<LPGAMEOBJECT> layerBacgrounds;
	vector<LPGAMEOBJECT> questionBlocks;
	vector<LPGAMEOBJECT> blocks;
	vector<LPGAMEOBJECT> Verticalplatforms;

	vector<LPGAMEOBJECT> objects;

	void _ParseSection_SPRITES(string line);
	void _ParseSection_ANIMATIONS(string line);

	void _ParseSection_ASSETS(string line);
	void _ParseSection_OBJECTS(string line);

	void LoadAssets(LPCWSTR assetFile);
	
public: 
	CPlayScene(int id, LPCWSTR filePath);

	virtual void Load();
	virtual void Update(DWORD dt);
	virtual void Render();
	virtual void Unload();

	LPGAMEOBJECT GetPlayer() { return player; }

	void Clear();
	void PurgeDeletedObjects();
	void LayerManagement();
	void AddObject(LPGAMEOBJECT obj);
	bool IsInCameraView(float x, float y);
	vector<LPGAMEOBJECT> GetQuestionBlocks() { return questionBlocks; }

	static bool IsGameObjectDeleted(const LPGAMEOBJECT& o);
};

typedef CPlayScene* LPPLAYSCENE;

