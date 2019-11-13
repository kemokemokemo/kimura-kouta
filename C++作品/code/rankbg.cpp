// ====================================================================================================
//
// �����L���O�w�i�����̐���[rankbg.cpp]
// Author : Kimura kouta
//
// ====================================================================================================

// ====================================================================================================
// �C���N���[�h�t�@�C��
// ====================================================================================================
#include "rankbg.h"
#include "input.h"
#include "fade.h"
#include "sound.h"
#include "renderer.h"
#include "manager.h"
#include "keybord.h"

// ====================================================================================================
// �}�N����`
// ====================================================================================================
#define RANKBG1	"DATA/TEX/RESULT.jpg"//�ǂݍ��ރe�N�X�`���t�@�C����

#define RANKBG_MAX	�@(1)					// �摜��

#define RANKBG_LEFT_X (0)					// ��
#define RANKBG_ON_Y	  (0)					// ��
#define RANKBG_SIZE_X (1280)				// �T�C�Y�i���j
#define RANKBG_SIZE_Y (720)					// �T�C�Y�i���j

// ====================================================================================================
// �O���[�o���ϐ�
// ====================================================================================================


// ====================================================================================================
// �����L���O�w�i����������
// ====================================================================================================
HRESULT CRankBG::Init(void)
{
	// �ϐ��錾
	VERTEX_2D *pVtx;	// ���_���ւ̃|�C���g

	// ������
	m_fRankbgY = -320.0f;		// y�̃|�W�V����
	m_nCntRankbg = 0;
	m_nNumRankbg = 0;


	// �e�N�X�`���̓ǂݍ���
	CRenderer *pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	D3DXCreateTextureFromFile(pDevice, RANKBG1, &m_pTextureRankbg);

	// ���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4, D3DUSAGE_WRITEONLY, FVF_VERTEX_2D, D3DPOOL_MANAGED, &m_pVtxBuffRankbg, NULL);

	// ���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^
	m_pVtxBuffRankbg->Lock(0, 0, (void **)&pVtx, 0);

	// ���_�̐ݒ�
	pVtx[0].pos = D3DXVECTOR3(RANKBG_LEFT_X, RANKBG_ON_Y, 0.0f);									// ��ڂ̒��_
	pVtx[1].pos = D3DXVECTOR3(RANKBG_LEFT_X + RANKBG_SIZE_X, RANKBG_ON_Y, 0.0f);					// ��ڂ̒��_
	pVtx[2].pos = D3DXVECTOR3(RANKBG_LEFT_X, RANKBG_ON_Y + RANKBG_SIZE_Y, 0.0f);					// �O�ڂ̒��_
	pVtx[3].pos = D3DXVECTOR3(RANKBG_LEFT_X + RANKBG_SIZE_X, RANKBG_ON_Y + RANKBG_SIZE_Y, 0.0f);	// �l�ڂ̒��_

	// ���_�쐬
	pVtx[0].rhw = 1.0f;																// ��ڂ̒��_�쐬
	pVtx[1].rhw = 1.0f;																// ��ڂ̒��_�쐬
	pVtx[2].rhw = 1.0f;																// �O�ڂ̒��_�쐬
	pVtx[3].rhw = 1.0f;																// �l�ڂ̒��_�쐬

	// �J���[�ݒ�
	pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);								// ��ڂ̐F�ݒ�
	pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);								// ��ڂ̐F�ݒ�
	pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);								// �O�ڂ̐F�ݒ�
	pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);								// �l�ڂ̐F�ݒ�

	// �e�N�X�`���̐ݒ�
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);											// ��ڂ̃e�N�X�`��
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);											// ��ڂ̃e�N�X�`��
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);											// �O�ڂ̃e�N�X�`��
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);											// �l�ڂ̃e�N�X�`��

	// �A�����b�N
	m_pVtxBuffRankbg->Unlock();

	return S_OK;
}

// ====================================================================================================
// �����L���O�w�i�I������
// ====================================================================================================
void CRankBG::Uninit(void)
{
	// �e�N�X�`���̊J��
	if (m_pTextureRankbg != NULL)
	{
		m_pTextureRankbg->Release();
		m_pTextureRankbg = NULL;
	}

	// ���_�o�b�t�@�̊J��
	if (m_pVtxBuffRankbg != NULL)
	{
		m_pVtxBuffRankbg->Release();
		m_pVtxBuffRankbg = NULL;
	}
}

// ====================================================================================================
//
// �����L���O�w�i�X�V����
//
// ====================================================================================================
void CRankBG::Update(void)
{
}

// ====================================================================================================
// �����L���O�w�i�`�揈��
// ====================================================================================================
void CRankBG::Draw(void)
{
	// �f�o�C�X���擾����
	CRenderer *pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	// ���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���Ƀo�C���h
	pDevice->SetStreamSource(0, m_pVtxBuffRankbg, 0, sizeof(VERTEX_2D));

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	pDevice->SetTexture(0, m_pTextureRankbg);

	// �����L���O�w�i�`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
}

// ====================================================================================================
// �R���X�g���N�^
// ====================================================================================================
CRankBG::CRankBG()
{
}

// ====================================================================================================
// �f�X�g���N�^
// ====================================================================================================
CRankBG::~CRankBG()
{
}

// ====================================================================================================
// �N���G�C�g
// ====================================================================================================
CRankBG * CRankBG::Create()
{
	CRankBG *pRankBG;

	pRankBG = new CRankBG();

	pRankBG->Init();

	return pRankBG;
}
