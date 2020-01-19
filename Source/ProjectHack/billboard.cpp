//=============================================================================
// �r���{�[�h�쐬
//=============================================================================
#include "main.h"
#include "billboard.h"
void CreateBillboard(LPDIRECT3DTEXTURE9	*pD3DTexture, LPDIRECT3DVERTEXBUFFER9 *pD3DVtxBuffBillboard, float size, char* texPath)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	// �I�u�W�F�N�g�̒��_�o�b�t�@�𐶐�
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4,	// ���_�f�[�^�p�Ɋm�ۂ���o�b�t�@�T�C�Y(�o�C�g�P��)
		D3DUSAGE_WRITEONLY,			// ���_�o�b�t�@�̎g�p�@�@
		FVF_VERTEX_3D,				 // �g�p���钸�_�t�H�[�}�b�g
		D3DPOOL_MANAGED,			// ���\�[�X�̃o�b�t�@��ێ����郁�����N���X���w��
		pD3DVtxBuffBillboard,	// ���_�o�b�t�@�C���^�[�t�F�[�X�ւ̃|�C���^
		NULL);						// NULL�ɐݒ�

	{//���_�o�b�t�@�̒��g�𖄂߂�
		VERTEX_3D *pVtx;

		// ���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
		pD3DVtxBuffBillboard[0]->Lock(0, 0, (void**)&pVtx, 0);

		for (int nCntVtxY = 0; nCntVtxY < 1; nCntVtxY++)
		{
			for (int nCntVtxX = 0; nCntVtxX < 2; nCntVtxX++, pVtx += 2)
			{
				// ���_���W�̐ݒ�
				pVtx[0].vtx.x = -(0.5f) * size + nCntVtxX * size;
				pVtx[0].vtx.y = (0.5f) *  size - size;
				pVtx[0].vtx.z = 0.0f;
				pVtx[1].vtx.x = -(0.5f) * size + nCntVtxX * size;
				pVtx[1].vtx.y = (0.5f) *  size;
				pVtx[1].vtx.z = 0.0f;

				// �@���̐ݒ�
				pVtx[0].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
				pVtx[1].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);

				// ���ˌ��̐ݒ�
				pVtx[0].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
				pVtx[1].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

				// �e�N�X�`�����W�̐ݒ�
				pVtx[0].tex.x = nCntVtxX;
				pVtx[0].tex.y = (nCntVtxY + 1);
				pVtx[1].tex.x = nCntVtxX;
				pVtx[1].tex.y = nCntVtxY;
			}
		}

		// ���_�f�[�^���A�����b�N����
		pD3DVtxBuffBillboard[0]->Unlock();
	}

	D3DXCreateTextureFromFile(pDevice,						// �f�o�C�X�ւ̃|�C���^
		texPath,			// �t�@�C���̖��O
		pD3DTexture);	// �ǂݍ��ރ������[
}

//=============================================================================
// �e�쐬
//=============================================================================
void CreateShadow(LPDIRECT3DTEXTURE9	*pD3DTexture, LPDIRECT3DVERTEXBUFFER9 *pD3DVtxBuffBillboard, float size, char* texPath)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	// �I�u�W�F�N�g�̒��_�o�b�t�@�𐶐�
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4,	// ���_�f�[�^�p�Ɋm�ۂ���o�b�t�@�T�C�Y(�o�C�g�P��)
		D3DUSAGE_WRITEONLY,			// ���_�o�b�t�@�̎g�p�@�@
		FVF_VERTEX_3D,				 // �g�p���钸�_�t�H�[�}�b�g
		D3DPOOL_MANAGED,			// ���\�[�X�̃o�b�t�@��ێ����郁�����N���X���w��
		pD3DVtxBuffBillboard,	// ���_�o�b�t�@�C���^�[�t�F�[�X�ւ̃|�C���^
		NULL);						// NULL�ɐݒ�

	{//���_�o�b�t�@�̒��g�𖄂߂�
		VERTEX_3D *pVtx;

		// ���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
		pD3DVtxBuffBillboard[0]->Lock(0, 0, (void**)&pVtx, 0);

		for (int nCntVtxY = 0; nCntVtxY < 1; nCntVtxY++)
		{
			for (int nCntVtxX = 0; nCntVtxX < 2; nCntVtxX++, pVtx += 2)
			{
				// ���_���W�̐ݒ�
				pVtx[0].vtx.x = -(0.5f) * size + nCntVtxX * size;
				pVtx[0].vtx.z = (0.5f) *  size - size;
				pVtx[0].vtx.y = 0.0f;
				pVtx[1].vtx.x = -(0.5f) * size + nCntVtxX * size;
				pVtx[1].vtx.z = (0.5f) *  size;
				pVtx[1].vtx.y = 0.0f;

				// �@���̐ݒ�
				pVtx[0].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
				pVtx[1].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

				// ���ˌ��̐ݒ�
				pVtx[0].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
				pVtx[1].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

				// �e�N�X�`�����W�̐ݒ�
				pVtx[0].tex.x = nCntVtxX;
				pVtx[0].tex.y = (nCntVtxY + 1);
				pVtx[1].tex.x = nCntVtxX;
				pVtx[1].tex.y = nCntVtxY;
			}
		}

		// ���_�f�[�^���A�����b�N����
		pD3DVtxBuffBillboard[0]->Unlock();
	}

	D3DXCreateTextureFromFile(pDevice,						// �f�o�C�X�ւ̃|�C���^
		texPath,			// �t�@�C���̖��O
		pD3DTexture);	// �ǂݍ��ރ������[
}