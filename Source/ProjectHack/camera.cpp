//=============================================================================
//
// カメラ処理 [camera.cpp]
//
//=============================================================================
#include "camera.h"
#include "input.h"
#include "fade.h"
#include "player.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define LOOKAT_PT			(100.0f)				// 注視点のキャラクターからの距離	
#define PLAYER_DEST			(5.0f)					// カメラとプレイヤーの距離	

#define STAGEDRAW_POS_X		(690.0f)				// ステージカメラ描画位置
#define STAGEDRAW_POS_Y		(10.0f)				// ステージカメラ描画位置
#define STAGEDRAW_SIZE		(100.0f)				// ステージカメラサイズ
#define	STAGECAMERA_POS_Y	(40.0f)				// ステージカメラの位置
//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
//===========================================================================
//	カメラメンバ関数
//===========================================================================
// コンストラクタ
CCamera::CCamera() :CObjBase()
{
	m_pos = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	m_drawedFlag = false;
}
//=============================================================================
// カメラの設定処理
//=============================================================================
void CCamera::SetCamera(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// ビューマトリックスの初期化
	D3DXMatrixIdentity(&m_mtxView);

	// ビューマトリックスの作成
	D3DXMatrixLookAtLH(&m_mtxView,
		&m_pos,		// カメラの視点
		&m_lookatPt,		// カメラの注視点
		&m_posCameraU);		// カメラの上方向

	pDevice->SetViewport(&m_port);

	// バックバッファ＆Ｚバッファのクリア
	pDevice->Clear(0, NULL, (D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER), D3DCOLOR_RGBA(0, 0, 0, 0), 1.0f, 0);

	// ビューマトリックスの設定
	pDevice->SetTransform(D3DTS_VIEW, &m_mtxView);

	m_drawedFlag = true;
}

CPlayerCamera::CPlayerCamera():CCamera() {
	m_posCameraU = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	// スクリーン上の配置
	m_port.X = 0;
	m_port.Y = 0;
	m_port.Width = SCREEN_WIDTH;
	m_port.Height = SCREEN_HEIGHT;
	m_aspect = (float)SCREEN_WIDTH / (float)SCREEN_HEIGHT;

	m_port.MaxZ = 1;
	m_port.MinZ = 0;

	// プロジェクションマトリックスの初期化
	D3DXMatrixIdentity(&m_mtxProjection);

	// プロジェクションマトリックスの作成
	D3DXMatrixPerspectiveFovLH(&m_mtxProjection,
		VIEW_ANGLE,										// 視野角
		m_aspect,	// アスペクト比
		VIEW_NEAR_Z,									// ビュー平面のNearZ値
		VIEW_FAR_Z);									// ビュー平面のFarZ値

	// プロジェクションマトリックスの設定
	GetDevice()->SetTransform(D3DTS_PROJECTION, &m_mtxProjection);
}

// プレイヤーカメラの更新処理

