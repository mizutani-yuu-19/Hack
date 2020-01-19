////////////////////////////////////////////////////////////////////////////////////
//
// player.cpp
//
////////////////////////////////////////////////////////////////////////////////////
//=================�C���N���[�h=====================
#include "player.h"
#include "input.h"
#include "camera.h"
#include "effect.h"
#include "billboard.h"
#include "sprite.h"
#include "stage.h"
#include "game.h"
#include "sound.h"
//================�萔==================
#define PLAYER_SPEED (0.03f)
#define PLAYER_ROT_SPEED (0.15f)
#define PLAYER_BULLET_SPEED (0.3f)
#define PLAYER_BULLET_SIZE	(0.4f)
#define PLAYER_BULLET_TEX	("data/TEXTURE/playerbullet.png")
#define PLAYER_BULLET_INTERVAL (5)
//==================================================
//=================�v���C���[�N���X=================
//==================================================
CPlayer::CPlayer() //:CObjBase()
{
	CObjBase();
	m_pos = point3(0.0f, 0.5f, -10.0f);
	m_move = point3(0.0f, 0.0f, 0.0f);

	m_life = 3;

	m_model[0] = new CModel("data/MODEL/player1.x");
	m_model[1] = new CModel("data/MODEL/player2.x");
	m_model[2] = new CModel("data/MODEL/player3.x");
	CreateShadow(&m_pD3DTexture, &m_pD3DVtxBuffShadow, 2, "data/TEXTURE/shadow.jpg"); 
	m_bulletInterval = PLAYER_BULLET_INTERVAL;
}

CPlayer::~CPlayer()
{
	for (int i = 0; i < 3; i++) {
		SAFE_DELETE(m_model[i]);
	}
	if (m_life == 0) {
		PlaySound(SOUND_LABEL_BREAK, 7.0f);
		CEffect::CreateEffect(EFFECT_BREAK, m_pos, m_rot);
	}
}

void CPlayer::Init() {

}

bool cbCollisionPlayerToBullet(CObjBase *pTgt, void *pPara)
{
	CPlayer* player = (CPlayer*)pPara;

	// ���̓����蔻��
	if ((player->m_pos.x - pTgt->m_pos.x) * (player->m_pos.x - pTgt->m_pos.x) + (player->m_pos.y - pTgt->m_pos.y)*(player->m_pos.y - pTgt->m_pos.y) + (player->m_pos.z - pTgt->m_pos.z)*(player->m_pos.z - pTgt->m_pos.z) <= (player->m_radius + pTgt->m_radius) *(player->m_radius + pTgt->m_radius)) {
		player->m_life--;
		pTgt->m_releaseFlag = true;
		PlaySound(SOUND_LABEL_ATTACK, 12.0f);
		return true;
	}
	return false;
}

