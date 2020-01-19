//=============================================================================
//
// サウンド処理 [sound.h]
//
//=============================================================================
#ifndef _SOUND_H_
#define _SOUND_H_

#include "main.h"
#include <XAudio2.h>

#define USE_SOUND
//*****************************************************************************
// サウンドファイル
//*****************************************************************************
typedef enum
{
	SOUND_LABEL_BGM = 0,
	SOUND_LABEL_SELECT,
	SOUND_LABEL_DECISION,
	SOUND_LABEL_BREAK,
	SOUND_LABEL_FADE,
	SOUND_LABEL_BULLET,
	SOUND_LABEL_ATTACK,
	SOUND_LABEL_MAX,			// 登録数の自動設定
} SOUND_LABEL;

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT InitSound(HWND hWnd);
void UninitSound(void);

// 第二引数は音量0.0f～1.0fの間
HRESULT PlaySound(int label,float vol);

void StopSound(int label);
void StopSound(void);

#endif