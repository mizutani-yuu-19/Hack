//=============================================================================
//
// ���f������ [model.h]
// Author : HIROHIKO HAMAYA
//
//=============================================================================
#ifndef ___MODEL_H_
#define ___MODEL_H_

#include "main.h"

//*****************************************************************************
// �\���̒�`
//*****************************************************************************
class CModel{
private:
	LPD3DXMESH			pMesh;		// ���b�V��
	D3DMATERIAL9*		pMaterial;	// �}�e���A���z��
	DWORD				dwNumMat;	// �}�e���A����
	DWORD				dwAttr;		// ������(�T�u�Z�b�g��)
	D3DXATTRIBUTERANGE*	pAttr;		// �����z��
public:	
	CModel(LPCTSTR pszFName);
	~CModel();
	void DrawModel();
	void DrawModelNoAlpha();
	void DrawModelAlpha(float fAlpha);
};

#endif
