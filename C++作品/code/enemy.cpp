//====================================================================================================
//
// 敵処理 (enemy.cpp)
// Author (Kimura kouta)
//
//====================================================================================================
#include "enemy.h"	//インクルードファイル
#include "renderer.h"
#include "manager.h"
#include "explosion.h"
#include "player.h"
#include "Neutral.h"
#include "bullet.h"
#include "Score.h"
#include "boss.h"
#include "Game.h"
#include "gauge.h"
#include "Item.h"
#include "sound.h"

//====================================================================================================
// マクロ定義
//====================================================================================================
#define ENEMY_SIZE (100)
#define BULLETLIMIT (120)

//====================================================================================================
// プロトタイプ宣言
//====================================================================================================

//====================================================================================================
// グローバル変数
//====================================================================================================
LPDIRECT3DTEXTURE9 CEnemy::m_pTextureEnemy[MAX_TEXENEMY] = {};

//====================================================================================================
// コンストラクタ
//====================================================================================================
CEnemy::CEnemy(OBJTYPE type) : CScene2D(type)
{
	int m_move = 30;
	m_nBulletCount = BULLETLIMIT;
}

//====================================================================================================
// コンストラクタ
//====================================================================================================
CEnemy::CEnemy()
{
	m_nBulletCount = BULLETLIMIT;
	m_nLife = 0;
}

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CEnemy::Init(D3DXVECTOR3 pos, D3DXVECTOR3 move,int nLife, AIPATTERN Pattern,int nType)
{
	CScene2D::Init();

	{//初期化
		m_nBulletCount = BULLETLIMIT;
	}

	{//値の取得
		m_nLife = nLife;
		m_AiPattern = Pattern;
		m_Type = nType;
		m_EnemyState = ENEMYSTATE_NORMAL;
	}

	SetObjType(OBJTYPE_ENEMY);
	SetPos(pos);
	SetMove(move);

	return S_OK;
}

//==================================================================================================
//終了処理
//===================================================================================================
void CEnemy::Uninit(void)
{
	CScene2D::Uninit();
	this->Release();
}

//====================================================================================================
//更新処理
//=====================================================================================================
void CEnemy::Update(void)
{
	CScene2D::Update();

	//変数宣言
	float Size = ENEMY_SIZE;
	D3DXVECTOR3 PosP;

	//ポジションの取得
	m_pos = CScene2D::GetPos();
	//移動処理
	m_pos += m_move;
	//移動処理
	MoveAI();

	if (m_Type == 0)
	{
		switch (m_Enemy)
		{
		case ENEMY_RIGHT:
			SetAnim(0.5f, 0.0f, 0.5f, 10);
			break;

		case ENEMY_LEFT:
			SetAnim(0.5f, 0.5f, 1.0f, 10);
			break;
		}
		CScene2D::SetSize(Size, Size);
	}

	if (m_Type == 1)
	{
		CScene2D::SetAnim(1.0f, 0.0f, 1.0f, 10);
		CScene2D::SetSize(350, 350);
	}

	//ポジションのセット
	CScene2D::SetPos(m_pos);

	//当たり判定
	CollisionEN_PL();
	//ダメージ処理
	Damage();
	//画面外の処理
	OffScreen();
}
//========================================================================================================
// 移動処理
//========================================================================================================
void CEnemy::SetMove(D3DXVECTOR3 move)
{
	m_move = move;
}

