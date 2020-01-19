////////////////////////////////////////////////////////////////////////////////////
//
// game.cpp
//
////////////////////////////////////////////////////////////////////////////////////
//=============インクルード===============
#include "game.h"
#include "objbase.h"
#include "camera.h"
#include "light.h"
#include "player.h"
#include "effect.h"
#include "stage.h"
#include "enemy.h"
#include "UI.h"
#include "fade.h"
#include "input.h"
#include "sound.h"
int g_step = STEP_GAMING;
static int g_count;

int clear[MAX_LEVEL] = { 0,0,0,0,0 };
bool end[MAX_LEVEL] = { 0,0,0,0,0 };
int nowLevel = 0;

void(*LevelFuncList[MAX_LEVEL])(void);		// 関数リスト

//============関数==================
void Level1() {
	InitLight();
	CObjBase *temp;
	temp = new CPlayerCamera();
	ObjSys.Add(temp, OBJ_CAMERA);
	temp = new CStageCamera();
	ObjSys.Add(temp, OBJ_CAMERA);
	temp = new CPlayer();
	ObjSys.Add(temp, OBJ_PLAYER);
	temp = new CEffect();
	ObjSys.Add(temp, OBJ_EFFECT);
	temp = new CStage(1, 1, 32, 32);
	ObjSys.Add(temp, OBJ_STAGE);
	temp = new CBallEnemyEight(point3(0, 0, 0), 8);
	ObjSys.Add(temp, OBJ_ENEMY);

	StartFadeIn();
	g_step = STEP_GAMING;
	g_count = 0;
}

void Level2() {
	InitLight();
	CObjBase *temp;
	temp = new CPlayerCamera();
	ObjSys.Add(temp, OBJ_CAMERA);
	temp = new CStageCamera();
	ObjSys.Add(temp, OBJ_CAMERA);
	temp = new CPlayer();
	ObjSys.Add(temp, OBJ_PLAYER);
	temp = new CEffect();
	ObjSys.Add(temp, OBJ_EFFECT);
	temp = new CStage(1, 1, 32, 32);
	ObjSys.Add(temp, OBJ_STAGE);
	temp = new CFollowEnemy(point3(-6, 0, 13), 2);
	ObjSys.Add(temp, OBJ_ENEMY);
	temp = new CFollowEnemy(point3(6, 0, 13), 2);
	ObjSys.Add(temp, OBJ_ENEMY);
	temp = new CFollowEnemy(point3(-10, 0, -8), 2);
	ObjSys.Add(temp, OBJ_ENEMY);
	temp = new CFollowEnemy(point3(10, 0, -8), 2);
	ObjSys.Add(temp, OBJ_ENEMY);

	StartFadeIn();
	g_step = STEP_GAMING;
	g_count = 0;
}
void Level3() {
	InitLight();
	CObjBase *temp;
	temp = new CPlayerCamera();
	ObjSys.Add(temp, OBJ_CAMERA);
	temp = new CStageCamera();
	ObjSys.Add(temp, OBJ_CAMERA);
	temp = new CPlayer();
	ObjSys.Add(temp, OBJ_PLAYER);
	temp = new CEffect();
	ObjSys.Add(temp, OBJ_EFFECT);
	temp = new CStage(1, 1, 32, 32);
	ObjSys.Add(temp, OBJ_STAGE);
	temp = new CBallEnemyLR(point3(0, 0, 0), 8);
	ObjSys.Add(temp, OBJ_ENEMY);

	StartFadeIn();
	g_step = STEP_GAMING;
	g_count = 0;
}
void Level4() {
	InitLight();
	CObjBase *temp;
	temp = new CPlayerCamera();
	ObjSys.Add(temp, OBJ_CAMERA);
	temp = new CStageCamera();
	ObjSys.Add(temp, OBJ_CAMERA);
	temp = new CPlayer();
	ObjSys.Add(temp, OBJ_PLAYER);
	temp = new CEffect();
	ObjSys.Add(temp, OBJ_EFFECT);
	temp = new CStage(1, 1, 32, 32);
	ObjSys.Add(temp, OBJ_STAGE);
	int difficult = (clear[nowLevel] + 1);
	temp = new CBallEnemy(point3(0, 0, 15), difficult);
	ObjSys.Add(temp, OBJ_ENEMY);
	temp = new CBallEnemy(point3(15, 0, -15), difficult);
	ObjSys.Add(temp, OBJ_ENEMY);
	temp = new CBallEnemy(point3(-15, 0, -15), difficult);
	ObjSys.Add(temp, OBJ_ENEMY);

	StartFadeIn();
	g_step = STEP_GAMING;
	g_count = 0;
}
void Level5() {
	InitLight();
	CObjBase *temp;
	temp = new CPlayerCamera();
	ObjSys.Add(temp, OBJ_CAMERA);
	temp = new CStageCamera();
	ObjSys.Add(temp, OBJ_CAMERA);
	temp = new CPlayer();
	ObjSys.Add(temp, OBJ_PLAYER);
	temp = new CEffect();
	ObjSys.Add(temp, OBJ_EFFECT);
	temp = new CStage(1, 1, 32, 32);
	ObjSys.Add(temp, OBJ_STAGE);
	temp = new CFollowEnemy(point3(13, 0, 13), 0);
	ObjSys.Add(temp, OBJ_ENEMY);
	temp = new CBallEnemy(point3(-13, 0, 13), (clear[nowLevel] + 3));
	ObjSys.Add(temp, OBJ_ENEMY);
	temp = new CFollowEnemy(point3(8, 0, 0), 2);
	ObjSys.Add(temp, OBJ_ENEMY);
	temp = new CFollowEnemy(point3(-8, 0, 0), 0);
	ObjSys.Add(temp, OBJ_ENEMY);
	temp = new CFollowEnemy(point3(-13, 0, -15), 1);
	ObjSys.Add(temp, OBJ_ENEMY);
	temp = new CFollowEnemy(point3(13, 0, -15), 1);
	ObjSys.Add(temp, OBJ_ENEMY);

	StartFadeIn();
	g_step = STEP_GAMING;
	g_count = 0;
}
void Title() {
	CObjBase *temp = new CUITitle();
	ObjSys.Add(temp, OBJ_UI);
	temp = new CTitleCamera();
	ObjSys.Add(temp, OBJ_CAMERA);
	StartFadeIn();
	g_count = 0;
	g_step = STEP_TITLE;
}
void Select() {
	CObjBase *temp = new CSelect();
	ObjSys.Add(temp, OBJ_UI);
	temp = new CTitleCamera();
	ObjSys.Add(temp, OBJ_CAMERA);
	g_step = STEP_SELECT;
	StartFadeIn();
}
void GameInit() {
	ObjSys.Init();
	Title();
	LevelFuncList[0] = Level1;
	LevelFuncList[1] = Level2;
	LevelFuncList[2] = Level3;
	LevelFuncList[3] = Level4;
	LevelFuncList[4] = Level5;
	PlaySound(SOUND_LABEL_BGM, 1.0f);
}

