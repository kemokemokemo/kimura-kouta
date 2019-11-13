//====================================================================================================
//
// �e���� (bullet.cpp)
// Author (Kimura kouta)
//
//====================================================================================================
#include "bullet.h"
#include "renderer.h"
#include "manager.h"
#include "explosion.h"
#include "enemy.h"
#include "effect.h"
#include "Score.h"
#include "Neutral.h"
#include "animation.h"
#include "boss.h"
#include "Item.h"
#include "Game.h"
#include "player.h"

//====================================================================================================
// �}�N����`
//====================================================================================================
#define BULLET_TEX "DATA/TEX/Bullet002.png"
#define BULLET_TEX2 "DATA/TEX/bossBullet.png"				//�ǂݍ��ރe�N�X�`���t�@�C����
#define BULLET_SIZE (40)
#define MAX_LIFE (40)

//====================================================================================================
// �v���g�^�C�v�錾
//====================================================================================================

//====================================================================================================
// �O���[�o���ϐ�
//====================================================================================================
LPDIRECT3DTEXTURE9 CBullet::m_pTextureBullet[MAX_TEXBULLET] = {};

//====================================================================================================
// �R���X�g���N�^
//====================================================================================================
CBullet::CBullet(OBJTYPE type) : CScene2D(type)
{
	m_move = D3DXVECTOR3(0.0f,0.0f,0.0f);
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_nLife = 0;
}

//====================================================================================================
// �R���X�g���N�^
//====================================================================================================
CBullet::CBullet()
{

}

//=============================================================================
// ����������
//=============================================================================
HRESULT CBullet::Init(D3DXVECTOR3 pos, D3DXVECTOR3 move, BULLETTEX BulletTex, int nLife)
{
	CScene2D::Init();

	m_nLife = nLife;
	m_BulletTex = BulletTex;

	SetPos(pos);
	SetMove(move);


	return S_OK;
}

//==================================================================================================
//�I������
//===================================================================================================
void CBullet::Uninit(void)
{
	CScene2D::Uninit();
}

//====================================================================================================
//�X�V����
//=====================================================================================================
void CBullet::Update(void)
{
	CScene2D::Update();

	float Size = BULLET_SIZE;

	//�|�W�V�����̎擾
	m_pos = CScene2D::GetPos();

	//�ړ�����
	m_pos += m_move;

	//���C�t�̃J�E���g
	m_nLife--;

	{//���C�t�̏���
		if (m_nLife < 0)
		{
			//�����̐���
			CExplosion *pExplosion = CExplosion::Create();
			pExplosion->SetPos(m_pos);
			Release();
		}
	}

	switch (m_BulletTex)
	{
	case BULLETTEX_PLAYER:
		CScene2D::SetSize(120, 120);
		CEffect::SetEffect(D3DXVECTOR3(m_pos.x + 50, m_pos.y, m_pos.z), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f), 8);
		break;

	case BULLETTEX_BOSS_NORMAL:
		CScene2D::SetSize(Size, Size);
		CEffect::SetEffect(D3DXVECTOR3(m_pos.x + 30, m_pos.y + 10, m_pos.z), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f), 8);
		break;
	}

	CScene2D::SetPos(m_pos);

	{//�����蔻��
		EnemyCollision();
		PlayerCollision();
		NeutralCollision();
		BossCollision();
	}
}

//========================================================================================================
// �ړ�����
//========================================================================================================
void CBullet::SetMove(D3DXVECTOR3 move)
{
	m_move = move;
}

//========================================================================================================
// �̗͂̎擾
//========================================================================================================
int CBullet::GetLife()
{
	return m_nLife;
}

//========================================================================================================
// �`�揈��
//========================================================================================================
CBullet *CBullet::Create(D3DXVECTOR3 pos, D3DXVECTOR3 move,BULLETTYPE BulletType, BULLETTEX BulletTex,int nLife)
{
	CBullet *pBullet;

	pBullet = new CBullet(OBJTYPE_BULLET);

	pBullet->BindTexture(m_pTextureBullet[BulletTex]);

	pBullet->Init(pos,move, BulletTex,nLife);

	pBullet->BulletType(BulletType);

	return pBullet;
}

//========================================================================================================
// �e�N�X�`���̓ǂݍ���
//========================================================================================================
HRESULT CBullet::Load(void)
{
	CRenderer *pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(
		pDevice,
		BULLET_TEX,
		&m_pTextureBullet[0]);

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(
		pDevice,
		BULLET_TEX2,
		&m_pTextureBullet[1]);

	return S_OK;
}
//========================================================================================================
// �G�ƒe�̓����蔻��
//========================================================================================================
void CBullet::EnemyCollision()
{
	//�G�̎擾
	D3DXVECTOR3 PosE;

	int EType;

	//���a
	float fRadiusE1 = 100 / 2;
	float fRadiusE2 = 600 / 2;
	float fRadiusP = BULLET_SIZE / 2;

	for (int nCntScene = 0; nCntScene < 256; nCntScene++)
	{
		CScene *pScene;
		pScene = CScene::GetScene(OBJTYPE_ENEMY, nCntScene);

		CNumber *pNumber;
		pNumber = CScore::GetaScore();

		if (pScene != NULL)
		{
			CScene::OBJTYPE objtype;
			objtype = pScene->GetObjType();

			if (objtype == CScene::OBJTYPE_ENEMY)
			{

				PosE = ((CEnemy*)pScene)->GetEPos();
				EType = ((CEnemy*)pScene)->GetType();

				if (m_BulletType == BULLETTYPE_PLAYER)
				{
					if (EType == 0)
					{
						//�~�̓����蔻��
						if ((m_pos.x - PosE.x) * (m_pos.x - PosE.x) + (m_pos.y - PosE.y) * (m_pos.y - PosE.y) <= (fRadiusP + fRadiusE1) * (fRadiusP + fRadiusE1))
						{
							//�G�̏���
							((CEnemy*)pScene)->EnemyDamage(1);

							Release();
						}
					}
					if (EType == 1)
					{
						//�~�̓����蔻��
						if ((m_pos.x - PosE.x) * (m_pos.x - PosE.x) + (m_pos.y - PosE.y) * (m_pos.y - PosE.y) <= (fRadiusP + fRadiusE2) * (fRadiusP + fRadiusE2))
						{
							//�G�̏���
							((CEnemy*)pScene)->EnemyDamage(1);

							Release();
						}
					}
				}
			}
		}
	}
}

