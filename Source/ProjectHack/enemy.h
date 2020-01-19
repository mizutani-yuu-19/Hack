////////////////////////////////////////////////////////////////////////////////////
//
// enemy.h
//
////////////////////////////////////////////////////////////////////////////////////
#pragma once
//=============インクルード===============
#include "objbase.h"
#include "character.h"
#include "model.h"
//============えねみークラス==================
class CBallEnemy :public CCharacter {
public:
	CBallEnemy(point3 pos, int difficulty);
	~CBallEnemy();

	void Init();
	virtual void Update();
	void DrawAlpha();
	int m_bulletNum;
	int m_bulletInterval;
	int m_time;
private:
	vector3 m_bulletDirect;
	static LPDIRECT3DTEXTURE9		m_pD3DTexture;		// テクスチャへのポインタ
	LPDIRECT3DTEXTURE9		m_pD3DTextureShadow;		// テクスチャへのポインタ
	static LPDIRECT3DVERTEXBUFFER9	m_pD3DVtxBuffBillboard;		// 頂点バッファへのポインタ
};

class CBallEnemyEight :public CBallEnemy {
public:
	CBallEnemyEight(point3 pos, int difficulty) :CBallEnemy(pos, difficulty) {};
	//~CBallEnemyEight();
	void Update();
private:
	float m_rad = 0.0f;
	int m_difficulty;
};

class CBallEnemyLR :public CBallEnemy {
public:
	CBallEnemyLR(point3 pos, int difficulty) :CBallEnemy(pos, difficulty) {};
	//~CBallEnemyEight();
	void Update();
private:
	float m_rad = 0.0f;
	int m_difficulty;
};

class CFollowEnemy :public CCharacter {
public:
	CFollowEnemy(point3 pos,int bulletType);
	~CFollowEnemy();

	void Init();
	void Update();
	void Draw();
	void DrawAlpha();
private:
	int m_bulletInterval;
	static CModel *m_model;
	int m_bulletType;
	LPDIRECT3DTEXTURE9		m_pD3DTexture;		// テクスチャへのポインタ
};

class CEnemyPurpleBullet :public CObjBase {
public:
	CEnemyPurpleBullet(point3 pos, vector3 rot);
	~CEnemyPurpleBullet();

	void Update();
	void DrawAlpha();
private:
	static LPDIRECT3DTEXTURE9		m_pD3DTexture;		// テクスチャへのポインタ
	static LPDIRECT3DVERTEXBUFFER9	m_pD3DVtxBuffBillboard;		// 頂点バッファへのポインタ
};

class CEnemyOrangeBullet :public CObjBase {

public:
	CEnemyOrangeBullet(point3 pos, vector3 rot);
	~CEnemyOrangeBullet();

	void Update();
	void DrawAlpha();
private:
	static LPDIRECT3DTEXTURE9		m_pD3DTexture;		// テクスチャへのポインタ
	static LPDIRECT3DVERTEXBUFFER9	m_pD3DVtxBuffBillboard;		// 頂点バッファへのポインタ
};

class CFollowBullet :public CObjBase {
public:
	CFollowBullet(point3 pos, vector3 rot);
	~CFollowBullet();

	void Init();
	void Update();
	void Draw();
private:
	static CModel *m_model;
};