void CPlayer::Update() {
	m_accel = m_move*-0.2f;		// �t�Œ�R�I��
	bool right = false;
	bool left = false;
	{// �����ύX
		vector2 vec1 = point2(0.0f, 0.0f);
		vector2 vec2 = point2(sin(m_rot.y), cos(m_rot.y));
		//float rot = 0.0f;

		if (DIGetKey(DIK_I) || DIGetKey(DIK_UPARROW)) {
			vec1.y += 1.0f;
			right = true;
		}
		if (DIGetKey(DIK_O)) {
			vec1.x += 0.5f;
			vec1.y += 0.5f;
			right = true;
		}
		if (DIGetKey(DIK_L) || DIGetKey(DIK_RIGHTARROW)) {
			vec1.x += 1.0f;
			right = true;
		}
		if (DIGetKey(DIK_PERIOD)) {
			vec1.x += 0.5f;
			vec1.y -= 0.5f;
			right = true;
		}
		if (DIGetKey(DIK_COMMA) || DIGetKey(DIK_DOWNARROW)) {
			vec1.y -= 1.0f;
			right = true;
		}
		if (DIGetKey(DIK_M)) {
			vec1.x -= 0.5f;
			vec1.y -= 0.5f;
			right = true;
		}
		if (DIGetKey(DIK_J) || DIGetKey(DIK_LEFTARROW)) {
			vec1.x -= 1.0f;
			right = true;
		}
		if (DIGetKey(DIK_U)) {
			vec1.x -= 0.5f;
			vec1.y += 0.5f;
			right = true;
		}
		if (right) {
			float cross = vec1.x*vec2.y - vec2.x*vec1.y;
			if (cross > 0)
				cross = 1;
			else
				cross = -1;

			float sita = vec1.x*vec2.x + vec2.y*vec1.y / (sqrt(vec2.x*vec2.x + vec2.y*vec2.y) * sqrt(vec1.x*vec1.x + vec1.y*vec1.y));
			if (cos(PI*0.18f) > sita) {
				m_rot.y += cross*PLAYER_ROT_SPEED;
			}
			else {
				m_rot.y += cross*0.05f;
			}
		}
	}
	{// �ړ��i�E��{�����ĂȂ���Ή�]���j
		vector2 vec1 = point2(0.0f, 0.0f);
		vector2 vec2 = point2(sin(m_rot.y), cos(m_rot.y));
		if (DIGetKey(DIK_W)) {
			if (!right) {
				vec1.y += 1.0f;
				left = true;
			}
			m_accel.z += PLAYER_SPEED;
		}
		if (DIGetKey(DIK_S)) {
			if (!right) {
				vec1.y -= 1.0f;
				left = true;
			}
			m_accel.z += -PLAYER_SPEED;
		}
		if (DIGetKey(DIK_D)) {
			if (!right) {
				vec1.x += 1.0f;
				left = true;
			}
			m_accel.x += PLAYER_SPEED;
		}
		if (DIGetKey(DIK_A)) {
			if (!right) {
				vec1.x -= 1.0f;
				left = true;
			}
			m_accel.x -= PLAYER_SPEED;
		}
		if (left) {
			float cross = vec1.x*vec2.y - vec2.x*vec1.y;
			if (cross > 0)
				cross = 1;
			else
				cross = -1;

			float sita = vec1.x*vec2.x + vec2.y*vec1.y / (sqrt(vec2.x*vec2.x + vec2.y*vec2.y) * sqrt(vec1.x*vec1.x + vec1.y*vec1.y));
			if (cos(PI*0.1f) > sita) {
				m_rot.y += cross*PLAYER_ROT_SPEED;
			}
			else {
				m_rot.y += cross*0.02f;
			}
		}
	}
	if (D3DX_PI * 2 < m_rot.y)
		m_rot.y = 0.0f;
	if (0.0f > m_rot.y) {
		m_rot.y = PI*2.0f + m_rot.y;
	}
	if (m_bulletInterval < 0) {
		CObjBase* pPlayerBullet = new CPlayerBullet(m_pos, m_rot);
		ObjSys.Add(pPlayerBullet, OBJ_PLAYERBULLET);
		m_bulletInterval = PLAYER_BULLET_INTERVAL;
		PlaySound(SOUND_LABEL_BULLET, 1.0f);
	}
	m_move += m_accel;
	m_pos += m_move;
	// �ǉ����߂�
	ObjSys.LoopStage(OBJLIST_STAGE, cbStageOutCharacter, this);
	// �Փ�
	if (g_step != STEP_GAMEEND) {
		ObjSys.LoopStage(OBJLIST_ENEMYBULLET + OBJLIST_ENEMYBULLETPURPLE, cbCollisionPlayerToBullet, this);
	}
	m_bulletInterval--;
}

void CPlayer::Draw() {
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXMATRIX mtxRot, mtxTranslate, mtxSize, mtxWorld;
	D3DXMATERIAL *pD3DXMat;
	D3DMATERIAL9 matDef;


	//���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&mtxWorld);

	//�傫���𔽉f
	//D3DXMatrixScaling(&mtxSize, 2, 2, 2);
	//D3DXMatrixMultiply(&mtxWorld, &mtxWorld, &mtxSize);

	//��]�𔽉f
	D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y, 0, 0);
	D3DXMatrixMultiply(&mtxWorld, &mtxWorld, &mtxRot);

	//�ړ��𔽉f
	D3DXMatrixTranslation(&mtxTranslate, m_pos.x, m_pos.y, m_pos.z);
	D3DXMatrixMultiply(&mtxWorld, &mtxWorld, &mtxTranslate);

	// �e�N�X�`���Ȃ�
	pDevice->SetTexture(0, NULL);

	//���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &mtxWorld);

	for (int i = 0; i < m_life; i++) {
		m_model[i]->DrawModel();
	}
}

