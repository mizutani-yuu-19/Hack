////////////////////////////////////////////////////////////////////////////////////
//
// objbase.h
//
////////////////////////////////////////////////////////////////////////////////////
#pragma once
//============インクルード==============
#include "main.h"
#include "sprite.h"

//============列挙体=================
enum {
	OBJ_CAMERA,
	OBJ_LIGHT,
	OBJ_PLAYER,
	OBJ_PLAYERBULLET,
	OBJ_ENEMYBULLET,
	OBJ_ENEMYBULLETPURPLE,
	OBJ_ENEMY,
	OBJ_WALL,
	OBJ_STAGE,
	OBJ_EFFECT,
	OBJ_UI,
	OBJ_MAX
};

#define OBJLIST_CAMERA			(1 << OBJ_CAMERA)
#define OBJLIST_LIGHT			(1 << OBJ_LIGHT)
#define OBJLIST_PLAYER			(1 << OBJ_PLAYER)
#define OBJLIST_PLAYERBULLET	(1 << OBJ_PLAYERBULLET)
#define OBJLIST_ENEMY			(1 << OBJ_ENEMY)
#define OBJLIST_ENEMYBULLET		(1 << OBJ_ENEMYBULLET)
#define OBJLIST_ENEMYBULLETPURPLE		(1 << OBJ_ENEMYBULLETPURPLE)
#define OBJLIST_WALL			(1 << OBJ_WALL)
#define OBJLIST_STAGE			(1 << OBJ_STAGE)
#define OBJLIST_EFFECT			(1 << OBJ_EFFECT)
#define OBJLIST_UI				(1 << OBJ_UI)
#define OBJLIST_ALL				((1 << OBJ_MAX) - 1)


//============typedef化=============
typedef D3DXVECTOR3 point3;
typedef D3DXVECTOR3 vector3;
typedef D3DXVECTOR2 point2;
typedef D3DXVECTOR2 vector2;
#define PI D3DX_PI
//============クラス===============
//----------ベース-------------
//これを継承することで同じものとして見れる
class CObjBase
{
public:
	CObjBase();
	virtual ~CObjBase();

	virtual void Init() {};
	virtual void Uninit() {};
	virtual void Update() {};
	virtual void Update2() {};
	virtual void Draw() {};
	virtual void DrawAlpha() {};
	virtual void Draw2D() {};
	
	point3 m_pos;
	vector3 m_move;
	vector3 m_accel;
	vector3 m_rot;
	float m_radius;
	int m_life;
	bool m_releaseFlag = false;
private:

};

class CBackGround
{
public:
	CBackGround();
	~CBackGround();

	void DrawBG();
private:
	LPDIRECT3DTEXTURE9 m_tex;
	CSprite m_sprite;
};

//------------オブジェクトのシステム---------------
class CObjSys
{
public:
	typedef std::list<CObjBase*> CObjList;
	typedef std::vector<CObjList*> CObjListArray;
	typedef bool(*LoopStageFunc)(CObjBase *pTgt, void *pPara);	/*true を返した時巡回終了*/

private:
	CObjListArray m_ObjListArray;
	CBackGround* m_pBackGround;
public:
//	CObjSys();
	~CObjSys();
	void Add(CObjBase *pObj, int stage);
	void Init();
	void AllUpdate();
	void AllDraw();
	void AllUninit();
	bool LoopStage(unsigned int StageMask, LoopStageFunc Func, void *pPara);	//true:ループの途中で抜け出した
};

bool ChkExistStage(unsigned int stage);

extern CObjSys ObjSys;