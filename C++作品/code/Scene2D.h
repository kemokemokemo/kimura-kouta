//====================================================================================================
//
// 2D処理 (Scene.h)
// Author (Kimura kouta)
//
//====================================================================================================
#ifndef _SCENE2D_H_
#define _SCENE2D_H_

//====================================================================================================
//インクリードファイル
//====================================================================================================
#include"main.h"
#include"Scene.h"

//====================================================================================================
// マクロ定義
//==================================================================================================== 
#define TEXTUER_001 "DATA/TEX/player000.png"				//読み込むテクスチャファイル名
#define TEXTUER_002 "DATA/TEX/bullet001.png"				//読み込むテクスチャファイル名
#define TEXTUER_003 "DATA/TEX/explosion000.png"				//読み込むテクスチャファイル名
#define TEXTUER_004 "DATA/TEX/enemy01.png"					//読み込むテクスチャファイル名
#define TEXTUER_005 "DATA/TEX/bg100.png"					//読み込むテクスチャファイル名
#define TEXTUER_006 "DATA/TEX/bg101.png"					//読み込むテクスチャファイル名
#define TEXTUER_007 "DATA/TEX/bg102.png"					//読み込むテクスチャファイル名
#define TEXTUER_008 "DATA/TEX/Neutral01.png"				//読み込むテクスチャファイル名
#define TEXTUER_009 "DATA/TEX/pipo-btleffect044.png"		//読み込むテクスチャファイル名
#define TEXTUER_010 "DATA/TEX/pipo-btleffect018.png"		//読み込むテクスチャファイル名
#define TEXTUER_011 "DATA/TEX/Life001.png"					//読み込むテクスチャファイル名
#define TEXTUER_012 "DATA/TEX/pipo-btleffect134.png"		//読み込むテクスチャファイル名
#define TEXTUER_013 "DATA/TEX/Item000.png"					//読み込むテクスチャファイル名
#define TEXTUER_014 "DATA/TEX/pipo-btleffect019.png"		//読み込むテクスチャファイル名
#define TEXTUER_015 "DATA/TEX/title.png"					//読み込むテクスチャファイル名
#define TEXTUER_016 "DATA/TEX/result.JPG"					//読み込むテクスチャファイル名
#define TEXTUER_017 "DATA/TEX/1HPbar.png"					//読み込むテクスチャファイル名
#define TEXTUER_018 "DATA/TEX/boss001.png"					//読み込むテクスチャファイル名
#define TEXTUER_019 "DATA/TEX/OVER.png"						//読み込むテクスチャファイル名
#define TEXTUER_020 "DATA/TEX/Neutral002.png"				//読み込むテクスチャファイル名
#define TEXTUER_021 "DATA/TEX/press_enter.png"				//読み込むテクスチャファイル名
#define TEXTUER_022 "DATA/TEX/titlelog.png"					//読み込むテクスチャファイル名
#define TEXTUER_023 "DATA/TEX/tutorial.png"					//読み込むテクスチャファイル名
#define TEXTUER_024 "DATA/TEX/RankBG.png"					//読み込むテクスチャファイル名
#define TEXTUER_025 "DATA/TEX/bariya.png"					//読み込むテクスチャファイル名
#define TEXTUER_026 "DATA/TEX/BulletMove000.png"			//読み込むテクスチャファイル名
#define TEXTUER_027 "DATA/TEX/tutorial2.png"				//読み込むテクスチャファイル名
#define TEXTUER_028 "DATA/TEX/bg100.png"					//読み込むテクスチャファイル名
#define TEXTUER_029 "DATA/TEX/bg101.png"					//読み込むテクスチャファイル名



//================================================================
// レンダリングクラス
//================================================================
class CScene2D : public CScene
{
public:

	typedef enum
	{
		MODE_NORMAL = 0,
		MODE_BATTLE,
		MODE_MAX,
	} MODESTATE;

	//================================================================
	// プロトタイプ宣言
	//================================================================
	CScene2D(OBJTYPE nPriority);
	CScene2D();
	~CScene2D();

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	D3DXVECTOR3 GetPos(void);
	void SetPos(D3DXVECTOR3 pos);
	void SetSize(float Size_x, float Size_y);
	void SetColor(D3DXCOLOR Color);
	void SetSpeed(float tex);
	void UIUpdate(int nLife,int size);
	void TexMove();
	void SetTex(int nDigits);
	//void CollisionTest2();
	void SetModeState(MODESTATE mode);
	MODESTATE GetModeState(void);
	void BgUpdate();

	void BindTexture(LPDIRECT3DTEXTURE9 cName);
	void SetAnim(float fHeight, float fWidht,float fWidht2,int fChange);
	void SetInitTex(float fHeight, float fWidht);
	void SetRadius(float fRadius);

private:

	VERTEX_2D m_Vertex[4];
	LPDIRECT3DTEXTURE9 m_pTexturePolygon;
	D3DXVECTOR3 m_pos = D3DXVECTOR3(0.0f,0.0f,0.0f);	//ポジション
	D3DXVECTOR3 m_posmove;
	D3DXVECTOR2 m_tex;
	float m_PosSize_X;
	float m_PosSize_Y;
	float m_Rot = D3DX_PI*0.25f;
	float m_CountRot = 0.0f;
	float m_RotRand = 0.0f;
	D3DXCOLOR m_Col = D3DXCOLOR(1.0f,1.0f,1.0f,1.0f);
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuffScene = NULL;		// 頂点バッファへのポインタ
	int m_nCounterAnim;
	int m_nPatternAnim;
	float m_TexMove;
	float m_Speed;
	float m_fHeight;
	float m_fWidht;
	float m_fWidht2;
	MODESTATE m_ModeState;

};

//====================================================================================================
// マクロ定義
//==================================================================================================== 
#endif