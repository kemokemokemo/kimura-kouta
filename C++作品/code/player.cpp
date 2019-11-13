//====================================================================================================
//
// プレイヤー処理 (player.cpp)
// Author (Kimura kouta)
//
//====================================================================================================
#include "player.h"	//インクルードファイル
#include "renderer.h"
#include "manager.h"
#include "keybord.h"
#include "bullet.h"
#include "effect.h"
#include "Explosion.h"
#include "Game.h"
#include "iostream"
#include "sound.h"

//====================================================================================================
// マクロ定義
//==================================================================================================== 
#define PLAYER_SIZE				(100)	//プレイヤーのサイズ
#define PLAYER_SPEED			(10.0f)	//プレイヤーの速さ
#define PLAYER_LIFE				(5)		//プレイヤーのHP
#define PLAYER_DAMAGETIME		(180)	//プレイヤーの無敵時間
#define BULLET_SPEED			(30.0f)	//弾の速さ

//====================================================================================================
// プロトタイプ宣言
//====================================================================================================

//====================================================================================================
// グローバル変数
//====================================================================================================
LPDIRECT3DTEXTURE9 CPlayer::m_pTexturePlayer = {};
CBullet *pBullet;
int CPlayer::m_nLife =NULL;

//====================================================================================================
// コンストラクタ
//====================================================================================================
CPlayer::CPlayer(OBJTYPE type) : CScene2D(type)
{

}

//====================================================================================================
// コンストラクタ
//====================================================================================================
CPlayer::CPlayer()
{

}

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CPlayer::Init(D3DXVECTOR3 pos)
{
	CScene2D::Init();

	SetPos(pos);

	m_nLife = PLAYER_LIFE;
	m_DeathCount = 60;
	m_PlayerState = PLAYERSTATE_NORMAL;
	BulletLimit = 0;

	SetObjType(OBJTYPE_PLAYER);

	return S_OK;
}

//==================================================================================================
//終了処理
//===================================================================================================
void CPlayer::Uninit(void)
{
	CScene2D::Uninit();
	this->Release();
}

//====================================================================================================
//更新処理
//=====================================================================================================
void CPlayer::Update(void)
{
	CScene2D::Update();

	float Size = PLAYER_SIZE;

	m_PlayerPos = CScene2D::GetPos();

	PlayerMove();

	CScene2D::SetAnim(0.5f, 0.0f, 1.0f,10);

	MoveLimit();

	CScene2D::SetSize(Size, Size);
	CScene2D::SetPos(m_PlayerPos);

	Damage();
}

//========================================================================================================
//描画処理
//========================================================================================================
CPlayer *CPlayer::Create(D3DXVECTOR3 pos)
{
	CPlayer *pPlayer;

	pPlayer = new CPlayer(OBJTYPE_PLAYER);

	pPlayer->BindTexture(m_pTexturePlayer);

	pPlayer->Init(pos);

	pPlayer->SetInitTex(0.5f, 1.0f);

	return pPlayer;
}

//========================================================================================================
//描画処理
//========================================================================================================
void CPlayer::Draw(void)
{
	CScene2D::Draw();
}

//========================================================================================================
// プレイヤーの移動処理
//========================================================================================================
void CPlayer::PlayerMove(void)
{
	CKeybord *pKetybord = CManager::GetKeybord();
	CSound *pSound = CManager::GetSound();

	if (pKetybord->GetKeyboardPress(DIK_A))
	{//  A キー操作
		if (pKetybord->GetKeyboardPress(DIK_W))
		{// 左上
			m_PlayerPos.x += sinf(-D3DX_PI*0.75f) * PLAYER_SPEED;
			m_PlayerPos.y += cosf(-D3DX_PI*0.75f) * PLAYER_SPEED;
		}
		else if (pKetybord->GetKeyboardPress(DIK_S))
		{// 右下
			m_PlayerPos.x += sinf(-D3DX_PI*0.25) * PLAYER_SPEED;
			m_PlayerPos.y += cosf(-D3DX_PI*0.25) * PLAYER_SPEED;
		}
		else
		{// 左
			m_PlayerPos.x += cosf(D3DX_PI*1.0) * PLAYER_SPEED;
		}
	}

	else if (pKetybord->GetKeyboardPress(DIK_D) )
	{//  D キー操作

		if (pKetybord->GetKeyboardPress(DIK_W))
		{// 右上
			m_PlayerPos.x += sinf(D3DX_PI*0.75f) * PLAYER_SPEED;
			m_PlayerPos.y += cosf(D3DX_PI*0.75f) * PLAYER_SPEED;
		}
		else if (pKetybord->GetKeyboardPress(DIK_S))
		{// 右下 
			m_PlayerPos.x += sinf(D3DX_PI*0.25) * PLAYER_SPEED;
			m_PlayerPos.y += cosf(D3DX_PI*0.25) * PLAYER_SPEED;
		}
		else
		{// 右
			m_PlayerPos.x += sinf(D3DX_PI*0.5) * PLAYER_SPEED;
		}
	}

	else if (pKetybord->GetKeyboardPress(DIK_S) )
	{//  S キー操作
			m_PlayerPos.y += cosf(D3DX_PI*0.0) * PLAYER_SPEED;
	}

	else if (pKetybord->GetKeyboardPress(DIK_W))
	{//  W キー操作
		m_PlayerPos.y += cosf(D3DX_PI*1.0) * PLAYER_SPEED;
	}

	BulletLimit++;

	if (BulletLimit>=10)
	{
		if (pKetybord->GetKeyboardTrigger(DIK_SPACE))
		{

			pSound->PlaySound(SOUND_LABEL_SE_SHOT);

			CBullet::Create(D3DXVECTOR3(m_PlayerPos.x - 15, m_PlayerPos.y, 0.0f),
			D3DXVECTOR3(0.0f, -BULLET_SPEED, 0.0f), CBullet::BULLETTYPE_PLAYER, CBullet::BULLETTEX_PLAYER, 20);
			BulletLimit = 0;
		}
	}
}

