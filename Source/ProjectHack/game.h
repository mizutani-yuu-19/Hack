////////////////////////////////////////////////////////////////////////////////////
//
// game.h
//
////////////////////////////////////////////////////////////////////////////////////
#pragma once
//============�C���N���[�h==============
#include "main.h"
#include "select.h"

//=============�񋓑�================--
enum {
	STEP_TITLE,
	STEP_GAMING,
	STEP_GAMEEND,
	STEP_SELECT
};
//============�v���g�^�C�v�錾=============
void GameInit();
void GameUpdate();
void GameDraw();
void GameUninit();

extern int clear[MAX_LEVEL];
extern bool end[MAX_LEVEL];
extern int nowLevel;
extern int g_step;
