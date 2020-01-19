//=======================================================
//
// フェード イン/アウト処理 (fade.cpp)
//
//=======================================================
#include "fade.h"
#include "sprite.h"
#include "sound.h"
//----- マクロ定義

//=======================================================
//　構　造　体　宣　言
//=======================================================

//=======================================================
//　グ　ロ　ー　バ　ル　変　数
//=======================================================

VERTEX_2D	g_vertex[VERTEX_NUM];	//頂点情報

int	g_fadeCount;
int g_nDir;

int	g_nRed;			// フェードアウト色(R)
int	g_nGreen;		// フェードアウト色(G)
int	g_nBlue;		// フェードアウト色(B)

static LPDIRECT3DDEVICE9 g_pDevice;
static LPDIRECT3DTEXTURE9 g_pTex;

//=======================================================
//　初　期　化　処　理
//=======================================================
void InitFade()
{
	for (int i = 0; i < VERTEX_NUM; i++)
	{
		g_vertex[i].uv = D3DXVECTOR2(i & 1, i >> 1);
		g_vertex[i].vtxPos.x = g_vertex[i].uv.x * SCREEN_WIDTH;
		g_vertex[i].vtxPos.y = g_vertex[i].uv.y * SCREEN_HEIGHT;
		g_vertex[i].vtxPos.z = 0.0f;
		g_vertex[i].rhw = 1.0f;
		g_vertex[i].diffuse = D3DCOLOR_ARGB(0, 0, 0, 0);
	}
	g_pTex = SetTexture("data/TEXTURE/background.png");
	g_fadeCount = -1;
	g_nDir = -1;
	g_nRed = 255;
	g_nBlue = 255;
	g_nGreen = 255;
}
//=======================================================
//　更　新　処　理
//=======================================================
void UpdateFade()
{
	g_fadeCount += g_nDir;

	if (g_fadeCount < 0)
	{
		g_fadeCount = 0;
	}

	else if (g_fadeCount > FADE_TIME)
	{
		g_fadeCount = FADE_TIME;
	}

	int nAlpha = g_fadeCount * 255 / FADE_TIME;

	D3DCOLOR color = D3DCOLOR_ARGB(nAlpha, g_nRed, g_nGreen, g_nBlue);

	for (int i = 0; i < 4; ++i)
	{
		g_vertex[i].diffuse = color;
	}
}

//=======================================================
//　描　画　処　理
//=======================================================
void DrawFade()
{
	g_pDevice = GetDevice();
	// 頂点書式設定
	g_pDevice->SetFVF(FVF_VERTEX_2D);

	// テクスチャ設定
	g_pDevice->SetTexture(0, g_pTex);
	SetRenderMode(BLEND_TRANSLUCENT);
	// ポリゴン描画(頂点配列使用)
	g_pDevice->DrawPrimitiveUP( D3DPT_TRIANGLESTRIP, 2, g_vertex, sizeof(g_vertex[0]));
}

//=======================================================
//　フェードイン開始
//=======================================================
void  StartFadeIn()
{
	g_fadeCount = FADE_TIME;
	g_nDir = -1;
}
//=======================================================
//　フェードアウト開始
//=======================================================
void StartFadeOut()
{
	g_fadeCount = 0;
	g_nDir = 1;
	PlaySound(SOUND_LABEL_FADE, 10.0f);
}

//=======================================================
//　フェードイン終了
//=======================================================
int EndFadeIn()
{
	return (g_nDir < 0 && g_fadeCount <= 0);
}

//=======================================================
//　フェードアウト終了
//=======================================================
int EndFadeOut()
{
	return (g_nDir > 0 && g_fadeCount >= FADE_TIME);
}
