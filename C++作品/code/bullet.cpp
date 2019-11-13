//====================================================================================================
//
// 弾処理 (bullet.cpp)
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
// マクロ定義
//====================================================================================================
#define BULLET_TEX "DATA/TEX/Bullet002.png"
#define BULLET_TEX2 "DATA/TEX/bossBullet.png"				//読み込むテクスチャファイル名
#define BULLET_SIZE (40)
#define MAX_LIFE (40)

//====================================================================================================
// プロトタイプ宣言
//====================================================================================================

//====================================================================================================
// グローバル変数
//====================================================================================================
LPDIRECT3DTEXTURE9 CBullet::m_pTextureBullet[MAX_TEXBULLET] = {};

//====================================================================================================
// コンストラクタ
//====================================================================================================
CBullet::CBullet(OBJTYPE type) : CScene2D(type)
{
	m_move = D3DXVECTOR3(0.0f,0.0f,0.0f);
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_nLife = 0;
}

//====================================================================================================
// コンストラクタ
//====================================================================================================
CBullet::CBullet()
{

}

//=============================================================================
// 初期化処理
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
//終了処理
//===================================================================================================
void CBullet::Uninit(void)
{
	CScene2D::Uninit();
}

//====================================================================================================
//更新処理
//=====================================================================================================
void CBullet::Update(void)
{
	CScene2D::Update();

	float Size = BULLET_SIZE;

	//ポジションの取得
	m_pos = CScene2D::GetPos();

	//移動処理
	m_pos += m_move;

	//ライフのカウント
	m_nLife--;

	{//ライフの処理
		if (m_nLife < 0)
		{
			//爆発の生成
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

	{//当たり判定
		EnemyCollision();
		PlayerCollision();
		NeutralCollision();
		BossCollision();
	}
}

//========================================================================================================
// 移動処理
//========================================================================================================
void CBullet::SetMove(D3DXVECTOR3 move)
{
	m_move = move;
}

//========================================================================================================
// 体力の取得
//========================================================================================================
int CBullet::GetLife()
{
	return m_nLife;
}

//========================================================================================================
// 描画処理
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
// テクスチャの読み込み
//========================================================================================================
HRESULT CBullet::Load(void)
{
	CRenderer *pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(
		pDevice,
		BULLET_TEX,
		&m_pTextureBullet[0]);

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(
		pDevice,
		BULLET_TEX2,
		&m_pTextureBullet[1]);

	return S_OK;
}
//========================================================================================================
// 敵と弾の当たり判定
//========================================================================================================
void CBullet::EnemyCollision()
{
	//敵の取得
	D3DXVECTOR3 PosE;

	int EType;

	//半径
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
						//円の当たり判定
						if ((m_pos.x - PosE.x) * (m_pos.x - PosE.x) + (m_pos.y - PosE.y) * (m_pos.y - PosE.y) <= (fRadiusP + fRadiusE1) * (fRadiusP + fRadiusE1))
						{
							//敵の消去
							((CEnemy*)pScene)->EnemyDamage(1);

							Release();
						}
					}
					if (EType == 1)
					{
						//円の当たり判定
						if ((m_pos.x - PosE.x) * (m_pos.x - PosE.x) + (m_pos.y - PosE.y) * (m_pos.y - PosE.y) <= (fRadiusP + fRadiusE2) * (fRadiusP + fRadiusE2))
						{
							//敵の消去
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
// 弾とプレイヤーの当たり判定
//========================================================================================================
void CBullet::PlayerCollision()
{
	//変数宣言
	D3DXVECTOR3 PosP;
	//半径
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
					//円の当たり判定
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
// 味方と弾の当たり判定
//========================================================================================================
void CBullet::NeutralCollision()
{
	//半径
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

				//円の当たり判定
				if ((m_pos.x - PosN.x) * (m_pos.x - PosN.x) + (m_pos.y - PosN.y) * (m_pos.y - PosN.y) <= (fRadiusP + fRadiusE) * (fRadiusP + fRadiusE))
				{
					CAnimation::Create(PosN,CAnimation::ANIMATION_PLAYER,40);

					CNumber *pNumber;
					pNumber = CScore::GetaScore();

					//スコア加算
					((CScore*)pNumber)->AddScore(-1000);

					//敵の消去
					pScene->Release();

					Release();
				}
			}
		}
	}
}

//========================================================================================================
// 弾とプレイヤーの当たり判定
//========================================================================================================
void CBullet::BossCollision()
{
	D3DXVECTOR3 PosP;

	//半径
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
					//円の当たり判定
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
// テクスチャの破棄
//========================================================================================================
void CBullet::Unload(void)
{
	for (int nCnt =0; nCnt < MAX_TEXBULLET; nCnt++)
	{
		// 頂点バッファの開放
		if (m_pTextureBullet[nCnt] != NULL)
		{
			m_pTextureBullet[nCnt]->Release();
			m_pTextureBullet[nCnt] = NULL;
		}
	}
}

//========================================================================================================
// バレットタイプ処理
//========================================================================================================
void CBullet::BulletType(BULLETTYPE BulletType)
{
	m_BulletType = BulletType;
}

//========================================================================================================
// 描画処理
//========================================================================================================
void CBullet::Draw(void)
{
	CScene2D::Draw();
}

//====================================================================================================
// デストラクタ
//=====================================================================================================
CBullet::~CBullet()
{

}