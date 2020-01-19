//=============================================================================
// ビルボード作成
//=============================================================================
#include "main.h"
#include "billboard.h"
void CreateBillboard(LPDIRECT3DTEXTURE9	*pD3DTexture, LPDIRECT3DVERTEXBUFFER9 *pD3DVtxBuffBillboard, float size, char* texPath)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	// オブジェクトの頂点バッファを生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4,	// 頂点データ用に確保するバッファサイズ(バイト単位)
		D3DUSAGE_WRITEONLY,			// 頂点バッファの使用法　
		FVF_VERTEX_3D,				 // 使用する頂点フォーマット
		D3DPOOL_MANAGED,			// リソースのバッファを保持するメモリクラスを指定
		pD3DVtxBuffBillboard,	// 頂点バッファインターフェースへのポインタ
		NULL);						// NULLに設定

	{//頂点バッファの中身を埋める
		VERTEX_3D *pVtx;

		// 頂点データの範囲をロックし、頂点バッファへのポインタを取得
		pD3DVtxBuffBillboard[0]->Lock(0, 0, (void**)&pVtx, 0);

		for (int nCntVtxY = 0; nCntVtxY < 1; nCntVtxY++)
		{
			for (int nCntVtxX = 0; nCntVtxX < 2; nCntVtxX++, pVtx += 2)
			{
				// 頂点座標の設定
				pVtx[0].vtx.x = -(0.5f) * size + nCntVtxX * size;
				pVtx[0].vtx.y = (0.5f) *  size - size;
				pVtx[0].vtx.z = 0.0f;
				pVtx[1].vtx.x = -(0.5f) * size + nCntVtxX * size;
				pVtx[1].vtx.y = (0.5f) *  size;
				pVtx[1].vtx.z = 0.0f;

				// 法線の設定
				pVtx[0].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
				pVtx[1].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);

				// 反射光の設定
				pVtx[0].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
				pVtx[1].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

				// テクスチャ座標の設定
				pVtx[0].tex.x = nCntVtxX;
				pVtx[0].tex.y = (nCntVtxY + 1);
				pVtx[1].tex.x = nCntVtxX;
				pVtx[1].tex.y = nCntVtxY;
			}
		}

		// 頂点データをアンロックする
		pD3DVtxBuffBillboard[0]->Unlock();
	}

	D3DXCreateTextureFromFile(pDevice,						// デバイスへのポインタ
		texPath,			// ファイルの名前
		pD3DTexture);	// 読み込むメモリー
}

//=============================================================================
// 影作成
//=============================================================================
void CreateShadow(LPDIRECT3DTEXTURE9	*pD3DTexture, LPDIRECT3DVERTEXBUFFER9 *pD3DVtxBuffBillboard, float size, char* texPath)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	// オブジェクトの頂点バッファを生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4,	// 頂点データ用に確保するバッファサイズ(バイト単位)
		D3DUSAGE_WRITEONLY,			// 頂点バッファの使用法　
		FVF_VERTEX_3D,				 // 使用する頂点フォーマット
		D3DPOOL_MANAGED,			// リソースのバッファを保持するメモリクラスを指定
		pD3DVtxBuffBillboard,	// 頂点バッファインターフェースへのポインタ
		NULL);						// NULLに設定

	{//頂点バッファの中身を埋める
		VERTEX_3D *pVtx;

		// 頂点データの範囲をロックし、頂点バッファへのポインタを取得
		pD3DVtxBuffBillboard[0]->Lock(0, 0, (void**)&pVtx, 0);

		for (int nCntVtxY = 0; nCntVtxY < 1; nCntVtxY++)
		{
			for (int nCntVtxX = 0; nCntVtxX < 2; nCntVtxX++, pVtx += 2)
			{
				// 頂点座標の設定
				pVtx[0].vtx.x = -(0.5f) * size + nCntVtxX * size;
				pVtx[0].vtx.z = (0.5f) *  size - size;
				pVtx[0].vtx.y = 0.0f;
				pVtx[1].vtx.x = -(0.5f) * size + nCntVtxX * size;
				pVtx[1].vtx.z = (0.5f) *  size;
				pVtx[1].vtx.y = 0.0f;

				// 法線の設定
				pVtx[0].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
				pVtx[1].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

				// 反射光の設定
				pVtx[0].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
				pVtx[1].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

				// テクスチャ座標の設定
				pVtx[0].tex.x = nCntVtxX;
				pVtx[0].tex.y = (nCntVtxY + 1);
				pVtx[1].tex.x = nCntVtxX;
				pVtx[1].tex.y = nCntVtxY;
			}
		}

		// 頂点データをアンロックする
		pD3DVtxBuffBillboard[0]->Unlock();
	}

	D3DXCreateTextureFromFile(pDevice,						// デバイスへのポインタ
		texPath,			// ファイルの名前
		pD3DTexture);	// 読み込むメモリー
}