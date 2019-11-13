//====================================================================================================
//
// プレイヤー処理 (player.h)
// Author (Kimura kouta)
//
//====================================================================================================
#ifndef _PLAYER_H_
#define _PLAYER_H_

//====================================================================================================
//インクリードファイル
//====================================================================================================
#include"main.h"
#include"Scene2D.h"

class CBullet;
//================================================================
// レンダリングクラス
//================================================================
class CPlayer : public CScene2D
{
public:
	typedef enum
	{
		PLAYERSTATE_NORMAL = 0,
		PLAYERSTATE_DAMAGE,
		PLAYERSTATE_DEATH,
		PLAYERSTATE_MAX,
	} PLAYERSTATE;

	//================================================================
	// プロトタイプ宣言
	//================================================================
	CPlayer(OBJTYPE type);
	CPlayer();
	~CPlayer();

	HRESULT Init(D3DXVECTOR3 pos);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	void PlayerMove(void);

	static CPlayer *Create(D3DXVECTOR3 pos);
	static HRESULT Load(void);
	static void Unload(void);
	static CBullet *GetBullet(void);
	D3DXVECTOR3 GetPlayerPos(void);
	void PlayerDamage(int nDamage);
	void Damage(void);
	void MoveLimit(void);
	static int GetLife(void);

private:

	VERTEX_2D m_Vertex[4];
	static LPDIRECT3DTEXTURE9 m_pTexturePlayer;
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuffPlayer = NULL;		// 頂点バッファへのポインタ

	D3DXVECTOR3 m_PlayerPos;		//プレイヤーのポジション
	static int m_nLife;				//プレイヤーのライフ
	PLAYERSTATE m_PlayerState;		//プレイヤーの状態
	int m_PlayerStateCount;
	int m_DeathCount;
	int BulletLimit;
};

//====================================================================================================
// マクロ定義
//==================================================================================================== 
#endif
