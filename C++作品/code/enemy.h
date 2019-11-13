//====================================================================================================
//
// 敵処理 (enemy.h)
// Author (Kimura kouta)
//
//====================================================================================================
#ifndef _ENEMY_H_
#define _ENEMY_H_

//====================================================================================================
//インクリードファイル
//====================================================================================================
#include"main.h"
#include"Scene2D.h"

#define MAX_TEXENEMY (2)	//読み込むテクスチャファイル名

//================================================================
// レンダリングクラス
//================================================================
class CEnemy : public CScene2D
{
public:

	typedef enum
	{
		ENEMYSTATE_NORMAL = 0,
		ENEMYSTATE_DAMAGE,
		ENEMYSTATE_DEATH,
		ENEMYSTATE_MAX,
	} ENEMYSTATE;

	typedef enum
	{
		AIPATTERN_1 = 0,
		AIPATTERN_2,
		AIPATTERN_3,
		AIPATTERN_4,
		AIPATTERN_5,
		AIPATTERN_MAX,
	} AIPATTERN;

	typedef enum
	{
		ENEMY_RIGHT = 0,
		ENEMY_LEFT,
		ENEMY_MAX,
	} ENEMY;

	//================================================================
	// プロトタイプ宣言
	//================================================================
	CEnemy(OBJTYPE type);	//描画順番の設定
	CEnemy();				//コンストラクタ
	~CEnemy();				//デストラクタ

	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 move, int nLife, AIPATTERN Pattern, int nType);	//初期化
	void Uninit(void);			// 終了
	void Update(void);			// 更新
	void Draw(void);			// 描画

	static CEnemy *Create(D3DXVECTOR3 pos, D3DXVECTOR3 move, int nLife, AIPATTERN Pattern, int nType);	// 敵の生成
	static HRESULT Load(void);				// テクスチャの読み込み
	static void Unload(void);				// テクスチャの破棄

	D3DXVECTOR3 GetEPos(void);				// 敵のポジションの取得
	D3DXVECTOR3 GetEMove(void);				// 敵の移動値の取得

	void SetMove(D3DXVECTOR3 move);			// 移動値の獲得
	void EnemyDamage(int nDamage);			// 敵のダメージ処理
	void CollisionEN_PL(void);				// 敵とプレイヤーの当たり判定
	void OffScreen(void);					// 画面外の処理
	void Damage(void);						// ダメージを受けた時の点滅処理
	void MoveAI(void);						// 敵の移動


	int GetType(void);						// 敵の種類の取得
	int GetELife(void);						// 敵のHPの取得

private:

	static LPDIRECT3DTEXTURE9 m_pTextureEnemy[MAX_TEXENEMY];

	ENEMYSTATE m_EnemyState;	// 敵の状態
	AIPATTERN m_AiPattern;		// AIパターン
	ENEMY m_Enemy;				// 敵の方向の情報
	D3DXVECTOR3 m_move;			// 敵の移動値情報
	D3DXVECTOR3 m_pos;			// 敵の位置情報

	int m_nLife;				// HPの状態
	int m_nBulletCount;			// バレットの発射制限
	int m_Type;					// 敵の種類
	int m_EnemyStateCount;		// 敵の状態のカウント

	float m_fDistanceX;			// X軸の計算用変数
	float m_fDistanceY;			// Y軸の計算用変数
	float m_fDistance;			// 距離
};

//====================================================================================================
// マクロ定義
//==================================================================================================== 
#endif
