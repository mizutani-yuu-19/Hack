//=============================================================================
//
// モデル処理 [model.h]
// Author : HIROHIKO HAMAYA
//
//=============================================================================
#ifndef ___MODEL_H_
#define ___MODEL_H_

#include "main.h"

//*****************************************************************************
// 構造体定義
//*****************************************************************************
class CModel{
private:
	LPD3DXMESH			pMesh;		// メッシュ
	D3DMATERIAL9*		pMaterial;	// マテリアル配列
	DWORD				dwNumMat;	// マテリアル数
	DWORD				dwAttr;		// 属性数(サブセット数)
	D3DXATTRIBUTERANGE*	pAttr;		// 属性配列
public:	
	CModel(LPCTSTR pszFName);
	~CModel();
	void DrawModel();
	void DrawModelNoAlpha();
	void DrawModelAlpha(float fAlpha);
};

#endif
