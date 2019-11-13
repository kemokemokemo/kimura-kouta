// ====================================================================================================
//
// ランキング背景処理の説明[rankbg.cpp]
// Author : Kimura kouta
//
// ====================================================================================================

// ====================================================================================================
// インクルードファイル
// ====================================================================================================
#include "rankbg.h"
#include "input.h"
#include "fade.h"
#include "sound.h"
#include "renderer.h"
#include "manager.h"
#include "keybord.h"

// ====================================================================================================
// マクロ定義
// ====================================================================================================
#define RANKBG1	"DATA/TEX/RESULT.jpg"//読み込むテクスチャファイル名

#define RANKBG_MAX	　(1)					// 画像数

#define RANKBG_LEFT_X (0)					// 左
#define RANKBG_ON_Y	  (0)					// 上
#define RANKBG_SIZE_X (1280)				// サイズ（ｘ）
#define RANKBG_SIZE_Y (720)					// サイズ（ｙ）

// ====================================================================================================
// グローバル変数
// ====================================================================================================


// ====================================================================================================
// ランキング背景初期化処理
// ====================================================================================================
HRESULT CRankBG::Init(void)
{
	// 変数宣言
	VERTEX_2D *pVtx;	// 頂点情報へのポイント

	// 初期化
	m_fRankbgY = -320.0f;		// yのポジション
	m_nCntRankbg = 0;
	m_nNumRankbg = 0;


	// テクスチャの読み込み
	CRenderer *pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	D3DXCreateTextureFromFile(pDevice, RANKBG1, &m_pTextureRankbg);

	// 頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4, D3DUSAGE_WRITEONLY, FVF_VERTEX_2D, D3DPOOL_MANAGED, &m_pVtxBuffRankbg, NULL);

	// 頂点データの範囲をロックし、頂点バッファへのポインタ
	m_pVtxBuffRankbg->Lock(0, 0, (void **)&pVtx, 0);

	// 頂点の設定
	pVtx[0].pos = D3DXVECTOR3(RANKBG_LEFT_X, RANKBG_ON_Y, 0.0f);									// 一つ目の頂点
	pVtx[1].pos = D3DXVECTOR3(RANKBG_LEFT_X + RANKBG_SIZE_X, RANKBG_ON_Y, 0.0f);					// 二つ目の頂点
	pVtx[2].pos = D3DXVECTOR3(RANKBG_LEFT_X, RANKBG_ON_Y + RANKBG_SIZE_Y, 0.0f);					// 三つ目の頂点
	pVtx[3].pos = D3DXVECTOR3(RANKBG_LEFT_X + RANKBG_SIZE_X, RANKBG_ON_Y + RANKBG_SIZE_Y, 0.0f);	// 四つ目の頂点

	// 頂点作成
	pVtx[0].rhw = 1.0f;																// 一つ目の頂点作成
	pVtx[1].rhw = 1.0f;																// 二つ目の頂点作成
	pVtx[2].rhw = 1.0f;																// 三つ目の頂点作成
	pVtx[3].rhw = 1.0f;																// 四つ目の頂点作成

	// カラー設定
	pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);								// 一つ目の色設定
	pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);								// 二つ目の色設定
	pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);								// 三つ目の色設定
	pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);								// 四つ目の色設定

	// テクスチャの設定
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);											// 一つ目のテクスチャ
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);											// 二つ目のテクスチャ
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);											// 三つ目のテクスチャ
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);											// 四つ目のテクスチャ

	// アンロック
	m_pVtxBuffRankbg->Unlock();

	return S_OK;
}

// ====================================================================================================
// ランキング背景終了処理
// ====================================================================================================
void CRankBG::Uninit(void)
{
	// テクスチャの開放
	if (m_pTextureRankbg != NULL)
	{
		m_pTextureRankbg->Release();
		m_pTextureRankbg = NULL;
	}

	// 頂点バッファの開放
	if (m_pVtxBuffRankbg != NULL)
	{
		m_pVtxBuffRankbg->Release();
		m_pVtxBuffRankbg = NULL;
	}
}

// ====================================================================================================
//
// ランキング背景更新処理
//
// ====================================================================================================
void CRankBG::Update(void)
{
}

// ====================================================================================================
// ランキング背景描画処理
// ====================================================================================================
void CRankBG::Draw(void)
{
	// デバイスを取得する
	CRenderer *pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	// 頂点バッファをデバイスのデータストリームにバインド
	pDevice->SetStreamSource(0, m_pVtxBuffRankbg, 0, sizeof(VERTEX_2D));

	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	pDevice->SetTexture(0, m_pTextureRankbg);

	// ランキング背景描画
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
}

// ====================================================================================================
// コンストラクタ
// ====================================================================================================
CRankBG::CRankBG()
{
}

// ====================================================================================================
// デストラクタ
// ====================================================================================================
CRankBG::~CRankBG()
{
}

// ====================================================================================================
// クリエイト
// ====================================================================================================
CRankBG * CRankBG::Create()
{
	CRankBG *pRankBG;

	pRankBG = new CRankBG();

	pRankBG->Init();

	return pRankBG;
}
