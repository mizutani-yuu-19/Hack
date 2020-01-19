//---------------------------------------------------------
// エフェクト
// Effekseerを使用
//---------------------------------------------------------
#include "effect.h"
#include "camera.h"

//::EffekseerRendererDX9::Renderer	*CEffect::m_renderer = NULL;
//std::vector<CEffect*>	CEffect::m_vecEffect;
//::EffekseerSound::Sound*		CEffect::m_sound = NULL;
//::Effekseer::Manager*			CEffect::m_manager = NULL;
//std::vector<::Effekseer::Effect*>			CEffect::m_effect;
//IXAudio2*						CEffect::m_xa2 = NULL;
//IXAudio2MasteringVoice*			CEffect::m_xa2_master = NULL;
CEffect* CEffect::m_pEffect;
// パス
static const wchar_t*  g_effectPath[EFFECT_MAX] = {
	{ L"data/EFFECT/break.efk" },
	{ L"data/EFFECT/bulletbreak.efk" },
	{ L"data/EFFECT/playerbullet.efk" },
};
// カメラから必要な情報
typedef struct {
	point3 pos;
	point3 lookAt;
	vector3 direct;
	float aspect;
}CAM_INF;

//===========静的メンバ==============
void CEffect::CreateEffect(EFFECT effect, D3DXVECTOR3 pos, D3DXVECTOR3 rot) {
	m_pEffect->Create(effect, pos, rot);
}

bool cbGetCameraInf(CObjBase *pTgt, void *pPara) {
	CCamera* camera = (CCamera*)pTgt;
	// 描画済みなら描画中の可能性もある
	if (camera->m_drawedFlag) {
		CAM_INF* inf = (CAM_INF*)pPara;
		inf->pos = camera->m_pos;
		inf->lookAt = camera->m_lookatPt;
		inf->direct = camera->m_posCameraU;
		inf->aspect = camera->m_aspect;
		return false;
	}
	return true;
}
CEffect::CEffect() {
	m_pEffect = this;
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// 描画管理インスタンスの生成
	if (!m_renderer)
		m_renderer = ::EffekseerRendererDX9::Renderer::Create(pDevice, 1000);

	// XAudio2の初期化を行う
	if (!m_xa2)
		XAudio2Create(&m_xa2);
	if (!m_xa2_master)
		m_xa2->CreateMasteringVoice(&m_xa2_master);
	// サウンド管理インスタンスの生成
	if (!m_sound)
		m_sound = ::EffekseerSound::Sound::Create(m_xa2, 16, 16);

	if (!m_manager) {
		// エフェクト管理用インスタンスの生成
		m_manager = ::Effekseer::Manager::Create(1000);
		// 描画用インスタンスから描画機能を設定
		m_manager->SetSpriteRenderer(m_renderer->CreateSpriteRenderer());
		m_manager->SetRibbonRenderer(m_renderer->CreateRibbonRenderer());
		m_manager->SetRingRenderer(m_renderer->CreateRingRenderer());
		m_manager->SetTrackRenderer(m_renderer->CreateTrackRenderer());
		m_manager->SetModelRenderer(m_renderer->CreateModelRenderer());

		// 描画用インスタンスからテクスチャの読込機能を設定
		// 独自拡張可能、現在はファイルから読み込んでいる。
		m_manager->SetTextureLoader(m_renderer->CreateTextureLoader());
		m_manager->SetModelLoader(m_renderer->CreateModelLoader());

		// 音再生用インスタンスから再生機能を指定
		m_manager->SetSoundPlayer(m_sound->CreateSoundPlayer());

		// 音再生用インスタンスからサウンドデータの読込機能を設定
		// 独自拡張可能、現在はファイルから読み込んでいる。
		m_manager->SetSoundLoader(m_sound->CreateSoundLoader());
	}

	//	m_manager->CreateCullingWorld(1000, 1000, 1000, 5);
		// エフェクトの読込
	::Effekseer::Effect* effect = NULL;
	for (int i = 0; i < EFFECT_MAX; i++) {
		effect = Effekseer::Effect::Create(m_manager, (const EFK_CHAR*)g_effectPath[i]);
		m_effect.push_back(effect);
	}
}


void CEffect::Uninit() {
	if (!m_handle.size())	return;

	// 描画用インスタンスを破棄
	if (m_renderer) {
		m_renderer->Destroy();
	}
	// エフェクト管理用インスタンスを破棄
	m_manager->Destroy();
	// サウンド用インスタンスを破棄
	m_sound->Destroy();
}

void CEffect::Update() {
	//アップデート
	m_manager->Update();
	for (int i = 0; i < m_handle.size(); i++) {
		// 再生終了していたらvectorから削除
		if (CheckEffect(m_handle[i])) {
			m_handle.erase(m_handle.begin() + i);
			i--;
		}
	}
}
void CEffect::Draw() {
	if (!m_handle.size())	return;

	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// カメラから必要情報取得
	CAM_INF camInf;
	ObjSys.LoopStage(OBJLIST_CAMERA, cbGetCameraInf, &camInf);

	// 投影行列を設定
	m_renderer->SetProjectionMatrix(
		::Effekseer::Matrix44().PerspectiveFovLH(VIEW_ANGLE, camInf.aspect, VIEW_NEAR_Z, VIEW_FAR_Z));
	// カメラ行列を設定
	CEffect::m_renderer->SetCameraMatrix(
		::Effekseer::Matrix44().LookAtLH(::Effekseer::Vector3D(camInf.pos.x, camInf.pos.y, camInf.pos.z), ::Effekseer::Vector3D(camInf.lookAt.x, camInf.lookAt.y, camInf.lookAt.z), ::Effekseer::Vector3D(camInf.direct.x, camInf.direct.y, camInf.direct.z)));

	CEffect::m_renderer->BeginRendering();
	m_manager->Draw();
	CEffect::m_renderer->EndRendering();
}

//============メンバ関数==============

void CEffect::Create(EFFECT effect, D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	// エフェクトの再生
	Effekseer::Handle handle = m_manager->Play(m_effect[effect], pos.x, pos.y, pos.z);
	m_handle.push_back(handle);
	m_manager->SetRotation(handle, rot.x, -rot.y, rot.z);
	m_manager->SetScale(handle, 1, 1, 1);
}

CEffect::~CEffect()
{

}

bool CEffect::CheckEffect(Effekseer::Handle handle) {
	if (handle) {
		return true;
	}
	return false;
}