//====================================================================================================
//
// ボス処理 (boss.cpp)
// Author (Kimura kouta)
//
//====================================================================================================
#include "boss.h"
#include "renderer.h"
#include "manager.h"
#include "explosion.h"
#include "player.h"
#include "Neutral.h"
#include "Score.h"
#include "Game.h"
#include "gauge.h"
#include "bullet.h"
#include "animation.h"

//====================================================================================================
// マクロ定義
//====================================================================================================
#define BOSS_SIZE (200)
#define BOSS_ANGLE	(0.125f)
#define BULLET_MOVE	(5.0f)

//====================================================================================================
// プロトタイプ宣言
//====================================================================================================

//====================================================================================================
// グローバル変数
//====================================================================================================
LPDIRECT3DTEXTURE9 CBoss::m_pTextureBoss[MAX_TEXBOSS] = {};
int CBoss::m_nLife =NULL;
D3DXVECTOR3 CBoss::m_move = D3DXVECTOR3(0.0f,0.0f,0.0f);
D3DXVECTOR3 CBoss::m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

//====================================================================================================
// コンストラクタ
//====================================================================================================
CBoss::CBoss(OBJTYPE type) : CScene2D(type)
{

}

//====================================================================================================
// コンストラクタ
//====================================================================================================
CBoss::CBoss()
{
	int m_move = 0;
}

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CBoss::Init(D3DXVECTOR3 pos, D3DXVECTOR3 move)
{
	CScene2D::Init();

	//値の初期化
	m_bBossT = false;
	m_bBossB = false;
	m_bBossM = false;
	m_nLife = 20;
	m_BossState = BOSSSTATE_DAMAGE;
	m_nBossCnt = 0;
	m_nBulletCnt = 0;
	m_nBulletCnt2 = 0;
	m_fRangeX= 0.0f;
	m_fRangeY= 0.0f;
	m_fAnglePlayer = 0.0f;
	m_fAngle = 0.0f;
	m_fAngleBoss = 90.0f;

	m_BossPattern = BOSSPATTERN_03;

	CGauge::Create(pos, move, CGauge::GAUGE_BOSS);

	SetPos(pos);

	SetMove(move);

	SetObjType(OBJTYPE_BOSS);

	return S_OK;
}

//==================================================================================================
//終了処理
//===================================================================================================
void CBoss::Uninit(void)
{
	CScene2D::Uninit();
}

//====================================================================================================
//更新処理
//=====================================================================================================
void CBoss::Update(void)
{
	CScene2D::Update();

	m_pos = CScene2D::GetPos();

	//移動処理
	m_pos += m_move;

	//変数宣言
	float Size = BOSS_SIZE;

	SetAnim(0.5f, 0.0f, 1.0f, 10);

	CollisionB_PL();
	
	MoveAI();

	CScene2D::SetPos(m_pos);
	SetMove(m_move);
	CScene2D::SetSize(Size, Size);
}

//========================================================================================================
// 移動処理
//========================================================================================================
void CBoss::SetMove(D3DXVECTOR3 move)
{
	m_move = move;
}

//========================================================================================================
// 当たり判定
//========================================================================================================
void CBoss::CollisionB_PL()
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

//========================================================================================================
// 敵の動き
//========================================================================================================
void CBoss::MoveAI(void)
{
	D3DXVECTOR3 PosP;

	//プレイヤーの位置の取得
	for (int nCntScene = 0; nCntScene < 256; nCntScene++)
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

				//差分
				D3DXVECTOR3 fDiffpos = PosP - m_pos;

				m_fRangeX = PosP.x - m_pos.x;							// 敵とプレイヤーの距離X
				m_fRangeY = PosP.y - m_pos.y;							// 敵とプレイヤーの距離Y
				m_fAnglePlayer = float(atan2(m_fRangeX, m_fRangeY));	// プレイヤーへの弾の発射角度
				m_fAngle = 0.0f;										// 弾の発射角度
			}
		}
	}


	{//ボスの登場
		if (m_pos.y >= 200)
		{
			m_move.y = 0;
			m_bBossT = true;
			m_BossState = BOSSSTATE_NORMAL;
		}
	}

	{//バリア発動
		if (m_bBossB == false)
		{
			CBoss::BossAI05();
		}
	}

	{//ボスの行動パターン
		if (m_bBossT == true)
		{
			switch (m_BossPattern)
			{
			case BOSSPATTERN_01:
				CBoss::BossAI01();
				break;

			case BOSSPATTERN_02:
				CBoss::BossAI02();

				break;

			case BOSSPATTERN_03:
				CBoss::BossAI03();
				break;

			case BOSSPATTERN_04:
				CBoss::BossAI04();
				break;
			}
		}
	}
}

//========================================================================================================
// 描画処理
//========================================================================================================
CBoss *CBoss::Create(D3DXVECTOR3 pos, D3DXVECTOR3 move)
{
	CBoss *pBoss;

	pBoss = new CBoss(OBJTYPE_BOSS);

	pBoss->BindTexture(m_pTextureBoss[0]);

	pBoss->Init(pos, move);

	pBoss->SetInitTex(0.5f, 1.0f);

	return pBoss;
}

