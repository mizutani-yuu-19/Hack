////////////////////////////////////////////////////////////////////////////////////
//
// enemy.cpp
//
////////////////////////////////////////////////////////////////////////////////////
//=================インクルード=====================
#include "enemy.h"
#include "input.h"
#include "camera.h"
#include "effect.h"
#include "billboard.h"
#include "sprite.h"
#include "stage.h"
#include "player.h"
#include "game.h"
#include "sound.h"
//================定数==================
#define ENEMY_SPEED (0.05f)
#define ENEMY_ROT_SPEED (0.05f)
#define ENEMY_BULLET_ROT_SPEED (0.1f)
#define ENEMY_BULLET_SPEED (0.15f)
#define ENEMY_BULLET_FOLLOW_SPEED (0.1f)
#define ENEMY_BULLET_SIZE	(2.0f)
#define BALLENEMY_SIZE	(2.0f)
#define ENEMY_PURPLE_BULLET_TEX	("data/TEXTURE/enemypurplebullet.png")
#define ENEMY_ORANGE_BULLET_TEX	("data/TEXTURE/enemyorangebullet.png")
#define BALLENEMY_TEX			("data/TEXTURE/ballenemy.png")
#define ENEMY_BULLET_INTERVAL (30)
#define FOLLOWENEMY_BULLET_INTERVAL (60)
#define FOLLOWENEMY_FOLLOWBULLET_INTERVAL (40)

void CreateEnemyBullet(point3 pos, vector3 rot, int type);

typedef struct COLOR_VERTEX {
	D3DXVECTOR3 vecCoord;
	//	FLOAT w;
	FLOAT fScale;
	DWORD dwColor;
};

//==================================================
//=================ボールエネミークラス=================
//==================================================
LPDIRECT3DTEXTURE9		CBallEnemy::m_pD3DTexture;		// テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9	CBallEnemy::m_pD3DVtxBuffBillboard;		// 頂点バッファへのポインタ
CBallEnemy::CBallEnemy(point3 pos, int difficulty)
{
	CObjBase();
	m_pos = pos;
	m_pos.y = 0.5f;
	m_move = point3(0.0f, 0.0f, 0.0f);
	m_rot = point3(0.0f, PI, 0.0f);
	m_radius = BALLENEMY_SIZE*0.5f;
	m_life = 5;
	m_bulletNum = difficulty;
	m_bulletDirect = point3(0.0f, 0.0f, 0.0f);
	if (!m_pD3DVtxBuffBillboard) {
		CreateBillboard(&m_pD3DTexture, &m_pD3DVtxBuffBillboard, BALLENEMY_SIZE, BALLENEMY_TEX);
	}
	m_pD3DTextureShadow = SetTexture("data/TEXTURE/shadow.jpg");
	m_bulletInterval = ENEMY_BULLET_INTERVAL;
}

CBallEnemy::~CBallEnemy()
{
	if (m_life == 0) {
		PlaySound(SOUND_LABEL_BREAK, 7.0f);
		CEffect::CreateEffect(EFFECT_BREAK, m_pos, m_rot);
	}
}

void CBallEnemy::Init() {

}

void CBallEnemy::Update() {
	point3 player;
	ObjSys.LoopStage(OBJLIST_PLAYER, cbGetPlayerPos, &player);
	// 移動
	vector2 vec1 = vector2(player.x - m_pos.x, player.z - m_pos.z);
	vector2 vec2 = point2(m_move.x, m_move.z);

	float cross = vec1.x*vec2.y - vec2.x*vec1.y;
	if (cross > 0)
		cross = 1;
	else
		cross = -1;

	if (cos(PI*0.1f) > vec1.x*vec2.x + vec2.y*vec1.y / (sqrt(vec2.x*vec2.x + vec2.y*vec2.y) * sqrt(vec1.x*vec1.x + vec1.y*vec1.y))) {
		m_rot.y += cross*ENEMY_ROT_SPEED;
	}
	m_move.x = ENEMY_SPEED*sin(m_rot.y);
	m_move.z = ENEMY_SPEED*cos(m_rot.y);

	m_pos += m_move;

	if (m_bulletInterval < 0) {
		for (int i = 0; i < m_bulletNum; i++) {
			CreateEnemyBullet(m_pos, vector3(0.0f, m_bulletDirect.y + PI*2.0f / m_bulletNum*i, 0.0f), (i + m_bulletInterval + 100) % 2);
		}
		m_bulletInterval = ENEMY_BULLET_INTERVAL;
	}
	m_bulletDirect.y += 0.01f;
	m_bulletInterval -= clear[nowLevel] + 1;
	// 壁押し戻し
	ObjSys.LoopStage(OBJLIST_STAGE, cbStageOutCharacter, this);
}

