﻿#include <iostream>
#include <fstream>
#include "AssetIDs.h"

#include "PlayScene.h"
#include "Utils.h"
#include "Textures.h"
#include "Sprites.h"
#include "Portal.h"
#include "Coin.h"
#include "Platform.h"
#include "SinglePlatform.h"
#include "LayerBackGround.h"
#include "VerticalPlatform.h"
#include "QuestionBlock.h"
#include "Mushroom.h"
#include "Piranha.h"
#include "ParaGoomba.h"
#include "Koopa.h"
#include "RedKoopa.h"
#include "Leaf.h"
#include "ParaKoopa.h"
#include "Tunnel.h"
#include "SampleKeyEventHandler.h"

using namespace std;

CPlayScene::CPlayScene(int id, LPCWSTR filePath):
	CScene(id, filePath)
{
	player = NULL;
	key_handler = new CSampleKeyHandler(this);
	hud = NULL;
}


#define SCENE_SECTION_UNKNOWN -1
#define SCENE_SECTION_ASSETS	1
#define SCENE_SECTION_OBJECTS	2

#define ASSETS_SECTION_UNKNOWN -1
#define ASSETS_SECTION_SPRITES 1
#define ASSETS_SECTION_ANIMATIONS 2

#define MAX_SCENE_LINE 1024

void CPlayScene::_ParseSection_SPRITES(string line)
{
	vector<string> tokens = split(line);

	if (tokens.size() < 6) return; // skip invalid lines

	int ID = atoi(tokens[0].c_str());
	int l = atoi(tokens[1].c_str());
	int t = atoi(tokens[2].c_str());
	int r = atoi(tokens[3].c_str());
	int b = atoi(tokens[4].c_str());
	int texID = atoi(tokens[5].c_str());

	LPTEXTURE tex = CTextures::GetInstance()->Get(texID);
	if (tex == NULL)
	{
		DebugOut(L"[ERROR] Texture ID %d not found!\n", texID);
		return; 
	}

	CSprites::GetInstance()->Add(ID, l, t, r, b, tex);
}

void CPlayScene::_ParseSection_ASSETS(string line)
{
	vector<string> tokens = split(line);

	if (tokens.size() < 1) return;

	wstring path = ToWSTR(tokens[0]);
	
	LoadAssets(path.c_str());
}

void CPlayScene::_ParseSection_ANIMATIONS(string line)
{
	vector<string> tokens = split(line);

	if (tokens.size() < 3) return; // skip invalid lines - an animation must at least has 1 frame and 1 frame time

	//DebugOut(L"--> %s\n",ToWSTR(line).c_str());

	LPANIMATION ani = new CAnimation();

	int ani_id = atoi(tokens[0].c_str());
	for (int i = 1; i < tokens.size(); i += 2)	// why i+=2 ?  sprite_id | frame_time  
	{
		int sprite_id = atoi(tokens[i].c_str());
		int frame_time = atoi(tokens[i+1].c_str());
		ani->Add(sprite_id, frame_time);
	}

	CAnimations::GetInstance()->Add(ani_id, ani);
}