//========================================================================================================
// テクスチャの読み込み
//========================================================================================================
HRESULT CBoss::Load(void)
{
	CRenderer *pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(
		pDevice,
		TEXTUER_018,
		&m_pTextureBoss[0]);

	return S_OK;
}

//========================================================================================================
// テクスチャの破棄
//========================================================================================================
void CBoss::Unload(void)
{
	for (int nCnt =0; nCnt < MAX_TEXBOSS; nCnt++)
	{
		// 頂点バッファの開放
		if (m_pTextureBoss[nCnt] != NULL)
		{
			m_pTextureBoss[nCnt]->Release();
			m_pTextureBoss[nCnt] = NULL;
		}
	}
}

//========================================================================================================
// エネミーの処理
//========================================================================================================
D3DXVECTOR3 CBoss::GetEPos(void)
{
	return m_pos;
}

//========================================================================================================
// ライフの取得
//========================================================================================================
int CBoss::GetLife(void)
{
	return m_nLife;
}

//========================================================================================================
// 移動量の取得
//========================================================================================================
D3DXVECTOR3 CBoss::GetMove()
{
	return m_move;
}

//========================================================================================================
// 描画処理
//========================================================================================================
void CBoss::Draw(void)
{
	CScene2D::Draw();
}

//====================================================================================================
// プレイヤーのダメージ処理
//=====================================================================================================
void CBoss::BossDamage(int nDamage)
{
	if (m_BossState == BOSSSTATE_NORMAL)
	{
		//ダメージ処理
		m_nLife -= nDamage;
	}

	if (m_nLife != 0)
	{

	}
	else
	{
		//爆発の生成
		CExplosion *pExplosion = CExplosion::Create();
		pExplosion->SetPos(m_pos);

		//スコアの取得
		CNumber *pNumber;
		pNumber = CScore::GetaScore();

		//スコア加算
		((CScore*)pNumber)->AddScore(30000);

		CFade::SetFade(CManager::MODE_RESULT);
		Release();
	}
}

//====================================================================================================
// ボスのAI
//=====================================================================================================
void CBoss::BossAI01()
{
	m_nBossCnt++;
	if (m_nBossCnt >= 60)
	{
		{//通常弾
			m_fAngle = D3DX_PI * BOSS_ANGLE + m_fAnglePlayer;// 弾の発射角度

			CBullet::Create(D3DXVECTOR3(m_pos.x + 80, m_pos.y + 80, 0.0f), D3DXVECTOR3(sinf(m_fAngle) * BULLET_MOVE, cosf(m_fAngle) * BULLET_MOVE, 0.0f),
				CBullet::BULLETTYPE_ENEMY, CBullet::BULLETTEX_BOSS_NORMAL, 100);


			m_fAngle = D3DX_PI * -BOSS_ANGLE + m_fAnglePlayer;// 弾の発射角度

			CBullet::Create(D3DXVECTOR3(m_pos.x + 80, m_pos.y + 80, 0.0f), D3DXVECTOR3(sinf(m_fAngle) * BULLET_MOVE, cosf(m_fAngle) * BULLET_MOVE, 0.0f),
				CBullet::BULLETTYPE_ENEMY, CBullet::BULLETTEX_BOSS_NORMAL, 100);
			m_nBossCnt = 0;

			m_BossPattern = BOSSPATTERN_02;
		}
	}
}

//====================================================================================================
// ボスのAI
//=====================================================================================================
void CBoss::BossAI02()
{
	m_nBossCnt++;
	if (m_nBossCnt >= 120)
	{
		{//散弾
			for (int i = 0; i < 10; i++)
			{
				m_fAngle = (float(rand() % 375) / 1000.0f - float(rand() % 375) / 1000.0f) + m_fAnglePlayer;

				CBullet::Create(D3DXVECTOR3(m_pos.x + 80, m_pos.y + 80, 0.0f), D3DXVECTOR3(sinf(m_fAngle) * float(rand() % 80) / 10.0f, cosf(m_fAngle) * float(rand() % 80) / 10.0f, 0.0f),
					CBullet::BULLETTYPE_ENEMY, CBullet::BULLETTEX_BOSS_NORMAL, 200);
				m_nBossCnt = 0;

			}
			m_BossPattern = BOSSPATTERN_01;
		}
	}
}

