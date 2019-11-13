//====================================================================================================
//
// 中立処理 (Neutral.cpp)
// Author (Kimura kouta)
//
//====================================================================================================
#include "neutral.h"	//インクルードファイル
#include "renderer.h"
#include "manager.h"
#include "explosion.h"
#include "player.h"
#include "enemy.h"
#include "animation.h"
#include "Score.h"
#include "Game.h"

//====================================================================================================
// マクロ定義
//====================================================================================================
#define ENEMY_SIZE (100)

//====================================================================================================
// プロトタイプ宣言
//====================================================================================================

//====================================================================================================
// グローバル変数
//====================================================================================================
LPDIRECT3DTEXTURE9 CNeutral::m_pTextureNeutral[MAX_TEXNEUTRAL] = {};

//====================================================================================================
// コンストラクタ
//====================================================================================================
CNeutral::CNeutral(OBJTYPE type) : CScene2D(type)
{
	int m_move = 0;
}

//=============================================================================
// 初期化処理
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
//終了処理
//===================================================================================================
void CNeutral::Uninit(void)
{
	CScene2D::Uninit();
	this->Release();
}

//====================================================================================================
//更新処理
//=====================================================================================================
void CNeutral::Update(void)
{
	CScene2D::Update();

	//変数宣言
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

	//移動処理
	m_pos += m_move;

	CScene2D::SetPos(m_pos);
	CScene2D::SetSize(Size, Size);
	SetMove(m_move);

	if (m_pos.x >= 1380 || m_pos.x <= -100 || m_pos.y <= -100 || m_pos.y >= 820)
	{
		OffScreen();
	}

	//当たり判定
	CollisionEN();
	CollisionPL();

	DirectionMove();

}

//========================================================================================================
// 移動処理
//========================================================================================================
void CNeutral::SetMove(D3DXVECTOR3 move)
{
	m_move = move;
}

//========================================================================================================
// 画面外の処理
//========================================================================================================
void CNeutral::OffScreen(void)
{
	CNumber *pNumber;
	pNumber = CScore::GetaScore();

	//スコア加算
	((CScore*)pNumber)->AddScore(20000);
	Release();
}

//========================================================================================================
// 敵の動き
//========================================================================================================
//void CNeutral::MoveAI(void)
//{
//	//変数宣言
//	D3DXVECTOR3 EnemyPos;
//	D3DXVECTOR3 EnemyMove;
//
//	{//味方の向いている方向
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
//				//差分
//				D3DXVECTOR3 fDiffpos = EnemyPos - m_pos;
//
//				float fDistanceX = EnemyPos.x - m_pos.x;
//				float fDistanceY = EnemyPos.y - m_pos.y;
//
//				//距離
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
// 描画処理
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
// テクスチャの読み込み
//========================================================================================================
HRESULT CNeutral::Load(void)
{
	CRenderer *pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(
		pDevice,
		TEXTUER_008,
		&m_pTextureNeutral[0]);

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(
		pDevice,
		TEXTUER_020,
		&m_pTextureNeutral[1]);

	return S_OK;
}
//========================================================================================================
// テクスチャの破棄
//========================================================================================================
void CNeutral::Unload(void)
{
	for (int nCnt =0; nCnt < MAX_TEXENEMY; nCnt++)
	{
		// 頂点バッファの開放
		if (m_pTextureNeutral[nCnt] != NULL)
		{
			m_pTextureNeutral[nCnt]->Release();
			m_pTextureNeutral[nCnt] = NULL;
		}
	}
}

//========================================================================================================
// 当たり判定
//========================================================================================================
void CNeutral::CollisionEN(void)
{
	//敵の取得
	//CEnemy *pEnemy = CGame::GetEnemy();

	D3DXVECTOR3 PosE;

	//半径
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

				//円の当たり判定
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
// 当たり判定
//========================================================================================================
void CNeutral::CollisionPL(void)
{
	//敵の取得
	//CPlayer *pPlayer = CGame::GetPlayer();

	//敵の取得
	//CScore *pScore = CGame::GetScore();

	D3DXVECTOR3 PosP;

	//半径
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

				//円の当たり判定
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
// 味方の向いている方向
//========================================================================================================
void CNeutral::DirectionMove(void)
{
	{//味方の向いている方向
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
// AIのパターン
//========================================================================================================
void CNeutral::N_AIPATERN01(void)
{
	if (m_pos.x >= 900)
	{
		m_move.x *= -1;
	}
}

//========================================================================================================
// AIのパターン
//========================================================================================================
void CNeutral::N_AIPATERN02(void)
{
	if (m_pos.x <= 300)
	{
		m_move.x *= -1;
	}
}

//========================================================================================================
// AIのパターン
//========================================================================================================
void CNeutral::N_AIPATERN03(void)
{
}

//========================================================================================================
// AIのパターン
//========================================================================================================
void CNeutral::N_AIPATERN04(void)
{
}
//========================================================================================================
// 描画処理
//========================================================================================================
void CNeutral::Draw(void)
{
	CScene2D::Draw();
}

//========================================================================================================
// エネミーの処理
//========================================================================================================
D3DXVECTOR3 CNeutral::GetNPos(void)
{
	return m_pos;
}

//====================================================================================================
// デストラクタ
//=====================================================================================================
CNeutral::~CNeutral()
{

}