//========================================================================================================
// 敵の動き
//========================================================================================================
void CEnemy::MoveAI(void)
{
	//変数宣言
	D3DXVECTOR3 NeutralPos;
	D3DXVECTOR3 PlayerPos;
	D3DXVECTOR3 BossMove;

	for (int nCntScene = 0; nCntScene < 256; nCntScene++)
	{
		CScene *pScene;
		pScene = CScene::GetScene(OBJTYPE_NEUTRAL, nCntScene);

		CScene *pSceneB;
		pSceneB = CScene::GetScene(OBJTYPE_BOSS, nCntScene);

		if (pScene != NULL)
		{
			CScene::OBJTYPE objtype;
			objtype = pScene->GetObjType();

			if (objtype == CScene::OBJTYPE_NEUTRAL)
			{
				NeutralPos = ((CNeutral*)pScene)->GetPos();

				//差分
				D3DXVECTOR3 fDiffpos = NeutralPos - m_pos;

				m_fDistanceX = NeutralPos.x - m_pos.x;
				m_fDistanceY = NeutralPos.y - m_pos.y;

				//距離
				 m_fDistance = sqrtf(fDiffpos.y * fDiffpos.y + fDiffpos.x * fDiffpos.x);


			}

			if (objtype == CScene::OBJTYPE_BOSS)
			{
				BossMove = ((CBoss*)pSceneB)->GetPos();

				if (m_Type == 1)
				{
					m_pos = BossMove;
				}
			}
		}
	}

	switch (m_AiPattern)
	{
	case AIPATTERN_1:
		
		if (m_fDistance <= 500)
		{
			m_move.x = (float)cos(atan2(m_fDistanceY, m_fDistanceX)) * 3.5f;
			m_move.y = (float)sin(atan2(m_fDistanceY, m_fDistanceX)) * 3.5f;
		}
		break;

	case AIPATTERN_2:
		m_move.x -= 0.01f;
		m_move.y += 0.01f;
		break;
	case AIPATTERN_3:
		m_move.y += 0.01f;
		break;

	case AIPATTERN_4:

		for (int nCntScene = 0; nCntScene < 256; nCntScene++)
		{
			CScene *pSceneP;

			pSceneP = CScene::GetScene(OBJTYPE_PLAYER, nCntScene);

			if (pSceneP != NULL)
			{
				CScene::OBJTYPE objtype;
				objtype = pSceneP->GetObjType();

				if (objtype == CScene::OBJTYPE_PLAYER)
				{
					PlayerPos = ((CPlayer*)pSceneP)->GetPos();

					//差分
					D3DXVECTOR3 fDiffpos = PlayerPos - m_pos;

					float fDistanceX = PlayerPos.x - m_pos.x;
					float fDistanceY = PlayerPos.y - m_pos.y;

					//距離
					float fDistance = sqrtf(fDiffpos.y * fDiffpos.y + fDiffpos.x * fDiffpos.x);

					m_move.x = (float)cos(atan2(fDistanceY, fDistanceX)) * 3;
					m_move.y = (float)sin(atan2(fDistanceY, fDistanceX)) * 3;
					
				}
			}
		}

		break;

	case AIPATTERN_5:
		break;
	}
	if (m_move.x <= 0)
	{
		m_Enemy = ENEMY_LEFT;
	}
	else if (m_move.x >= 0)
	{
		m_Enemy = ENEMY_RIGHT;
	}


}

//========================================================================================================
// 当たり判定
//========================================================================================================
void CEnemy::CollisionEN_PL()
{
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

			CScene2D::MODESTATE mode;
			mode = GetModeState();

			if (objtype == CScene::OBJTYPE_PLAYER)
			{
				PosP = ((CPlayer*)pScene)->GetPos();
				//円の当たり判定
				if ((m_pos.x - PosP.x) * (m_pos.x - PosP.x) + (m_pos.y - PosP.y) * (m_pos.y - PosP.y)
					<= (fRadiusP + fRadiusE) * (fRadiusP + fRadiusE))
				{
					//プレイヤーの消去
					((CPlayer*)pScene)->PlayerDamage(1);
				}
			}
		}
	}
}

