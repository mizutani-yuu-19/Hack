////////////////////////////////////////////////////////////////////////////////////
//
// game.h
//
////////////////////////////////////////////////////////////////////////////////////
#pragma once
//============インクルード==============
#include "main.h"
#include "select.h"

//=============列挙隊================--
enum {
	STEP_TITLE,
	STEP_GAMING,
	STEP_GAMEEND,
	STEP_SELECT
};
//============プロトタイプ宣言=============
void GameInit();
void GameUpdate();
void GameDraw();
void GameUninit();

extern int clear[MAX_LEVEL];
extern bool end[MAX_LEVEL];
extern int nowLevel;
extern int g_step;
