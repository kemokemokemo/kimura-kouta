//=============================================================================
//
// エフェクトの処理 [effect.cpp]
// Author : KIMURA KOUTA
//
//=============================================================================
#include "effect.h"
#include "manager.h"
#include "renderer.h"
#include "bullet.h"
#include "player.h"

//=============================================================================
// グローバル変数
//=============================================================================
LPDIRECT3DTEXTURE9 CEffect::m_pTextureEffect[MAX_EFFECTTEX] = {};
LPDIRECT3DVERTEXBUFFER9 CEffect::m_pVtxBuffEffect = NULL;
CEffect::EFFECT CEffect::m_aEffect[MAX_EFFECT] = {};

//=============================================================================
// マクロ定義
//=============================================================================
#define EFFECT_SIZE (50)

//=============================================================================
// コンストラクタ
//=============================================================================
CEffect::CEffect(OBJTYPE type) : CScene(type)
{

}
//=============================================================================
// コンストラクタ
//=============================================================================
CEffect::CEffect()
{

}
//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CEffect::Init(void)
{
	for (int nCntEffect = 0; nCntEffect < MAX_EFFECT; nCntEffect++)
	{
		m_aEffect[nCntEffect].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		m_aEffect[nCntEffect].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		m_aEffect[nCntEffect].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f);
		m_aEffect[nCntEffect].fRadius = 0;
		m_aEffect[nCntEffect].nLife = 0;
		m_aEffect[nCntEffect].bUse = false;
	}

	// オブジェクトの種類の設定
	SetObjType(CScene::OBJTYPE_EFFECT);

	CEffect::MakeVertex();
	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void CEffect::Uninit(void)
{
	if (m_pVtxBuffEffect != NULL)
	{// 頂点バッファの開放
		m_pVtxBuffEffect->Release();
		m_pVtxBuffEffect = NULL;
	}
}

//=============================================================================
// 更新処理
//=============================================================================
void CEffect::Update(void)
{
	VERTEX_2D *pVtx;

	// 頂点データの範囲をロックし、頂点バッファへのポインタを取得
	m_pVtxBuffEffect->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntEffect = 0; nCntEffect < MAX_EFFECT; nCntEffect++, pVtx += 4)
	{
		if (m_aEffect[nCntEffect].bUse == true)					  // 弾が使用されている
		{
			// 頂点座標の更新
			pVtx[0].pos = D3DXVECTOR3(m_aEffect[nCntEffect].pos.x - m_aEffect[nCntEffect].fRadius, m_aEffect[nCntEffect].pos.y - m_aEffect[nCntEffect].fRadius, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(m_aEffect[nCntEffect].pos.x + m_aEffect[nCntEffect].fRadius, m_aEffect[nCntEffect].pos.y - m_aEffect[nCntEffect].fRadius, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(m_aEffect[nCntEffect].pos.x - m_aEffect[nCntEffect].fRadius, m_aEffect[nCntEffect].pos.y + m_aEffect[nCntEffect].fRadius, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(m_aEffect[nCntEffect].pos.x + m_aEffect[nCntEffect].fRadius, m_aEffect[nCntEffect].pos.y + m_aEffect[nCntEffect].fRadius, 0.0f);

			// 頂点カラーの更新
			pVtx[0].col = m_aEffect[nCntEffect].col;
			pVtx[1].col = m_aEffect[nCntEffect].col;
			pVtx[2].col = m_aEffect[nCntEffect].col;
			pVtx[3].col = m_aEffect[nCntEffect].col;

			m_aEffect[nCntEffect].nLife--;

			m_aEffect[nCntEffect].fRadius -= 5.0f;

			if (m_aEffect[nCntEffect].fRadius <= 0)
			{
				m_aEffect[nCntEffect].fRadius = 0;
			}

			if (m_aEffect[nCntEffect].nLife <= 0)
			{
				m_aEffect[nCntEffect].bUse = false;
			}
		}
	}
	// 頂点データをアンロックする
	m_pVtxBuffEffect->Unlock();
}

//=============================================================================
// 描画処理
//=============================================================================
void CEffect::Draw(void)
{
	CRenderer *pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	// レンダーステート(加算合成処理)
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);

	// 頂点バッファをデータストリームにバインド
	pDevice->SetStreamSource(0, m_pVtxBuffEffect, 0, sizeof(VERTEX_2D));

	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	// テクスチャの設定
	pDevice->SetTexture(0, m_pTextureEffect[0]);

	// ポリゴン描画
	for (int nCntEffect = 0; nCntEffect < MAX_EFFECT; nCntEffect++)
	{
		if (m_aEffect[nCntEffect].bUse == true)					  // 弾が使用されている
		{
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntEffect * 4, 2);
		}
	}

	// レンダーステート(通常ブレンド処理)
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
}

