//====================================================================================================
//
// レンダリング (Scene2D.cpp)
// Author (Kimura kouta)
//
//====================================================================================================
#include "Scene2D.h"
#include "renderer.h"
#include "manager.h"
#include "keybord.h"
#include "enemy.h"
#include "player.h"
#include "bullet.h"
#include "explosion.h"
#include "LIfe.h"
#include "Game.h"

//====================================================================================================
// プロトタイプ宣言
//====================================================================================================
#define BG_POS_X	(0)			    //ポリゴンの表示位置(左上X)
#define BG_POS_Y	(0)			    //ポリゴンの表示位置(左上Y)
#define BG_SIZE_X	(1280)			//ポリゴンのサイズ(横幅)
#define BG_SIZE_Y	(720)			//ポリゴンのサイズ(立幅)

//====================================================================================================
// グローバル変数
//====================================================================================================

//====================================================================================================
// コンストラクタ
//====================================================================================================
 CScene2D::CScene2D(OBJTYPE nPriority) : CScene(nPriority)
{
	m_TexMove = 0;
}

 //====================================================================================================
 // コンストラクタ
 //====================================================================================================
 CScene2D::CScene2D()
 {
	 int m_nCounterAnim = 0;
	 int m_nPatternAnim = 0;
 }

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CScene2D::Init(void)
{
	CRenderer *pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	//初期化
	int m_nCounterAnim = 0;
	int m_nPatternAnim = 0;
	float m_TexMove = 0.0f;
	float m_Speed = 0.0f;
	float m_fHeight = 0.0f;
	float m_fWidht = 0.0f;
	float m_fWidht2 = 0.0f;;

	 VERTEX_2D *pVtx;

	// オブジェクトの頂点バッファを生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&m_pVtxBuffScene,
		NULL);

	//初期化
	float Pos = 2.0f;

	m_ModeState = MODE_NORMAL;

	// 頂点データの範囲をロックし、頂点バッファへのポインタを取得
	m_pVtxBuffScene->Lock(0, 0, (void**)&pVtx, 0);

	pVtx[0].pos = m_pos + D3DXVECTOR3(-Pos, -Pos, 0.0f);
	pVtx[1].pos = m_pos + D3DXVECTOR3(Pos, -Pos, 0.0f);
	pVtx[2].pos = m_pos + D3DXVECTOR3(-Pos, Pos, 0.0f);
	pVtx[3].pos = m_pos + D3DXVECTOR3(Pos, Pos, 0.0f);

	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	// 頂点データをアンロックする
	m_pVtxBuffScene->Unlock();
	return S_OK;
}

//==================================================================================================
// 終了処理
//===================================================================================================
void CScene2D::Uninit(void)
{
	// 頂点バッファの開放
	if (m_pVtxBuffScene != NULL)
	{
		m_pVtxBuffScene->Release();
		m_pVtxBuffScene = NULL;
	}
	// 頂点バッファの開放
	if (m_pTexturePolygon != NULL)
	{
		m_pTexturePolygon->Release();
		m_pTexturePolygon = NULL;
	}
}

//====================================================================================================
//更新処理
//=====================================================================================================
void CScene2D::Update(void)
{
	VERTEX_2D *pVtx;

	// 頂点データの範囲をロックし、頂点バッファへのポインタを取得
	m_pVtxBuffScene->Lock(0, 0, (void**)&pVtx, 0);

	pVtx[0].pos = m_pos + D3DXVECTOR3(-0.0f, -0.0f, 0.0f);
	pVtx[1].pos = m_pos + D3DXVECTOR3(m_PosSize_X, -0.0f, 0.0f);
	pVtx[2].pos = m_pos + D3DXVECTOR3(-0.0f, m_PosSize_Y, 0.0f);
	pVtx[3].pos = m_pos + D3DXVECTOR3(m_PosSize_X, m_PosSize_Y, 0.0f);

	pVtx[0].col = m_Col;
	pVtx[1].col = m_Col;
	pVtx[2].col = m_Col;
	pVtx[3].col = m_Col;

	// 頂点データをアンロックする
	m_pVtxBuffScene->Unlock();
}