//============アップデート================
//----コールバック---
bool cbCharaPushCalc(CObjBase *pTgt, void *pPara)
{//影響を計算
	((CCharacter *)pTgt)->PushCalc();
	return false;
}
bool cbCharaPushRefl(CObjBase *pTgt, void *pPara)
{//影響を反映
	((CCharacter *)pTgt)->PushRefl();
	return false;
}
// 本アップデート
void GameUpdate() {
	ObjSys.AllUpdate();
	UpdateFade();
	switch (g_step)
	{
	case STEP_TITLE: {
		if (EndFadeIn() && DIGetKeyTrigger(DIK_RETURN)) {
			StartFadeOut();
		}
		else if (EndFadeOut()) {
			ObjSys.Init();
			Select();
		}
		break;
	}
	case STEP_SELECT: {
		if (EndFadeOut()) {
			ObjSys.Init();
			LevelFuncList[nowLevel]();
		}
		break;
	}
	case STEP_GAMING: {
		if (!ChkExistStage(OBJLIST_ENEMY)) {
			CObjBase *temp = new CUIComplete();
			ObjSys.Add(temp, OBJ_UI);
			g_step = STEP_GAMEEND;
			g_count = 0;
			if (clear[nowLevel] < 3)
				clear[nowLevel]++;
			else
				end[nowLevel] = true;
		}
		else if (!ChkExistStage(OBJLIST_PLAYER)) {
			CObjBase *temp = new CUIGameOver();
			ObjSys.Add(temp, OBJ_UI);
			g_step = STEP_GAMEEND;
			g_count = 0;
		}
		break;
	}
	case STEP_GAMEEND: {
		if (g_count > 120) {
			if (EndFadeIn()) {
				StartFadeOut();
			}
			else if (EndFadeOut()) {
				ObjSys.Init();
				Select();
			}
		}
		break;
	}
	default:
		break;
	}
	ObjSys.LoopStage(OBJLIST_PLAYER + OBJLIST_ENEMY, cbCharaPushCalc, NULL);
	ObjSys.LoopStage(OBJLIST_PLAYER + OBJLIST_ENEMY, cbCharaPushRefl, NULL);
	g_count++;
}
void GameDraw() {
	ObjSys.AllDraw();
}
void GameUninit() {
	ObjSys.AllUninit();
}
