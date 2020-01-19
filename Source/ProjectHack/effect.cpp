//---------------------------------------------------------
// �G�t�F�N�g
// Effekseer���g�p
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
// �p�X
static const wchar_t*  g_effectPath[EFFECT_MAX] = {
	{ L"data/EFFECT/break.efk" },
	{ L"data/EFFECT/bulletbreak.efk" },
	{ L"data/EFFECT/playerbullet.efk" },
};
// �J��������K�v�ȏ��
typedef struct {
	point3 pos;
	point3 lookAt;
	vector3 direct;
	float aspect;
}CAM_INF;

//===========�ÓI�����o==============
void CEffect::CreateEffect(EFFECT effect, D3DXVECTOR3 pos, D3DXVECTOR3 rot) {
	m_pEffect->Create(effect, pos, rot);
}

bool cbGetCameraInf(CObjBase *pTgt, void *pPara) {
	CCamera* camera = (CCamera*)pTgt;
	// �`��ς݂Ȃ�`�撆�̉\��������
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

	// �`��Ǘ��C���X�^���X�̐���
	if (!m_renderer)
		m_renderer = ::EffekseerRendererDX9::Renderer::Create(pDevice, 1000);

	// XAudio2�̏��������s��
	if (!m_xa2)
		XAudio2Create(&m_xa2);
	if (!m_xa2_master)
		m_xa2->CreateMasteringVoice(&m_xa2_master);
	// �T�E���h�Ǘ��C���X�^���X�̐���
	if (!m_sound)
		m_sound = ::EffekseerSound::Sound::Create(m_xa2, 16, 16);

	if (!m_manager) {
		// �G�t�F�N�g�Ǘ��p�C���X�^���X�̐���
		m_manager = ::Effekseer::Manager::Create(1000);
		// �`��p�C���X�^���X����`��@�\��ݒ�
		m_manager->SetSpriteRenderer(m_renderer->CreateSpriteRenderer());
		m_manager->SetRibbonRenderer(m_renderer->CreateRibbonRenderer());
		m_manager->SetRingRenderer(m_renderer->CreateRingRenderer());
		m_manager->SetTrackRenderer(m_renderer->CreateTrackRenderer());
		m_manager->SetModelRenderer(m_renderer->CreateModelRenderer());

		// �`��p�C���X�^���X����e�N�X�`���̓Ǎ��@�\��ݒ�
		// �Ǝ��g���\�A���݂̓t�@�C������ǂݍ���ł���B
		m_manager->SetTextureLoader(m_renderer->CreateTextureLoader());
		m_manager->SetModelLoader(m_renderer->CreateModelLoader());

		// ���Đ��p�C���X�^���X����Đ��@�\���w��
		m_manager->SetSoundPlayer(m_sound->CreateSoundPlayer());

		// ���Đ��p�C���X�^���X����T�E���h�f�[�^�̓Ǎ��@�\��ݒ�
		// �Ǝ��g���\�A���݂̓t�@�C������ǂݍ���ł���B
		m_manager->SetSoundLoader(m_sound->CreateSoundLoader());
	}

	//	m_manager->CreateCullingWorld(1000, 1000, 1000, 5);
		// �G�t�F�N�g�̓Ǎ�
	::Effekseer::Effect* effect = NULL;
	for (int i = 0; i < EFFECT_MAX; i++) {
		effect = Effekseer::Effect::Create(m_manager, (const EFK_CHAR*)g_effectPath[i]);
		m_effect.push_back(effect);
	}
}


void CEffect::Uninit() {
	if (!m_handle.size())	return;

	// �`��p�C���X�^���X��j��
	if (m_renderer) {
		m_renderer->Destroy();
	}
	// �G�t�F�N�g�Ǘ��p�C���X�^���X��j��
	m_manager->Destroy();
	// �T�E���h�p�C���X�^���X��j��
	m_sound->Destroy();
}

void CEffect::Update() {
	//�A�b�v�f�[�g
	m_manager->Update();
	for (int i = 0; i < m_handle.size(); i++) {
		// �Đ��I�����Ă�����vector����폜
		if (CheckEffect(m_handle[i])) {
			m_handle.erase(m_handle.begin() + i);
			i--;
		}
	}
}
void CEffect::Draw() {
	if (!m_handle.size())	return;

	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// �J��������K�v���擾
	CAM_INF camInf;
	ObjSys.LoopStage(OBJLIST_CAMERA, cbGetCameraInf, &camInf);

	// ���e�s���ݒ�
	m_renderer->SetProjectionMatrix(
		::Effekseer::Matrix44().PerspectiveFovLH(VIEW_ANGLE, camInf.aspect, VIEW_NEAR_Z, VIEW_FAR_Z));
	// �J�����s���ݒ�
	CEffect::m_renderer->SetCameraMatrix(
		::Effekseer::Matrix44().LookAtLH(::Effekseer::Vector3D(camInf.pos.x, camInf.pos.y, camInf.pos.z), ::Effekseer::Vector3D(camInf.lookAt.x, camInf.lookAt.y, camInf.lookAt.z), ::Effekseer::Vector3D(camInf.direct.x, camInf.direct.y, camInf.direct.z)));

	CEffect::m_renderer->BeginRendering();
	m_manager->Draw();
	CEffect::m_renderer->EndRendering();
}

//============�����o�֐�==============

void CEffect::Create(EFFECT effect, D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	// �G�t�F�N�g�̍Đ�
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