//========================================================================================================
// テクスチャの読み込み
//========================================================================================================
HRESULT CPlayer::Load(void)
{
	CRenderer *pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(
		pDevice,
		TEXTUER_001,
		&m_pTexturePlayer);

	return S_OK;
}

//========================================================================================================
// テクスチャの破棄
//========================================================================================================
void CPlayer::Unload(void)
{
	// 頂点バッファの開放
	if (m_pTexturePlayer != NULL)
	{
		m_pTexturePlayer->Release();
		m_pTexturePlayer = NULL;
	}
}

//========================================================================================================
// テクスチャの破棄
//========================================================================================================
CBullet * CPlayer::GetBullet(void)
{
	return pBullet;
}

//========================================================================================================
// テクスチャの破棄
//========================================================================================================
D3DXVECTOR3 CPlayer::GetPlayerPos(void)
{
	return m_PlayerPos;
}

//====================================================================================================
// プレイヤーのダメージ処理
//=====================================================================================================
void CPlayer::PlayerDamage(int nDamage)
{
	CSound *pSound = CManager::GetSound();

	if (m_PlayerState == PLAYERSTATE_NORMAL)
	{
		m_nLife -= nDamage;
		m_PlayerState = PLAYERSTATE_DAMAGE;
		m_PlayerStateCount = 60;
	}

	if (m_nLife != 0)
	{

	}
	else
	{
		CExplosion *pExplosion = CExplosion::Create();
		pExplosion->SetPos(m_PlayerPos);
		pSound->PlaySound(SOUND_LABEL_SE_EXPLOSION);
		CFade::SetFade(CManager::MODE_GAMEOVER);
		Release();
	}
}

//====================================================================================================
// ダメージ処理
//=====================================================================================================
void CPlayer::Damage(void)
{
	if (m_PlayerState == PLAYERSTATE_DAMAGE)
	{
		m_PlayerStateCount--;

		//点滅処理
		if (m_PlayerStateCount >= 60)
		{
			SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f));
		}
		else if (m_PlayerStateCount >= 50)
		{
			SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
		}
		else if (m_PlayerStateCount >= 40)
		{
			SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f));
		}
		else if (m_PlayerStateCount >= 30)
		{
			SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
		}
		else if (m_PlayerStateCount >= 20)
		{
			SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f));
		}

		if (m_PlayerStateCount <= 0)
		{
			m_PlayerState = PLAYERSTATE_NORMAL;
		}
	}
	else
	{
		SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	}
}

//====================================================================================================
// 異動制限
//=====================================================================================================
void CPlayer::MoveLimit(void)
{
	if (m_PlayerPos.x >= 1200)
	{
		m_PlayerPos.x = 1200;
	}
	else if (m_PlayerPos.x <= 0)
	{
		m_PlayerPos.x = 0;
	}
	else if (m_PlayerPos.y <= 0)
	{
		m_PlayerPos.y = 0;
	}
	else if (m_PlayerPos.y >= 650)
	{
		m_PlayerPos.y = 650;
	}
}

//====================================================================================================
// ライフの取得
//=====================================================================================================
int CPlayer::GetLife(void)
{
	return m_nLife;
}

//====================================================================================================
// デストラクタ
//=====================================================================================================
CPlayer::~CPlayer()
{

}