void CPlayer::DrawAlpha() {
	//LPDIRECT3DDEVICE9 pDevice = GetDevice();
	//D3DXMATRIX mtxRot, mtxTranslate,mtxWorld;

	//// ���[���h�}�g���b�N�X�̏�����
	//D3DXMatrixIdentity(&mtxWorld);

	//// ��]�𔽉f
	//D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y, m_rot.x, m_rot.z);
	//D3DXMatrixMultiply(&mtxWorld, &mtxWorld, &mtxRot);

	//// �ړ��𔽉f
	//D3DXMatrixTranslation(&mtxTranslate, m_pos.x, m_pos.y, m_pos.z-0.5f);
	//D3DXMatrixMultiply(&mtxWorld, &mtxWorld, &mtxTranslate);

	//// ���[���h�}�g���b�N�X�̐ݒ�
	//pDevice->SetTransform(D3DTS_WORLD, &mtxWorld);

	//// ���_�o�b�t�@�������_�����O�p�C�v���C���ɐݒ�
	//pDevice->SetStreamSource(0, m_pD3DVtxBuffShadow, 0, sizeof(VERTEX_3D));

	//// ���_�t�H�[�}�b�g�̐ݒ�
	//pDevice->SetFVF(FVF_VERTEX_3D);

	//// �e�N�X�`���̐ݒ�
	//pDevice->SetTexture(0, m_pD3DTexture);

	//// ���Z�����̐ݒ�
	////	pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	////	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	//pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_REVSUBTRACT);
	//pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);
	//// Z�o�b�t�@���Q�Ƃ��Ȃ�
	//pDevice->SetRenderState(D3DRS_ZENABLE, FALSE);

	//// �|���S���̕`��
	//pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);

	//// Z�o�b�t�@���Q�Ƃ���
	//pDevice->SetRenderState(D3DRS_ZENABLE, TRUE);
	//// ���Z����������
	//pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	//pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
	////	pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, FALSE);
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	struct COLOR_VERTEX {
		D3DXVECTOR3 vecCoord;
		//	FLOAT w;
		FLOAT fScale;
		DWORD dwColor;
	};
	D3DXMATRIX mtxWorld;
	// ���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&mtxWorld);

	// ���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &mtxWorld);

	point3 camPos;
	ObjSys.LoopStage(OBJLIST_CAMERA, cbGetCamPos, &camPos);

	FLOAT fScale;
	if (camPos.x == 0.0f&&camPos.z == 0.0f) {
		fScale = 10;
	}
	else {
		fScale = 60;
	}
	COLOR_VERTEX* pointSprite = new COLOR_VERTEX;
	pointSprite->dwColor = D3DCOLOR_ARGB(128, 128, 128, 255);
	pointSprite->fScale = fScale;
	pointSprite->vecCoord = m_pos;


	// �[�x�o�b�t�@������
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);
	// ���C�e�B���O������
	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);
	pDevice->SetRenderState(D3DRS_POINTSPRITEENABLE, TRUE);
	pDevice->SetTexture(0, m_pD3DTexture);
	pDevice->SetFVF(D3DFVF_XYZ | D3DFVF_PSIZE | D3DFVF_DIFFUSE);
	// �|���S���̕`��
	//// ���Z�����̐ݒ�
	SetRenderMode(BLEND_ADDITION);
	pDevice->DrawPrimitiveUP(D3DPT_POINTLIST, 1, pointSprite, sizeof(COLOR_VERTEX));

	delete[] pointSprite;

	// ���C�e�B���O�L����
	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);
}
//==================================================
//=================�v���C���[�e�N���X===============
//==================================================
LPDIRECT3DTEXTURE9		CPlayerBullet::m_pD3DTexture = NULL;				// �e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9	CPlayerBullet::m_pD3DVtxBuffBillboard = NULL;		// ���_�o�b�t�@�ւ̃|�C���^