//=============================================================================
// テクスチャのセット
//=============================================================================
void CScene2D::SetTex(int nDigits)
{
	VERTEX_2D *pVtx;

	// 頂点情報の設定
	m_pVtxBuffScene->Lock(0, 0, (void**)&pVtx, 0);

	pVtx[0].tex = D3DXVECTOR2(0.33f * nDigits, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(0.33f * nDigits + 0.33f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.33f * nDigits, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(0.33f * nDigits + 0.33f, 1.0f);

	// 頂点データをアンロックする
	m_pVtxBuffScene->Unlock();
}


//========================================================================================================
// 現在のモード処理
//========================================================================================================
void CScene2D::SetModeState(MODESTATE mode)
{
	m_ModeState = mode;
}

//====================================================================================================
// オブジェクトの取得
//====================================================================================================
CScene2D::MODESTATE CScene2D::GetModeState(void)
{
	return m_ModeState;
}

//====================================================================================================
// オブジェクトの取得
//====================================================================================================
void CScene2D::BgUpdate()
{
	VERTEX_2D *pVtx;

	// 頂点情報の設定
	m_pVtxBuffScene->Lock(0, 0, (void**)&pVtx, 0);

	pVtx[0].pos = D3DXVECTOR3(BG_POS_X, BG_POS_Y, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(BG_POS_X + BG_SIZE_X, BG_POS_Y, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(BG_POS_X, BG_POS_Y + BG_SIZE_Y, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(BG_POS_X + BG_SIZE_X, BG_POS_Y + BG_SIZE_Y, 0.0f);


	// 頂点データをアンロックする
	m_pVtxBuffScene->Unlock();
}

//========================================================================================================
// 描画処理
//========================================================================================================
void CScene2D::Draw(void)
{
	CRenderer *pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	// 頂点バッファをデバイスのデータストリームにバインド
	pDevice->SetStreamSource(0, m_pVtxBuffScene, 0, sizeof(VERTEX_2D));

	pDevice->SetTexture(0, m_pTexturePolygon);

	pDevice->SetFVF(FVF_VERTEX_2D);

	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,0,2);

}

//========================================================================================================
// アニメーション
//========================================================================================================
void CScene2D::SetInitTex(float fHeight, float fWidht)
{
	//変数宣言
	VERTEX_2D *pVtx;

	// 頂点データの範囲をロックし、頂点バッファへのポインタを取得
	m_pVtxBuffScene->Lock(0, 0, (void**)&pVtx, 0);

	// 頂点の設定
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(fHeight, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, fWidht);
	pVtx[3].tex = D3DXVECTOR2(fHeight, fWidht);

	// 頂点データをアンロックする
	m_pVtxBuffScene->Unlock();
}

//========================================================================================================
// アニメーション
//========================================================================================================
void CScene2D::TexMove()
{
	//変数宣言
	VERTEX_2D *pVtx;

	// 頂点データの範囲をロックし、頂点バッファへのポインタを取得
	m_pVtxBuffScene->Lock(0, 0, (void**)&pVtx, 0);

	float move = -m_Speed;
	m_TexMove += move;

	// 頂点の設定
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f+ m_TexMove);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f+ m_TexMove);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f+ m_TexMove);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f+ m_TexMove);

	// 頂点データをアンロックする
	m_pVtxBuffScene->Unlock();
}