/*
	Parse a line in section [OBJECTS] 
*/
void CPlayScene::_ParseSection_OBJECTS(string line)
{
	vector<string> tokens = split(line);

	// skip invalid lines - an object set must have at least id, x, y
	if (tokens.size() < 2) return;

	int object_type = atoi(tokens[0].c_str());
	float x = (float)atof(tokens[1].c_str());
	float y = (float)atof(tokens[2].c_str());

	CGameObject *obj = NULL;

	switch (object_type)
	{
	case OBJECT_TYPE_MARIO:
		if (player!=NULL) 
		{
			DebugOut(L"[ERROR] MARIO object was created before!\n");
			return;
		}
		player = new CMario(x, y); 
		//obj = new CMario(x,y); 
		//player = (CMario*)obj;  

		DebugOut(L"[INFO] Player object has been created!\n");
		break;
	case OBJECT_TYPE_GOOMBA:
	{
		
		obj = new CGoomba(x, y); enemies.push_back(obj); break;
	}
	case OBJECT_TYPE_PARAGOOMBA:
	{
		obj = new CParaGoomba(x, y); enemies.push_back(obj); break;

	}
	case OBJECT_TYPE_KOOPA:
		obj = new CKoopa(x, y); enemies.push_back(obj); break;
	case OBJECT_TYPE_RED_KOOPA:
		obj = new CRedKoopa(x, y); enemies.push_back(obj); break;
	case OBJECT_TYPE_PARA_KOOPA:
		obj = new CParaKoopa(x, y); enemies.push_back(obj); break;
	case OBJECT_TYPE_BRICK: obj = new CBrick(x, y); blocks.push_back(obj);	break;
	case OBJECT_TYPE_COIN:
	{ 
		int state = atoi(tokens[3].c_str());
		obj = new CCoin(x, y, state);	blocks.push_back(obj);	
		break; 
	}

	case OBJECT_TYPE_PLATFORM:  
	{

		float cell_width = (float)atof(tokens[3].c_str());
		float cell_height = (float)atof(tokens[4].c_str());
		int length = atoi(tokens[5].c_str());
		int sprite_begin = atoi(tokens[6].c_str());
		int sprite_middle = atoi(tokens[7].c_str());
		int sprite_end = atoi(tokens[8].c_str());
		bool isCloud = (bool)atoi(tokens[9].c_str());

		obj = new CPlatform(
			x, y,
			cell_width, cell_height, length,
			isCloud ,sprite_begin, sprite_middle, sprite_end
		);
		blocks.push_back(obj);
		break;
	}
	case OBJECT_TYPE_VERTICAL_PLATFORM:
	{
		float cell_width = (float)atof(tokens[3].c_str());
		float cell_height = (float)atof(tokens[4].c_str());
		int length = atoi(tokens[5].c_str());
		int sprite_begin = atoi(tokens[6].c_str());
		int sprite_middle = atoi(tokens[7].c_str());
		int sprite_end = atoi(tokens[8].c_str());

		obj = new CVerticalPlatform(x, y, cell_width, cell_height, length, sprite_begin, sprite_middle, sprite_end);
		Verticalplatforms.push_back(obj);
		break;
	}
	case OBJECT_TYPE_SINGLE_PLATFORM:// thêm platformid = 6
	{
		float cell_width = (float)atof(tokens[3].c_str());
		float cell_height = (float)atof(tokens[4].c_str());
		bool isCloud = (bool)atoi(tokens[5].c_str());
		int sprite_id = atoi(tokens[6].c_str());
		

		obj = new CSinglePlatform(x, y, cell_width, cell_height, isCloud,sprite_id);
		blocks.push_back(obj);
		break;
	}
	case OBJECT_TYPE_LAYER_BLOCK: // quản lý các layer background
	{
		float cell_width = (float)atof(tokens[3].c_str());
		float cell_height = (float)atof(tokens[4].c_str());
		int sprite_id = atoi(tokens[5].c_str());
		obj = new CLayerBackGround(x, y, cell_width, cell_height, sprite_id);
		layerBacgrounds.push_back(obj); // không push vào blocks vì thứ tự các layer block luôn xếp cuối
		break;
	}
	case OBJECT_TYPE_QUESTION_BLOCK:
	{
		int itemType = atoi(tokens[3].c_str());
		int typeBlock = atoi(tokens[4].c_str()); // 1: simple brick, 2: normal question block
		questionBlocks.push_back(new CQuestionBlock(x, y, itemType, typeBlock));
		break;
	}
	case OBJECT_TYPE_MUSHROOM:
	{

		obj = new CMushroom(x, y);
		blocks.push_back(obj);
		break;
	}
	case OBJECT_TYPE_LEAF:
	{
		obj = new CLeaf(x, y);
		blocks.push_back(obj);
		break;

	}
	case OBJECT_TYPE_PIRANHA:
	{
		int type = atoi(tokens[3].c_str()); // 1: red, 2: green, 3: melee
		obj = new CPiranha(x, y, type);
		piranhas.push_back(obj);
		break;
	}
	case OBJECT_TYPE_TUNNEL:
	{
		int number = atoi(tokens[3].c_str());
		obj = new CTunnel(x, y, number);
		Verticalplatforms.push_back(obj);
		break;
	}
	case OBJECT_TYPE_PORTAL:
	{
		float r = (float)atof(tokens[3].c_str());
		float b = (float)atof(tokens[4].c_str());
		int scene_id = atoi(tokens[5].c_str());
		obj = new CPortal(x, y, r, b, scene_id);
		objects.push_back(obj);
		break;
	}


	


	default:
		DebugOut(L"[ERROR] Invalid object type: %d\n", object_type);

		return;
	}

	// General object setup
	//obj->SetPosition(x, y);


	//objects.push_back(obj);

}

