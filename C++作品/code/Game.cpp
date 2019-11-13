//====================================================================================================
//
// �Q�[������ (Game.cpp)
// Author  Kimura Kouta
//
//====================================================================================================
#include"Game.h"//�C���N���[�h�t�@�C��
#include"manager.h"
#include "Scene.h"
#include "Scene2D.h"
#include "renderer.h"
#include "keybord.h"
#include "player.h"
#include "bullet.h"
#include "explosion.h"
#include "enemy.h"
#include "bg.h"
#include "Neutral.h"
#include "Number.h"
#include "effect.h"
#include "Score.h"
#include "animation.h"
#include "time.h"
#include "LIfe.h"
#include "boss.h"
#include "Item.h"
#include "Title.h"
#include "Result.h"
#include "fade.h"
#include "save.h"
#include "road.h"
#include "gauge.h"

//====================================================================================================
// �}�N����`
//==================================================================================================== 

//=====================================================================================================
// �O���錾������
//=====================================================================================================
CScore *CGame::pScore = NULL;
CTime *CGame::pTime = NULL;
CLife *CGame::pLife = NULL;
CManager *CGame::m_pManager = NULL;
CSave *CGame::pSave = NULL;
CRoad*CGame::pLoad = NULL;

int CGame::m_nSpownCnt = NULL;

//================================================================================================
// �R���X�g���N�^
//=================================================================================================
CGame::CGame()
{

}

//================================================================================================
// �f�X�g���N�^
//=================================================================================================
CGame::~CGame()
{

}

//================================================================================================
// �w�i�̏�����
//=================================================================================================
HRESULT CGame::Init(void)
{
	m_nSpownCnt = 0;

	{//�摜�ǂݍ���
		CExplosion::Load();
		CEnemy::Load();
		CBg::Load();
		CPlayer::Load();
		CBoss::Load();
		CNeutral::Load();
		CNumber::Load();
		CEffect::Load();
		CBullet::Load();
		CLife::Load();
		CItem::Load();
		CGauge::Load();
	}

	{//�w�i�̐���
		CBg::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f), 0.005f, 0);
		CBg::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f), 0.002f, 1);
		CBg::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f), 0.003f, 2);
	}

	{//�v���C���[�̐���
		CPlayer::Create(D3DXVECTOR3(640.0f, 360.0f, 0.0f));
	}

	{//�X�R�A�̐���
		CScore::Create(0);
	}

	{//�G�t�F�N�g�̐���
		CEffect::Create();
	}

	{//�������Ԃ̐���
		pTime = CTime::Create(300);
	}

	{//HP�Q�[�W�̐���
		CGauge::Create(D3DXVECTOR3(120.0f, 50.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), CGauge::GAUGE_PLAYER);
	}

	return S_OK;
}

//================================================================================================
// �w�i�̊J������
//=================================================================================================
void CGame::Uninit(void)
{
	{//�摜�̔j��
		CExplosion::Unload();
		CPlayer::Unload();
		CBullet::Unload();
		CEnemy::Unload();
		CNeutral::Unload();
		CNumber::Unload();
		CEffect::Unload();
		CLife::Unload();
		CBoss::Unload();
		CItem::Unload();
		CGauge::Unload();
	}
}

//================================================================================================
// �w�i�̍X�V����
//=================================================================================================
void CGame::Update(void)
{
	CKeybord *pKetybord = CManager::GetKeybord();

	if (pKetybord->GetKeyboardTrigger(DIK_RETURN))
	{
		CFade::SetFade(m_pManager->MODE_RESULT);
	}

	{//�X�e�[�W�̓ǂݍ���
		stage1();
	}
}

//================================================================================================
// �w�i�̕`�揈��
//=================================================================================================
void CGame::Draw(void)
{

}

//====================================================================================================
// ���Ԃ̏��
//====================================================================================================
CTime * CGame::GetTime(void)
{
	return pTime;
}

//================================================================================================
// �^�C�g������
//================================================================================================
CGame * CGame::Create(void)
{
	CGame *pGame;

	pGame = new CGame();

	pGame->Init();

	return pGame;
}


//================================================================================================
// �X�e�[�W����
//================================================================================================
void CGame::stage1(void)
{

	m_nSpownCnt++;

	if (m_nSpownCnt == 180)
	{
		CNeutral::Create(D3DXVECTOR3(0.0f, 100.0f, 0.0f), D3DXVECTOR3(2.2f, 0.5f, 0.0f), CNeutral::TYPENEUTRAL_PATERN1);
		CNeutral::Create(D3DXVECTOR3(100.0f, 0.0f, 0.0f), D3DXVECTOR3(2.2f,0.5f, 0.0f), CNeutral::TYPENEUTRAL_PATERN1);
	}

	if (m_nSpownCnt == 580)
	{
		CEnemy::Create(D3DXVECTOR3(1180.0f, 0.0f, 0.0f),  D3DXVECTOR3(-2.2f, 0.5f, 0.0f),1, CEnemy::AIPATTERN_1,0);
		CEnemy::Create(D3DXVECTOR3(1280.0f, 100.0f, 0.0f), D3DXVECTOR3(-2.2f, 0.5f, 0.0f),1, CEnemy::AIPATTERN_1, 0);
	}

	if (m_nSpownCnt == 1000)
	{
		CNeutral::Create(D3DXVECTOR3(1280.0f, 100.0f, 0.0f), D3DXVECTOR3(-2.2f, 0.5f, 0.0f), CNeutral::TYPENEUTRAL_PATERN2);
		CNeutral::Create(D3DXVECTOR3(1180.0f, 0.0f, 0.0f), D3DXVECTOR3(-2.2f, 0.5f, 0.0f), CNeutral::TYPENEUTRAL_PATERN2);
	}

	if (m_nSpownCnt == 1460)
	{
		CEnemy::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(2.2f, 0.5f, 0.0f), 1, CEnemy::AIPATTERN_1, 0);
		CEnemy::Create(D3DXVECTOR3(100.0f, 100.0f, 0.0f), D3DXVECTOR3(2.2f, 0.5f, 0.0f), 1, CEnemy::AIPATTERN_1, 0);
	}

	//if (m_nSpownCnt == 1800)
	//{
	//	CNeutral::Create(D3DXVECTOR3(0.0f, 640.0f, 0.0f), D3DXVECTOR3(2.2f, -0.5f, 0.0f), CNeutral::TYPENEUTRAL_PATERN2);
	//	CNeutral::Create(D3DXVECTOR3(100.0f, 740.0f, 0.0f), D3DXVECTOR3(2.2f, -0.5f, 0.0f), CNeutral::TYPENEUTRAL_PATERN2);
	//}

	//if (m_nSpownCnt == 2200)
	//{
	//	CEnemy::Create(D3DXVECTOR3(0.0f, 640.0f, 0.0f), D3DXVECTOR3(2.2f, -0.5f, 0.0f), 1, CEnemy::AIPATTERN_1, 0);
	//	CEnemy::Create(D3DXVECTOR3(100.0f, 740.0f, 0.0f), D3DXVECTOR3(2.2f, -0.5f, 0.0f), 1, CEnemy::AIPATTERN_1, 0);
	//}


	if (m_nSpownCnt == 2000)
	{
		CBoss::Create(D3DXVECTOR3(550.0f, 100.0f, 0.0f), D3DXVECTOR3(0.0f, 0.5f, 0.0f));
	}

}
