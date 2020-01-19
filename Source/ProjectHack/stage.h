////////////////////////////////////////////////////////////////////////////////////
//
// stage.h
//
////////////////////////////////////////////////////////////////////////////////////
#pragma once
//=============インクルード===============
#include "objbase.h"

//============ステージクラス==================
class CStage:public CObjBase
{
public:
	CStage(int nNumBlockX, int nNumBlockZ, float fSizeBlockX, float fSizeBlockZ);
	~CStage();

	void Draw();
private:
	int m_nNumBlockX;
	int m_nNumBlockZ;
	int	m_nNumVertex;
	int m_nNumIndex;
	int m_nNumPolygon;
	int m_fSizeBlockX;
	int m_fSizeBlockZ;

	LPDIRECT3DVERTEXBUFFER9 m_pD3DVtxBuffField;	// 頂点バッファへのポインタ
	LPDIRECT3DINDEXBUFFER9 m_pD3DIdxBuffField;	// インデックスバッファへのポインタ
};

// 画面外
bool cbStageOutBullet(CObjBase *pTgt, void *pPara);
bool cbStageOutCharacter(CObjBase *pTgt, void *pPara);

