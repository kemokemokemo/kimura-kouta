//=============================================================================
//
// �A�j���[�V�����̏��� [animation.cpp]
// Author : KIMURA KOUTA
//
//=============================================================================
#include "Animation.h"
#include "renderer.h"
#include "manager.h"

//=============================================================================
// �}�N����`
//=============================================================================
#define	MAX_EXPLOSION			(256)							// �G�t�F�N�g�̍ő吔
#define ANIMATION_SIZE			(150)

//=============================================================================
// �O���錾�̏�����
//=============================================================================
LPDIRECT3DTEXTURE9 CAnimation::m_pTextureAnimation[MAX_ANIMATION] = {};

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CAnimation::CAnimation(OBJTYPE type) : CScene2D(type)
{
	{//������
		m_nLife = 0;
		m_EnterCnt = 0;
		m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	}
}

//=============================================================================
// ����������
//=============================================================================
HRESULT CAnimation::Init(D3DXVECTOR3 pos, ANIM Type,int nLife)
{
	CScene2D::Init();
	SetPos(pos);
	m_Anim = Type;
	m_nLife = nLife;
	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void CAnimation::Uninit(void)
{
	CScene2D::Uninit();
}

//=============================================================================
// �X�V����
//=============================================================================
void CAnimation::Update(void)
{
	CScene2D::Update();
	float Size = ANIMATION_SIZE;

	m_EnterCnt++;
	m_pos = CScene2D::GetPos();

	switch (m_Anim)
	{
	case ANIMATION_ENEMY:
		m_nLife--;
		SetAnim(0.1f, 0.0f, 1.0f, 5);
		CScene2D::SetSize(Size, Size);
		break;

	case ANIMATION_PLAYER:
		m_nLife--;
		SetAnim(0.125f, 0.0f, 1.0f, 5);
		CScene2D::SetSize(Size, Size);
		break;

	case ANIMATION_NET:
		m_nLife--;
		SetAnim(0.33f, 0.0f, 0.2f, 5);
		CScene2D::SetSize(Size, Size);
		break;

	case ANIMATION_POWERUP:
		m_nLife--;
		SetAnim(0.1f, 0.0f, 1.0f, 6);
		CScene2D::SetSize(Size, Size);
		break;

	case ANIMATION_PRESSENTER:

		CScene2D::SetSize(450, Size);

		if (m_EnterCnt >= 0 && m_EnterCnt <= 60)
		{
			SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
		}
		else if (m_EnterCnt >= 60 && m_EnterCnt <= 120)
		{
			SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f));
		}
		else
		{
			m_EnterCnt = 0;
		}
		break;

	case ANIMATION_TITLEBIRD:

		CScene2D::SetSize(1000, 1000);
		break;
	}

	{//�A�j���[�V�����̊J��
		if (m_nLife <= 0)
		{
			Release();
		}
	}

	CScene2D::SetPos(m_pos);
}

//=============================================================================
// �`�揈��
//=============================================================================
void CAnimation::Draw(void)
{
	CScene2D::Draw();
}

//=============================================================================
// �`�揈��
//=============================================================================
CAnimation *CAnimation::Create(D3DXVECTOR3 pos, ANIM nType, int nLife)
{
	CAnimation *pAnimation;

	pAnimation = new CAnimation(OBJTYPE_ANIMATION);

	pAnimation->BindTexture(m_pTextureAnimation[nType]);

	pAnimation->Init(pos ,nType, nLife);

	return pAnimation;
}

//========================================================================================================
// �e�N�X�`���̓ǂݍ���
//========================================================================================================
HRESULT CAnimation::Load(void)
{
	CRenderer *pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(
		pDevice,
		TEXTUER_009,
		&m_pTextureAnimation[0]);

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(
		pDevice,
		TEXTUER_010,
		&m_pTextureAnimation[1]);

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(
		pDevice,
		TEXTUER_012,
		&m_pTextureAnimation[2]);

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(
		pDevice,
		TEXTUER_014,
		&m_pTextureAnimation[3]);

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(
		pDevice,
		TEXTUER_021,
		&m_pTextureAnimation[4]);

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(
		pDevice,
		TEXTUER_022,
		&m_pTextureAnimation[5]);

	return S_OK; 
}

//========================================================================================================
// �e�N�X�`���̔j��
//========================================================================================================
void CAnimation::Unload(void)
{
	for (int nCnt = 0; nCnt < MAX_ANIMATION; nCnt++)
	{
		// ���_�o�b�t�@�̊J��
		if (m_pTextureAnimation[nCnt] != NULL)
		{
			m_pTextureAnimation[nCnt]->Release();
			m_pTextureAnimation[nCnt] = NULL;
		}
	}
}

//====================================================================================================
// �f�X�g���N�^
//=====================================================================================================
CAnimation::~CAnimation()
{

}