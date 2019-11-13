//====================================================================================================
//
// 中立処理 (Neutral.h)
// Author (Kimura kouta)
//
//====================================================================================================
#ifndef _NEUTRAL_H_
#define _NEUTRAL_H_

//====================================================================================================
//インクリードファイル
//====================================================================================================
#include"main.h"
#include"Scene2D.h"

#define MAX_TEXNEUTRAL (1)	//読み込むテクスチャファイル名

//================================================================
// レンダリングクラス
//================================================================
class CNeutral : public CScene2D
{
public:

	typedef enum
	{
		TYPENEUTRAL_PATERN1,
		TYPENEUTRAL_PATERN2,
		TYPENEUTRAL_PATERN3,
		TYPENEUTRAL_PATERN4,
		TYPENEUTRAL_MAX,
	} TYPE;

	typedef enum
	{
		NEUTRAL_RIGHT,
		NEUTRAL_LEFT,
		NEUTRAL_MAX,
	} NEUTRAL;

	//================================================================
	// プロトタイプ宣言
	//================================================================
	CNeutral(OBJTYPE type);
	~CNeutral();

	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 move, TYPE Type);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	void SetMove(D3DXVECTOR3 move);
	static CNeutral *Create(D3DXVECTOR3 pos, D3DXVECTOR3 move, TYPE Type);
	static HRESULT Load(void);
	static void Unload(void);
	void CollisionEN(void);
	void CollisionPL(void);
	void DirectionMove(void);
	void N_AIPATERN01(void);
	void N_AIPATERN02(void);
	void N_AIPATERN03(void);
	void N_AIPATERN04(void);
	D3DXVECTOR3 GetNPos(void);
	void OffScreen(void);


private:

	VERTEX_2D m_Vertex[4];
	static LPDIRECT3DTEXTURE9 m_pTextureNeutral[MAX_TEXNEUTRAL];
	D3DXVECTOR3 m_move;
	D3DXVECTOR3 m_pos;
	TYPE m_Type;
	NEUTRAL m_Neutral;
};

//====================================================================================================
// マクロ定義
//==================================================================================================== 
#endif