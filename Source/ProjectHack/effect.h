//---------------------------------------------------------
// エフェクト
// Effekseerを使用
//---------------------------------------------------------
#pragma once

//---------インクルード--------
#include "main.h"
#include "objbase.h"

#include <Effekseer.h>
#include <EffekseerRendererDX9.h>
#include <EffekseerSoundXAudio2.h>

#if _DEBUG
#pragma comment(lib, "VS2015/Debug/Effekseer.lib" )
#pragma comment(lib, "VS2015/Debug/EffekseerRendererDX9.lib" )
#pragma comment(lib, "VS2015/Debug/EffekseerSoundXAudio2.lib" )
#else
#pragma comment(lib, "VS2015/Release/Effekseer.lib" )
#pragma comment(lib, "VS2015/Release/EffekseerRendererDX9.lib" )
#pragma comment(lib, "VS2015/Release/EffekseerSoundXAudio2.lib" )
#endif


//-----------列挙体----------------
typedef enum {
	EFFECT_BREAK,
	EFFECT_BULLETBREAK,
	EFFECT_PLAYERBULLET,
	EFFECT_MAX
}EFFECT;
//-----------定数----------------

class CEffect :public CObjBase
{
public:
	CEffect();
	~CEffect();

	static void CreateEffect(EFFECT effect, D3DXVECTOR3 pos, D3DXVECTOR3 rot);
	static CEffect* m_pEffect;

	void Create(EFFECT effect, D3DXVECTOR3 pos, D3DXVECTOR3 rot);
	void Uninit();
	void Update();
	void Draw();

private:
	bool CheckEffect(Effekseer::Handle handle);

	std::vector<::Effekseer::Handle>			m_handle;
	::Effekseer::Manager*			m_manager = NULL;
	::EffekseerRendererDX9::Renderer*	m_renderer=NULL;
	::EffekseerSound::Sound*		m_sound=NULL;
	std::vector<::Effekseer::Effect*>		m_effect;
	IXAudio2*						m_xa2=NULL;
	IXAudio2MasteringVoice*			m_xa2_master=NULL;
};
