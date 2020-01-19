////////////////////////////////////////////////////////////////////////////////////
//
// stage.h
//
////////////////////////////////////////////////////////////////////////////////////
//=============インクルード===============
#include "stage.h"

//============ステージクラス==================
CStage::CStage(int nNumBlockX, int nNumBlockZ, float fSizeBlockX, float fSizeBlockZ)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	m_radius = nNumBlockX * fSizeBlockX * 0.5f;

	// 位置・向きの初期設定
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	// ブロック数
	m_nNumBlockX = nNumBlockX;
	m_nNumBlockZ = nNumBlockZ;

	// 頂点数
	m_nNumVertex =
		(nNumBlockX + 1) * (nNumBlockZ + 1);

	// インデックス数 (縮退ポリゴンも考慮)
	m_nNumIndex =
		(nNumBlockX + 1) * nNumBlockZ * 2 +
		(nNumBlockZ - 1) * 2;

	// ポリゴン数 (縮退ポリゴンも考慮)
	m_nNumPolygon =
		nNumBlockX * nNumBlockZ * 2 +
		(nNumBlockZ - 1) * 4;

	// ブロックサイズ
	m_fSizeBlockX = fSizeBlockX;
	m_fSizeBlockZ = fSizeBlockZ;

	// オブジェクトの頂点バッファを生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * m_nNumVertex,	// 頂点データ用に確保するバッファサイズ(バイト単位)
		D3DUSAGE_WRITEONLY,			// 頂点バッファの使用法　
		FVF_VERTEX_3D,				// 使用する頂点フォーマット
		D3DPOOL_MANAGED,			// リソースのバッファを保持するメモリクラスを指定
		&m_pD3DVtxBuffField,		// 頂点バッファインターフェースへのポインタ
		NULL);			// NULLに設定

	// オブジェクトのインデックスバッファを生成
	pDevice->CreateIndexBuffer(
		sizeof(WORD) * m_nNumIndex,
		D3DUSAGE_WRITEONLY,
		D3DFMT_INDEX16,
		D3DPOOL_MANAGED,
		&m_pD3DIdxBuffField,
		NULL);


	{//頂点バッファの中身を埋める
		VERTEX_3D *pVtx;
		const float fSizeTexX = 1.0f;
		const float fSizeTexZ = 1.0f;

		// 頂点データの範囲をロックし、頂点バッファへのポインタを取得
		m_pD3DVtxBuffField->Lock(0, 0, (void**)&pVtx, 0);

		for (int nCntVtxZ = 0; nCntVtxZ < (m_nNumBlockZ + 1); nCntVtxZ++)
		{
			for (int nCntVtxX = 0; nCntVtxX < (m_nNumBlockX + 1); nCntVtxX++, pVtx++)
			{
				// 頂点座標の設定
				pVtx[0].vtx.x = -(m_nNumBlockX / 2.0f) * m_fSizeBlockX + nCntVtxX * m_fSizeBlockX;
				pVtx[0].vtx.y = 0.0f;
				pVtx[0].vtx.z = (m_nNumBlockZ / 2.0f) * m_fSizeBlockZ - nCntVtxZ * m_fSizeBlockZ;

				// 法線の設定
				pVtx[0].nor = D3DXVECTOR3(0.0f, 1.0, 0.0f);

				// 反射光の設定
				pVtx[0].diffuse = D3DXCOLOR(0.5f, 0.5f, 0.5f, 1.0f);
			}
		}

		// 頂点データをアンロックする
		m_pD3DVtxBuffField->Unlock();
	}
	{// インデックスバッファの中身を埋める
		WORD* pIdx;

		// インデックスデータの範囲をロックし、
		//インデックスバッファへのポインタを取得
		m_pD3DIdxBuffField->Lock(0, 0, (void**)&pIdx, 0);

		for (int nCntVtxZ = 0;
			nCntVtxZ < m_nNumBlockZ; nCntVtxZ++)
		{
			if (nCntVtxZ > 0)
			{// 縮退ポリゴン用の重複設定
				pIdx[0] = (nCntVtxZ + 1) *
					(m_nNumBlockX + 1);
				++pIdx;
			}
			for (int nCntVtxX = 0;
				nCntVtxX < (m_nNumBlockX + 1);
				nCntVtxX++)
			{
				pIdx[0] = (nCntVtxZ + 1) *
					(m_nNumBlockX + 1) +
					nCntVtxX;
				++pIdx;
				pIdx[0] = nCntVtxZ *
					(m_nNumBlockX + 1) +
					nCntVtxX;
				++pIdx;
			}
			if (nCntVtxZ < (m_nNumBlockZ - 1))
			{// 縮退ポリゴン用の重複設定
				pIdx[0] = nCntVtxZ *
					(m_nNumBlockX + 1) +
					m_nNumBlockX;
				++pIdx;
			}
		}

		// インデックスデータをアンロックする
		m_pD3DIdxBuffField->Unlock();
	}
}

