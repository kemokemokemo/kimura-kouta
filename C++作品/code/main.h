//====================================================================================================
//
// メイン (main.h)
// Author (Kimura kouta)
//
//====================================================================================================
#ifndef _MAIN_H_
#define _MAIN_H_

#define _CRT_SECURE_NO_WARNINGS

//====================================================================================================
//インクリードファイル
//====================================================================================================
#include<windows.h>
#include <stdio.h>
#include"d3dx9.h"		//描画処理に必要
#define DIRECTINPUT_VERSION	(0x0800)
#include"dinput.h"		//入力処理に必要

//====================================================================================================
//ライブラのリンク
//====================================================================================================
#pragma comment(lib,"d3d9.lib")		//描画処理に必要
#pragma comment(lib,"d3dx9.lib")	//[d3d9,lib]の拡張
#pragma comment(lib,"dxguid.lib")	//DirectXコンポーネント
#pragma comment(lib,"winmm.lib")	//システム時間に必要
#pragma comment(lib,"dinput8.lib")	//入力処理に必要

//====================================================================================================
// マクロ定義
//==================================================================================================== 
#define SCREEN_WIDTH	(1280)		//ウィンドウの幅
#define SCREEN_HEIGHT	(720)		//ウィンドウの高さ
#define FVF_VERTEX_2D	(D3DFVF_XYZRHW|D3DFVF_DIFFUSE|D3DFVF_TEX1)

int GetFPS();

#endif