//====================================================================================================
//
// 弾処理 (bullet.h)
// Author (Kimura kouta)
//
//====================================================================================================
#ifndef _BULLET_H_
#define _BULLET_H_

//====================================================================================================
//インクリードファイル
//====================================================================================================
#include"main.h"
#include"Scene2D.h"

#define MAX_TEXBULLET (2)	//読み込むテクスチャファイル名
class CBullet;

//================================================================
// レンダリングクラス
//================================================================
class CBullet : public CScene2D
{
public:

	//====================================================================================================
	// 列挙型定義
	//=====================================================================================================
	typedef enum
	{
		BULLETTYPE_PLAYER = 0,
		BULLETTYPE_ENEMY,
		BULLETTYPE_BOSS,
		BULLETTYPE_MAX,
	} BULLETTYPE;

	typedef enum
	{
		BULLETTEX_PLAYER = 0,
		BULLETTEX_BOSS_NORMAL,
		BULLETTEX_MAX,
	} BULLETTEX;

	//================================================================
	// プロトタイプ宣言
	//================================================================
	CBullet(OBJTYPE type);
	CBullet();
	~CBullet();

	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 move, BULLETTEX BulletTex, int nLife);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	void SetMove(D3DXVECTOR3 move);
	int GetLife();
	static CBullet *Create(D3DXVECTOR3 pos, D3DXVECTOR3 move, BULLETTYPE BulletType, BULLETTEX BulletTex,int nLife);
	static HRESULT Load(void);
	static void Unload(void);
	void BulletType(BULLETTYPE BulletType);		//味方と弾の当たり判定
	void EnemyCollision(void);					//敵と弾の当たり判定
	void PlayerCollision(void);					//味方と弾の当たり判定
	void NeutralCollision(void);				//味方と弾の当たり判定
	void BossCollision(void);

private:

	VERTEX_2D m_Vertex[4];
	static LPDIRECT3DTEXTURE9 m_pTextureBullet[MAX_TEXBULLET];
	D3DXVECTOR3 m_move;
	D3DXVECTOR3 m_pos;
	float Size;
	int m_nLife;
	BULLETTYPE m_BulletType;
	BULLETTEX m_BulletTex;
};

//====================================================================================================
// マクロ定義
//==================================================================================================== 
#endif
