//=============================================================================
//
// �T�E���h���� [sound.h]
//
//=============================================================================
#ifndef _SOUND_H_
#define _SOUND_H_

#include "main.h"
#include <XAudio2.h>

#define USE_SOUND
//*****************************************************************************
// �T�E���h�t�@�C��
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
	SOUND_LABEL_MAX,			// �o�^���̎����ݒ�
} SOUND_LABEL;

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT InitSound(HWND hWnd);
void UninitSound(void);

// �������͉���0.0f�`1.0f�̊�
HRESULT PlaySound(int label,float vol);

void StopSound(int label);
void StopSound(void);

#endif