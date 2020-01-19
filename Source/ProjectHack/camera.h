//=============================================================================
//
// カメラ処理 [camera.h]
//
//=============================================================================
#ifndef _CAMERA_H_
#define _CAMERA_H_

#include "main.h"
#include "objbase.h"

#define	VIEW_ANGLE			(D3DXToRadian(45.0f))	// 視野角
#define	VIEW_NEAR_Z			(10.0f)					// ビュー平面のNearZ値
#define	VIEW_FAR_Z			(2000.0f)				// ビュー平面のFarZ値
//*****************************************************************************
// クラス
//*****************************************************************************
class CCamera :public CObjBase
{
public:
	CCamera();
//	~CCamera();
	void Init(void) {};
	void Uninit(void) {};
	virtual void Update(void){ m_drawedFlag = false; };
	void Draw() {};
	void SetCamera(void);

	bool m_drawedFlag;		// 描画済みフラグ
	D3DXVECTOR3		m_lookatPt;					// カメラの注視点
	float			m_aspect;					// アスペクト比
	D3DXVECTOR3		m_posCameraU;				// カメラの上方向
	D3DXMATRIX		m_mtxView;					// ビューマトリックス
private:
protected:
	float			m_dest;						// 視点と注視点の距離
	D3DXMATRIX		m_mtxProjection;			// プロジェクションマトリックス
	D3DVIEWPORT9	m_port;						// ポート　分割描画に必要
};

class CPlayerCamera :public CCamera
{
public:
	CPlayerCamera();
//	~CPlayerCamera();

	void Update();
private:
	point3 m_playerPos;
};
class CStageCamera :public CCamera {
public:
	CStageCamera();
	//	~CStageCamera();

	void Update();
private:
};
class CTitleCamera :public CCamera {
public:
	CTitleCamera();
	//	~CStageCamera();

	void Update();
private:
};
bool cbGetViewMatrix(CObjBase *pTgt, void *pPara);
bool cbGetCamPos(CObjBase *pTgt, void *pPara);
#endif
