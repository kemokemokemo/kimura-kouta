//=============================================================================
//
// �G�t�F�N�g�̏��� [effect.cpp]
// Author : KIMURA KOUTA
//
//=============================================================================
#include "effect.h"
#include "manager.h"
#include "renderer.h"
#include "bullet.h"
#include "player.h"

//=============================================================================
// �O���[�o���ϐ�
//=============================================================================
LPDIRECT3DTEXTURE9 CEffect::m_pTextureEffect[MAX_EFFECTTEX] = {};
LPDIRECT3DVERTEXBUFFER9 CEffect::m_pVtxBuffEffect = NULL;
CEffect::EFFECT CEffect::m_aEffect[MAX_EFFECT] = {};

//=============================================================================
// �}�N����`
//=============================================================================
#define EFFECT_SIZE (50)

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CEffect::CEffect(OBJTYPE type) : CScene(type)
{

}
//=============================================================================
// �R���X�g���N�^
//=============================================================================
CEffect::CEffect()
{

}
//=============================================================================
// ����������
//=============================================================================
HRESULT CEffect::Init(void)
{
	for (int nCntEffect = 0; nCntEffect < MAX_EFFECT; nCntEffect++)
	{
		m_aEffect[nCntEffect].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		m_aEffect[nCntEffect].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		m_aEffect[nCntEffect].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f);
		m_aEffect[nCntEffect].fRadius = 0;
		m_aEffect[nCntEffect].nLife = 0;
		m_aEffect[nCntEffect].bUse = false;
	}

	// �I�u�W�F�N�g�̎�ނ̐ݒ�
	SetObjType(CScene::OBJTYPE_EFFECT);

	CEffect::MakeVertex();
	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void CEffect::Uninit(void)
{
	if (m_pVtxBuffEffect != NULL)
	{// ���_�o�b�t�@�̊J��
		m_pVtxBuffEffect->Release();
		m_pVtxBuffEffect = NULL;
	}
}

//=============================================================================
// �X�V����
//=============================================================================
void CEffect::Update(void)
{
	VERTEX_2D *pVtx;

	// ���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
	m_pVtxBuffEffect->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntEffect = 0; nCntEffect < MAX_EFFECT; nCntEffect++, pVtx += 4)
	{
		if (m_aEffect[nCntEffect].bUse == true)					  // �e���g�p����Ă���
		{
			// ���_���W�̍X�V
			pVtx[0].pos = D3DXVECTOR3(m_aEffect[nCntEffect].pos.x - m_aEffect[nCntEffect].fRadius, m_aEffect[nCntEffect].pos.y - m_aEffect[nCntEffect].fRadius, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(m_aEffect[nCntEffect].pos.x + m_aEffect[nCntEffect].fRadius, m_aEffect[nCntEffect].pos.y - m_aEffect[nCntEffect].fRadius, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(m_aEffect[nCntEffect].pos.x - m_aEffect[nCntEffect].fRadius, m_aEffect[nCntEffect].pos.y + m_aEffect[nCntEffect].fRadius, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(m_aEffect[nCntEffect].pos.x + m_aEffect[nCntEffect].fRadius, m_aEffect[nCntEffect].pos.y + m_aEffect[nCntEffect].fRadius, 0.0f);

			// ���_�J���[�̍X�V
			pVtx[0].col = m_aEffect[nCntEffect].col;
			pVtx[1].col = m_aEffect[nCntEffect].col;
			pVtx[2].col = m_aEffect[nCntEffect].col;
			pVtx[3].col = m_aEffect[nCntEffect].col;

			m_aEffect[nCntEffect].nLife--;

			m_aEffect[nCntEffect].fRadius -= 5.0f;

			if (m_aEffect[nCntEffect].fRadius <= 0)
			{
				m_aEffect[nCntEffect].fRadius = 0;
			}

			if (m_aEffect[nCntEffect].nLife <= 0)
			{
				m_aEffect[nCntEffect].bUse = false;
			}
		}
	}
	// ���_�f�[�^���A�����b�N����
	m_pVtxBuffEffect->Unlock();
}

//=============================================================================
// �`�揈��
//=============================================================================
void CEffect::Draw(void)
{
	CRenderer *pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	// �����_�[�X�e�[�g(���Z��������)
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);

	// ���_�o�b�t�@���f�[�^�X�g���[���Ƀo�C���h
	pDevice->SetStreamSource(0, m_pVtxBuffEffect, 0, sizeof(VERTEX_2D));

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	// �e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, m_pTextureEffect[0]);

	// �|���S���`��
	for (int nCntEffect = 0; nCntEffect < MAX_EFFECT; nCntEffect++)
	{
		if (m_aEffect[nCntEffect].bUse == true)					  // �e���g�p����Ă���
		{
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntEffect * 4, 2);
		}
	}

	// �����_�[�X�e�[�g(�ʏ�u�����h����)
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
}