//====================================================================================================
// ボスのAI
//=====================================================================================================
void CBoss::BossAI03()
{
	m_nBossCnt++;
	if (m_nBossCnt >= 60)
	{
		if (m_bBossM == false)
		{
			m_move.x = 4.0f;
		}

		{//通常弾
			m_fAngle = D3DX_PI * BOSS_ANGLE + m_fAnglePlayer;// 弾の発射角度

			CBullet::Create(D3DXVECTOR3(m_pos.x + 80, m_pos.y + 80, 0.0f), D3DXVECTOR3(sinf(m_fAngle) * BULLET_MOVE, cosf(m_fAngle) * BULLET_MOVE, 0.0f),
				CBullet::BULLETTYPE_ENEMY, CBullet::BULLETTEX_BOSS_NORMAL, 100);

			m_fAngle = D3DX_PI * -BOSS_ANGLE + m_fAnglePlayer;// 弾の発射角度

			CBullet::Create(D3DXVECTOR3(m_pos.x + 80, m_pos.y + 80, 0.0f), D3DXVECTOR3(sinf(m_fAngle) * BULLET_MOVE, cosf(m_fAngle) * BULLET_MOVE, 0.0f),
				CBullet::BULLETTYPE_ENEMY, CBullet::BULLETTEX_BOSS_NORMAL, 100);

			m_nBossCnt = 0;
			m_nBulletCnt2++;
		}
	}

	if (m_pos.x >= 1000)
	{
		m_bBossM = true;
		m_move.x = 0;
	}

	{//回転
		m_fRadius = m_fAngleBoss * (D3DX_PI / 180);
		m_fAdd_x = cosf(m_fRadius) * 5;
		m_fAdd_y = sinf(m_fRadius) * 5;
		m_pos.x = m_pos.x + m_fAdd_x;
		m_pos.y = m_pos.y + m_fAdd_y;
		m_fAngleBoss += 2.0f;
	}

	{//特定の値で移動値変化
		if (m_nBulletCnt2 >= 7 && m_nBulletCnt2 <= 13)
		{
			if (m_pos.x >= 1000)
			{
				m_move.x = -4.0f;
			}
			if (m_pos.x <= 250)
			{
				m_move.x = 0.0f;
			}
		}

		else if (m_nBulletCnt2 >= 14 && m_nBulletCnt2 <= 15)
		{
			if (m_pos.x <= 300)
			{
				m_move.x = 4.0f;
			}
		}

		else if (m_nBulletCnt2 >= 16)
		{
			m_nBulletCnt2 = 0;
			m_BossPattern = BOSSPATTERN_04;
		}
	}

}

//====================================================================================================
// ボスのAI
//=====================================================================================================
void CBoss::BossAI04()
{
	//カウントを進める
	m_nBulletCnt++;

	{//敵の召喚
		if (m_nBulletCnt == 120)
		{
			CEnemy::Create(m_pos, D3DXVECTOR3(0.0f, 0.0f, 0.0f), 1, CEnemy::AIPATTERN_4, 0);
		}
		else if (m_nBulletCnt == 170)
		{
			CEnemy::Create(m_pos, D3DXVECTOR3(0.0f, 0.0f, 0.0f), 1, CEnemy::AIPATTERN_4, 0);
		}
		else if (m_nBulletCnt == 215)
		{
			CEnemy::Create(m_pos, D3DXVECTOR3(0.0f, 0.0f, 0.0f), 1, CEnemy::AIPATTERN_4, 0);
		}
	}

	if (m_nBulletCnt <= 220)
	{
		{//回転
			m_fRadius = m_fAngleBoss * (D3DX_PI / 180);
			m_fAdd_x = cosf(m_fRadius) * 5;
			m_fAdd_y = sinf(m_fRadius) * 5;
			m_pos.x = m_pos.x + m_fAdd_x;
			m_pos.y = m_pos.y + m_fAdd_y;
			m_fAngleBoss += 2.0f;
		}
	}

	{//ボスの移動
		if (m_pos.x >= 1000)
		{
			m_move.x = -4.0f;
		}

		if (m_pos.x <= 270)
		{
			m_move.x = 4.0f;
			m_nBulletCnt = 0;
		}
	}
}

//====================================================================================================
// ボスのバリア発動管理
//=====================================================================================================
void CBoss::BossAI05()
{
	if (m_nLife <= 11)
	{
		m_BossPattern = BOSSPATTERN_01;		// ボスのパターン変更
		m_BossState = BOSSSTATE_DAMAGE;		// ボスを無敵状態にする
		m_bBossT = false;
		m_nBossCnt++;
		m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

		if (m_pos.x <= 570)
		{
			m_pos.x += 3.0f;
		}
		if (m_pos.x >= 570)
		{
			m_pos.x -= 3.0f;
		}

		if (m_pos.y >= 200)
		{
			m_pos.y -= 3.0f;
		}

		if (m_pos.y <= 200)
		{
			m_pos.y += 3.0f;
		}

		if (m_nBossCnt >= 180)
		{
			//敵の生成
			CEnemy::Create(D3DXVECTOR3(m_pos.x - 80, m_pos.y - 80, 0.0f), m_move, 10, CEnemy::AIPATTERN_5, 1);
			m_bBossB = true;
			m_BossState = BOSSSTATE_NORMAL;
			m_bBossT = true;

		}
	}
}

//====================================================================================================
// デストラクタ
//=====================================================================================================
CBoss::~CBoss()
{

}