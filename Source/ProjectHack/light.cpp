//=============================================================================
//
// ���C�g���� [light.cpp]
// Author : AKIRA TANAKA
//
//=============================================================================
#include "light.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define	NUM_LIGHT		(1)		// ���C�g�̐�

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
D3DLIGHT9 g_aLight[NUM_LIGHT];		// ���C�g���

//=============================================================================
// ���C�g�̏���������
//=============================================================================
HRESULT InitLight(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXVECTOR3 vecDir;

	// D3DLIGHT9�\���̂�0�ŃN���A����
	ZeroMemory(&g_aLight[0], sizeof(D3DLIGHT9));

	// ���C�g�̃^�C�v�̐ݒ�
	g_aLight[0].Type = D3DLIGHT_DIRECTIONAL;

	// �g�U��
	g_aLight[0].Diffuse = D3DXCOLOR(1.0f, 1.0f, 0.7f, 1.0f);

	// ����
	g_aLight[0].Ambient = D3DXCOLOR(1.0f, 1.0f, 0.7f, 1.0f);

	// ���C�g�̕����̐ݒ�
	vecDir = D3DXVECTOR3(-0.0f, -1.0f, 0.0f);
	D3DXVec3Normalize((D3DXVECTOR3*)&g_aLight[0].Direction, &vecDir);

	// ���C�g�������_�����O�p�C�v���C���ɐݒ�
	pDevice->SetLight(0, &g_aLight[0]);

	// ���C�g�̐ݒ�
	pDevice->LightEnable(0, TRUE);

	//// D3DLIGHT9�\���̂�0�ŃN���A����
	//ZeroMemory(&g_aLight[1], sizeof(D3DLIGHT9));

	//// ���C�g�̃^�C�v�̐ݒ�
	//g_aLight[1].Type = D3DLIGHT_DIRECTIONAL;

	//// �g�U��
	//g_aLight[1].Diffuse = D3DXCOLOR(0.5f, 0.5f, 0.5f, 1.0f);

	//// ����
	//g_aLight[1].Ambient = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
 //   // ���C�g�̕����̐ݒ�
	//vecDir = D3DXVECTOR3(-0.0f, -1.0f, -0.8f);
	//D3DXVec3Normalize((D3DXVECTOR3*)&g_aLight[1].Direction, &vecDir);

	//// ���C�g�������_�����O�p�C�v���C���ɐݒ�
	//pDevice->SetLight(1, &g_aLight[1]);

	//// ���C�g�̐ݒ�
	//pDevice->LightEnable(1, TRUE);



	//// D3DLIGHT9�\���̂�0�ŃN���A����
	//ZeroMemory(&g_aLight[2], sizeof(D3DLIGHT9));

	//// ���C�g�̃^�C�v�̐ݒ�
	//g_aLight[2].Type = D3DLIGHT_DIRECTIONAL;

	//// �g�U��
	//g_aLight[2].Diffuse = D3DXCOLOR(0.2f, 0.2f, 0.2f, 1.0f);

	//// ����
	//g_aLight[2].Ambient = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	//// ���C�g�̕����̐ݒ�
	//vecDir = D3DXVECTOR3(-0.0f, 1.0f, 0.8f);
	//D3DXVec3Normalize((D3DXVECTOR3*)&g_aLight[2].Direction, &vecDir);

	//// ���C�g�������_�����O�p�C�v���C���ɐݒ�
	//pDevice->SetLight(2, &g_aLight[2]);

	//// ���C�g�̐ݒ�
	//pDevice->LightEnable(2, TRUE);

	// ���C�e�B���O���[�h
	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);

	return S_OK;
}

//=============================================================================
// ���C�g�̏I������
//=============================================================================
void UninitLight(void)
{
}

//=============================================================================
// ���C�g�̍X�V����
//=============================================================================
void UpdateLight(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// ���f���ʒu�̎擾
	//D3DXVECTOR3 posModel = CCharacter::GetPlayerPos(0);

    // ���C�g�̈ʒu�̐ݒ�
	//g_aLight[2].Position.x = posModel.x;
	//g_aLight[2].Position.z = posModel.z;

	// ���C�g�������_�����O�p�C�v���C���ɐݒ�
	//pDevice->SetLight(2, &g_aLight[2]);
}