//====================================================================================================
// プレイヤーのダメージ処理
//=====================================================================================================
void CEnemy::EnemyDamage(int nDamage)
{
	m_nLife -= nDamage;

	if (m_nLife != 0)
	{
		if (m_EnemyState == ENEMYSTATE_NORMAL)
		{
			m_EnemyState = ENEMYSTATE_DAMAGE;
			m_EnemyStateCount = 180;
		}
	}
	else
	{
		if (m_Type == 0)
		{
			//アイテム生成
			CItem *pItem = CItem::Create();
			pItem->SetPos(m_pos);
			pItem->SetMove(D3DXVECTOR3(0.0f, 1.0f, 0.0f));

			//爆発の生成
			CExplosion *pExplosion = CExplosion::Create();
			pExplosion->SetPos(m_pos);
		}
			CSound *pSound = CManager::GetSound();
			pSound->PlaySound(SOUND_LABEL_SE_EXPLOSION);
		
		CNumber *pNumber;
		pNumber = CScore::GetaScore();

		//スコア加算
		((CScore*)pNumber)->AddScore(3000);

		//敵の開放
		Release();
	}
}

//====================================================================================================
// ダメージ処理
//=====================================================================================================
void CEnemy::Damage(void)
{
	if (m_EnemyState == ENEMYSTATE_DAMAGE)
	{
		m_EnemyStateCount--;

		//点滅処理
		if (m_EnemyStateCount >= 150)
		{
			SetColor(D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f));
		}
		else if (m_EnemyStateCount >= 120)
		{
			SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
		}
		else if (m_EnemyStateCount >= 90)
		{
			SetColor(D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f));
		}
		else if (m_EnemyStateCount >= 60)
		{
			SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
		}
		else if (m_EnemyStateCount >= 30)
		{
			SetColor(D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f));
		}

		if (m_EnemyStateCount <= 0)
		{
			m_EnemyState = ENEMYSTATE_NORMAL;
		}
	}
	else
	{
		SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	}
}
int CEnemy::GetType(void)
{
	return m_Type;
}
//========================================================================================================
// 描画処理
//========================================================================================================
CEnemy *CEnemy::Create(D3DXVECTOR3 pos,D3DXVECTOR3 move, int nLife, AIPATTERN Pattern,int nType)
{
	CEnemy *pEnemy;

	pEnemy = new CEnemy(OBJTYPE_ENEMY);

	pEnemy->BindTexture(m_pTextureEnemy[nType]);

	pEnemy->Init(pos, move, nLife, Pattern, nType);

	//pEnemy->SetInitTex(0.5f, 1.0f);

	return pEnemy;
}

//========================================================================================================
// テクスチャの読み込み
//========================================================================================================
HRESULT CEnemy::Load(void)
{
	CRenderer *pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(
		pDevice,
		TEXTUER_004,
		&m_pTextureEnemy[0]);

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(
		pDevice,
		TEXTUER_025,
		&m_pTextureEnemy[1]);

	return S_OK;
}

//========================================================================================================
// テクスチャの破棄
//========================================================================================================
void CEnemy::Unload(void)
{
	for (int nCnt =0; nCnt < MAX_TEXENEMY; nCnt++)
	{
		// 頂点バッファの開放
		if (m_pTextureEnemy[nCnt] != NULL)
		{
			m_pTextureEnemy[nCnt]->Release();
			m_pTextureEnemy[nCnt] = NULL;
		}
	}
}

//========================================================================================================
// エネミーの処理
//========================================================================================================
D3DXVECTOR3 CEnemy::GetEPos(void)
{
	return m_pos;
}

//========================================================================================================
// エネミーの処理
//========================================================================================================
D3DXVECTOR3 CEnemy::GetEMove(void)
{
	return m_move;
}

//========================================================================================================
// エネミーの処理
//========================================================================================================
int CEnemy::GetELife(void)
{
	return m_nLife;
}

//========================================================================================================
// 画面外の処理
//========================================================================================================
void CEnemy::OffScreen(void)
{
	if (m_pos.x >= 1580 || m_pos.x <= -300 || m_pos.y <= -300 || m_pos.y >= 1020)
	{
		Release();
	}
}


//========================================================================================================
// 描画処理
//========================================================================================================
void CEnemy::Draw(void)
{
	CScene2D::Draw();
}

//====================================================================================================
// デストラクタ
//=====================================================================================================
CEnemy::~CEnemy()
{

}