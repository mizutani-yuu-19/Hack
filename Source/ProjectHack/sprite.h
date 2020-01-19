#ifndef _SPRITE_H_
#define	_SPRITE_H_

#include "main.h"
//-----------�萔�}�N��-------------
enum {
	BLEND_NOBLEND,					// �ʏ�i�u�����h�����j
	BLEND_TRANSLUCENT,				// ������
	BLEND_ADDITION,					// ���Z����
	BLEND_ADDITION_TRANSLUCENT,		// ���Z����������
	BLEND_SUBTRACTION,				// ���Z����
	BLEND_MULTIPLICATION,			// ��Z����
	BLEND_SCREEN,					// �X�N���[������
	BLEND_REVERSE,					// ���o�[�X
};

class CSprite {
public:
	CSprite();
	~CSprite();
	void InitSprite(D3DXVECTOR2 pos, float width, float height, int divideX, int divideY);
	void DrawSprite(LPDIRECT3DTEXTURE9 pTexture);
	void SetDirection(int direct);		// �����ύX�@�Por-1

	D3DXVECTOR2 m_pos;			// ���S�ʒu
	D3DXVECTOR2	m_scale;		// �g�嗦
	float		m_angleDegree;	// ��]�p�x�i���j
	D3DCOLOR	m_color;		// �F
	int			m_patNum;		// �p�^�[��No
	float		m_width;		// �X�v���C�g�̕��i�e�N�X�`���̐؂��蕝�j
	float		m_height;		// �X�v���C�g�̍����i�e�N�X�`���̐؂��荂���j
private:
	int			m_direction;	// ����
	VERTEX_2D	m_vertex[4];	// ���_���
	int			m_divideX;		// ������X
	int			m_divideY;		// ������Y

protected:

};

//-------�v���g�^�C�v---------
LPDIRECT3DTEXTURE9 SetTexture(LPCSTR pass);
void SetRenderMode(int mode);
#endif // !_SPRITE_H_