void CPlayScene::LayerManagement()
{
	for (size_t i = 0; i < layerBacgrounds.size(); i++)
	{
		objects.push_back(layerBacgrounds[i]);
	}
	for (size_t i = 0; i < piranhas.size(); i++)
	{
		objects.push_back(piranhas[i]);
	}
	for (size_t i = 0; i < blocks.size(); i++)
	{
		objects.push_back(blocks[i]);
	}
	for (size_t i = 0; i < questionBlocks.size(); i++)
	{
		objects.push_back(questionBlocks[i]);
	}
	for (size_t i = 0; i < enemies.size(); i++)
	{
		objects.push_back(enemies[i]);
	}

	objects.push_back(player);
	for (size_t i = 0; i < Verticalplatforms.size(); i++)
	{
		objects.push_back(Verticalplatforms[i]);
	}
	if (player != NULL)
	{
		hud = new CHud(player);
		objects.push_back(hud);

	}

	
}

void CPlayScene::LoadAssets(LPCWSTR assetFile)
{
	DebugOut(L"[INFO] Start loading assets from : %s \n", assetFile);

	ifstream f;
	f.open(assetFile);

	int section = ASSETS_SECTION_UNKNOWN;

	char str[MAX_SCENE_LINE];
	while (f.getline(str, MAX_SCENE_LINE))
	{
		string line(str);

		if (line[0] == '#') continue;	// skip comment lines	

		if (line == "[SPRITES]") { section = ASSETS_SECTION_SPRITES; continue; };
		if (line == "[ANIMATIONS]") { section = ASSETS_SECTION_ANIMATIONS; continue; };
		if (line[0] == '[') { section = SCENE_SECTION_UNKNOWN; continue; }

		//
		// data section
		//
		switch (section)
		{
		case ASSETS_SECTION_SPRITES: _ParseSection_SPRITES(line); break;
		case ASSETS_SECTION_ANIMATIONS: _ParseSection_ANIMATIONS(line); break;
		}
	}

	f.close();

	DebugOut(L"[INFO] Done loading assets from %s\n", assetFile);
}

void CPlayScene::Load()
{
	DebugOut(L"[INFO] Start loading scene from : %s \n", sceneFilePath);

	ifstream f;
	f.open(sceneFilePath);

	// current resource section flag
	int section = SCENE_SECTION_UNKNOWN;					

	char str[MAX_SCENE_LINE];
	while (f.getline(str, MAX_SCENE_LINE))
	{
		string line(str);

		if (line[0] == '#') continue;	// skip comment lines	
		if (line == "[ASSETS]") { section = SCENE_SECTION_ASSETS; continue; };
		if (line == "[OBJECTS]") { section = SCENE_SECTION_OBJECTS; continue; };
		if (line[0] == '[') { section = SCENE_SECTION_UNKNOWN; continue; }	

		//
		// data section
		//
		switch (section)
		{ 
			case SCENE_SECTION_ASSETS: _ParseSection_ASSETS(line); break;
			case SCENE_SECTION_OBJECTS: _ParseSection_OBJECTS(line); break;
		}
	}

	f.close();

	//sắp xếp các layer:
	LayerManagement();

	DebugOut(L"[INFO] Done loading scene  %s\n", sceneFilePath);
}