CPlayerBullet::CPlayerBullet(point3 pos, vector3 rot)
{
	m_life = 1;
	m_radius = PLAYER_BULLET_SIZE;
	m_pos = pos;
	m_pos.y = 0.5f;
	m_move.x = PLAYER_BULLET_SPEED * sin(rot.y);
	m_move.z = PLAYER_BULLET_SPEED * cos(rot.y);
	m_pos += m_move*5.0f;
	if (!m_pD3DVtxBuffBillboard) {
		CreateBillboard(&m_pD3DTexture, &m_pD3DVtxBuffBillboard, PLAYER_BULLET_SIZE, PLAYER_BULLET_TEX);
	}
}

CPlayerBullet::~CPlayerBullet()
{
	CEffect::CreateEffect(EFFECT_PLAYERBULLET, m_pos, m_rot);
}

bool cbCollisionPlayerBulletCollision(CObjBase *pTgt, void *pPara)
{
	CObjBase* playerBullet = (CObjBase*)pPara;

	// ���̓����蔻��
	if ((playerBullet->m_pos.x - pTgt->m_pos.x) * (playerBullet->m_pos.x - pTgt->m_pos.x) + (playerBullet->m_pos.y - pTgt->m_pos.y)*(playerBullet->m_pos.y - pTgt->m_pos.y) + (playerBullet->m_pos.z - pTgt->m_pos.z)*(playerBullet->m_pos.z - pTgt->m_pos.z) <= (playerBullet->m_radius + pTgt->m_radius) *(playerBullet->m_radius + pTgt->m_radius)) {
		playerBullet->m_releaseFlag = true;
		pTgt->m_life--;
		if (pTgt->m_life == 0) {
			pTgt->m_releaseFlag = true;
		}
		PlaySound(SOUND_LABEL_ATTACK, 12.0f);
		return true;
	}
	return false;
}

void CPlayerBullet::Update() {
	m_pos += m_move;
	ObjSys.LoopStage(OBJLIST_ENEMY + OBJLIST_ENEMYBULLET, cbCollisionPlayerBulletCollision, this);
	ObjSys.LoopStage(OBJLIST_STAGE, cbStageOutBullet, this);
}
void CPlayerBullet::DrawAlpha() {
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	D3DXMATRIX mtxWorld;
	// ���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&mtxWorld);

	// ��]�𔽉f
	D3DXMATRIX mtxView;
	ObjSys.LoopStage(OBJLIST_CAMERA, cbGetViewMatrix, &mtxView);
	mtxWorld._11 = mtxView._11;
	mtxWorld._12 = mtxView._21;
	mtxWorld._13 = mtxView._31;
	mtxWorld._21 = mtxView._12;
	mtxWorld._22 = mtxView._22;
	mtxWorld._23 = mtxView._32;
	mtxWorld._31 = mtxView._13;
	mtxWorld._32 = mtxView._23;
	mtxWorld._33 = mtxView._33;
	// ���_�o�b�t�@�������_�����O�p�C�v���C���ɐݒ�
	pDevice->SetStreamSource(0, m_pD3DVtxBuffBillboard, 0, sizeof(VERTEX_3D));

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_3D);

	// �e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, m_pD3DTexture);

	SetRenderMode(BLEND_ADDITION_TRANSLUCENT);
	// ���C�e�B���O������
	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

	point3 pos;
	vector3 move;
	if (m_move.z < 0) {
		pos = m_pos - m_move * 2.0f;
		move = m_move*-1.0f;
	}
	else {
		pos = m_pos;
		move = m_move;
	}

	for (int i = 0; i < 8; i++) {
		// �ړ��𔽉f
		mtxWorld._41 = pos.x;
		mtxWorld._42 = pos.y;
		mtxWorld._43 = pos.z;
		pos -= move*0.5f;
		// ���[���h�}�g���b�N�X�̐ݒ�
		pDevice->SetTransform(D3DTS_WORLD, &mtxWorld);

		// �|���S���̕`��
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);


	}
	// ���C�e�B���O�L����
	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
}

// �ق��Ŏg���R�[���o�b�N
bool cbGetPlayerPos(CObjBase *pTgt, void *pPara) {
	point3* pos = (point3*)pPara;
	*pos = pTgt->m_pos;
	return false;
}