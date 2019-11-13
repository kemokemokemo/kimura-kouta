//=============================================================================
//
// キーボード処理 [keybord.h]
// Author :  Kimura Kouta
//
//=============================================================================
#ifndef _KEYBORD_H_
#define _KEYBORD_H_


//=============================================================================
// インクルードファイル
//=============================================================================
#include "main.h"
#include "input.h"

//=============================================================================
// マクロ定義
//=============================================================================
#define	NUM_KEY_MAX			(256)	// キーの最大数

//================================================================
// レンダリングクラス
//================================================================
class CKeybord : public CInput
{
public:

	// プロトタイプ宣言
	CKeybord();
	~CKeybord();

	HRESULT Init(HINSTANCE hInstance, HWND hWnd);
	void Uninit(void);
	void Update(void);
	bool GetKeyboardPress(int nKey);
	bool GetKeyboardTrigger(int nKey);

private:

	BYTE m_aKeyState[NUM_KEY_MAX] = {};
	BYTE m_aKeystateTrigger[NUM_KEY_MAX] = {};
};


#endif