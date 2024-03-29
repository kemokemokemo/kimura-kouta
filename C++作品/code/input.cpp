//====================================================================================================
//
// 入力処理 (input.cpp)
// Author (Kimura kouta)
//
//====================================================================================================
#include "input.h"
#include "keybord.h"

//====================================================================================================
// マクロ定義
//==================================================================================================== 

//====================================================================================================
// プロトタイプ宣言
//====================================================================================================

//====================================================================================================
// グローバル変数
//====================================================================================================
LPDIRECTINPUT8 CInput::m_pInput = NULL;
LPDIRECTINPUTDEVICE8 CInput::m_pDevKeyboard = NULL;

//====================================================================================================
// コンストラクタ
//====================================================================================================
CInput::CInput()
{

}

HRESULT CInput::Init(HINSTANCE hInstance, HWND hWnd)
{
	// DirectInputオブジェクトの作成
	if (FAILED(DirectInput8Create(hInstance, DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&m_pInput, NULL)))
	{
		return E_FAIL;
	}

	// 入力デバイス（キーボード）の作成
	if (FAILED(m_pInput->CreateDevice(GUID_SysKeyboard, &m_pDevKeyboard, NULL)))
	{
		return E_FAIL;
	}

	// データフォーマットを設定
	if (FAILED(m_pDevKeyboard->SetDataFormat(&c_dfDIKeyboard)))
	{
		return E_FAIL;
	}

	// 協調モードを設定（フォアグラウンド＆非排他モード）
	if (FAILED(m_pDevKeyboard->SetCooperativeLevel(hWnd, (DISCL_FOREGROUND | DISCL_NONEXCLUSIVE))))
	{
		return E_FAIL;
	}

	// キーボードへのアクセス権を獲得(入力制御開始)
	m_pDevKeyboard->Acquire();

	return S_OK;
}

void CInput::Uninit(void)
{
	// 入力デバイス(キーボード)の開放
	if (m_pDevKeyboard != NULL)
	{
		m_pDevKeyboard->Unacquire();
		m_pDevKeyboard->Release();
		m_pDevKeyboard = NULL;
	}

	// DirectInputオブジェクトの開放
	if (m_pInput != NULL)
	{
		m_pInput->Release();
		m_pInput = NULL;
	}
}

//====================================================================================================
// インプットの取得
//====================================================================================================
LPDIRECTINPUT8 CInput::GetInput(void)
{
	return m_pInput;
}

//====================================================================================================
// キーボードの取得
//====================================================================================================
LPDIRECTINPUTDEVICE8 CInput::GetDevKeyboard(void)
{
	return m_pDevKeyboard;
}

//====================================================================================================
// デストラクタ
//====================================================================================================
CInput::~CInput()
{

}