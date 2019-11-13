//=============================================================================
//
// スコア処理 [score.cpp]
// Author : KIMURA KOUTA
//
//=============================================================================
#include "Score.h"
#include "renderer.h"
#include "manager.h"

//=============================================================================
// マクロ定義
//=============================================================================
#define	TEXTURE_SCORE		"DATA/TEX/number000.png"	// 読み込むテクスチャファイル名
#define SCORE_POS_X	(0)			    //ポリゴンの表示位置(左上X)
#define SCORE_POS_Y	(0)			    //ポリゴンの表示位置(左上Y)
#define SCORE_SIZE_X	(20)			//ポリゴンのサイズ(横幅)
#define SCORE_SIZE_Y	(30)			//ポリゴンのサイズ(立幅)
#define SCORECOLOR_TEX   (255)

//=============================================================================
// 前方宣言の初期化
//=============================================================================
CNumber *CScore::m_apScore[MAX_SCORE] = {};
int CScore::m_nScore = NULL;

//=============================================================================
// コンストラクタ
//=============================================================================
CScore::CScore(OBJTYPE nPriority) : CScene(nPriority)
{
	int m_nScore = 0;
}

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CScore::Init(void)
{
	int nScore = CScore::GetScore();

	D3DXVECTOR3 pos;

	for (int nCntScore = 0; nCntScore < MAX_SCORE; nCntScore++)
	{
		pos = D3DXVECTOR3(1000.0f + (SCORE_SIZE_X +15.0f)*nCntScore, 10.0f + SCORE_SIZE_Y, 0.0f);

		int nDigits = nScore % (int)powf(10.0f,(float)MAX_SCORE - nCntScore) / (int)powf(10.0f, (float)MAX_SCORE - 1.0f - nCntScore);

		m_apScore[nCntScore] = CNumber::Create(pos, SCORE_SIZE_X, SCORE_SIZE_Y, nDigits);
	}

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void CScore::Uninit(void)
{
	for (int nCntScore = 0; nCntScore < MAX_SCORE; nCntScore++)
	{
		m_apScore[nCntScore]->Uninit();
	}
}

//=============================================================================
// 更新処理
//=============================================================================
void CScore::Update(void)
{
	for (int nCntScore = 0; nCntScore < MAX_SCORE; nCntScore++)
	{
		m_apScore[nCntScore]->Update();
	}
}

//=============================================================================
// 描画処理
//=============================================================================
void CScore::Draw(void)
{
	for (int nCntScore = 0; nCntScore < MAX_SCORE; nCntScore++)
	{
		m_apScore[nCntScore]->Draw();
	}

}
//=============================================================================
// スコアの変更
//=============================================================================
CScore * CScore::Create(int nScore)
{
	
	CScore *pScore;

	pScore = new CScore(OBJTYPE_SCORE);

	pScore->SetScore(nScore);

	pScore->Init();

	return pScore;
}

//=============================================================================
// スコアの取得
//=============================================================================
int CScore::GetScore()
{
	return m_nScore;
}

//=============================================================================
// スコアの取得
//=============================================================================
CNumber *CScore::GetaScore()
{
	return m_apScore[MAX_SCORE];
}

//=============================================================================
// スコアの加算
//=============================================================================
void CScore::AddScore(int nNumber)
{
	m_nScore += nNumber;

	if (m_nScore <= 0)
	{
		m_nScore = 0;
	}

	for (int nCntScore = 0; nCntScore < MAX_SCORE; nCntScore++)
	{
		int nDigits = m_nScore % (int)powf(10.0f, (float)MAX_SCORE + nCntScore) / (int)powf(10.0f, (float)MAX_SCORE - 1.0f - nCntScore);

		m_apScore[nCntScore]->SetTex(nDigits);
	}
}

//=============================================================================
// スコアのセット
//=============================================================================
void CScore::SetScore(int nScore)
{
	m_nScore = nScore;
}

//=============================================================================
// デストラクタ
//=============================================================================
CScore::~CScore()
{

}