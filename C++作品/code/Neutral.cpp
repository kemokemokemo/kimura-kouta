//====================================================================================================
//
// �������� (Neutral.cpp)
// Author (Kimura kouta)
//
//====================================================================================================
#include "neutral.h"	//�C���N���[�h�t�@�C��
#include "renderer.h"
#include "manager.h"
#include "explosion.h"
#include "player.h"
#include "enemy.h"
#include "animation.h"
#include "Score.h"
#include "Game.h"

//====================================================================================================
// �}�N����`
//====================================================================================================
#define ENEMY_SIZE (100)

//====================================================================================================
// �v���g�^�C�v�錾
//====================================================================================================

//====================================================================================================
// �O���[�o���ϐ�
//====================================================================================================
LPDIRECT3DTEXTURE9 CNeutral::m_pTextureNeutral[MAX_TEXNEUTRAL] = {};

//====================================================================================================
// �R���X�g���N�^
//====================================================================================================
CNeutral::CNeutral(OBJTYPE type) : CScene2D(type)
{
	int m_move = 0;
}

//=============================================================================
// ����������
//=============================================================================
HRESULT CNeutral::Init(D3DXVECTOR3 pos, D3DXVECTOR3 move, TYPE Type)
{
	CScene2D::Init();
	m_Neutral = NEUTRAL_RIGHT;
	m_Type = Type;
	SetPos(pos);
	SetMove(move);
	return S_OK;
}

//==================================================================================================
//�I������
//===================================================================================================
void CNeutral::Uninit(void)
{
	CScene2D::Uninit();
	this->Release();
}

//====================================================================================================
//�X�V����
//=====================================================================================================
void CNeutral::Update(void)
{
	CScene2D::Update();

	//�ϐ��錾
	float Size = ENEMY_SIZE;
	m_pos = CScene2D::GetPos();

	switch (m_Type)
	{
	case TYPENEUTRAL_PATERN1:
		N_AIPATERN01();

		break;

	case TYPENEUTRAL_PATERN2:
		N_AIPATERN02();

		break;

	case TYPENEUTRAL_PATERN3:
		N_AIPATERN03();

		break;

	case TYPENEUTRAL_PATERN4:
		N_AIPATERN04();
		break;
	}

	//�ړ�����
	m_pos += m_move;

	CScene2D::SetPos(m_pos);
	CScene2D::SetSize(Size, Size);
	SetMove(m_move);

	if (m_pos.x >= 1380 || m_pos.x <= -100 || m_pos.y <= -100 || m_pos.y >= 820)
	{
		OffScreen();
	}

	//�����蔻��
	CollisionEN();
	CollisionPL();

	DirectionMove();

}

//========================================================================================================
// �ړ�����
//========================================================================================================
void CNeutral::SetMove(D3DXVECTOR3 move)
{
	m_move = move;
}

//========================================================================================================
// ��ʊO�̏���
//========================================================================================================
void CNeutral::OffScreen(void)
{
	CNumber *pNumber;
	pNumber = CScore::GetaScore();

	//�X�R�A���Z
	((CScore*)pNumber)->AddScore(20000);
	Release();
}

//========================================================================================================
// �G�̓���
//========================================================================================================
//void CNeutral::MoveAI(void)
//{
//	//�ϐ��錾
//	D3DXVECTOR3 EnemyPos;
//	D3DXVECTOR3 EnemyMove;
//
//	{//�����̌����Ă������
//		if (m_move.x <= 0)
//		{
//			m_Neutral = NEUTRAL_LEFT;
//		}
//		else if (m_move.x >= 0)
//		{
//			m_Neutral = NEUTRAL_RIGHT;
//		}
//	}
//
//	for (int nCntScene = 0; nCntScene < 256; nCntScene++)
//	{
//		CScene *pScene;
//		pScene = CScene::GetScene(OBJTYPE_ENEMY, nCntScene);
//
//		if (pScene != NULL)
//		{
//			CScene::OBJTYPE objtype;
//			objtype = pScene->GetObjType();
//
//			if (objtype == CScene::OBJTYPE_ENEMY)
//			{
//
//				EnemyPos = ((CEnemy*)pScene)->GetPos();
//				EnemyMove = ((CEnemy*)pScene)->GetEMove();
//
//				//����
//				D3DXVECTOR3 fDiffpos = EnemyPos - m_pos;
//
//				float fDistanceX = EnemyPos.x - m_pos.x;
//				float fDistanceY = EnemyPos.y - m_pos.y;
//
//				//����
//				float fDistance = sqrtf(fDiffpos.y * fDiffpos.y + fDiffpos.x * fDiffpos.x);
//
//				if (fDistance <= 500)
//				{
//				//m_move.x = 4;
//				//m_move.y = EnemyMove.y;
//				}
//			}
//		}
//	}
//
//}

//========================================================================================================
// �`�揈��
//========================================================================================================
CNeutral *CNeutral::Create(D3DXVECTOR3 pos,D3DXVECTOR3 move, TYPE Type)
{
	CNeutral *pNeutral;

	pNeutral = new CNeutral(OBJTYPE_NEUTRAL);

	pNeutral->BindTexture(m_pTextureNeutral[0]);

	pNeutral->Init(pos,move, Type);

	pNeutral->SetInitTex(0.5f, 1.0f);

	return pNeutral;
}

