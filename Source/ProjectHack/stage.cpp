////////////////////////////////////////////////////////////////////////////////////
//
// stage.h
//
////////////////////////////////////////////////////////////////////////////////////
//=============�C���N���[�h===============
#include "stage.h"

//============�X�e�[�W�N���X==================
CStage::CStage(int nNumBlockX, int nNumBlockZ, float fSizeBlockX, float fSizeBlockZ)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	m_radius = nNumBlockX * fSizeBlockX * 0.5f;

	// �ʒu�E�����̏����ݒ�
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	// �u���b�N��
	m_nNumBlockX = nNumBlockX;
	m_nNumBlockZ = nNumBlockZ;

	// ���_��
	m_nNumVertex =
		(nNumBlockX + 1) * (nNumBlockZ + 1);

	// �C���f�b�N�X�� (�k�ރ|���S�����l��)
	m_nNumIndex =
		(nNumBlockX + 1) * nNumBlockZ * 2 +
		(nNumBlockZ - 1) * 2;

	// �|���S���� (�k�ރ|���S�����l��)
	m_nNumPolygon =
		nNumBlockX * nNumBlockZ * 2 +
		(nNumBlockZ - 1) * 4;

	// �u���b�N�T�C�Y
	m_fSizeBlockX = fSizeBlockX;
	m_fSizeBlockZ = fSizeBlockZ;

	// �I�u�W�F�N�g�̒��_�o�b�t�@�𐶐�
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * m_nNumVertex,	// ���_�f�[�^�p�Ɋm�ۂ���o�b�t�@�T�C�Y(�o�C�g�P��)
		D3DUSAGE_WRITEONLY,			// ���_�o�b�t�@�̎g�p�@�@
		FVF_VERTEX_3D,				// �g�p���钸�_�t�H�[�}�b�g
		D3DPOOL_MANAGED,			// ���\�[�X�̃o�b�t�@��ێ����郁�����N���X���w��
		&m_pD3DVtxBuffField,		// ���_�o�b�t�@�C���^�[�t�F�[�X�ւ̃|�C���^
		NULL);			// NULL�ɐݒ�

	// �I�u�W�F�N�g�̃C���f�b�N�X�o�b�t�@�𐶐�
	pDevice->CreateIndexBuffer(
		sizeof(WORD) * m_nNumIndex,
		D3DUSAGE_WRITEONLY,
		D3DFMT_INDEX16,
		D3DPOOL_MANAGED,
		&m_pD3DIdxBuffField,
		NULL);


	{//���_�o�b�t�@�̒��g�𖄂߂�
		VERTEX_3D *pVtx;
		const float fSizeTexX = 1.0f;
		const float fSizeTexZ = 1.0f;

		// ���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
		m_pD3DVtxBuffField->Lock(0, 0, (void**)&pVtx, 0);

		for (int nCntVtxZ = 0; nCntVtxZ < (m_nNumBlockZ + 1); nCntVtxZ++)
		{
			for (int nCntVtxX = 0; nCntVtxX < (m_nNumBlockX + 1); nCntVtxX++, pVtx++)
			{
				// ���_���W�̐ݒ�
				pVtx[0].vtx.x = -(m_nNumBlockX / 2.0f) * m_fSizeBlockX + nCntVtxX * m_fSizeBlockX;
				pVtx[0].vtx.y = 0.0f;
				pVtx[0].vtx.z = (m_nNumBlockZ / 2.0f) * m_fSizeBlockZ - nCntVtxZ * m_fSizeBlockZ;

				// �@���̐ݒ�
				pVtx[0].nor = D3DXVECTOR3(0.0f, 1.0, 0.0f);

				// ���ˌ��̐ݒ�
				pVtx[0].diffuse = D3DXCOLOR(0.5f, 0.5f, 0.5f, 1.0f);
			}
		}

		// ���_�f�[�^���A�����b�N����
		m_pD3DVtxBuffField->Unlock();
	}
	{// �C���f�b�N�X�o�b�t�@�̒��g�𖄂߂�
		WORD* pIdx;

		// �C���f�b�N�X�f�[�^�͈̔͂����b�N���A
		//�C���f�b�N�X�o�b�t�@�ւ̃|�C���^���擾
		m_pD3DIdxBuffField->Lock(0, 0, (void**)&pIdx, 0);

		for (int nCntVtxZ = 0;
			nCntVtxZ < m_nNumBlockZ; nCntVtxZ++)
		{
			if (nCntVtxZ > 0)
			{// �k�ރ|���S���p�̏d���ݒ�
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
			{// �k�ރ|���S���p�̏d���ݒ�
				pIdx[0] = nCntVtxZ *
					(m_nNumBlockX + 1) +
					m_nNumBlockX;
				++pIdx;
			}
		}

		// �C���f�b�N�X�f�[�^���A�����b�N����
		m_pD3DIdxBuffField->Unlock();
	}
}

CStage::~CStage()
{
	if (m_pD3DVtxBuffField)
	{// ���_�o�b�t�@�̊J��
		m_pD3DVtxBuffField->Release();
		m_pD3DVtxBuffField = NULL;
	}
	if (m_pD3DIdxBuffField)
	{// �C���f�b�N�X�o�b�t�@�̊J��
		m_pD3DIdxBuffField->Release();
		m_pD3DIdxBuffField = NULL;
	}
}

void CStage::Draw() {
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXMATRIX mtxRot, mtxTranslate, mtxWorld;

	// ���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&mtxWorld);

	// �ړ��𔽉f
	D3DXMatrixTranslation(&mtxTranslate, m_pos.x, m_pos.y, m_pos.z);
	D3DXMatrixMultiply(&mtxWorld, &mtxWorld, &mtxTranslate);

	// ���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &mtxWorld);

	// ���_�o�b�t�@�������_�����O�p�C�v���C���ɐݒ�
	pDevice->SetStreamSource(0, m_pD3DVtxBuffField, 0, sizeof(VERTEX_3D));

	// �e�N�X�`���Ȃ�
	pDevice->SetTexture(0, NULL);

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_3D);

	// �C���f�b�N�X�o�b�t�@�������_�����O�p�C�v���C���ɐݒ�
	pDevice->SetIndices(m_pD3DIdxBuffField);

	// �|���S���̕`��
	pDevice->DrawIndexedPrimitive(
		D3DPT_TRIANGLESTRIP, 0, 0,
		m_nNumVertex, 0, m_nNumPolygon);
}

// ��ʊO�Œe������
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
// ��ʊO�ŃL�����N�^�[��߂�
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