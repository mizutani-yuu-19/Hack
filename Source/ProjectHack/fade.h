//=======================================================
//			�t�F�[�h �C��/�A�E�g���� (fade.h)
//=======================================================
#ifndef _FADE_H_
#define _FADE_H_
//-------�C���N���[�h��-------
#include "main.h"
//-------�萔��`-------
#define VERTEX_NUM	(4)
#define FADE_TIME	(60)

//-------�v���g�^�C�v�錾-------
void InitFade();

void UpdateFade();
void DrawFade();

void StartFadeIn();
void StartFadeOut();

int EndFadeIn();
int EndFadeOut();

#endif
