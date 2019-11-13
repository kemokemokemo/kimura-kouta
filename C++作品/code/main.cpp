//====================================================================================================
//
// メイン (main.cpp)
// Author (Kimura kouta)
//
//====================================================================================================
#include"main.h"
#include"manager.h"

//====================================================================================================
// マクロ定義
//==================================================================================================== 
#define CLASS_NAME	"WindowClass"    //ウィンドウクラスの名前
#define WINDOW_NAME	"BirdProtect"//キャプション

//================================================================
// プロトタイプ宣言
//================================================================
LRESULT CALLBACK WindowsProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

//=====================================================================================================
// グローバル変数
//=====================================================================================================
#ifdef _DEBUG
LPD3DXFONT			g_pFont = NULL;			// フォントへのポインタ
int					g_nCountFPS = 0;		// FPSカウンタ
#endif

//====================================================================================================
//  メイン関数
//====================================================================================================
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hInstaPer, LPSTR lpCnd, int nCandShow)
{
	RECT rect{ 0,0,SCREEN_WIDTH,SCREEN_HEIGHT };
		// 指定されたクライアント領域を確保するための計算
	AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, false);

	WNDCLASSEX wcex =
	{
		sizeof(WNDCLASSEX),					//WNDCLASSEXのメモリサイズ
		CS_CLASSDC,							//表示するウィンドウのスタイルを決定
		WindowsProc,						//ウィンドウプロシージャのアドレスを指定
		0,									//通定は使用しないので0
		0,									//通定は使用しないので0
		hInstance,							//windowsの引数のインプット

		LoadIcon(NULL,IDI_APPLICATION),		//タスクバーに
		LoadCursor(NULL,IDC_ARROW),			//使用マウスカーソルの色決定＿変更なし
		(HBRUSH)(COLOR_WINDOW + 1),
		NULL,								//メニューを指定
		CLASS_NAME,							//ウィンドウクラスの名前
		LoadIcon(NULL,IDI_APPLICATION)		//小さいアイコンの措定＿いじる可能性あり


	};
	HWND hwnd;
	MSG msg;
	DWORD dwCurrentTime;//
	DWORD dwExeclastTime;//

	DWORD dwFrameCount;
	DWORD dwFPSLastTime;

		//ウィンドウクラスの登録
		RegisterClassEx(&wcex);

		//ウィンドウクラスの登録
		hwnd = CreateWindowEx(0,
			CLASS_NAME,						//ウィンドウクラス名
			WINDOW_NAME,					//ウィンドウの名前
			WS_OVERLAPPEDWINDOW,			//ウィンドウスタイル
			CW_USEDEFAULT,					//ウィンドウの左上X軸_変更の可能性あり
			CW_USEDEFAULT,					//ウィンドウの左上Y軸_変更の可能性あり
			(rect.right - rect.left),			//ウィンドウの幅
			(rect.bottom - rect.top),			//ウィンドウの高さ
			NULL,							//親ウィンドウのハンドル
			NULL,							//メニューハンドルまたは子ウィンドウ
			hInstance,					    //インスタンスハンドル
			NULL);						    //ウィンドウ作成データ

		CManager*pManager;

		pManager = new CManager;

	//初期化処理
	if (FAILED(pManager->Init(hInstance,hwnd, FALSE)))
	{
		return-1;
	}


	//ウィンドウの表示
	ShowWindow(hwnd, nCandShow);		//指定されたウィンドウの表示設定
	UpdateWindow(hwnd);					//ウィンドウのクライアント領域更新

										//メッセージループ(メッセージキューからメッセージを取得)
	dwCurrentTime = 0;
	dwExeclastTime = timeGetTime();

	dwFrameCount = 0;
	dwFPSLastTime = timeGetTime();		// システム時刻をミリ秒単位で取得

	//メッセージループ
	while (1)
	{//メッセージを取得しなかったら0を返す
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE) != 0)
		{//Window処理
			if (msg.message == WM_QUIT)
			{//WM_QUITメッセージが送られてくると終了
				break;
			}
			else
			{//メッセージの翻訳
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
		}
		else
		{//Directxの処理
			dwCurrentTime = timeGetTime();
			dwCurrentTime = timeGetTime();		// システム時刻を取得

			if ((dwCurrentTime - dwFPSLastTime) >= 500)	// 0.5秒ごとに実行
			{
#ifdef _DEBUG
				g_nCountFPS = (dwFrameCount * 1000) / (dwCurrentTime - dwFPSLastTime);		// FPSを測定
#endif

				dwFPSLastTime = dwCurrentTime;		// FPSを測定した時刻を保存
				dwFrameCount = 0;					// カウントをクリア
			}
			if ((dwCurrentTime - dwExeclastTime) >= (1000 / 60))
			{
				dwExeclastTime = dwCurrentTime;

				//更新処理
				pManager->Update();
				//描画処理
				pManager->Draw();

				dwFrameCount++;			// カウントを加算
			}
		}
	}

	//終了処理
	if (pManager != NULL)
	{
		pManager->Uninit();
		delete pManager;
		pManager = NULL;
	}

	//ウィンドウクラスの登録解除
	UnregisterClass(CLASS_NAME, wcex.hInstance);

	return(int)msg.wParam;
}

//===========================================================================================
//ウィンドウプロシージャー関数
//===========================================================================================
LRESULT CALLBACK WindowsProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_DESTROY:			  //ウィンドウ確率メッセージ
								  //ウィンドウを破棄(WM_DESTROYメッセージの発生)
		PostQuitMessage(0);		  //閉じる処理
		break;

	case WM_KEYDOWN:			  //キーが押された際のメッセージ表示
		switch (wParam)
		{
		case VK_ESCAPE:
			DestroyWindow(hWnd);  //[ESC]キーが押された際のメッセージ表示
			break;
		}
		break;
	case WM_CLOSE:

		DestroyWindow(hWnd);	  //[ESC]キーが押された際のメッセージ表示
		break;
	default:
		break;
	}
	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}

#ifdef _DEBUG
int GetFPS()
{
	return g_nCountFPS;
}
#endif
