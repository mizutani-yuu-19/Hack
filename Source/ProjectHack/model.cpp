//=============================================================================
//
// ���f������ [model.cpp]
// Author : HIROHIKO HAMAYA
//
//=============================================================================
#define _CRT_SECURE_NO_WARNINGS
#include "model.h"
#include <stdlib.h>

//*****************************************************************************
// �}�N����`
//*****************************************************************************

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************

//=============================================================================
// X�t�@�C���ǂݍ���
//=============================================================================
CModel::CModel(LPCTSTR pszFName)
{
	TCHAR				szDir[_MAX_DIR] = "data/MODEL";
	TCHAR				szCurrentDir[_MAX_PATH];
	LPDIRECT3DDEVICE9	pDevice = GetDevice();
	LPD3DXBUFFER		pBuffMaterial = NULL;

	// �t�H���_���𒊏o
	//_tsplitpath(pszFName, NULL, szDir, NULL, NULL);

	// X�t�@�C���ǂݍ���
	D3DXLoadMeshFromX(pszFName,
		D3DXMESH_SYSTEMMEM, pDevice, NULL, &pBuffMaterial,
		NULL, &dwNumMat, &pMesh);

	// �����e�[�u���擾
	pMesh->OptimizeInplace(D3DXMESHOPT_COMPACT | D3DXMESHOPT_ATTRSORT, 0, 0, 0, 0);
	dwAttr = 0;
	pMesh->GetAttributeTable(NULL, &dwAttr);
	pAttr = new D3DXATTRIBUTERANGE[dwAttr];
	pMesh->GetAttributeTable(pAttr, &dwAttr);

	// �J�����g�f�B���N�g����ύX
	if (szDir[0]) {
		GetCurrentDirectory(_MAX_PATH, szCurrentDir);
		SetCurrentDirectory(szDir);
	}

	// �}�e���A���ǂݍ���
	D3DXMATERIAL* material = (D3DXMATERIAL*)pBuffMaterial->GetBufferPointer();
	pMaterial = new D3DMATERIAL9[dwNumMat];
	for (DWORD i = 0; i < dwNumMat; ++i) {
		pMaterial[i] = material[i].MatD3D;
		pMaterial[i].Ambient = pMaterial[i].Diffuse;
	}
	SAFE_RELEASE(pBuffMaterial);

	// �J�����g�f�B���N�g�������ɖ߂�
	if (szDir[0])
		SetCurrentDirectory(szCurrentDir);
}

//=============================================================================
// X�t�@�C���\��
//=============================================================================
void CModel::DrawModel()
{
	LPDIRECT3DDEVICE9	pDevice = GetDevice();

	D3DMATERIAL9 matDef;

	// ���݂̃}�e���A�����擾
	pDevice->GetMaterial(&matDef);

	for (DWORD i = 0; i < dwAttr; ++i) {
		DWORD id = pAttr[i].AttribId;
		pDevice->SetMaterial(&pMaterial[id]);	// �}�e���A����ݒ�
		pMesh->DrawSubset(i);					// �`������s
	}

	// �}�e���A�����f�t�H���g�ɖ߂�
	pDevice->SetMaterial(&matDef);
}

//=============================================================================
// X�t�@�C���s���������\��
//=============================================================================
void CModel::DrawModelNoAlpha()
{
	LPDIRECT3DDEVICE9	pDevice = GetDevice();

	for (DWORD i = 0; i < dwAttr; ++i) {
		DWORD id = pAttr[i].AttribId;
		if (pMaterial[id].Diffuse.a < 1.0f) continue;
		pDevice->SetMaterial(&pMaterial[id]);	// �}�e���A����ݒ�
		pMesh->DrawSubset(i);					// �`������s
	}
}

//=============================================================================
// X�t�@�C���������\��
//=============================================================================
void CModel::DrawModelAlpha(float fAlpha)
{
	LPDIRECT3DDEVICE9	pDevice = GetDevice();
	D3DMATERIAL9 material;

	for (DWORD i = 0; i < dwAttr; ++i) {
		DWORD id = pAttr[i].AttribId;
		material = pMaterial[id];
		material.Diffuse.a *= fAlpha;
		if (material.Diffuse.a >= 1.0f) continue;
		pDevice->SetMaterial(&material);	// �}�e���A����ݒ�
		pMesh->DrawSubset(i);					// �`������s
	}
}

//=============================================================================
// X�t�@�C�����
//=============================================================================
CModel::~CModel()
{
	dwNumMat = 0;
	SAFE_DELETE_ARRAY(pMaterial);
	SAFE_RELEASE(pMesh);
}
