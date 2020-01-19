#pragma once
#include "objbase.h"
#include "sprite.h"
class CUIComplete :public CObjBase
{
public:
	CUIComplete();
	~CUIComplete();

	void Draw2D();
private:
	LPDIRECT3DTEXTURE9 m_tex;
	CSprite m_sprite;
};

class CUIGameOver :public CObjBase
{
public:
	CUIGameOver();
	~CUIGameOver();

	void Draw2D();
private:
	LPDIRECT3DTEXTURE9 m_tex;
	CSprite m_sprite;
};

class CUITitle :public CObjBase
{
public:
	CUITitle();
	~CUITitle();
	void Update();
	void Draw2D();
private:
	LPDIRECT3DTEXTURE9 m_tex;
	CSprite m_sprite;
};
