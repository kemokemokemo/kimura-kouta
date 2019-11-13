//====================================================================================================
//
// ゲージ処理 (gauge.h)
// Author (Kimura kouta)
//
//====================================================================================================
#ifndef _GAUGE_H_
#define _GAUGE_H_

//====================================================================================================
//インクリードファイル
//====================================================================================================
#include"main.h"
#include"Scene2D.h"

#define MAX_TEXGAUGE (1)	//読み込むテクスチャファイル名

//================================================================
// レンダリングクラス
//================================================================
class CGauge : public CScene2D
{
public:

	typedef enum
	{
		GAUGE_PLAYER = 0,
		GAUGE_ENEMY,
		GAUGE_BOSS,
		GAUGE_MAX,
	} GAUGE;

	//================================================================
	// プロトタイプ宣言
	//================================================================
	CGauge(OBJTYPE type);
	CGauge();
	~CGauge();

	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 move,GAUGE Gauge);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	void SetMove(D3DXVECTOR3 move);
	void SetLife(int nLife);
	D3DXVECTOR3 Getmove();
	int GetLife();
	static CGauge *Create(D3DXVECTOR3 pos, D3DXVECTOR3 move, GAUGE Gauge);
	static HRESULT Load(void);
	static void Unload(void);


private:

	VERTEX_2D m_Vertex[4];
	static LPDIRECT3DTEXTURE9 m_pTextureGauge[MAX_TEXGAUGE];
	D3DXVECTOR3 m_move;
	D3DXVECTOR3 m_pos;
	float Size;
	int m_nLife;
	GAUGE m_aGauge;
};

//====================================================================================================
// マクロ定義
//==================================================================================================== 
#endif