//=============================================================================
// エフェクトの作成
//=============================================================================
CEffect * CEffect::Create()
{
	CEffect *pEffect = new CEffect(OBJTYPE_EFFECT);
	pEffect->Init();
	return pEffect;
}

//=============================================================================
// テクスチャの読み込み
//=============================================================================
HRESULT CEffect::Load(void)
{
	CRenderer *pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	// テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,				// デバイスへのポインタ
		TEXTURE_EFFECT,		// ファイルの名前
		&m_pTextureEffect[0]);	// 読み込むメモリー

								// テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,				// デバイスへのポインタ
		TEXTURE_EFFECT2,		// ファイルの名前
		&m_pTextureEffect[1]);	// 読み込むメモリー


	return S_OK;
}

//=============================================================================
// テクスチャの破棄
//=============================================================================
void CEffect::Unload(void)
{
	// テクスチャの開放
	for (int nCntEffect = 0; nCntEffect < MAX_EFFECTTEX; nCntEffect++)
	{
		if (m_pTextureEffect[nCntEffect] != NULL)
		{
			m_pTextureEffect[nCntEffect]->Release();
			m_pTextureEffect[nCntEffect] = NULL;
		}
	}
}

//=============================================================================
// 頂点情報の生成
//=============================================================================
void CEffect::MakeVertex(void)
{
	// 頂点情報の設定
	for (int nCnt = 0; nCnt < MAX_EFFECT; nCnt++)
	{
		m_aEffect[nCnt].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		m_aEffect[nCnt].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		m_aEffect[nCnt].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		m_aEffect[nCnt].nLife = 0;
		m_aEffect[nCnt].fRadius = 0.0f;
		m_aEffect[nCnt].bUse = false;
	}

	// 頂点バッファのポインタ
	VERTEX_2D *pVtx;

	CRenderer *pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	int nCnt;

	// オブジェクトの頂点バッファを生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_EFFECT, D3DUSAGE_WRITEONLY, FVF_VERTEX_2D, D3DPOOL_MANAGED, &m_pVtxBuffEffect, NULL);

	// 頂点データの範囲をロックし、頂点バッファへのポインタを取得
	m_pVtxBuffEffect->Lock(0, 0, (void**)&pVtx, 0);

	// 頂点情報の設定
	for (nCnt = 0; nCnt < MAX_EFFECT; nCnt++)
	{
		// 頂点の設定
		pVtx[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;

		pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		// テクスチャ座標の設定
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		pVtx += 4;
	}
	// 頂点データをアンロック
	m_pVtxBuffEffect->Unlock();
}

//=========================================================================
// エフェクトの設置
//=========================================================================
void CEffect::SetEffect(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXCOLOR col, int nLife)
{
	VERTEX_2D *pVtx;
	int nCnt;

	// 頂点データの範囲をロックし、頂点バッファへのポインタを取得
	m_pVtxBuffEffect->Lock(0, 0, (void**)&pVtx, 0);

	for (nCnt = 0; nCnt < MAX_EFFECT; nCnt++)
	{
		if (!m_aEffect[nCnt].bUse)
		{
			m_aEffect[nCnt].pos = pos;
			m_aEffect[nCnt].col = col;
			m_aEffect[nCnt].nLife = nLife;
			m_aEffect[nCnt].fRadius = 40.0f;

			// 頂点の設定
			pVtx[0].pos = D3DXVECTOR3(m_aEffect[nCnt].pos.x - m_aEffect[nCnt].fRadius, m_aEffect[nCnt].pos.y - m_aEffect[nCnt].fRadius, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(m_aEffect[nCnt].pos.x + m_aEffect[nCnt].fRadius, m_aEffect[nCnt].pos.y - m_aEffect[nCnt].fRadius, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(m_aEffect[nCnt].pos.x - m_aEffect[nCnt].fRadius, m_aEffect[nCnt].pos.y + m_aEffect[nCnt].fRadius, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(m_aEffect[nCnt].pos.x + m_aEffect[nCnt].fRadius, m_aEffect[nCnt].pos.y + m_aEffect[nCnt].fRadius, 0.0f);

			// 頂点カラーの設定
			pVtx[0].col = m_aEffect[nCnt].col;
			pVtx[1].col = m_aEffect[nCnt].col;
			pVtx[2].col = m_aEffect[nCnt].col;
			pVtx[3].col = m_aEffect[nCnt].col;

			m_aEffect[nCnt].bUse = true;

			break;
		}
		pVtx += 4;
	}
	// 頂点データをアンロック
	m_pVtxBuffEffect->Unlock();
}

//=============================================================================
// デストラクタ
//=============================================================================
CEffect::~CEffect()
{

}
