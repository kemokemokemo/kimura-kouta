//====================================================================================================
//
// マネージャー (manager.cpp)
// Author (Kimura kouta)
//
//====================================================================================================
#include "manager.h"
#include "Scene.h"
#include "renderer.h"
#include "keybord.h"
#include "Title.h"
#include "Game.h"
#include "Result.h"
#include "bg.h"
#include "sound.h"
#include "rankbg.h"
#include "RankingAll.h"
#include "save.h"
#include "road.h"
#include "Score.h"
#include "animation.h"
#include "Gameover.h"
#include "tutorial.h"
#include "tutorial2.h"

//====================================================================================================
// マクロ定義
//==================================================================================================== 
#define MAX_POLIGON	(2)

//====================================================================================================
// プロトタイプ宣言
//====================================================================================================

//====================================================================================================
// 変数
//====================================================================================================
CRenderer *CManager::m_pRenderer = NULL;
CKeybord *CManager::m_pKeybord = NULL;
CTitle *CManager::pTitle = NULL;
CGame *CManager::pGame = NULL;
CResult *CManager::pResult = NULL;
CSound *CManager::pSound = NULL;
CRankingAll *CManager::pRankingAll = NULL;
CRankBG *CManager::pRankBG = NULL;
CSave *CManager::pSave = NULL;
CRoad *CManager::pLoad = NULL;
CGameover *CManager::pGameover = NULL;
CTutorial *CManager::pTutorial = NULL;
CTutorial2 *CManager::pTutorial2 = NULL;
CManager::MODE CManager::m_mode = CManager::MODE_TITLE;

//====================================================================================================
// コンストラクタ
//====================================================================================================
CManager::CManager()
{

}

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CManager::Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindow)
{
	m_pRenderer = new CRenderer;
	m_pKeybord = new CKeybord;

	//初期化処理
	if (FAILED(m_pRenderer->Init(hWnd, TRUE)))
	{
		m_pRenderer->Uninit();
		return-1;
	}

	if (FAILED(m_pKeybord->Init(hInstance, hWnd)))
	{
		m_pKeybord->Uninit();
		return-1;
	}

	CBg::Load();
	CAnimation::Load();

	switch (m_mode)
	{
	case MODE_TITLE:
		pTitle->Init();
		break;

	case MODE_TUTRIAL:
		pTutorial->Init();
		break;

	case MODE_TUTRIAL2:
		pTutorial2->Init();
		break;

	case MODE_GAME:
		pGame->Init();
		break;

	case MODE_RESULT:
		pResult->Init();
		break;

	case MODE_RANKING:
		pRankingAll->Init();
		break;

	case MODE_GAMEOVER:
		pGameover->Init();
		break;
	}

	pLoad = pLoad->Create();

	pSave = pSave->Create();

	pSound->InitSound(hWnd);
	return S_OK;
}

//==================================================================================================
//終了処理
//===================================================================================================
void CManager::Uninit(void)
{
	CScene::ReleaseAll();

	//終了処理
	if (m_pRenderer != NULL)
	{
		m_pRenderer->Uninit();
		delete m_pRenderer;
		m_pRenderer = NULL;
	}

	if (m_pKeybord != NULL)
	{
		m_pKeybord->Uninit();
		delete m_pKeybord;
		m_pKeybord = NULL;
	}

	pSound->UninitSound();

	CBg::Unload();

	CAnimation::Unload();

	switch (m_mode)
	{
	case MODE_TITLE:
		pTitle->Uninit();
		break;

	case MODE_TUTRIAL:
		pTutorial->Uninit();
		break;


	case MODE_TUTRIAL2:
		pTutorial2->Uninit();
		break;

	case MODE_GAME:
		pGame->Uninit();
		break;

	case MODE_RESULT:
		pResult->Uninit();
		break;

	case MODE_RANKING:
		pRankingAll->Uninit(); 
		break;

	case MODE_GAMEOVER:
		pGameover->Uninit();
		break;
	}
}

