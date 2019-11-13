//=============================================================================
//
// 数字処理 [number.h]
// Author :KIMURA KOUTA
//
//=============================================================================
#ifndef _NUMBER_H_
#define _NUMBER_H_

//=============================================================================
// インクルードファイル
//=============================================================================
#include "main.h"

//================================================================
// レンダリングクラス
//================================================================
class CNumber
{
public:

	//====================================================================================================
	// 構造体定義
	//=====================================================================================================
	typedef struct
	{
		D3DXVECTOR3 pos;	//ポジション
		float       rhw;	//1で固定する
		D3DCOLOR    col;	//色
		D3DXVECTOR2 tex;	//テクスチャ情報
	}VERTEX_2D;

	//================================================================
	// プロトタイプ宣言
	//================================================================
	CNumber();
	~CNumber();

	HRESULT Init();
	void Uninit(void);
	void Update(void);
	void Draw(void);

	static CNumber *Create(D3DXVECTOR3 pos, float size_x, float size_y, int nNumber);
	static HRESULT Load(void);
	static void Unload(void);
	void SetNumber(int nNumber);
	void SetPosition(D3DXVECTOR3 pos);
	void SetSize(float size_x, float size_y);
	void SetTex(int nDigits);

private:

	static LPDIRECT3DTEXTURE9 m_pTextureNumber;
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuffNumber;		// 頂点バッファへのポインタ
	D3DXVECTOR3 m_pos;
	float m_Size_X;
	float m_Size_Y;
	int m_nNumber;
};

//====================================================================================================
// マクロ定義
//==================================================================================================== 

#endif
