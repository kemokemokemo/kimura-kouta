//=============================================================================
//
// 制限時間処理 [time.cpp]
// Author : KIMURA KOUTA
//
//=============================================================================
#include "time.h"
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
#define MAX_TIMER   (300)

//=============================================================================
// 前方宣言の初期化
//=============================================================================

//=============================================================================
// コンストラクタ
//=============================================================================
CTime::CTime(OBJTYPE nPriority) : CScene(nPriority)
{
	m_nTime = 0;
	m_nCntTime = 0;
	m_TimerState = 0;
}

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CTime::Init(void)
{
	int nScore = CTime::GetTime();

	D3DXVECTOR3 pos;

	for (int nCntScore = 0; nCntScore < MAX_TIME; nCntScore++)
	{
		pos = D3DXVECTOR3(600.0f + (SCORE_SIZE_X +15.0f)*nCntScore, 10.0f + SCORE_SIZE_Y, 0.0f);

		int nDigits = nScore % (int)powf(10.0f,(float)MAX_TIME - nCntScore) / (int)powf(10.0f, (float)MAX_TIME - 1.0f - nCntScore);

		m_apTime[nCntScore] = CNumber::Create(pos, SCORE_SIZE_X, SCORE_SIZE_Y, nDigits);
	}

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void CTime::Uninit(void)
{
	for (int nCntScore = 0; nCntScore < MAX_TIME; nCntScore++)
	{
		m_apTime[nCntScore]->Uninit();
	}
}

//=============================================================================
// 更新処理
//=============================================================================
void CTime::Update(void)
{
	for (int nCntScore = 0; nCntScore < MAX_TIME; nCntScore++)
	{
		m_apTime[nCntScore]->Update();
	}

	if (m_TimerState < MAX_TIMER)
	{
		m_nCntTime++;
	}
	if (m_nCntTime >= 60)
	{
		AddTime(-1);
		m_nCntTime = 0;
		m_TimerState++;
	}
}

//=============================================================================
// 描画処理
//=============================================================================
void CTime::Draw(void)
{
	for (int nCntScore = 0; nCntScore < MAX_TIME; nCntScore++)
	{
		m_apTime[nCntScore]->Draw();
	}
}

//=============================================================================
// スコアの変更
//=============================================================================
CTime * CTime::Create(int nScore)
{
	
	CTime *pNumber;

	pNumber = new CTime(OBJTYPE_SCORE);

	pNumber->SetTime(nScore);

	pNumber->Init();

	return pNumber;
}

//=============================================================================
// スコアの取得
//=============================================================================
int CTime::GetTime()
{
	return m_nTime;
}

//=============================================================================
// スコアの加算
//=============================================================================
void CTime::AddTime(int nNumber)
{
	m_nTime += nNumber;

	if (m_nTime > 300)
	{
		m_nTime = 300;
	}
	if (m_nTime < 0)
	{
		m_nTime = 0;
	}

	for (int nCntTime = 0; nCntTime < MAX_TIME; nCntTime++)
	{
		int nTime = m_nTime / (int)powf(10.0f, MAX_TIME - nCntTime - 1.0f * 1.0f) % 10;

		m_apTime[nCntTime]->SetTex(nTime);
	}
}

//=============================================================================
// スコアのセット
//=============================================================================
void CTime::SetTime(int nScore)
{
	m_nTime = nScore;
}

//=============================================================================
// デストラクタ
//=============================================================================
CTime::~CTime()
{

}