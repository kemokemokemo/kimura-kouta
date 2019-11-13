//=============================================================================
//
// アニメーションの処理 [animation.cpp]
// Author : KIMURA KOUTA
//
//=============================================================================
#include "Animation.h"
#include "renderer.h"
#include "manager.h"

//=============================================================================
// マクロ定義
//=============================================================================
#define	MAX_EXPLOSION			(256)							// エフェクトの最大数
#define ANIMATION_SIZE			(150)

//=============================================================================
// 前方宣言の初期化
//=============================================================================
LPDIRECT3DTEXTURE9 CAnimation::m_pTextureAnimation[MAX_ANIMATION] = {};

//=============================================================================
// コンストラクタ
//=============================================================================
CAnimation::CAnimation(OBJTYPE type) : CScene2D(type)
{
	{//初期化
		m_nLife = 0;
		m_EnterCnt = 0;
		m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	}
}

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CAnimation::Init(D3DXVECTOR3 pos, ANIM Type,int nLife)
{
	CScene2D::Init();
	SetPos(pos);
	m_Anim = Type;
	m_nLife = nLife;
	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void CAnimation::Uninit(void)
{
	CScene2D::Uninit();
}

//=============================================================================
// 更新処理
//=============================================================================
void CAnimation::Update(void)
{
	CScene2D::Update();
	float Size = ANIMATION_SIZE;

	m_EnterCnt++;
	m_pos = CScene2D::GetPos();

	switch (m_Anim)
	{
	case ANIMATION_ENEMY:
		m_nLife--;
		SetAnim(0.1f, 0.0f, 1.0f, 5);
		CScene2D::SetSize(Size, Size);
		break;

	case ANIMATION_PLAYER:
		m_nLife--;
		SetAnim(0.125f, 0.0f, 1.0f, 5);
		CScene2D::SetSize(Size, Size);
		break;

	case ANIMATION_NET:
		m_nLife--;
		SetAnim(0.33f, 0.0f, 0.2f, 5);
		CScene2D::SetSize(Size, Size);
		break;

	case ANIMATION_POWERUP:
		m_nLife--;
		SetAnim(0.1f, 0.0f, 1.0f, 6);
		CScene2D::SetSize(Size, Size);
		break;

	case ANIMATION_PRESSENTER:

		CScene2D::SetSize(450, Size);

		if (m_EnterCnt >= 0 && m_EnterCnt <= 60)
		{
			SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
		}
		else if (m_EnterCnt >= 60 && m_EnterCnt <= 120)
		{
			SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f));
		}
		else
		{
			m_EnterCnt = 0;
		}
		break;

	case ANIMATION_TITLEBIRD:

		CScene2D::SetSize(1000, 1000);
		break;
	}

	{//アニメーションの開放
		if (m_nLife <= 0)
		{
			Release();
		}
	}

	CScene2D::SetPos(m_pos);
}

//=============================================================================
// 描画処理
//=============================================================================
void CAnimation::Draw(void)
{
	CScene2D::Draw();
}

//=============================================================================
// 描画処理
//=============================================================================
CAnimation *CAnimation::Create(D3DXVECTOR3 pos, ANIM nType, int nLife)
{
	CAnimation *pAnimation;

	pAnimation = new CAnimation(OBJTYPE_ANIMATION);

	pAnimation->BindTexture(m_pTextureAnimation[nType]);

	pAnimation->Init(pos ,nType, nLife);

	return pAnimation;
}

//========================================================================================================
// テクスチャの読み込み
//========================================================================================================
HRESULT CAnimation::Load(void)
{
	CRenderer *pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(
		pDevice,
		TEXTUER_009,
		&m_pTextureAnimation[0]);

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(
		pDevice,
		TEXTUER_010,
		&m_pTextureAnimation[1]);

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(
		pDevice,
		TEXTUER_012,
		&m_pTextureAnimation[2]);

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(
		pDevice,
		TEXTUER_014,
		&m_pTextureAnimation[3]);

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(
		pDevice,
		TEXTUER_021,
		&m_pTextureAnimation[4]);

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(
		pDevice,
		TEXTUER_022,
		&m_pTextureAnimation[5]);

	return S_OK; 
}

//========================================================================================================
// テクスチャの破棄
//========================================================================================================
void CAnimation::Unload(void)
{
	for (int nCnt = 0; nCnt < MAX_ANIMATION; nCnt++)
	{
		// 頂点バッファの開放
		if (m_pTextureAnimation[nCnt] != NULL)
		{
			m_pTextureAnimation[nCnt]->Release();
			m_pTextureAnimation[nCnt] = NULL;
		}
	}
}

//====================================================================================================
// デストラクタ
//=====================================================================================================
CAnimation::~CAnimation()
{

}