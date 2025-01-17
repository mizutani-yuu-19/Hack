//=============================================================================
//
// ライト処理 [light.cpp]
// Author : AKIRA TANAKA
//
//=============================================================================
#include "light.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define	NUM_LIGHT		(1)		// ライトの数

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************

//*****************************************************************************
// グローバル変数
//*****************************************************************************
D3DLIGHT9 g_aLight[NUM_LIGHT];		// ライト情報

//=============================================================================
// ライトの初期化処理
//=============================================================================
HRESULT InitLight(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXVECTOR3 vecDir;

	// D3DLIGHT9構造体を0でクリアする
	ZeroMemory(&g_aLight[0], sizeof(D3DLIGHT9));

	// ライトのタイプの設定
	g_aLight[0].Type = D3DLIGHT_DIRECTIONAL;

	// 拡散光
	g_aLight[0].Diffuse = D3DXCOLOR(1.0f, 1.0f, 0.7f, 1.0f);

	// 環境光
	g_aLight[0].Ambient = D3DXCOLOR(1.0f, 1.0f, 0.7f, 1.0f);

	// ライトの方向の設定
	vecDir = D3DXVECTOR3(-0.0f, -1.0f, 0.0f);
	D3DXVec3Normalize((D3DXVECTOR3*)&g_aLight[0].Direction, &vecDir);

	// ライトをレンダリングパイプラインに設定
	pDevice->SetLight(0, &g_aLight[0]);

	// ライトの設定
	pDevice->LightEnable(0, TRUE);

	//// D3DLIGHT9構造体を0でクリアする
	//ZeroMemory(&g_aLight[1], sizeof(D3DLIGHT9));

	//// ライトのタイプの設定
	//g_aLight[1].Type = D3DLIGHT_DIRECTIONAL;

	//// 拡散光
	//g_aLight[1].Diffuse = D3DXCOLOR(0.5f, 0.5f, 0.5f, 1.0f);

	//// 環境光
	//g_aLight[1].Ambient = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
 //   // ライトの方向の設定
	//vecDir = D3DXVECTOR3(-0.0f, -1.0f, -0.8f);
	//D3DXVec3Normalize((D3DXVECTOR3*)&g_aLight[1].Direction, &vecDir);

	//// ライトをレンダリングパイプラインに設定
	//pDevice->SetLight(1, &g_aLight[1]);

	//// ライトの設定
	//pDevice->LightEnable(1, TRUE);



	//// D3DLIGHT9構造体を0でクリアする
	//ZeroMemory(&g_aLight[2], sizeof(D3DLIGHT9));

	//// ライトのタイプの設定
	//g_aLight[2].Type = D3DLIGHT_DIRECTIONAL;

	//// 拡散光
	//g_aLight[2].Diffuse = D3DXCOLOR(0.2f, 0.2f, 0.2f, 1.0f);

	//// 環境光
	//g_aLight[2].Ambient = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	//// ライトの方向の設定
	//vecDir = D3DXVECTOR3(-0.0f, 1.0f, 0.8f);
	//D3DXVec3Normalize((D3DXVECTOR3*)&g_aLight[2].Direction, &vecDir);

	//// ライトをレンダリングパイプラインに設定
	//pDevice->SetLight(2, &g_aLight[2]);

	//// ライトの設定
	//pDevice->LightEnable(2, TRUE);

	// ライティングモード
	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);

	return S_OK;
}

//=============================================================================
// ライトの終了処理
//=============================================================================
void UninitLight(void)
{
}

//=============================================================================
// ライトの更新処理
//=============================================================================
void UpdateLight(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// モデル位置の取得
	//D3DXVECTOR3 posModel = CCharacter::GetPlayerPos(0);

    // ライトの位置の設定
	//g_aLight[2].Position.x = posModel.x;
	//g_aLight[2].Position.z = posModel.z;

	// ライトをレンダリングパイプラインに設定
	//pDevice->SetLight(2, &g_aLight[2]);
}
