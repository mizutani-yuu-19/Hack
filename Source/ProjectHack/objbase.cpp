////////////////////////////////////////////////////////////////////////////////////
//
// objbase.cpp
//
////////////////////////////////////////////////////////////////////////////////////
//============�C���N���[�h=============
#include "objbase.h"
#include "camera.h"
#include "fade.h"	
//============�G�N�X�^�[��============
CObjSys ObjSys;

//============CObjBase===========
//-----------�R���X�g���N�^-------------
CObjBase::CObjBase() {
	m_pos = point3(0.0f, 0.0f, 0.0f);
	m_move = vector3(0.0f, 0.0f, 0.0f);
	m_accel = vector3(0.0f, 0.0f, 0.0f);
	m_rot = vector3(0.0f, 0.0f, 0.0f);
	m_radius = 0.5f;

	m_life = -1;
}
CObjBase::~CObjBase() {

}

//============CObjSys============
void CObjSys::Init()
{
	// ��x�S�������č�蒼��
	for (int stage = 0; stage < m_ObjListArray.size(); stage++) {
		CObjList *pList = m_ObjListArray[stage];
		CObjList::iterator _end = pList->end();
		for (CObjList::iterator i = pList->begin(); i != _end; i++)
		{
			delete *i;
		}
		pList->clear();
	}
	m_ObjListArray.clear();
	m_pBackGround = new CBackGround;

	for (int i = 0; i < OBJ_MAX; i++)
	{
		CObjList* pObjList = new CObjList();
		m_ObjListArray.push_back(pObjList);
	}
}

CObjSys::~CObjSys()			//�f�X�g���N�^
{
	for (unsigned int i = 0; i < m_ObjListArray.size(); i++)
	{
		delete m_ObjListArray[i];
	}
}

void CObjSys::Add(CObjBase *pObj, int stage)
{
	CObjList *pList = m_ObjListArray[stage];
	pList->push_back(pObj);
}

bool CObjSys::LoopStage(unsigned int StageMask, LoopStageFunc Func, void *pPara = NULL)
{
	unsigned int _Mask = StageMask;
	for (unsigned int Stage = 0; Stage < m_ObjListArray.size(); Stage++)
	{
		if (_Mask & 1)
		{
			CObjList *pList = m_ObjListArray[Stage];
			CObjList::iterator _end = pList->end();
			for (CObjList::iterator i = pList->begin(); i != _end; i++)
			{
				CObjBase *pObj = *i;
				if (Func(pObj, pPara))
				{
					return true;
				}
			}
		}
		_Mask = _Mask >> 1;
	}
	return false;
}

void CObjSys::AllUpdate() {
	for (unsigned int Stage = 0; Stage < m_ObjListArray.size(); Stage++)
	{//�Sobject�̎���
		CObjList *pList = m_ObjListArray[Stage];
		CObjList::iterator _end = pList->end();
		for (CObjList::iterator i = pList->begin(); i != _end; /* i++ */) {
			CObjBase *pObj = *i;
			pObj->Update();
			if (pObj->m_life == 0)	pObj->m_releaseFlag = true;
			if (pObj->m_releaseFlag)
			{
				i = pList->erase(i);
				//delete pObj;
				delete pObj;
				continue;
			}
			i++;  // �����Ŏ��̃C�e���[�g��
		}
	}
}

bool cbDrawAll(CObjBase *pTgt, void *pPara) {
	pTgt->Draw();
	return false;
}
bool cbDrawAlphaAll(CObjBase *pTgt, void *pPara) {
	pTgt->DrawAlpha();
	return false;
}
bool cbDraw2DAll(CObjBase *pTgt, void *pPara) {
	pTgt->Draw2D();
	return false;
}
bool cbSetCamera(CObjBase *pTgt, void *pPara) {
	CCamera* camera = (CCamera*)pTgt;
	if (!camera->m_drawedFlag) {
		camera->SetCamera();
		return true;
	}
	return false;
}
void CObjSys::AllDraw() {
	while (LoopStage(OBJLIST_CAMERA, cbSetCamera)) {
		m_pBackGround->DrawBG();
		// �A���t�@�u�����f�B���O������
		GetDevice()->SetRenderState(D3DRS_ALPHABLENDENABLE,FALSE);
		// �A���t�@�u�����f�B���O�̐ݒ�
		SetRenderMode(BLEND_NOBLEND);
		// ���ʕ`��
		LoopStage(OBJLIST_ALL, cbDrawAll);
		// �������`��
		// �A���t�@�u�����f�B���O��ݒ�
		GetDevice()->SetRenderState(D3DRS_ALPHABLENDENABLE,TRUE);
		LoopStage(OBJLIST_ALL, cbDrawAlphaAll);
		LoopStage(OBJLIST_ALL, cbDraw2DAll);
		DrawFade();
	}
}

bool cbUninitAll(CObjBase *pTgt, void *pPara) {
	pTgt->Uninit();
	return false;
}

void CObjSys::AllUninit() {
	LoopStage(OBJLIST_ALL, cbUninitAll);
}
// ���̃��X�g�ɃI�u�W�F�N�g�����݂��Ă��邩
bool cbChkListSize(CObjBase* pTgt, void* pPara) {
	return true;
}
bool ChkExistStage(unsigned int stage) {
	return ObjSys.LoopStage(stage, cbChkListSize, NULL);
}

// �w�i
CBackGround::CBackGround()
{
	m_tex = SetTexture("data/TEXTURE/background.png");
	m_sprite.InitSprite(point2(SCREEN_CENTER_X, SCREEN_CENTER_Y), SCREEN_WIDTH, SCREEN_HEIGHT, 1, 1);
}

CBackGround::~CBackGround()
{
	SAFE_RELEASE(m_tex);
}

void CBackGround::DrawBG() {
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	// BG�`��p�����_�����O�X�e�[�g�ݒ�
	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);
	pDevice->SetRenderState(D3DRS_ZENABLE, FALSE);
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);
	m_sprite.DrawSprite(m_tex);
	// BG�`��p�����_�����O�X�e�[�g�ݒ����
	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
	pDevice->SetRenderState(D3DRS_ZENABLE, TRUE);
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);
}