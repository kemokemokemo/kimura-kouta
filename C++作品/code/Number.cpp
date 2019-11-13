//=============================================================================
//
// 数字処理 [number.cpp]
// Author : KIMURA KOUTA
//
//=============================================================================
#include "Number.h"
#include "renderer.h"
#include "manager.h"

//=============================================================================
// マクロ定義
//=============================================================================
#define	TEXTURE_SCORE		"DATA/TEX/number000.png"	// 読み込むテクスチャファイル名
#define MAX_SCORE   (8)
#define SCORE_POS_X	(0)			    //ポリゴンの表示位置(左上X)
#define SCORE_POS_Y	(0)			    //ポリゴンの表示位置(左上Y)
#define SCORE_SIZE_X	(30)			//ポリゴンのサイズ(横幅)
#define SCORE_SIZE_Y	(40)			//ポリゴンのサイズ(立幅)
#define SCORECOLOR_TEX   (255)

//=============================================================================
// プロトタイプ宣言
//=============================================================================

//=============================================================================
// 前方宣言の初期化
//=============================================================================
LPDIRECT3DTEXTURE9 CNumber::m_pTextureNumber = NULL;

//=============================================================================
// コンストラクタ
//=============================================================================
CNumber::CNumber()
{
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Size_X = 0;
	m_Size_Y = 0;
	m_nNumber = 0;
}

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CNumber::Init()
{
	CRenderer *pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	VERTEX_2D *pVtx;

	// オブジェクトの頂点バッファを生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_SCORE,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&m_pVtxBuffNumber,
		NULL);

	// 頂点情報の設定
	m_pVtxBuffNumber->Lock(0, 0, (void**)&pVtx, 0);

	//頂点座標の設定(右回りで設定する）
	pVtx[0].pos = m_pos + D3DXVECTOR3(-m_Size_X, -m_Size_Y, 0.0f);
	pVtx[1].pos = m_pos + D3DXVECTOR3(m_Size_X, -m_Size_Y, 0.0f);
	pVtx[2].pos = m_pos + D3DXVECTOR3(-m_Size_X, m_Size_Y, 0.0f);
	pVtx[3].pos = m_pos + D3DXVECTOR3(m_Size_X, m_Size_Y, 0.0f);

	//rhwの設定（値は1.0で固定）：2Dとして動かすのに必要なもの
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	//頂点カラーの設定(0～255の値で設定）
	pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	pVtx[0].tex = D3DXVECTOR2(0.1f * m_nNumber, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(0.1f * m_nNumber + 0.1f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.1f * m_nNumber, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(0.1f * m_nNumber + 0.1f, 1.0f);

	// 頂点データをアンロックする
	m_pVtxBuffNumber->Unlock();

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void CNumber::Uninit(void)
{
	// テクスチャの開放
	if (m_pVtxBuffNumber != NULL)
	{
		m_pVtxBuffNumber->Release();
		m_pVtxBuffNumber = NULL;
	}
}

//=============================================================================
// 更新処理
//=============================================================================
void CNumber::Update(void)
{
}

//=============================================================================
// 描画処理
//=============================================================================
void CNumber::Draw(void)
{
	CRenderer *pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	// 頂点バッファをデバイスのデータストリームにバインド
	pDevice->SetStreamSource(0, m_pVtxBuffNumber, 0, sizeof(VERTEX_2D));

	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	// テクスチャの設定
	pDevice->SetTexture(0, m_pTextureNumber);

	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
}

//=============================================================================
// スコアの変更
//=============================================================================
CNumber * CNumber::Create(D3DXVECTOR3 pos, float size_x, float size_y, int nNumber)
{
	CNumber *pNumber;

	pNumber = new CNumber();

	pNumber->SetNumber(nNumber);

	pNumber->SetPosition(pos);

	pNumber->SetSize(size_x, size_y);

	pNumber->Init();

	return pNumber;
}

//=============================================================================
// スコアの変更
//=============================================================================
HRESULT CNumber::Load(void)
{
	CRenderer *pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	// テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,				// デバイスへのポインタ
		TEXTURE_SCORE,		// ファイルの名前
		&m_pTextureNumber);	// 読み込むメモリー

	return S_OK;
}

//=============================================================================
// スコアの変更
//=============================================================================
void CNumber::Unload(void)
{
	// 頂点バッファの開放
	if (m_pTextureNumber != NULL)
	{
		m_pTextureNumber->Release();
		m_pTextureNumber = NULL;
	}
}

//=============================================================================
// 数字のセット
//=============================================================================
void CNumber::SetNumber(int nNumber)
{
	m_nNumber = nNumber;
}

//=============================================================================
// ポジションのセット
//=============================================================================
void CNumber::SetPosition(D3DXVECTOR3 pos)
{
	m_pos = pos;
}

//=============================================================================
// サイズのセット
//=============================================================================
void CNumber::SetSize(float size_x, float size_y)
{
	m_Size_X = size_x;
	m_Size_Y = size_y;
}

//=============================================================================
// テクスチャのセット
//=============================================================================
void CNumber::SetTex(int nDigits)
{
	VERTEX_2D *pVtx;

	// 頂点情報の設定
	m_pVtxBuffNumber->Lock(0, 0, (void**)&pVtx, 0);

	pVtx[0].tex = D3DXVECTOR2(0.1f * nDigits, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(0.1f * nDigits + 0.1f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.1f * nDigits, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(0.1f * nDigits + 0.1f, 1.0f);

	// 頂点データをアンロックする
	m_pVtxBuffNumber->Unlock();
}

//=============================================================================
// デストラクタ
//=============================================================================
CNumber::~CNumber()
{
}