//====================================================================================================
//
// ボス処理 (boss.h)
// Author (Kimura kouta)
//
//====================================================================================================
#ifndef _BOSS_H_
#define _BOSS_H_

//====================================================================================================
//インクリードファイル
//====================================================================================================
#include"main.h"
#include"enemy.h"
#include"Scene2D.h"

#define MAX_TEXBOSS (1)	//読み込むテクスチャファイル名

//================================================================
// レンダリングクラス
//================================================================
class CBoss : public CScene2D
{
public:

	typedef enum
	{
		BOSSSTATE_NORMAL = 0,		//ボスの通常状態
		BOSSSTATE_DAMAGE,			//ボスの無敵状態
		BOSSSTATE_MAX,
	} BOSSSTATE;

	typedef enum
	{
		BOSSPATTERN_01 = 0,
		BOSSPATTERN_02,
		BOSSPATTERN_03,
		BOSSPATTERN_04,
		BOSSPATTERN_MAX,
	} BOSSPATTERN;

	//================================================================
	// プロトタイプ宣言
	//================================================================
	CBoss(OBJTYPE type);		// 描画順番の設定
	CBoss();					// コンストラクタ
	~CBoss();					// デストラクタ

	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 move);		// 初期化
	void Uninit(void);										// 終了
	void Update(void);										// 更新
	void Draw(void);										// 描画



	static CBoss *Create(D3DXVECTOR3 pos, D3DXVECTOR3 move);		// ボスの生成
	static HRESULT Load(void);										// テクスチャの読み込み
	static void Unload(void);										// テクスチャの破棄

	static D3DXVECTOR3 GetEPos(void);				// ボスの位置情報の取得
	static D3DXVECTOR3 GetMove(void);				// ボスの移動値の取得
	static int GetLife(void);						// ボスのHPの取得

	void SetMove(D3DXVECTOR3 move);					// ボスの移動値の獲得

	void BossDamage(int nDamage);					// ボスのダメージ処理
	void CollisionB_PL(void);						// ボスとプレイヤーの当たり判定
	void MoveAI(void);								// ボスの移動処理
	void BossAI01(void);							// ボスのAIパターン
	void BossAI02(void);							// ボスのAIパターン
	void BossAI03(void);							// ボスのAIパターン
	void BossAI04(void);							// ボスのAIパターン
	void BossAI05(void);							// ボスのAIパターン

private:

	static LPDIRECT3DTEXTURE9 m_pTextureBoss[MAX_TEXBOSS];		// ボスのテクスチャの状態
	static D3DXVECTOR3 m_move;									// ボスの移動値
	static D3DXVECTOR3 m_pos;									// ボスの位置
	static int m_nLife;											// ボスのライフ

	BOSSSTATE m_BossState;			// プレイヤーの状態
	BOSSPATTERN m_BossPattern;		// ボスのAIパターン

	int m_nBossCnt;					//ボス登場のカウント
	int m_nBulletCnt;				//ボスの弾発射カウント
	int m_nBulletCnt2;				//ボスの弾発射カウント

	bool m_bBossT;					// ボスのパターン取得管理
	bool m_bBossB;					// ボスのバリア発動管理
	bool m_bBossM;					// ボスの移動管理

	float m_fRangeX;				// 敵とプレイヤーの距離X
	float m_fRangeY;				// 敵とプレイヤーの距離Y
	float m_fAnglePlayer;			// プレイヤーへの弾の発射角度
	float m_fAngleBoss;				// 角度計算用変数
	float m_fAngle;					// 弾の発射角度
	float m_fRadius;				// 半径用変数
	float m_fAdd_x;					// X軸計算変数
	float m_fAdd_y;					// Y軸計算変数
	
};

//====================================================================================================
// マクロ定義
//==================================================================================================== 
#endif
