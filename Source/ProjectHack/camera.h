//=============================================================================
//
// �J�������� [camera.h]
//
//=============================================================================
#ifndef _CAMERA_H_
#define _CAMERA_H_

#include "main.h"
#include "objbase.h"

#define	VIEW_ANGLE			(D3DXToRadian(45.0f))	// ����p
#define	VIEW_NEAR_Z			(10.0f)					// �r���[���ʂ�NearZ�l
#define	VIEW_FAR_Z			(2000.0f)				// �r���[���ʂ�FarZ�l
//*****************************************************************************
// �N���X
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

	bool m_drawedFlag;		// �`��ς݃t���O
	D3DXVECTOR3		m_lookatPt;					// �J�����̒����_
	float			m_aspect;					// �A�X�y�N�g��
	D3DXVECTOR3		m_posCameraU;				// �J�����̏����
	D3DXMATRIX		m_mtxView;					// �r���[�}�g���b�N�X
private:
protected:
	float			m_dest;						// ���_�ƒ����_�̋���
	D3DXMATRIX		m_mtxProjection;			// �v���W�F�N�V�����}�g���b�N�X
	D3DVIEWPORT9	m_port;						// �|�[�g�@�����`��ɕK�v
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