//====================================================================================================
//更新処理
//=====================================================================================================
void CManager::Update(void)
{
	m_pRenderer->Update();

	m_pKeybord->Update();

	switch (m_mode)
	{
	case MODE_TITLE:
		pTitle->Update();
		break;

	case MODE_TUTRIAL:
		pTutorial->Update();
		break;

	case MODE_TUTRIAL2:
		pTutorial2->Update();
		break;

	case MODE_GAME:
		pGame->Update();
		pSave->SaveData(CScore::GetScore());
		pLoad->LoadData();
		break;

	case MODE_RESULT:
		pResult->Update();
		break;

	case MODE_RANKING:
		pRankingAll->Update();
		break;

	case MODE_GAMEOVER:
		pGameover->Update();
		break;
	}
}

//========================================================================================================
//描画処理
//========================================================================================================
void CManager::Draw(void)
{
	//描画処理
	m_pRenderer->Draw();

	switch (m_mode)
	{
	case MODE_TITLE:
		pTitle->Draw();
		break;

	case MODE_TUTRIAL:
		pTutorial->Draw();
		break;

	case MODE_TUTRIAL2:
		pTutorial2->Draw();
		break;

	case MODE_GAME:
		pGame->Draw();
		break;

	case MODE_RESULT:
		pResult->Draw();
		break;

	case MODE_RANKING:
		pRankingAll->Draw();
		break;

	case MODE_GAMEOVER:
		pGameover->Draw();
		break;
	}
}

//========================================================================================================
//ステージ処理
//========================================================================================================
void CManager::Stage1(void)
{
	m_nCnt++;
}

//========================================================================================================
// レンダラーの取得
//========================================================================================================
CRenderer *CManager::GetRenderer(void)
{
	return m_pRenderer;
}

//========================================================================================================
// キーボードの取得
//========================================================================================================
CKeybord *CManager::GetKeybord(void)
{
	return m_pKeybord;
}

CSound * CManager::GetSound(void)
{
	return pSound;
}

//====================================================================================================
// モードの情報
//====================================================================================================
void CManager::SetMode(MODE mode)
{
	CScene::ReleaseAll();

	switch (m_mode)
	{
	case MODE_TITLE:
		pSound->StopSound();
		pTitle->Uninit();
		delete pTitle;
		pTitle = NULL;
		break;

	case MODE_TUTRIAL:
		pSound->StopSound();
		pTutorial->Uninit();
		delete pTutorial;
		pTutorial = NULL;
		break;

	case MODE_TUTRIAL2:
		pSound->StopSound();
		pTutorial2->Uninit();
		delete pTutorial2;
		pTutorial2 = NULL;
		break;

	case MODE_GAME:
		pSound->StopSound();
		pGame->Uninit();
		delete pGame;
		pGame = NULL;
		break;

	case MODE_RESULT:
		pSound->StopSound();
		pResult->Uninit();
		delete pResult;
		pResult = NULL;
		break;

	case MODE_RANKING:
		pSound->StopSound();
		pRankingAll->Uninit();
		delete pRankingAll;
		pRankingAll = NULL;
		break;

	case MODE_GAMEOVER:
		pSound->StopSound();
		pGameover->Uninit();
		delete pGameover;
		pGameover = NULL;
		break;
	}

	m_mode = mode;

	switch (mode)
	{
	case MODE_TITLE:
		pSound->PlaySound(SOUND_LABEL_BGM000);
		pTitle = CTitle::Create();
		break;

	case MODE_TUTRIAL:
		pSound->PlaySound(SOUND_LABEL_BGM000);
		pTutorial = CTutorial::Create();
		break;

	case MODE_TUTRIAL2:
		pSound->PlaySound(SOUND_LABEL_BGM000);
		pTutorial2 = CTutorial2::Create();
		break;

	case MODE_GAME:
		pSound->PlaySound(SOUND_LABEL_BGM001);
		pGame = CGame::Create();
		break;

	case MODE_RESULT:
		pSound->PlaySound(SOUND_LABEL_BGM002);
		pResult = CResult::Create();
		break;

	case MODE_RANKING:
		pSound->PlaySound(SOUND_LABEL_BGM002);
		pRankingAll = CRankingAll::Create();
		break;

	case MODE_GAMEOVER:
		pSound->PlaySound(SOUND_LABEL_BGM002);
		pGameover = CGameover::Create();
		break;
	}
}

//====================================================================================================
// モードの取得
//====================================================================================================
CManager::MODE CManager::GetMode(void)
{
	return MODE();
}

//====================================================================================================
// デストラクタ
//====================================================================================================
CManager::~CManager()
{

}