void CBallEnemy::DrawAlpha() {
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	D3DXMATRIX mtxWorld;
	// ワールドマトリックスの初期化
	D3DXMatrixIdentity(&mtxWorld);

	// ワールドマトリックスの設定
	pDevice->SetTransform(D3DTS_WORLD, &mtxWorld);

	point3 camPos;
	ObjSys.LoopStage(OBJLIST_CAMERA, cbGetCamPos, &camPos);

	FLOAT fScale;
	if (camPos.x == 0.0f&&camPos.z == 0.0f) {
		fScale = 10;
	}
	else {
		fScale = 60;
	}
	COLOR_VERTEX* pointSprite = new COLOR_VERTEX;
	pointSprite->dwColor = D3DCOLOR_ARGB(255, 255, 255, 255);
	pointSprite->fScale = fScale;

	pointSprite->vecCoord = m_pos+point3(0.4f,-0.1f,-0.4f);
	// 深度バッファ無効化
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);
	// ライティング無効化
	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);
	pDevice->SetRenderState(D3DRS_POINTSPRITEENABLE, TRUE);
	pDevice->SetFVF(D3DFVF_XYZ | D3DFVF_PSIZE | D3DFVF_DIFFUSE);
	pDevice->SetTexture(0, m_pD3DTextureShadow);
	SetRenderMode(BLEND_SUBTRACTION);
	// ポリゴンの描画
	pDevice->DrawPrimitiveUP(D3DPT_POINTLIST, 1, pointSprite, sizeof(COLOR_VERTEX));

	pointSprite->vecCoord = m_pos;
	pDevice->SetTexture(0, m_pD3DTexture);
	SetRenderMode(BLEND_TRANSLUCENT);
	// ポリゴンの描画
	pDevice->DrawPrimitiveUP(D3DPT_POINTLIST, 1, pointSprite, sizeof(COLOR_VERTEX));


	delete[] pointSprite;

	// ライティング有効化
	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);
}

// 八の字
void CBallEnemyEight::Update() {
	m_pos.x = 10 * sin(m_rad * 3 * (clear[nowLevel] + 1));
	m_pos.z = 10 * sin(m_rad * 5 * ((clear[nowLevel] + 1) * 2));
	m_rad += 0.001f*(clear[nowLevel] + 1);
	if (m_bulletInterval < 0) {
		for (int i = 0; i < m_bulletNum; i++) {
			CreateEnemyBullet(m_pos, vector3(0.0f, PI*2.0f / m_bulletNum*i, 0.0f), 0);
		}
		m_bulletInterval = 60;
	}
	m_bulletInterval -= clear[nowLevel] + 1;
}
// さゆう
void CBallEnemyLR::Update() {
	m_pos.x = 10 * sin(m_rad);
	m_rad += 0.01f*(clear[nowLevel] + 1);
	if (m_bulletInterval < 0) {
		for (int i = 0; i < m_bulletNum; i++) {
			CreateEnemyBullet(m_pos, vector3(0.0f, PI*2.0f / m_bulletNum*i, 0.0f), (i + m_bulletInterval + 100) % (clear[nowLevel] + 1) % 3);
		}
		m_bulletInterval = 60;
	}
	m_bulletInterval -= clear[nowLevel] + 1;
}
//====================とがってる敵=====================
CModel *CFollowEnemy::m_model = NULL;
CFollowEnemy::CFollowEnemy(point3 pos, int bulletType)
{
	CObjBase();
	m_pos = pos;
	m_pos.y = 0.5f;
	m_move = point3(0.0f, 0.0f, 0.0f);
	m_radius = BALLENEMY_SIZE*0.5f;
	m_life = 2;
	m_bulletType = bulletType;
	if (!m_model) {
		m_model = new CModel("data/MODEL/followenemy.x");
	}
	m_pD3DTexture = SetTexture("data/TEXTURE/shadow.jpg");
	m_bulletInterval = ENEMY_BULLET_INTERVAL;
}

CFollowEnemy::~CFollowEnemy()
{
	if (m_life == 0) {
		PlaySound(SOUND_LABEL_BREAK, 7.0f);
		CEffect::CreateEffect(EFFECT_BREAK, m_pos, m_rot );
	}
}

void CFollowEnemy::Init() {

}

