//----------�C���N���[�h---------
#include "sprite.h"
#include <math.h>
//----------�萔�}�N��----------

//----------���\�b�h--------------
// �R���X�g���N�^
CSprite::CSprite() {
	m_pos = D3DXVECTOR2(0.0f, 0.0f);				// �ʒu
	m_color = D3DCOLOR_RGBA(255, 255, 255, 255);	// �F
	m_angleDegree = 0.0f;							// ��]�p�x�i���j
	m_scale.x = 1.0f;								// �g�嗦
	m_scale.y = 1.0f;								// �g�嗦
	m_width = 1.0f;									// ��
	m_height = 1.0f;								// ����
	m_divideX = 1;									// ��������
	m_divideY = 1;									// �������c
	m_patNum = 1;
	m_direction = 1;								// ���̌���

	for (int i = 0; i < 4; ++i)
	{
		m_vertex[i].rhw = 1.0f;
		m_vertex[i].diffuse = D3DCOLOR_ARGB(255, 255, 255, 255);
		m_vertex[i].uv.x = i % 2;
		m_vertex[i].uv.y = i * 0.5f;
		m_vertex[i].vtxPos.z = 0.0f;
	}
}
// �f�X�g���N�^
CSprite::~CSprite() {

}

void CSprite::InitSprite(D3DXVECTOR2 pos, float width, float height, int divideX, int divideY) {
	m_pos = pos;
	m_width = width;
	m_height = height;
	m_divideX = divideX;
	m_divideY = divideY;
	m_scale.x = 1.0f;								// �g�嗦
	m_scale.y = 1.0f;								// �g�嗦

	for (int i = 0; i < 4; ++i) {
		m_vertex[i].rhw = 1.0f;
		m_vertex[i].diffuse = D3DCOLOR_ARGB(255, 255, 255, 255);
	}
}

void CSprite::DrawSprite(LPDIRECT3DTEXTURE9 pTexture) {
	float rad = D3DXToRadian(m_angleDegree);  //D3DXToRadian�p�x��radian�ɕϊ�

	float s = sinf(rad);
	float c = cosf(rad);

	for (int i = 0; i < 4; ++i) {
		// �A�j���[�V����
		int u = m_patNum % m_divideX;
		int v = m_patNum / m_divideX;
		m_vertex[i].uv.x = (u + i % 2) * (1.0f / m_divideX) * m_direction;
		m_vertex[i].uv.y = (int)(v + i * 0.5f) * (1.0f / m_divideY);
		// �ʒu
		float x = ((i & 1)  * m_width - m_width * 0.5f) * m_scale.x;
		float y = ((i >> 1) * m_height - m_height * 0.5f) * m_scale.y;
		m_vertex[i].vtxPos.x = m_pos.x + x * c - y * s;
		m_vertex[i].vtxPos.y = m_pos.y + x * s + y * c;
		// �J���[
		m_vertex[i].diffuse = m_color;
	}

	// �f�o�C�X�擾
	LPDIRECT3DDEVICE9	pDevice = GetDevice();
	// ���_�����ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);
	// �e�N�X�`���ݒ�
	pDevice->SetTexture(0, pTexture);
	// �|���S���`��(���_�z��g�p)
	pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, 2, m_vertex, sizeof(VERTEX_2D));
	// �f�o�C�X���
	pDevice = NULL;
}
// 1�Ȃ琳,-1�Ȃ�t����
void CSprite::SetDirection(int direct) {
	m_direction = direct;
}
//-------�֐�----------

// �Z�b�g�e�N�X�`���֐�
// �����F�e�N�X�`���̃p�X
// �߂�l�FLPDIRECT3DTEXTURE9�^�@�e�N�X�`��
// �e�N�X�`���̃p�X�𑗂�ƃe�N�X�`�����Ԃ��Ă��܂��B
LPDIRECT3DTEXTURE9 SetTexture(LPCSTR pass) {
	// �f�o�C�X�擾
	LPDIRECT3DDEVICE9	pDevice = GetDevice();
	LPDIRECT3DTEXTURE9 texture;
	if (FAILED(D3DXCreateTextureFromFile(pDevice, pass, &texture))) {
		MessageBox(NULL, "�e�N�X�`���ǂݍ��ݎ��s", pass, MB_OK);
		texture = NULL;
	}
	// �f�o�C�X���
	pDevice = NULL;
	return texture;
}

// �����_�[���[�h
void SetRenderMode(int mode) {
	// �f�o�C�X�擾
	LPDIRECT3DDEVICE9	pDevice = GetDevice();
	switch (mode)
	{
	case		BLEND_NOBLEND:				// �ʏ�i�u�����h�����j
		pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_ONE);
		pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ZERO);
		break;
	case		BLEND_TRANSLUCENT:			// ������
		pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
		pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
		break;
	case		BLEND_ADDITION:				// ���Z����
		pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_ONE);
		pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);
		break;
	case		BLEND_ADDITION_TRANSLUCENT:	// ���Z����������
		pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
		pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);
		break;
	case		BLEND_SUBTRACTION:			// ���Z����
		pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_ZERO);
		pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCCOLOR);
		break;
	case		BLEND_MULTIPLICATION:		// ��Z����
		pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_ZERO);
		pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_SRCCOLOR);
		break;
	case		BLEND_SCREEN:				// �X�N���[������
		pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_INVDESTCOLOR);
		pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);
		break;
	case		BLEND_REVERSE:				// ���o�[�X
		pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_INVDESTCOLOR);
		pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCCOLOR);
		break;
	default:
		break;
	}
	// �f�o�C�X���
	pDevice = NULL;
}