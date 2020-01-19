#include "select.h"
#include "input.h"
#include "game.h"
#include "fade.h"
#include "sound.h"

LPDIRECT3DTEXTURE9 CSelect::m_numTex;
LPDIRECT3DTEXTURE9 CSelect::m_selectTex;
LPDIRECT3DTEXTURE9 CSelect::m_crownTex;

#define NUM_SIZE_X (99)
#define NUM_SIZE_Y (215)
#define SELECT_SIZE_X (40)
#define SELECT_SIZE_Y (40)

CSelect::CSelect()
{
	m_numTex = SetTexture("data/TEXTURE/number.png");
	m_selectTex = SetTexture("data/TEXTURE/selecting.png");
	m_crownTex = SetTexture("data/TEXTURE/crown.png");
	for (int i = 0; i < MAX_LEVEL; i++) {
		m_number[i].InitSprite(point2(60 + NUM_SIZE_X*0.5f + (NUM_SIZE_X + 40)*(i % 5), SCREEN_CENTER_Y), NUM_SIZE_X, NUM_SIZE_Y, 10, 1);
		m_number[i].m_patNum = i + 1;
		m_crown[i].InitSprite(point2(60 + NUM_SIZE_X*0.5f + (NUM_SIZE_X + 40)*(i % 5), SCREEN_CENTER_Y-100), SELECT_SIZE_X, SELECT_SIZE_Y, 5, 1);
		m_crown[i].m_patNum = i + 1;
	}
	m_selectNo = nowLevel;
	m_selectSprite.InitSprite(point2(0, SCREEN_CENTER_Y - 120), SELECT_SIZE_X, SELECT_SIZE_Y, 1, 1);
}

CSelect::~CSelect()
{
	SAFE_RELEASE(m_numTex);
	SAFE_RELEASE(m_selectTex);
	SAFE_RELEASE(m_crownTex);
}

void CSelect::Update() {
	for (int i = 0; i < MAX_LEVEL; i++) {	// ˆÃ‚­
		switch (clear[i])
		{
		case 0:
			m_number[i].m_color = D3DCOLOR_RGBA(60, 60, 0, 60);
			break;
		case 1:
			m_number[i].m_color = D3DCOLOR_RGBA(128, 128, 0, 120);
			break;
		case 2:
			m_number[i].m_color = D3DCOLOR_RGBA(200, 200, 0, 200);
			break;
		case 3:
			m_number[i].m_color = D3DCOLOR_RGBA(255, 255, 0, 255);
			break;
		default:
			break;
		}

		m_crown[i].m_patNum=m_time/20%MAX_LEVEL;
	}
	m_time++;
	m_selectSprite.m_pos.x = m_number[m_selectNo].m_pos.x;
	if (EndFadeIn() || EndFadeOut()) {
		if (DIGetKeyTrigger(DIK_D) || DIGetKeyTrigger(DIK_RIGHTARROW)) {
			PlaySound(SOUND_LABEL_SELECT, 10.0f);
			m_selectNo++;
		}
		else if (DIGetKeyTrigger(DIK_A) || DIGetKeyTrigger(DIK_LEFTARROW)) {
			PlaySound(SOUND_LABEL_SELECT, 10.0f);
			m_selectNo--;
		}
		else if (DIGetKeyTrigger(DIK_1) || DIGetKeyTrigger(DIK_NUMPAD1)) {
			PlaySound(SOUND_LABEL_SELECT, 10.0f);
			m_selectNo = 0;
		}
		else if (DIGetKeyTrigger(DIK_2) || DIGetKeyTrigger(DIK_NUMPAD2)) {
			PlaySound(SOUND_LABEL_SELECT, 10.0f);
			m_selectNo = 1;
		}
		else if (DIGetKeyTrigger(DIK_3) || DIGetKeyTrigger(DIK_NUMPAD3)) {
			PlaySound(SOUND_LABEL_SELECT, 10.0f);
			m_selectNo = 2;
		}
		else if (DIGetKeyTrigger(DIK_4) || DIGetKeyTrigger(DIK_NUMPAD4)) {
			PlaySound(SOUND_LABEL_SELECT, 10.0f);
			m_selectNo = 3;
		}
		else if (DIGetKeyTrigger(DIK_5) || DIGetKeyTrigger(DIK_NUMPAD5)) {
			PlaySound(SOUND_LABEL_SELECT, 10.0f);
			m_selectNo = 4;
		}
		m_selectNo = (m_selectNo + MAX_LEVEL) % MAX_LEVEL;
		if (DIGetKeyTrigger(DIK_RETURN)) {
			nowLevel = m_selectNo;
			m_selectSprite.m_color = D3DCOLOR_RGBA(255, 0, 0, 255);
			StartFadeOut();
			PlaySound(SOUND_LABEL_DECISION, 1.0f);
		}
	}
}

void CSelect::Draw2D() {
	SetRenderMode(BLEND_TRANSLUCENT);
	for (int i = 0; i < MAX_LEVEL; i++) {
		m_number[i].DrawSprite(m_numTex);
		if (end[i]) {
			m_crown[i].DrawSprite(m_crownTex);
		}
	}
	for (int j = 0; j < 3; j++) {
		for (int i = 0; i < MAX_LEVEL; i++) {
			if (clear[i] == 3) {
				m_number[i].DrawSprite(m_numTex);
			}
		}
	}
	m_selectSprite.DrawSprite(m_selectTex);
}