void CFollowEnemy::Update() {
	point3 player;
	ObjSys.LoopStage(OBJLIST_PLAYER, cbGetPlayerPos, &player);
	// 移動
	vector2 vec1 = vector2(player.x - m_pos.x, player.z - m_pos.z);
	vector2 vec2 = point2(m_move.x, m_move.z);

	float cross = vec1.x*vec2.y - vec2.x*vec1.y;
	if (cross > 0)
		cross = 1;
	else
		cross = -1;

	if (cos(PI*0.1f) > vec1.x*vec2.x + vec2.y*vec1.y / (sqrt(vec2.x*vec2.x + vec2.y*vec2.y) * sqrt(vec1.x*vec1.x + vec1.y*vec1.y))) {
		m_rot.y += cross*ENEMY_ROT_SPEED;
	}
	m_move.x = ENEMY_SPEED*sin(m_rot.y);
	m_move.z = ENEMY_SPEED*cos(m_rot.y);

	m_pos += m_move;

	// 弾発射
	if (m_bulletInterval < 0) {
		CreateEnemyBullet(m_pos, m_rot, m_bulletType);
		m_bulletInterval = FOLLOWENEMY_BULLET_INTERVAL;
	}
	m_bulletInterval -= (clear[nowLevel] + 1);
	// 壁押し戻し
	ObjSys.LoopStage(OBJLIST_STAGE, cbStageOutCharacter, this);
}
void CFollowEnemy::Draw() {
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXMATRIX mtxRot, mtxTranslate, mtxSize, mtxWorld;
	D3DXMATERIAL *pD3DXMat;
	D3DMATERIAL9 matDef;


	//ワールドマトリックスの初期化
	D3DXMatrixIdentity(&mtxWorld);

	//大きさを反映
	//D3DXMatrixScaling(&mtxSize, 2, 2, 2);
	//D3DXMatrixMultiply(&mtxWorld, &mtxWorld, &mtxSize);

	//回転を反映
	D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y, 0, 0);
	D3DXMatrixMultiply(&mtxWorld, &mtxWorld, &mtxRot);

	//移動を反映
	D3DXMatrixTranslation(&mtxTranslate, m_pos.x, m_pos.y, m_pos.z);
	D3DXMatrixMultiply(&mtxWorld, &mtxWorld, &mtxTranslate);

	// テクスチャなし
	pDevice->SetTexture(0, NULL);

	//ワールドマトリックスの設定
	pDevice->SetTransform(D3DTS_WORLD, &mtxWorld);

	m_model->DrawModel();
}
void CFollowEnemy::DrawAlpha() {

	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	struct COLOR_VERTEX {
		D3DXVECTOR3 vecCoord;
		//	FLOAT w;
		FLOAT fScale;
		DWORD dwColor;
	};
	D3DXMATRIX mtxWorld;
	// ワールドマトリックスの初期化
	D3DXMatrixIdentity(&mtxWorld);

	// ワールドマトリックスの設定
	pDevice->SetTransform(D3DTS_WORLD, &mtxWorld);

	point3 camPos;
	ObjSys.LoopStage(OBJLIST_CAMERA, cbGetCamPos, &camPos);

	FLOAT fScale;
	if (camPos.x == 0.0f&&camPos.z == 0.0f) {
		fScale = 10;
	}
	else {
		fScale = 60;
	}
	COLOR_VERTEX* pointSprite = new COLOR_VERTEX;
	pointSprite->dwColor = D3DCOLOR_ARGB(255, 255, 255, 255);
	pointSprite->fScale = fScale;
	pointSprite->vecCoord = m_pos;


	// 深度バッファ無効化
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);
	// ライティング無効化
	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);
	pDevice->SetRenderState(D3DRS_POINTSPRITEENABLE, TRUE);
	pDevice->SetTexture(0, m_pD3DTexture);
	pDevice->SetFVF(D3DFVF_XYZ | D3DFVF_PSIZE | D3DFVF_DIFFUSE);
	// ポリゴンの描画
	//// 減算合成の設定
	SetRenderMode(BLEND_SUBTRACTION);
	pDevice->DrawPrimitiveUP(D3DPT_POINTLIST, 1, pointSprite, sizeof(COLOR_VERTEX));

	delete[] pointSprite;

	// ライティング有効化
	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
}
//==================================================
//=================エネミー紫弾クラス===============
//==================================================
LPDIRECT3DTEXTURE9		CEnemyPurpleBullet::m_pD3DTexture = NULL;				// テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9	CEnemyPurpleBullet::m_pD3DVtxBuffBillboard = NULL;		// 頂点バッファへのポインタ

