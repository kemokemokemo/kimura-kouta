//=============================================================================
//
// �����̏��� [explosion.cpp]
// Author : KIMURA KOUTA
//
//=============================================================================
#include "explosion.h"
#include "renderer.h"
#include "manager.h"

//=============================================================================
// �}�N����`
//=============================================================================
#define	MAX_EXPLOSION			(256)							// �G�t�F�N�g�̍ő吔
#define EXPLOSION_SIZE (80)	

//=============================================================================
// �O���錾�̏�����
//=============================================================================
LPDIRECT3DTEXTURE9 CExplosion::m_pTextureExplosion[MAX_TEXE] = {};

//====================================================================================================
// �R���X�g���N�^
//====================================================================================================
CExplosion::CExplosion(OBJTYPE type) : CScene2D(type)
{
	m_nLife = 0;
}

//=============================================================================
// ����������
//=============================================================================
HRESULT CExplosion::Init()
{
	CScene2D::Init();

	m_nLife = 40;

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void CExplosion::Uninit(void)
{
	CScene2D::Uninit();
	this->Release();
}

//=============================================================================
// �X�V����
//=============================================================================
void CExplosion::Update(void)
{
	CScene2D::Update();
	float Size = EXPLOSION_SIZE;
	m_nLife--;

	SetAnim(0.125f, 0.0f,1.0f,6);

	if (m_nLife <= 0)
	{
		Release();
	}

	CScene2D::SetSize(Size, Size);
}

//=============================================================================
// �`�揈��
//=============================================================================
void CExplosion::Draw(void)
{
	CRenderer *pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	// �����_�[�X�e�[�g(���Z��������)
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);				//�A���t�@�u�����h���s��
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);

	CScene2D::Draw();

	// �����_�[�X�e�[�g(�ʏ�u�����h����)
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);				//�A���t�@�u�����h���s��
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
}

//========================================================================================================
// �`�揈��
//========================================================================================================
CExplosion *CExplosion::Create()
{
	CExplosion *pExplosion;

	pExplosion = new CExplosion(OBJTYPE_EXPLOSION);

	pExplosion->BindTexture(m_pTextureExplosion[0]);

	pExplosion->Init();

	pExplosion->SetInitTex(0.125f, 1.0f);

	return pExplosion;
}

//========================================================================================================
// �e�N�X�`���̓ǂݍ���
//========================================================================================================
HRESULT CExplosion::Load(void)
{
	CRenderer *pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(
		pDevice,
		TEXTUER_003,
		&m_pTextureExplosion[0]);

	return S_OK;
}

//========================================================================================================
// �e�N�X�`���̔j��
//========================================================================================================
void CExplosion::Unload(void)
{
	for (int nCnt = 0; nCnt < MAX_TEXE; nCnt++)
	{
		// ���_�o�b�t�@�̊J��
		if (m_pTextureExplosion[nCnt] != NULL)
		{
			m_pTextureExplosion[nCnt]->Release();
			m_pTextureExplosion[nCnt] = NULL;
		}
	}
}

//====================================================================================================
// �p�[�e�B�N��
//=====================================================================================================
void CExplosion::SetParticle(void)
{

}

//====================================================================================================
// �f�X�g���N�^
//=====================================================================================================
CExplosion::~CExplosion()
{

}