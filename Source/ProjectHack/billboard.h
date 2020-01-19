//=============================================================================
// ビルボード作成
//=============================================================================
#pragma once
#include "main.h"
void CreateBillboard(LPDIRECT3DTEXTURE9	*pD3DTexture, LPDIRECT3DVERTEXBUFFER9 *pD3DVtxBuffBillboard, float size, char* texPath);
void CreateShadow(LPDIRECT3DTEXTURE9	*pD3DTexture, LPDIRECT3DVERTEXBUFFER9 *pD3DVtxBuffBillboard, float size, char* texPath);