//========================================================================================================
// �e�ƃv���C���[�̓����蔻��
//========================================================================================================
void CBullet::PlayerCollision()
{
	//�ϐ��錾
	D3DXVECTOR3 PosP;
	//���a
	float fRadiusE = 100 / 2;
	float fRadiusP = 20 / 2;

	for (int nCntScene = 0; nCntScene < 256; nCntScene++)
	{
		CScene *pScene;

		pScene = CScene::GetScene(OBJTYPE_PLAYER, nCntScene);

		if (pScene != NULL)
		{
			CScene::OBJTYPE objtype;
			objtype = pScene->GetObjType();

			if (objtype == CScene::OBJTYPE_PLAYER)
			{

				PosP = ((CPlayer*)pScene)->GetPlayerPos();

				if (m_BulletType == BULLETTYPE_ENEMY)
				{
					//�~�̓����蔻��
					if ((m_pos.x - PosP.x) * (m_pos.x - PosP.x) + (m_pos.y - PosP.y) * (m_pos.y - PosP.y) <= (fRadiusP + fRadiusE) * (fRadiusP + fRadiusE))
					{
						((CPlayer*)pScene)->PlayerDamage(1);
						Release();
					}
				}
			}
		}
	}
}

//========================================================================================================
// �����ƒe�̓����蔻��
//========================================================================================================
void CBullet::NeutralCollision()
{
	//���a
	float fRadiusE = 100 / 2;
	float fRadiusP = BULLET_SIZE / 2;

	D3DXVECTOR3 PosN;

	for (int nCntScene = 0; nCntScene < 256; nCntScene++)
	{
		CScene *pScene;
		pScene = CScene::GetScene(OBJTYPE_NEUTRAL, nCntScene);

		if (pScene != NULL)
		{
			CScene::OBJTYPE objtype;
			objtype = pScene->GetObjType();

			if (objtype == CScene::OBJTYPE_NEUTRAL)
			{
				PosN = ((CNeutral*)pScene)->GetNPos();

				//�~�̓����蔻��
				if ((m_pos.x - PosN.x) * (m_pos.x - PosN.x) + (m_pos.y - PosN.y) * (m_pos.y - PosN.y) <= (fRadiusP + fRadiusE) * (fRadiusP + fRadiusE))
				{
					CAnimation::Create(PosN,CAnimation::ANIMATION_PLAYER,40);

					CNumber *pNumber;
					pNumber = CScore::GetaScore();

					//�X�R�A���Z
					((CScore*)pNumber)->AddScore(-1000);

					//�G�̏���
					pScene->Release();

					Release();
				}
			}
		}
	}
}

//========================================================================================================
// �e�ƃv���C���[�̓����蔻��
//========================================================================================================
void CBullet::BossCollision()
{
	D3DXVECTOR3 PosP;

	//���a
	float fRadiusE = 200 / 2;
	float fRadiusP = BULLET_SIZE / 2;


	for (int nCntScene = 0; nCntScene < 256; nCntScene++)
	{
		CScene *pScene;

		pScene = CScene::GetScene(OBJTYPE_BOSS, nCntScene);

		if (pScene != NULL)
		{
			CScene::OBJTYPE objtype;
			objtype = pScene->GetObjType();

			if (objtype == CScene::OBJTYPE_BOSS)
			{
				PosP = ((CBoss*)pScene)->GetEPos();

				if (m_BulletType == BULLETTYPE_PLAYER)
				{
					//�~�̓����蔻��
					if ((m_pos.x - PosP.x) * (m_pos.x - PosP.x) + (m_pos.y - PosP.y) * (m_pos.y - PosP.y) <= (fRadiusP + fRadiusE) * (fRadiusP + fRadiusE))
					{
						((CBoss*)pScene)->BossDamage(1);

						Release();
					}
				}
			}
		}
	}
}

//=======================================================================================================
// �e�N�X�`���̔j��
//========================================================================================================
void CBullet::Unload(void)
{
	for (int nCnt =0; nCnt < MAX_TEXBULLET; nCnt++)
	{
		// ���_�o�b�t�@�̊J��
		if (m_pTextureBullet[nCnt] != NULL)
		{
			m_pTextureBullet[nCnt]->Release();
			m_pTextureBullet[nCnt] = NULL;
		}
	}
}

//========================================================================================================
// �o���b�g�^�C�v����
//========================================================================================================
void CBullet::BulletType(BULLETTYPE BulletType)
{
	m_BulletType = BulletType;
}

//========================================================================================================
// �`�揈��
//========================================================================================================
void CBullet::Draw(void)
{
	CScene2D::Draw();
}

//====================================================================================================
// �f�X�g���N�^
//=====================================================================================================
CBullet::~CBullet()
{

}