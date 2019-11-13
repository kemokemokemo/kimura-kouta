//====================================================================================================
//
// シーン処理 (Scene.h)
// Author (Kimura kouta)
//
//====================================================================================================
#ifndef _SCENE_H_
#define _SCENE_H_

//====================================================================================================
//インクリードファイル
//====================================================================================================
#include"main.h"

//====================================================================================================
// マクロ定義
//==================================================================================================== 
#define MAX_POLYGON		(256)
#define MAX_PRIPRI	(7)

//================================================================
// レンダリングクラス
//================================================================
class CScene
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

	//====================================================================================================
	// 列挙型定義
	//=====================================================================================================
	typedef enum
	{
		OBJTYPE_BG,
		OBJTYPE_RANKING,
		OBJTYPE_PLAYER,
		OBJTYPE_ENEMY,
		OBJTYPE_BOSS,
		OBJTYPE_BULLET,
		OBJTYPE_EFFECT,
		OBJTYPE_NEUTRAL,
		OBJTYPE_ITEM,
		OBJTYPE_EXPLOSION,
		OBJTYPE_SCORE,
		OBJTYPE_LIFE,
		OBJTYPE_ANIMATION,
		OBJTYPE_MAX,
	} OBJTYPE;

	//================================================================
	// プロトタイプ宣言
	//================================================================
	CScene(OBJTYPE nPriority);
	CScene();
	virtual ~CScene();

	virtual HRESULT Init(void) =0;
	virtual void Uninit(void) = 0;
	virtual void Update(void) = 0;
	virtual void Draw(void) = 0;

	static void ReleaseAll(void);
	static void UpdateAll(void);
	static void DrawAll(void);

	OBJTYPE GetObjType(void);
	void Release(void);

protected:


	 void SetObjType(OBJTYPE Type);
	 CScene *GetScene(OBJTYPE nPriority,int bID);
	 
private:

	//スタティック変数
	static CScene *m_apScene[OBJTYPE_MAX][MAX_POLYGON];
	static int nNumAll;		//総数

	OBJTYPE objType;

	//変数
	int m_bID;	//自分の番号

	int m_nPriority;	//優先順位

};


//====================================================================================================
// マクロ定義
//==================================================================================================== 
#endif