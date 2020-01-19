//=============================================================================
//
// �J�������� [camera.cpp]
//
//=============================================================================
#include "camera.h"
#include "input.h"
#include "fade.h"
#include "player.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define LOOKAT_PT			(100.0f)				// �����_�̃L�����N�^�[����̋���	
#define PLAYER_DEST			(5.0f)					// �J�����ƃv���C���[�̋���	

#define STAGEDRAW_POS_X		(690.0f)				// �X�e�[�W�J�����`��ʒu
#define STAGEDRAW_POS_Y		(10.0f)				// �X�e�[�W�J�����`��ʒu
#define STAGEDRAW_SIZE		(100.0f)				// �X�e�[�W�J�����T�C�Y
#define	STAGECAMERA_POS_Y	(40.0f)				// �X�e�[�W�J�����̈ʒu
//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
//===========================================================================
//	�J���������o�֐�
//===========================================================================
// �R���X�g���N�^
CCamera::CCamera() :CObjBase()
{
	m_pos = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	m_drawedFlag = false;
}
//=============================================================================
// �J�����̐ݒ菈��
//=============================================================================
void CCamera::SetCamera(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// �r���[�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&m_mtxView);

	// �r���[�}�g���b�N�X�̍쐬
	D3DXMatrixLookAtLH(&m_mtxView,
		&m_pos,		// �J�����̎��_
		&m_lookatPt,		// �J�����̒����_
		&m_posCameraU);		// �J�����̏����

	pDevice->SetViewport(&m_port);

	// �o�b�N�o�b�t�@���y�o�b�t�@�̃N���A
	pDevice->Clear(0, NULL, (D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER), D3DCOLOR_RGBA(0, 0, 0, 0), 1.0f, 0);

	// �r���[�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_VIEW, &m_mtxView);

	m_drawedFlag = true;
}

CPlayerCamera::CPlayerCamera():CCamera() {
	m_posCameraU = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	// �X�N���[����̔z�u
	m_port.X = 0;
	m_port.Y = 0;
	m_port.Width = SCREEN_WIDTH;
	m_port.Height = SCREEN_HEIGHT;
	m_aspect = (float)SCREEN_WIDTH / (float)SCREEN_HEIGHT;

	m_port.MaxZ = 1;
	m_port.MinZ = 0;

	// �v���W�F�N�V�����}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&m_mtxProjection);

	// �v���W�F�N�V�����}�g���b�N�X�̍쐬
	D3DXMatrixPerspectiveFovLH(&m_mtxProjection,
		VIEW_ANGLE,										// ����p
		m_aspect,	// �A�X�y�N�g��
		VIEW_NEAR_Z,									// �r���[���ʂ�NearZ�l
		VIEW_FAR_Z);									// �r���[���ʂ�FarZ�l

	// �v���W�F�N�V�����}�g���b�N�X�̐ݒ�
	GetDevice()->SetTransform(D3DTS_PROJECTION, &m_mtxProjection);
}

// �v���C���[�J�����̍X�V����

bool cbGetPlayerRot(CObjBase *pTgt, void *pPara) {
	vector3* rot = (vector3*)pPara;
	*rot = pTgt->m_rot;
	return false;
}
void CPlayerCamera::Update(void) {
	CCamera::Update();
	// ���f���̈ʒu�擾
	if (ObjSys.LoopStage(OBJLIST_PLAYER, cbGetPlayerPos, m_playerPos)) {
		ObjSys.LoopStage(OBJLIST_PLAYER, cbGetPlayerRot, m_rot);
	}
	// �����_�̈ʒu
	m_lookatPt.x = m_playerPos.x;// +-LOOKAT_PT * sin(m_rot.y);
	m_lookatPt.y = m_playerPos.y;
	m_lookatPt.z = m_playerPos.z;// +-LOOKAT_PT * cos(m_rot.y);

	// ���_�̈ʒu
	m_pos.x = m_lookatPt.x;// + -PLAYER_DEST * sin(m_rot.y);
	m_pos.y = m_lookatPt.y + 30.0f;
	m_pos.z = m_lookatPt.z- 10.0f;// + -PLAYER_DEST * cos(m_rot.y);
}
//*****************************************************************************
//
// �X�e�[�W�J�����N���X
//
//*****************************************************************************
//===========================================================================
//	�J���������o�֐�
//===========================================================================
// �R���X�g���N�^
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

	// �v���W�F�N�V�����}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&m_mtxProjection);

	// �v���W�F�N�V�����}�g���b�N�X�̍쐬
	D3DXMatrixPerspectiveFovLH(&m_mtxProjection,
		VIEW_ANGLE,										// ����p
		m_aspect,	// �A�X�y�N�g��
		VIEW_NEAR_Z,									// �r���[���ʂ�NearZ�l
		VIEW_FAR_Z);									// �r���[���ʂ�FarZ�l

														// �v���W�F�N�V�����}�g���b�N�X�̐ݒ�
	GetDevice()->SetTransform(D3DTS_PROJECTION, &m_mtxProjection);

	// �����_�̈ʒu
	m_lookatPt.x = 0.0f;
	m_lookatPt.y = 0.0f;
	m_lookatPt.z = 0.0f;

	// ���_�̈ʒu
	m_pos.x = 0.0f;
	m_pos.y = STAGECAMERA_POS_Y;
	m_pos.z = 0.0f;
}
//=============================================================================
// �X�e�[�W�J�����̍X�V����
//=============================================================================
void CStageCamera::Update(void)
{
	CCamera::Update();
}
//*****************************************************************************
//
// �^�C�g���J�����N���X
//
//*****************************************************************************
//===========================================================================
//	�J���������o�֐�
//===========================================================================
// �R���X�g���N�^
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

	// �v���W�F�N�V�����}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&m_mtxProjection);

	// �v���W�F�N�V�����}�g���b�N�X�̍쐬
	D3DXMatrixPerspectiveFovLH(&m_mtxProjection,
		VIEW_ANGLE,										// ����p
		m_aspect,	// �A�X�y�N�g��
		VIEW_NEAR_Z,									// �r���[���ʂ�NearZ�l
		VIEW_FAR_Z);									// �r���[���ʂ�FarZ�l

														// �v���W�F�N�V�����}�g���b�N�X�̐ݒ�
	GetDevice()->SetTransform(D3DTS_PROJECTION, &m_mtxProjection);

	// �����_�̈ʒu
	m_lookatPt.x = 0.0f;
	m_lookatPt.y = 0.0f;
	m_lookatPt.z = 0.0f;

	// ���_�̈ʒu
	m_pos.x = 0.0f;
	m_pos.y = STAGECAMERA_POS_Y;
	m_pos.z = 0.0f;
}
//=============================================================================
// �X�e�[�W�J�����̍X�V����
//=============================================================================
void CTitleCamera::Update(void)
{
	CCamera::Update();
}
bool cbGetViewMatrix(CObjBase *pTgt, void *pPara) {
	CCamera* camera = (CCamera*)pTgt;
	// �`��ς݂Ȃ�`�撆�̉\��������
	if (camera->m_drawedFlag) {
		D3DMATRIX* mtx = (D3DMATRIX*)pPara;
		*mtx = camera->m_mtxView;
		return false;
	}
	return true;
}

bool cbGetCamPos(CObjBase *pTgt, void *pPara) {
	CCamera* camera = (CCamera*)pTgt;
	// �`��ς݂Ȃ�`�撆�̉\��������
	if (camera->m_drawedFlag) {
		point3* pos = (point3*)pPara;
		*pos = camera->m_pos;
		return false;
	}
	return true;
}