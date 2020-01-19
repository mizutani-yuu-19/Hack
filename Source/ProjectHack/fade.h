//=======================================================
//			フェード イン/アウト処理 (fade.h)
//=======================================================
#ifndef _FADE_H_
#define _FADE_H_
//-------インクルード部-------
#include "main.h"
//-------定数定義-------
#define VERTEX_NUM	(4)
#define FADE_TIME	(60)

//-------プロトタイプ宣言-------
void InitFade();

void UpdateFade();
void DrawFade();

void StartFadeIn();
void StartFadeOut();

int EndFadeIn();
int EndFadeOut();

#endif
