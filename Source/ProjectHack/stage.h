////////////////////////////////////////////////////////////////////////////////////
//
// stage.h
//
////////////////////////////////////////////////////////////////////////////////////
#pragma once
//=============�C���N���[�h===============
#include "objbase.h"

//============�X�e�[�W�N���X==================
class CStage:public CObjBase
{
public:
	CStage(int nNumBlockX, int nNumBlockZ, float fSizeBlockX, float fSizeBlockZ);
	~CStage();

	void Draw();
private:
	int m_nNumBlockX;
	int m_nNumBlockZ;
	int	m_nNumVertex;
	int m_nNumIndex;
	int m_nNumPolygon;
	int m_fSizeBlockX;
	int m_fSizeBlockZ;

	LPDIRECT3DVERTEXBUFFER9 m_pD3DVtxBuffField;	// ���_�o�b�t�@�ւ̃|�C���^
	LPDIRECT3DINDEXBUFFER9 m_pD3DIdxBuffField;	// �C���f�b�N�X�o�b�t�@�ւ̃|�C���^
};

// ��ʊO
bool cbStageOutBullet(CObjBase *pTgt, void *pPara);
bool cbStageOutCharacter(CObjBase *pTgt, void *pPara);