CEnemyPurpleBullet::CEnemyPurpleBullet(point3 pos, vector3 rot)
{
	m_life = -1;
	m_pos = pos;
	m_move.x = ENEMY_BULLET_SPEED * sin(rot.y);
	m_move.z = ENEMY_BULLET_SPEED * cos(rot.y);
	if (!m_pD3DVtxBuffBillboard) {
		CreateBillboard(&m_pD3DTexture, &m_pD3DVtxBuffBillboard, ENEMY_BULLET_SIZE, ENEMY_PURPLE_BULLET_TEX);
	}
}

CEnemyPurpleBullet::~CEnemyPurpleBullet()
{

}

void CEnemyPurpleBullet::Update() {
	m_pos += m_move;
	ObjSys.LoopStage(OBJLIST_STAGE, cbStageOutBullet, this);
}
void CEnemyPurpleBullet::DrawAlpha() {
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	D3DXMATRIX mtxWorld;
	// ワールドマトリックスの初期化
	D3DXMatrixIdentity(&mtxWorld);

	// ワールドマトリックスの設定
	pDevice->SetTransform(D3DTS_WORLD, &mtxWorld);

	point3 camPos;
	ObjSys.LoopStage(OBJLIST_CAMERA, cbGetCamPos, &camPos);

	FLOAT fScale;
	if (camPos.x == 0.0f&&camPos.z == 0.0f) {
		fScale = 10;
	}
	else {
		fScale = 60;
	}
	COLOR_VERTEX* pointSprite = new COLOR_VERTEX;
	pointSprite->dwColor = D3DCOLOR_ARGB(255, 255, 255, 255);
	pointSprite->fScale = fScale;
	pointSprite->vecCoord = m_pos;


	// 深度バッファ無効化
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);
	// ライティング無効化
	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);
	pDevice->SetRenderState(D3DRS_POINTSPRITEENABLE, TRUE);
	pDevice->SetTexture(0, m_pD3DTexture);
	pDevice->SetFVF(D3DFVF_XYZ | D3DFVF_PSIZE | D3DFVF_DIFFUSE);
	// ポリゴンの描画
	SetRenderMode(BLEND_TRANSLUCENT);
	pDevice->DrawPrimitiveUP(D3DPT_POINTLIST, 1, pointSprite, sizeof(COLOR_VERTEX));

	delete[] pointSprite;

	// ライティング有効化
	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);
}

//==================================================
//=================エネミーオレンジ弾クラス=============
//==================================================
LPDIRECT3DTEXTURE9		CEnemyOrangeBullet::m_pD3DTexture = NULL;				// テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9	CEnemyOrangeBullet::m_pD3DVtxBuffBillboard = NULL;		// 頂点バッファへのポインタ

CEnemyOrangeBullet::CEnemyOrangeBullet(point3 pos, vector3 rot)
{
	m_life = 1;
	m_pos = pos;
	m_move.x = ENEMY_BULLET_SPEED * sin(rot.y);
	m_move.z = ENEMY_BULLET_SPEED * cos(rot.y);
	if (!m_pD3DVtxBuffBillboard) {
		CreateBillboard(&m_pD3DTexture, &m_pD3DVtxBuffBillboard, ENEMY_BULLET_SIZE, ENEMY_ORANGE_BULLET_TEX);
	}
}

CEnemyOrangeBullet::~CEnemyOrangeBullet()
{
	if (m_life == 0) {
		CEffect::CreateEffect(EFFECT_BULLETBREAK, m_pos, m_rot);
	}
}

void CEnemyOrangeBullet::Update() {
	m_pos += m_move;
	ObjSys.LoopStage(OBJLIST_STAGE, cbStageOutBullet, this);
}
void CEnemyOrangeBullet::DrawAlpha() {
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	D3DXMATRIX mtxWorld;
	// ワールドマトリックスの初期化
	D3DXMatrixIdentity(&mtxWorld);

	// ワールドマトリックスの設定
	pDevice->SetTransform(D3DTS_WORLD, &mtxWorld);

	point3 camPos;
	ObjSys.LoopStage(OBJLIST_CAMERA, cbGetCamPos, &camPos);

	FLOAT fScale;
	if (camPos.x == 0.0f&&camPos.z == 0.0f) {
		fScale = 10;
	}
	else {
		fScale = 60;
	}
	COLOR_VERTEX* pointSprite = new COLOR_VERTEX;
	pointSprite->dwColor = D3DCOLOR_ARGB(255, 255, 255, 255);
	pointSprite->fScale = fScale;
	pointSprite->vecCoord = m_pos;


	// 深度バッファ無効化
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);
	// ライティング無効化
	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);
	pDevice->SetRenderState(D3DRS_POINTSPRITEENABLE, TRUE);
	pDevice->SetTexture(0, m_pD3DTexture);
	pDevice->SetFVF(D3DFVF_XYZ | D3DFVF_PSIZE | D3DFVF_DIFFUSE);
	// ポリゴンの描画
	SetRenderMode(BLEND_TRANSLUCENT);
	pDevice->DrawPrimitiveUP(D3DPT_POINTLIST, 1, pointSprite, sizeof(COLOR_VERTEX));

	delete[] pointSprite;

	// ライティング有効化
	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);
}