//========================================================================================================
// �e�N�X�`���̓ǂݍ���
//========================================================================================================
HRESULT CNeutral::Load(void)
{
	CRenderer *pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(
		pDevice,
		TEXTUER_008,
		&m_pTextureNeutral[0]);

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(
		pDevice,
		TEXTUER_020,
		&m_pTextureNeutral[1]);

	return S_OK;
}
//========================================================================================================
// �e�N�X�`���̔j��
//========================================================================================================
void CNeutral::Unload(void)
{
	for (int nCnt =0; nCnt < MAX_TEXENEMY; nCnt++)
	{
		// ���_�o�b�t�@�̊J��
		if (m_pTextureNeutral[nCnt] != NULL)
		{
			m_pTextureNeutral[nCnt]->Release();
			m_pTextureNeutral[nCnt] = NULL;
		}
	}
}

//========================================================================================================
// �����蔻��
//========================================================================================================
void CNeutral::CollisionEN(void)
{
	//�G�̎擾
	//CEnemy *pEnemy = CGame::GetEnemy();

	D3DXVECTOR3 PosE;

	//���a
	float fRadiusE = 100 / 2;
	float fRadiusP = 100 / 2;

	int nCntScene;

	for (nCntScene = 0; nCntScene < 256; nCntScene++)
	{
		CScene *pScene;
		pScene = CScene::GetScene(OBJTYPE_ENEMY,nCntScene);

		if (pScene != NULL)
		{
			CScene::OBJTYPE objtype;
			objtype = pScene->GetObjType();

			if (objtype == CScene::OBJTYPE_ENEMY)
			{
				PosE = ((CEnemy*)pScene)->GetEPos();

				//�~�̓����蔻��
				if ((m_pos.x - PosE.x) * (m_pos.x - PosE.x) + (m_pos.y - PosE.y) * (m_pos.y - PosE.y) <= (fRadiusP + fRadiusE) * (fRadiusP + fRadiusE))
				{
					CExplosion *pExplosion= CExplosion::Create();

					pExplosion->SetPos(m_pos);

					Release();
				}
			}
		}
	}
}

//========================================================================================================
// �����蔻��
//========================================================================================================
void CNeutral::CollisionPL(void)
{
	//�G�̎擾
	//CPlayer *pPlayer = CGame::GetPlayer();

	//�G�̎擾
	//CScore *pScore = CGame::GetScore();

	D3DXVECTOR3 PosP;

	//���a
	float fRadiusE = 100 / 2;
	float fRadiusP = 100 / 2;

	int nCntScene;

	for (nCntScene = 0; nCntScene < 256; nCntScene++)
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

				//�~�̓����蔻��
				if ((m_pos.x - PosP.x) * (m_pos.x - PosP.x) + (m_pos.y - PosP.y) * (m_pos.y - PosP.y) <= (fRadiusP + fRadiusE) * (fRadiusP + fRadiusE))
				{
					//CAnimation *pAnimation = CAnimation::Create(CAnimation::ANIMATION_ENEMY,40);

					//pAnimation->SetPos(m_pos);

					//pScore->AddScore(10000);

					//Release();
				}
			}
		}
	}
}

//========================================================================================================
// �����̌����Ă������
//========================================================================================================
void CNeutral::DirectionMove(void)
{
	{//�����̌����Ă������
		switch (m_Neutral)
		{
		case NEUTRAL_RIGHT:
			SetAnim(0.5f, 0.0f, 0.5f, 10);
			break;

		case NEUTRAL_LEFT:
			SetAnim(0.5f, 0.5f, 1.0f, 10);
			break;
		}

		if (m_move.x <= 0)
		{
			m_Neutral = NEUTRAL_LEFT;
		}
		else if (m_move.x >= 0)
		{
			m_Neutral = NEUTRAL_RIGHT;
		}
	}
}

//========================================================================================================
// AI�̃p�^�[��
//========================================================================================================
void CNeutral::N_AIPATERN01(void)
{
	if (m_pos.x >= 900)
	{
		m_move.x *= -1;
	}
}

//========================================================================================================
// AI�̃p�^�[��
//========================================================================================================
void CNeutral::N_AIPATERN02(void)
{
	if (m_pos.x <= 300)
	{
		m_move.x *= -1;
	}
}

//========================================================================================================
// AI�̃p�^�[��
//========================================================================================================
void CNeutral::N_AIPATERN03(void)
{
}

//========================================================================================================
// AI�̃p�^�[��
//========================================================================================================
void CNeutral::N_AIPATERN04(void)
{
}
//========================================================================================================
// �`�揈��
//========================================================================================================
void CNeutral::Draw(void)
{
	CScene2D::Draw();
}

//========================================================================================================
// �G�l�~�[�̏���
//========================================================================================================
D3DXVECTOR3 CNeutral::GetNPos(void)
{
	return m_pos;
}

//====================================================================================================
// �f�X�g���N�^
//=====================================================================================================
CNeutral::~CNeutral()
{

}