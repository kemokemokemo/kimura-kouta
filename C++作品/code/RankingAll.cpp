// ====================================================================================================
//
// ランキング処理 [ranking.cpp]
// Author : Kimura kouta
// ====================================================================================================
#include <stdio.h>              // 一般的なヘッダー
#include "road.h"				// ロードヘッダー
#include "ranking.h"			// ランキングヘッダー
#include "input.h"
#include "fade.h"
#include "sound.h"
#include "score.h"
#include "renderer.h"
#include "keybord.h"
#include "RankingAll.h"
#include "ranking.h"
#include "bg.h"

// ====================================================================================================
// マクロ定義
// ====================================================================================================


// ====================================================================================================
// プロトタイプ宣言
// ====================================================================================================


// ====================================================================================================
// 前方宣言初期化
// ====================================================================================================
CRanking *CRankingAll::pRanking = NULL;

// ====================================================================================================
// コンストラクタ
// ====================================================================================================
CRankingAll::CRankingAll()
{
}

// ====================================================================================================
// デストラクタ
// ====================================================================================================
CRankingAll::~CRankingAll()
{
}

// ====================================================================================================
// 初期化
// ====================================================================================================
HRESULT CRankingAll::Init(void)
{
	CBg::Load();

	CBg::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f), 10.0f, 7);

	CRanking::Create();
	return S_OK;
}

// ====================================================================================================
// 終了
// ====================================================================================================
void CRankingAll::Uninit(void)
{
}

// ====================================================================================================
// 更新
// ====================================================================================================
void CRankingAll::Update(void)
{
	CKeybord *pKetybord = CManager::GetKeybord();

	if (CFade::GetFade() == CFade::FADE_NONE)
	{
		if (pKetybord->GetKeyboardTrigger(DIK_RETURN))
		{
			CFade::SetFade(CManager::MODE_TITLE);
		}
	}
}

// ====================================================================================================
// 描画
// ====================================================================================================
void CRankingAll::Draw(void)
{
}

// ====================================================================================================
// メモリ確保
// ====================================================================================================
CRankingAll * CRankingAll::Create()
{
	CRankingAll *pRankingAll;

	pRankingAll = new CRankingAll();

	pRankingAll->Init();

	return pRankingAll;
}
