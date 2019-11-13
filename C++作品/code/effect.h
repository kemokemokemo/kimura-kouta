//=============================================================================
//
// エフェクトの処理 [effect.h]
// Author : KIMURA KOUTA
//
//=============================================================================
#ifndef _EFFECT_H_
#define _EFFECT_H_

#define _CRT_SECURE_NO_WARNINGS

//=============================================================================
// インクルードファイル
//=============================================================================
#include "main.h"
#include "Scene2D.h"

//=============================================================================
// マクロ定義
//=============================================================================
#define	TEXTURE_EFFECT		"DATA/TEX/effect000.jpg"		// 読み込むテクスチャファイル名
#define	TEXTURE_EFFECT2		"DATA/TEX/effect001.jpg"		// 読み込むテクスチャファイル名
#define	TEXTURE_EFFECT3		"DATA/TEX/efect002.jpg"		// 読み込むテクスチャファイル名
#define	TEXTURE_EFFECT4		"DATA/TEX/effect003.jpg"		// 読み込むテクスチャファイル名
#define	TEXTURE_EFFECT5		"DATA/TEX/effect004.jpg"		// 読み込むテクスチャファイル名
#define	TEXTURE_EFFECT6		"DATA/TEX/effect005.jpg"		// 読み込むテクスチャファイル名
#define	MAX_EFFECT			(256)							// エフェクトの最大数
#define	MAX_EFFECTTEX		(1)							// エフェクトの最大数


//================================================================
// レンダリングクラス
//================================================================
class CEffect :public CScene
{
public:

	//=============================================================================
	// プロトタイプ宣言
	//=============================================================================
	CEffect(OBJTYPE type);
	CEffect();
	~CEffect();
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static CEffect *Create();
	static HRESULT Load(void);
	static void Unload(void);
	static void MakeVertex(void);
	static void SetEffect(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXCOLOR col, int nLife);

private:

	// 構造体定義
	typedef struct
	{
		D3DXVECTOR3 pos;		// 位置
		D3DXVECTOR3 move;		// 移動量
		D3DXCOLOR col;			// 色
		float fRadius;			// 半径
		int nLife;				// 体力
		bool bUse;				// 使用しているかどうか
	} EFFECT;

	static LPDIRECT3DTEXTURE9 m_pTextureEffect[MAX_EFFECTTEX];		// テクスチャへのポインタ
	static LPDIRECT3DVERTEXBUFFER9 m_pVtxBuffEffect;	// 頂点バッファへのポインタ
	static EFFECT m_aEffect[MAX_EFFECT];				// エフェクト情報

};

#endif