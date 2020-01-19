//=============================================================================
//
// モデル処理 [model.cpp]
// Author : HIROHIKO HAMAYA
//
//=============================================================================
#define _CRT_SECURE_NO_WARNINGS
#include "model.h"
#include <stdlib.h>

//*****************************************************************************
// マクロ定義
//*****************************************************************************

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************

//*****************************************************************************
// グローバル変数
//*****************************************************************************

//=============================================================================
// Xファイル読み込み
//=============================================================================
CModel::CModel(LPCTSTR pszFName)
{
	TCHAR				szDir[_MAX_DIR] = "data/MODEL";
	TCHAR				szCurrentDir[_MAX_PATH];
	LPDIRECT3DDEVICE9	pDevice = GetDevice();
	LPD3DXBUFFER		pBuffMaterial = NULL;

	// フォルダ名を抽出
	//_tsplitpath(pszFName, NULL, szDir, NULL, NULL);

	// Xファイル読み込み
	D3DXLoadMeshFromX(pszFName,
		D3DXMESH_SYSTEMMEM, pDevice, NULL, &pBuffMaterial,
		NULL, &dwNumMat, &pMesh);

	// 属性テーブル取得
	pMesh->OptimizeInplace(D3DXMESHOPT_COMPACT | D3DXMESHOPT_ATTRSORT, 0, 0, 0, 0);
	dwAttr = 0;
	pMesh->GetAttributeTable(NULL, &dwAttr);
	pAttr = new D3DXATTRIBUTERANGE[dwAttr];
	pMesh->GetAttributeTable(pAttr, &dwAttr);

	// カレントディレクトリを変更
	if (szDir[0]) {
		GetCurrentDirectory(_MAX_PATH, szCurrentDir);
		SetCurrentDirectory(szDir);
	}

	// マテリアル読み込み
	D3DXMATERIAL* material = (D3DXMATERIAL*)pBuffMaterial->GetBufferPointer();
	pMaterial = new D3DMATERIAL9[dwNumMat];
	for (DWORD i = 0; i < dwNumMat; ++i) {
		pMaterial[i] = material[i].MatD3D;
		pMaterial[i].Ambient = pMaterial[i].Diffuse;
	}
	SAFE_RELEASE(pBuffMaterial);

	// カレントディレクトリを元に戻す
	if (szDir[0])
		SetCurrentDirectory(szCurrentDir);
}

//=============================================================================
// Xファイル表示
//=============================================================================
void CModel::DrawModel()
{
	LPDIRECT3DDEVICE9	pDevice = GetDevice();

	D3DMATERIAL9 matDef;

	// 現在のマテリアルを取得
	pDevice->GetMaterial(&matDef);

	for (DWORD i = 0; i < dwAttr; ++i) {
		DWORD id = pAttr[i].AttribId;
		pDevice->SetMaterial(&pMaterial[id]);	// マテリアルを設定
		pMesh->DrawSubset(i);					// 描画を実行
	}

	// マテリアルをデフォルトに戻す
	pDevice->SetMaterial(&matDef);
}

//=============================================================================
// Xファイル不透明部分表示
//=============================================================================
void CModel::DrawModelNoAlpha()
{
	LPDIRECT3DDEVICE9	pDevice = GetDevice();

	for (DWORD i = 0; i < dwAttr; ++i) {
		DWORD id = pAttr[i].AttribId;
		if (pMaterial[id].Diffuse.a < 1.0f) continue;
		pDevice->SetMaterial(&pMaterial[id]);	// マテリアルを設定
		pMesh->DrawSubset(i);					// 描画を実行
	}
}

//=============================================================================
// Xファイル半透明表示
//=============================================================================
void CModel::DrawModelAlpha(float fAlpha)
{
	LPDIRECT3DDEVICE9	pDevice = GetDevice();
	D3DMATERIAL9 material;

	for (DWORD i = 0; i < dwAttr; ++i) {
		DWORD id = pAttr[i].AttribId;
		material = pMaterial[id];
		material.Diffuse.a *= fAlpha;
		if (material.Diffuse.a >= 1.0f) continue;
		pDevice->SetMaterial(&material);	// マテリアルを設定
		pMesh->DrawSubset(i);					// 描画を実行
	}
}

//=============================================================================
// Xファイル解放
//=============================================================================
CModel::~CModel()
{
	dwNumMat = 0;
	SAFE_DELETE_ARRAY(pMaterial);
	SAFE_RELEASE(pMesh);
}
