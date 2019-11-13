//=============================================================================
//
// 爆発の処理 [explosion.h]
// Author : KIMURA KOUTA
//
//=============================================================================
#ifndef _EXPLOSION_H_
#define _EXPLOSION_H_

#define _CRT_SECURE_NO_WARNINGS

//=============================================================================
// インクルードファイル
//=============================================================================
#include "main.h"
#include "Scene2D.h"

//=============================================================================
// マクロ定義
//=============================================================================
#define MAX_TEXE (1)

//=============================================================================
// 構造体定義
//=============================================================================
typedef struct
{
	D3DXVECTOR3 pos;		// 位置
	D3DXVECTOR3 move;		// 移動
	D3DXMATRIX  mtxWorldWall;			//ワールドマトリックス
	D3DXCOLOR col;			// 色
	float fRadius;			// 半径
	int nLife;				// ライフ
	int nType;
	int ParticlenType;
	bool bUse;				// 使用しているかどうか
} EFFECT;

//================================================================
// レンダリングクラス
//================================================================
class CExplosion : public CScene2D
{
public:

	//=============================================================================
	// プロトタイプ宣言
	//=============================================================================
	CExplosion(OBJTYPE type);
	~CExplosion();

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	static CExplosion *Create();
	static HRESULT Load(void);
	static void Unload(void);
	static void SetParticle(void);

private:

	static LPDIRECT3DTEXTURE9 m_pTextureExplosion[MAX_TEXE];
	int m_nLife;
};

#endif