void CPlayScene::Update(DWORD dt)
{
	// We know that Mario is the first object in the list hence we won't add him into the colliable object list
	// TO-DO: This is a "dirty" way, need a more organized way 
	

	vector<LPGAMEOBJECT> coObjects;
	for (size_t i = 0; i < objects.size(); i++)
	{
		if (objects[i] == player) continue; // skip player
		coObjects.push_back(objects[i]);
	}


	for (size_t i = 0; i < objects.size(); i++)
	{
		objects[i]->Update(dt, &coObjects);
	}

	// skip the rest if scene was already unloaded (Mario::Update might trigger PlayScene::Unload)
	if (player == NULL) return; 

	// Update camera to follow mario
	float cx, cy;
	player->GetPosition(cx, cy);

	CGame *game = CGame::GetInstance();
	cx -= game->GetBackBufferWidth() / 2;
	cy -= game->GetBackBufferHeight() / 2;

	if (cx < 0) cx = 0;

	//CGame::GetInstance()->SetCamPos(cx, /*0*/ cy);

	//PurgeDeletedObjects();
	float current_cam_x, current_cam_y;
	game->GetCamPos(current_cam_x, current_cam_y);

	// Sử dụng lerp để làm mịn chuyển động camera
	float lerp_factor = 0.1f; // Tốc độ làm mịn (0.0f đến 1.0f)
	cx = current_cam_x + lerp_factor * (cx - current_cam_x);
	cy = current_cam_y + lerp_factor * (cy - current_cam_y);

	/*DebugOut(L"[DEBUG] Target camera pos: x=%f, y=%f\n", cx, cy);*/

	game->SetCamPos(cx, cy);

	PurgeDeletedObjects();
}

void CPlayScene::Render()
{
	for (int i = 0; i < objects.size(); i++)
		objects[i]->Render();
}

/*
*	Clear all objects from this scene
*/
void CPlayScene::Clear()
{
	vector<LPGAMEOBJECT>::iterator it;
	for (it = objects.begin(); it != objects.end(); it++)
	{
		delete (*it);
	}
	objects.clear();
}

/*
	Unload scene

	TODO: Beside objects, we need to clean up sprites, animations and textures as well 

*/
void CPlayScene::Unload()
{
	for (int i = 0; i < objects.size(); i++)
		delete objects[i];

	objects.clear();
	player = NULL;

	DebugOut(L"[INFO] Scene %d unloaded! \n", id);
}

bool CPlayScene::IsGameObjectDeleted(const LPGAMEOBJECT& o) { return o == NULL; }

void CPlayScene::PurgeDeletedObjects()
{
	vector<LPGAMEOBJECT>::iterator it;
	for (it = objects.begin(); it != objects.end(); it++)
	{
		LPGAMEOBJECT o = *it;
		if (o->IsDeleted())
		{
			delete o;
			*it = NULL;
		}
	}

	// NOTE: remove_if will swap all deleted items to the end of the vector
	// then simply trim the vector, this is much more efficient than deleting individual items
	objects.erase(
		std::remove_if(objects.begin(), objects.end(), CPlayScene::IsGameObjectDeleted),
		objects.end());
}
void CPlayScene::AddObject(LPGAMEOBJECT obj)
{
	objects.push_back(obj);
}

bool CPlayScene::IsInCameraView(float x, float y) {
	CGame* game = CGame::GetInstance();
	float cam_x, cam_y;
	game->GetCamPos(cam_x, cam_y);

	float left = cam_x - 50;
	float top = cam_y - 50;
	float right = cam_x + game->GetBackBufferWidth() + 50;
	float bottom = cam_y + game->GetBackBufferHeight() + 50;

	return (x >= left && x <= right && y >= top && y <= bottom);
}