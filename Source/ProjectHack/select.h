#pragma once

#include "objbase.h"
#include "sprite.h"
#define MAX_LEVEL (5)

class CSelect:public CObjBase
{
public:
	CSelect();
	~CSelect();

	void Draw2D();
	void Update();

private:
	CSprite m_number[MAX_LEVEL];
	CSprite m_crown[MAX_LEVEL];
	CSprite m_selectSprite;
	static LPDIRECT3DTEXTURE9 m_numTex;
	static LPDIRECT3DTEXTURE9 m_selectTex;
	static LPDIRECT3DTEXTURE9 m_crownTex;
	int m_time=0;
	int m_selectNo = 1;
};