CModel *CFollowBullet::m_model = NULL;
CFollowBullet::CFollowBullet(point3 pos, vector3 rot)
{
	CObjBase();
	m_rot = rot;
	m_move = point3(0.0f, 0.0f, 0.0f);
	m_move.x = ENEMY_BULLET_FOLLOW_SPEED*sin(m_rot.y);
	m_move.z = ENEMY_BULLET_FOLLOW_SPEED*cos(m_rot.y);
	m_pos = pos + m_move*10.0f;
	m_radius = BALLENEMY_SIZE*0.5f;
	m_life = 1;
	if (!m_model) {
		m_model = new CModel("data/MODEL/followbullet.x");
	}
}

CFollowBullet::~CFollowBullet()
{
	if (m_life == 0) {
		CEffect::CreateEffect(EFFECT_BULLETBREAK, m_pos, m_rot);
	}
}

void CFollowBullet::Init() {

}

void CFollowBullet::Update() {
	point3 player;
	ObjSys.LoopStage(OBJLIST_PLAYER, cbGetPlayerPos, &player);
	// 移動
	vector2 vec1 = vector2(player.x - m_pos.x, player.z - m_pos.z);
	vector2 vec2 = point2(m_move.x, m_move.z);

	float cross = vec1.x*vec2.y - vec2.x*vec1.y;
	if (cross > 0)
		cross = 1;
	else
		cross = -1;

	if (cos(PI*0.1f) > vec1.x*vec2.x + vec2.y*vec1.y / (sqrt(vec2.x*vec2.x + vec2.y*vec2.y) * sqrt(vec1.x*vec1.x + vec1.y*vec1.y))) {
		m_rot.y += cross*ENEMY_BULLET_ROT_SPEED;
	}
	m_move.x = ENEMY_BULLET_FOLLOW_SPEED*sin(m_rot.y);
	m_move.z = ENEMY_BULLET_FOLLOW_SPEED*cos(m_rot.y);

	m_pos += m_move;
	// 壁押し戻し
	ObjSys.LoopStage(OBJLIST_STAGE, cbStageOutCharacter, this);
}
void CFollowBullet::Draw() {
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXMATRIX mtxRot, mtxTranslate, mtxSize, mtxWorld;
	D3DXMATERIAL *pD3DXMat;
	D3DMATERIAL9 matDef;


	//ワールドマトリックスの初期化
	D3DXMatrixIdentity(&mtxWorld);

	//大きさを反映
	//D3DXMatrixScaling(&mtxSize, 2, 2, 2);
	//D3DXMatrixMultiply(&mtxWorld, &mtxWorld, &mtxSize);

	//回転を反映
	D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y, 0, 0);
	D3DXMatrixMultiply(&mtxWorld, &mtxWorld, &mtxRot);

	//移動を反映
	D3DXMatrixTranslation(&mtxTranslate, m_pos.x, m_pos.y, m_pos.z);
	D3DXMatrixMultiply(&mtxWorld, &mtxWorld, &mtxTranslate);

	// テクスチャなし
	pDevice->SetTexture(0, NULL);

	//ワールドマトリックスの設定
	pDevice->SetTransform(D3DTS_WORLD, &mtxWorld);

	m_model->DrawModel();
}

// 弾作成関数
void CreateEnemyBullet(point3 pos, vector3 rot, int type) {
	CObjBase* pEnemyBullet;
	switch (type)
	{
	case 0:
		pEnemyBullet = new CEnemyPurpleBullet(pos, rot);
		ObjSys.Add(pEnemyBullet, OBJ_ENEMYBULLETPURPLE);
		break;
	case 1:
		pEnemyBullet = new CEnemyOrangeBullet(pos, rot);
		ObjSys.Add(pEnemyBullet, OBJ_ENEMYBULLET);
		break;
	case 2:
		pEnemyBullet = new CFollowBullet(pos, rot);
		ObjSys.Add(pEnemyBullet, OBJ_ENEMYBULLET);
		break;
	default:
		break;
	}
}
