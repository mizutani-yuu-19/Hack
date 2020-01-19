#include "UI.h"
#include "input.h"
// コンプリート
CUIComplete::CUIComplete()
{
	m_tex = SetTexture("data/TEXTURE/complete.png");
	m_sprite.InitSprite(point2(SCREEN_CENTER_X, SCREEN_CENTER_Y), 512, 128, 1, 1);
}

CUIComplete::~CUIComplete()
{
	SAFE_RELEASE(m_tex);
}

void CUIComplete::Draw2D() {
	SetRenderMode(BLEND_TRANSLUCENT);
	m_sprite.DrawSprite(m_tex);
}

// ゲームオーバー
CUIGameOver::CUIGameOver()
{
	m_tex = SetTexture("data/TEXTURE/miss.png");
	m_sprite.InitSprite(point2(SCREEN_CENTER_X, SCREEN_CENTER_Y), 256, 128, 1, 1);
}

CUIGameOver::~CUIGameOver()
{
	SAFE_RELEASE(m_tex);
}

void CUIGameOver::Draw2D() {
	SetRenderMode(BLEND_TRANSLUCENT);
	m_sprite.DrawSprite(m_tex);
}

// タイトル
CUITitle::CUITitle()
{
	m_tex = SetTexture("data/TEXTURE/title.png");
	m_sprite.InitSprite(point2(SCREEN_CENTER_X, SCREEN_CENTER_Y), SCREEN_WIDTH, SCREEN_HEIGHT, 1, 1);
}

CUITitle::~CUITitle()
{
	SAFE_RELEASE(m_tex);
}

void CUITitle::Update() {

}

void CUITitle::Draw2D() {
	SetRenderMode(BLEND_TRANSLUCENT);
	m_sprite.DrawSprite(m_tex);
}
