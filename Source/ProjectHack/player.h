////////////////////////////////////////////////////////////////////////////////////
//
// player.h
//
////////////////////////////////////////////////////////////////////////////////////
#pragma once
//=============インクルード===============
#include "objbase.h"
#include "character.h"
#include "model.h"
//============プレイヤークラス==================
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
	LPDIRECT3DTEXTURE9		m_pD3DTexture;		// テクスチャへのポインタ
	LPDIRECT3DVERTEXBUFFER9	m_pD3DVtxBuffShadow;		// 頂点バッファへのポインタ
};

class CPlayerBullet :public CObjBase {

public:
	CPlayerBullet(point3 pos, vector3 rot);
	~CPlayerBullet();
	
	void Update();
	void DrawAlpha();
private:
	static LPDIRECT3DTEXTURE9		m_pD3DTexture;		// テクスチャへのポインタ
	static LPDIRECT3DVERTEXBUFFER9	m_pD3DVtxBuffBillboard;		// 頂点バッファへのポインタ
};

bool cbGetPlayerPos(CObjBase *pTgt, void *pPara);