bool cbGetPlayerRot(CObjBase *pTgt, void *pPara) {
	vector3* rot = (vector3*)pPara;
	*rot = pTgt->m_rot;
	return false;
}
void CPlayerCamera::Update(void) {
	CCamera::Update();
	// モデルの位置取得
	if (ObjSys.LoopStage(OBJLIST_PLAYER, cbGetPlayerPos, m_playerPos)) {
		ObjSys.LoopStage(OBJLIST_PLAYER, cbGetPlayerRot, m_rot);
	}
	// 注視点の位置
	m_lookatPt.x = m_playerPos.x;// +-LOOKAT_PT * sin(m_rot.y);
	m_lookatPt.y = m_playerPos.y;
	m_lookatPt.z = m_playerPos.z;// +-LOOKAT_PT * cos(m_rot.y);

	// 視点の位置
	m_pos.x = m_lookatPt.x;// + -PLAYER_DEST * sin(m_rot.y);
	m_pos.y = m_lookatPt.y + 30.0f;
	m_pos.z = m_lookatPt.z- 10.0f;// + -PLAYER_DEST * cos(m_rot.y);
}
//*****************************************************************************
//
// ステージカメラクラス
//
//*****************************************************************************
//===========================================================================
//	カメラメンバ関数
//===========================================================================
// コンストラクタ
CStageCamera::CStageCamera() :CCamera()
{
	m_posCameraU = D3DXVECTOR3(0.0f, 0.0f, 1.0f);

	m_port.X = STAGEDRAW_POS_X;
	m_port.Y = STAGEDRAW_POS_Y;
	m_port.Width = STAGEDRAW_SIZE;
	m_port.Height = STAGEDRAW_SIZE;
	m_aspect = 1;
	m_port.MaxZ = 1;
	m_port.MinZ = 0;

	m_dest = 500.0f;

	// プロジェクションマトリックスの初期化
	D3DXMatrixIdentity(&m_mtxProjection);

	// プロジェクションマトリックスの作成
	D3DXMatrixPerspectiveFovLH(&m_mtxProjection,
		VIEW_ANGLE,										// 視野角
		m_aspect,	// アスペクト比
		VIEW_NEAR_Z,									// ビュー平面のNearZ値
		VIEW_FAR_Z);									// ビュー平面のFarZ値

														// プロジェクションマトリックスの設定
	GetDevice()->SetTransform(D3DTS_PROJECTION, &m_mtxProjection);

	// 注視点の位置
	m_lookatPt.x = 0.0f;
	m_lookatPt.y = 0.0f;
	m_lookatPt.z = 0.0f;

	// 視点の位置
	m_pos.x = 0.0f;
	m_pos.y = STAGECAMERA_POS_Y;
	m_pos.z = 0.0f;
}
//=============================================================================
// ステージカメラの更新処理
//=============================================================================
void CStageCamera::Update(void)
{
	CCamera::Update();
}
//*****************************************************************************
//
// タイトルカメラクラス
//
//*****************************************************************************
//===========================================================================
//	カメラメンバ関数
//===========================================================================
// コンストラクタ
CTitleCamera::CTitleCamera() :CCamera()
{
	m_posCameraU = D3DXVECTOR3(0.0f, 0.0f, 1.0f);

	m_port.X = 0;
	m_port.Y = 0 ;
	m_port.Width = SCREEN_WIDTH;
	m_port.Height = SCREEN_HEIGHT;
	m_aspect = 1;
	m_port.MaxZ = 1;
	m_port.MinZ = 0;

	m_dest = 500.0f;

	// プロジェクションマトリックスの初期化
	D3DXMatrixIdentity(&m_mtxProjection);

	// プロジェクションマトリックスの作成
	D3DXMatrixPerspectiveFovLH(&m_mtxProjection,
		VIEW_ANGLE,										// 視野角
		m_aspect,	// アスペクト比
		VIEW_NEAR_Z,									// ビュー平面のNearZ値
		VIEW_FAR_Z);									// ビュー平面のFarZ値

														// プロジェクションマトリックスの設定
	GetDevice()->SetTransform(D3DTS_PROJECTION, &m_mtxProjection);

	// 注視点の位置
	m_lookatPt.x = 0.0f;
	m_lookatPt.y = 0.0f;
	m_lookatPt.z = 0.0f;

	// 視点の位置
	m_pos.x = 0.0f;
	m_pos.y = STAGECAMERA_POS_Y;
	m_pos.z = 0.0f;
}
//=============================================================================
// ステージカメラの更新処理
//=============================================================================
void CTitleCamera::Update(void)
{
	CCamera::Update();
}
bool cbGetViewMatrix(CObjBase *pTgt, void *pPara) {
	CCamera* camera = (CCamera*)pTgt;
	// 描画済みなら描画中の可能性もある
	if (camera->m_drawedFlag) {
		D3DMATRIX* mtx = (D3DMATRIX*)pPara;
		*mtx = camera->m_mtxView;
		return false;
	}
	return true;
}

bool cbGetCamPos(CObjBase *pTgt, void *pPara) {
	CCamera* camera = (CCamera*)pTgt;
	// 描画済みなら描画中の可能性もある
	if (camera->m_drawedFlag) {
		point3* pos = (point3*)pPara;
		*pos = camera->m_pos;
		return false;
	}
	return true;
}