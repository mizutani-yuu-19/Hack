////////////////////////////////////////////////////////////////////////////////////
//
// player.h
//
////////////////////////////////////////////////////////////////////////////////////
#pragma once
//=============�C���N���[�h===============
#include "objbase.h"
#include "character.h"
#include "model.h"
//============�v���C���[�N���X==================
class CPlayer :public CCharacter{
public:
	CPlayer();
	~CPlayer();

	void Init();
	void Update();
	void Draw();
	void DrawAlpha();
private:
	CModel* m_model[3];
	int m_bulletInterval;
	LPDIRECT3DTEXTURE9		m_pD3DTexture;		// �e�N�X�`���ւ̃|�C���^
	LPDIRECT3DVERTEXBUFFER9	m_pD3DVtxBuffShadow;		// ���_�o�b�t�@�ւ̃|�C���^
};

class CPlayerBullet :public CObjBase {

public:
	CPlayerBullet(point3 pos, vector3 rot);
	~CPlayerBullet();
	
	void Update();
	void DrawAlpha();
private:
	static LPDIRECT3DTEXTURE9		m_pD3DTexture;		// �e�N�X�`���ւ̃|�C���^
	static LPDIRECT3DVERTEXBUFFER9	m_pD3DVtxBuffBillboard;		// ���_�o�b�t�@�ւ̃|�C���^
};

bool cbGetPlayerPos(CObjBase *pTgt, void *pPara);