CStage::~CStage()
{
	if (m_pD3DVtxBuffField)
	{// 頂点バッファの開放
		m_pD3DVtxBuffField->Release();
		m_pD3DVtxBuffField = NULL;
	}
	if (m_pD3DIdxBuffField)
	{// インデックスバッファの開放
		m_pD3DIdxBuffField->Release();
		m_pD3DIdxBuffField = NULL;
	}
}

void CStage::Draw() {
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXMATRIX mtxRot, mtxTranslate, mtxWorld;

	// ワールドマトリックスの初期化
	D3DXMatrixIdentity(&mtxWorld);

	// 移動を反映
	D3DXMatrixTranslation(&mtxTranslate, m_pos.x, m_pos.y, m_pos.z);
	D3DXMatrixMultiply(&mtxWorld, &mtxWorld, &mtxTranslate);

	// ワールドマトリックスの設定
	pDevice->SetTransform(D3DTS_WORLD, &mtxWorld);

	// 頂点バッファをレンダリングパイプラインに設定
	pDevice->SetStreamSource(0, m_pD3DVtxBuffField, 0, sizeof(VERTEX_3D));

	// テクスチャなし
	pDevice->SetTexture(0, NULL);

	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_3D);

	// インデックスバッファをレンダリングパイプラインに設定
	pDevice->SetIndices(m_pD3DIdxBuffField);

	// ポリゴンの描画
	pDevice->DrawIndexedPrimitive(
		D3DPT_TRIANGLESTRIP, 0, 0,
		m_nNumVertex, 0, m_nNumPolygon);
}

// 画面外で弾を消す
bool cbStageOutBullet(CObjBase *pTgt, void *pPara) {
	CObjBase* stage = (CObjBase*)pTgt;
	CObjBase* obj = (CObjBase*)pPara;
	if (obj->m_pos.x > stage->m_radius) {
		obj->m_releaseFlag = true;
		return true;
	}
	if (obj->m_pos.x < -stage->m_radius) {
		obj->m_releaseFlag = true;
		return true;
	}
	if (obj->m_pos.z > stage->m_radius) {
		obj->m_releaseFlag = true;
		return true;
	}
	if (obj->m_pos.z < -stage->m_radius) {
		obj->m_releaseFlag = true;
		return true;
	}
	return false;
}
// 画面外でキャラクターを戻す
bool cbStageOutCharacter(CObjBase *pTgt, void *pPara) {
	CObjBase* stage = (CObjBase*)pTgt;
	CObjBase* obj = (CObjBase*)pPara;
	bool r = false;;
	if (obj->m_pos.x > stage->m_radius) {
		obj->m_pos.x = stage->m_radius;
		r = true;
	}
	else if (obj->m_pos.x < -stage->m_radius) {
		obj->m_pos.x = -stage->m_radius;
		r = true;
	}
	if (obj->m_pos.z > stage->m_radius) {
		obj->m_pos.z = stage->m_radius;
		r = true;
	}
	else if (obj->m_pos.z < -stage->m_radius) {
		obj->m_pos.z = -stage->m_radius;
		r= true;
	}
	return r;
}