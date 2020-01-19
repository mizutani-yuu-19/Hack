//////////////////////////////////////////
//
// debug.cpp
// �f�o�b�O�Ɏg�������Ȃ���
//
/////////////////////////////////////////
//--------------�C���N���[�h----------------
#include "main.h"
#include "model.h"
//--------------�O���[�o���ϐ�----------------
static LPDIRECT3DDEVICE9	g_pDevice;
static ID3DXLine			*g_pLine;
static LPD3DXFONT			g_pD3DXFont = NULL;		// �t�H���g�ւ̃|�C���^
//static CModel				g_box;
//---------------�֐�---------------
// ������
HRESULT InitDebug() {
	HRESULT hr;
	// �f�o�C�X�擾
	g_pDevice = GetDevice();
	// ���C���I�u�W�F�N�g����
	hr = D3DXCreateLine(g_pDevice, &g_pLine);
	if (FAILED(hr)) {
		return hr;
	}
//	hr = LoadModel("data/MODEL/box.x", &g_box);
//	if (FAILED(hr)) {
//		return hr;
//	}
	return hr;
}

/*
���������܂�
�����F���C���̒��_
*/
void DrawDebugLine(D3DXVECTOR2 vertex1, D3DXVECTOR2 vertex2) {
	// ���_�쐬
	D3DXVECTOR2 *vec;
	vec = new D3DXVECTOR2[2];
	vec[0] = vertex1;
	vec[1] = vertex2;

	// ���`��
	g_pLine->Begin();
	g_pLine->Draw(vec, 2, D3DCOLOR_RGBA(255, 0, 0, 255));
	g_pLine->End();

	// ���
	if (vec != NULL) {
		delete[] vec;
		vec = NULL;
	}
}

/*
�{�b�N�X�����܂�
�����F�ʒu,�傫��
*/
void DrawDebugBox(D3DXVECTOR3 pos, D3DXVECTOR3 size) {
	// ���_�쐬
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXMATRIX mtxRot, mtxTranslate, mtxSize,mtxWorld;
	//���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&mtxWorld);

	//�傫���𔽉f
	D3DXMatrixScaling(&mtxSize, size.x,size.y,size.z);
	D3DXMatrixMultiply(&mtxWorld, &mtxWorld, &mtxSize);

	//�ړ��𔽉f
	D3DXMatrixTranslation(&mtxTranslate, pos.x, pos.y, pos.z);
	D3DXMatrixMultiply(&mtxWorld, &mtxWorld, &mtxTranslate);

	//���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &mtxWorld);
	pDevice->BeginScene();
	//�`��
	//DrawModel(&g_box);	

}