//=============================================================================
// �G�t�F�N�g�̍쐬
//=============================================================================
CEffect * CEffect::Create()
{
	CEffect *pEffect = new CEffect(OBJTYPE_EFFECT);
	pEffect->Init();
	return pEffect;
}

//=============================================================================
// �e�N�X�`���̓ǂݍ���
//=============================================================================
HRESULT CEffect::Load(void)
{
	CRenderer *pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	// �e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,				// �f�o�C�X�ւ̃|�C���^
		TEXTURE_EFFECT,		// �t�@�C���̖��O
		&m_pTextureEffect[0]);	// �ǂݍ��ރ������[

								// �e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,				// �f�o�C�X�ւ̃|�C���^
		TEXTURE_EFFECT2,		// �t�@�C���̖��O
		&m_pTextureEffect[1]);	// �ǂݍ��ރ������[


	return S_OK;
}

//=============================================================================
// �e�N�X�`���̔j��
//=============================================================================
void CEffect::Unload(void)
{
	// �e�N�X�`���̊J��
	for (int nCntEffect = 0; nCntEffect < MAX_EFFECTTEX; nCntEffect++)
	{
		if (m_pTextureEffect[nCntEffect] != NULL)
		{
			m_pTextureEffect[nCntEffect]->Release();
			m_pTextureEffect[nCntEffect] = NULL;
		}
	}
}

//=============================================================================
// ���_���̐���
//=============================================================================
void CEffect::MakeVertex(void)
{
	// ���_���̐ݒ�
	for (int nCnt = 0; nCnt < MAX_EFFECT; nCnt++)
	{
		m_aEffect[nCnt].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		m_aEffect[nCnt].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		m_aEffect[nCnt].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		m_aEffect[nCnt].nLife = 0;
		m_aEffect[nCnt].fRadius = 0.0f;
		m_aEffect[nCnt].bUse = false;
	}

	// ���_�o�b�t�@�̃|�C���^
	VERTEX_2D *pVtx;

	CRenderer *pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	int nCnt;

	// �I�u�W�F�N�g�̒��_�o�b�t�@�𐶐�
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_EFFECT, D3DUSAGE_WRITEONLY, FVF_VERTEX_2D, D3DPOOL_MANAGED, &m_pVtxBuffEffect, NULL);

	// ���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
	m_pVtxBuffEffect->Lock(0, 0, (void**)&pVtx, 0);

	// ���_���̐ݒ�
	for (nCnt = 0; nCnt < MAX_EFFECT; nCnt++)
	{
		// ���_�̐ݒ�
		pVtx[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;

		pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		// �e�N�X�`�����W�̐ݒ�
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		pVtx += 4;
	}
	// ���_�f�[�^���A�����b�N
	m_pVtxBuffEffect->Unlock();
}

//=========================================================================
// �G�t�F�N�g�̐ݒu
//=========================================================================
void CEffect::SetEffect(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXCOLOR col, int nLife)
{
	VERTEX_2D *pVtx;
	int nCnt;

	// ���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
	m_pVtxBuffEffect->Lock(0, 0, (void**)&pVtx, 0);

	for (nCnt = 0; nCnt < MAX_EFFECT; nCnt++)
	{
		if (!m_aEffect[nCnt].bUse)
		{
			m_aEffect[nCnt].pos = pos;
			m_aEffect[nCnt].col = col;
			m_aEffect[nCnt].nLife = nLife;
			m_aEffect[nCnt].fRadius = 40.0f;

			// ���_�̐ݒ�
			pVtx[0].pos = D3DXVECTOR3(m_aEffect[nCnt].pos.x - m_aEffect[nCnt].fRadius, m_aEffect[nCnt].pos.y - m_aEffect[nCnt].fRadius, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(m_aEffect[nCnt].pos.x + m_aEffect[nCnt].fRadius, m_aEffect[nCnt].pos.y - m_aEffect[nCnt].fRadius, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(m_aEffect[nCnt].pos.x - m_aEffect[nCnt].fRadius, m_aEffect[nCnt].pos.y + m_aEffect[nCnt].fRadius, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(m_aEffect[nCnt].pos.x + m_aEffect[nCnt].fRadius, m_aEffect[nCnt].pos.y + m_aEffect[nCnt].fRadius, 0.0f);

			// ���_�J���[�̐ݒ�
			pVtx[0].col = m_aEffect[nCnt].col;
			pVtx[1].col = m_aEffect[nCnt].col;
			pVtx[2].col = m_aEffect[nCnt].col;
			pVtx[3].col = m_aEffect[nCnt].col;

			m_aEffect[nCnt].bUse = true;

			break;
		}
		pVtx += 4;
	}
	// ���_�f�[�^���A�����b�N
	m_pVtxBuffEffect->Unlock();
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CEffect::~CEffect()
{

}
