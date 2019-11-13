//=============================================================================
//
// 爆発の処理 [explosion.cpp]
// Author : KIMURA KOUTA
//
//=============================================================================
#include "explosion.h"
#include "renderer.h"
#include "manager.h"

//=============================================================================
// マクロ定義
//=============================================================================
#define	MAX_EXPLOSION			(256)							// エフェクトの最大数
#define EXPLOSION_SIZE (80)	

//=============================================================================
// 前方宣言の初期化
//=============================================================================
LPDIRECT3DTEXTURE9 CExplosion::m_pTextureExplosion[MAX_TEXE] = {};

//====================================================================================================
// コンストラクタ
//====================================================================================================
CExplosion::CExplosion(OBJTYPE type) : CScene2D(type)
{
	m_nLife = 0;
}

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CExplosion::Init()
{
	CScene2D::Init();

	m_nLife = 40;

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void CExplosion::Uninit(void)
{
	CScene2D::Uninit();
	this->Release();
}

//=============================================================================
// 更新処理
//=============================================================================
void CExplosion::Update(void)
{
	CScene2D::Update();
	float Size = EXPLOSION_SIZE;
	m_nLife--;

	SetAnim(0.125f, 0.0f,1.0f,6);

	if (m_nLife <= 0)
	{
		Release();
	}

	CScene2D::SetSize(Size, Size);
}

//=============================================================================
// 描画処理
//=============================================================================
void CExplosion::Draw(void)
{
	CRenderer *pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	// レンダーステート(加算合成処理)
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);				//アルファブレンドを行う
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);

	CScene2D::Draw();

	// レンダーステート(通常ブレンド処理)
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);				//アルファブレンドを行う
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
}

//========================================================================================================
// 描画処理
//========================================================================================================
CExplosion *CExplosion::Create()
{
	CExplosion *pExplosion;

	pExplosion = new CExplosion(OBJTYPE_EXPLOSION);

	pExplosion->BindTexture(m_pTextureExplosion[0]);

	pExplosion->Init();

	pExplosion->SetInitTex(0.125f, 1.0f);

	return pExplosion;
}

//========================================================================================================
// テクスチャの読み込み
//========================================================================================================
HRESULT CExplosion::Load(void)
{
	CRenderer *pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(
		pDevice,
		TEXTUER_003,
		&m_pTextureExplosion[0]);

	return S_OK;
}

//========================================================================================================
// テクスチャの破棄
//========================================================================================================
void CExplosion::Unload(void)
{
	for (int nCnt = 0; nCnt < MAX_TEXE; nCnt++)
	{
		// 頂点バッファの開放
		if (m_pTextureExplosion[nCnt] != NULL)
		{
			m_pTextureExplosion[nCnt]->Release();
			m_pTextureExplosion[nCnt] = NULL;
		}
	}
}

//====================================================================================================
// パーティクル
//=====================================================================================================
void CExplosion::SetParticle(void)
{

}

//====================================================================================================
// デストラクタ
//=====================================================================================================
CExplosion::~CExplosion()
{

}