//========================================================================================================
// アニメーション
//========================================================================================================
void CScene2D::SetAnim(float fHeight, float fWidht, float fWidht2, int fChange)
{
	VERTEX_2D *pVtx;

	m_fHeight = fHeight;
	m_fWidht = fWidht;
	m_fWidht2 = fWidht2;

	m_nCounterAnim++;
	
	if (m_nCounterAnim % fChange == 0)
	{
		// パターンの初期化
		m_nPatternAnim = (m_nPatternAnim + 1) % 8;
	}

	// 頂点情報の設定
	m_pVtxBuffScene->Lock(0, 0, (void**)&pVtx, 0);

	// 頂点の設定
	pVtx[0].tex = D3DXVECTOR2(0.0f + m_nPatternAnim * m_fHeight, m_fWidht);
	pVtx[1].tex = D3DXVECTOR2(m_fHeight + m_nPatternAnim * m_fHeight, m_fWidht);
	pVtx[2].tex = D3DXVECTOR2(0.0f + m_nPatternAnim * m_fHeight, m_fWidht2);
	pVtx[3].tex = D3DXVECTOR2(m_fHeight + m_nPatternAnim * m_fHeight, m_fWidht2);

	// 頂点データをアンロックする
	m_pVtxBuffScene->Unlock();
}

//========================================================================================================
// ポジションの取得
//========================================================================================================
D3DXVECTOR3 CScene2D::GetPos(void)
{
	return m_pos;
}

//========================================================================================================
// ポジションのセット
//========================================================================================================
void CScene2D::SetPos(D3DXVECTOR3 pos)
{
	m_pos = pos;
}

//========================================================================================================
// ポジションのセット
//========================================================================================================
void CScene2D::SetSpeed(float tex)
{
	m_Speed = tex;
}

//========================================================================================================
// ポジションのセット
//========================================================================================================
void CScene2D::UIUpdate(int nLife, int size)
{
	VERTEX_2D *pVtx;

	// 頂点データの範囲をロックし、頂点バッファへのポインタを取得
	m_pVtxBuffScene->Lock(0, 0, (void**)&pVtx, 0);

		pVtx[0].pos = D3DXVECTOR3(m_pos.x - size, m_pos.y - size, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(m_pos.x + (nLife * size), m_pos.y - size, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(m_pos.x - size, m_pos.y + size, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(m_pos.x + (nLife * size), m_pos.y + size, 0.0f);

		pVtx[0].col = m_Col;
		pVtx[1].col = m_Col;
		pVtx[2].col = m_Col;
		pVtx[3].col = m_Col;

	// 頂点データをアンロックする
	m_pVtxBuffScene->Unlock();
}

//========================================================================================================
// ポジションのセット
//========================================================================================================
void CScene2D::SetSize(float Size_x, float Size_y)
{
	m_PosSize_X = Size_x;
	m_PosSize_Y = Size_y;
}

//========================================================================================================
// カラーのセット
//========================================================================================================
void CScene2D::SetColor(D3DXCOLOR Color)
{
	m_Col = Color;
}

//========================================================================================================
// ポジションのセット
//========================================================================================================
void CScene2D::SetRadius(float fRadius)
{
	//変数宣言
	VERTEX_2D *pVtx;

	// 頂点データの範囲をロックし、頂点バッファへのポインタを取得
	m_pVtxBuffScene->Lock(0, 0, (void**)&pVtx, 0);

	fRadius -= 3.0f;
	if (fRadius <= 0)
	{
		fRadius = 0;
	}

	// 頂点情報の設定
	pVtx[0].pos = D3DXVECTOR3(m_pos.x - fRadius * 0.4f, m_pos.y - fRadius * 0.4f, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(m_pos.x + fRadius * 0.4f, m_pos.y - fRadius * 0.4f, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(m_pos.x - fRadius * 0.4f, m_pos.y + fRadius * 0.4f, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(m_pos.x + fRadius * 0.4f, m_pos.y + fRadius * 0.4f, 0.0f);

	// 頂点データをアンロックする
	m_pVtxBuffScene->Unlock();
}

//========================================================================================================
// テクスチャのセット
//========================================================================================================
void CScene2D::BindTexture(LPDIRECT3DTEXTURE9 cName)
{
	m_pTexturePolygon = cName;
}

//====================================================================================================
// デストラクタ
//=====================================================================================================
CScene2D::~CScene2D()
{

}