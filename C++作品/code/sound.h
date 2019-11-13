//=============================================================================
//
// サウンド処理 [sound.h]
// Author :kimura kouta
//
//=============================================================================
#ifndef _SOUND_H_
#define _SOUND_H_

#include "main.h"
#include"xaudio2.h"

//=============================================================================
// サウンドファイル
//=============================================================================
typedef enum
{
	SOUND_LABEL_BGM000 = 0,		// BGM0
	SOUND_LABEL_BGM001,			// BGM1
	SOUND_LABEL_BGM002,			// BGM2
	SOUND_LABEL_BGM003,			// BGM3
	SOUND_LABEL_BGM004,			// BGM4
	SOUND_LABEL_BGM005,			// BGM5
	SOUND_LABEL_SE_SHOT,		// 弾発射音
	SOUND_LABEL_SE_HIT,			// ヒット音
	SOUND_LABEL_SE_EXPLOSION,	// 爆発音
	SOUND_LABEL_SE_ENTER,		//ENTERの決定音
	SOUND_LABEL_SE_SUCORUP,		//スコアアップ音
	SOUND_LABEL_SE_SUCORDOWN,	//スコアダウン音
	SOUND_LABEL_SE_KYOUKA,		//強化音
	SOUND_LABEL_SE_BULLETMOVE,	//竜巻音
	SOUND_LABEL_MAX,
} SOUND_LABEL;

//================================================================
// レンダリングクラス
//================================================================
class CSound
{
public:

	//=============================================================================
	// プロトタイプ宣言
	//=============================================================================
	HRESULT InitSound(HWND hWnd);
	void UninitSound(void);

	HRESULT PlaySound(SOUND_LABEL label);
	void StopSound(SOUND_LABEL label);
	void StopSound(void);


	//=============================================================================
	// パラメータ構造体定義
	//=============================================================================
	typedef struct
	{
		char *pFilename;	// ファイル名
		int nCntLoop;		// ループカウント
	} SOUNDPARAM;

	//=============================================================================
	// プロトタイプ宣言
	//=============================================================================
	HRESULT CheckChunk(HANDLE hFile, DWORD format, DWORD *pChunkSize, DWORD *pChunkDataPosition);
	HRESULT ReadChunkData(HANDLE hFile, void *pBuffer, DWORD dwBuffersize, DWORD dwBufferoffset);

	//=============================================================================
	// グローバル変数
	//=============================================================================
	static IXAudio2 *m_pXAudio2;							// XAudio2オブジェクトへのインターフェイス
	static IXAudio2MasteringVoice *m_pMasteringVoice;			// マスターボイス
	static IXAudio2SourceVoice *m_apSourceVoice[SOUND_LABEL_MAX];	// ソースボイス
	static BYTE *m_apDataAudio[SOUND_LABEL_MAX];					// オーディオデータ
	static DWORD m_aSizeAudio[SOUND_LABEL_MAX];					// オーディオデータサイズ

																// 各音素材のパラメータ
	static SOUNDPARAM m_aParam[SOUND_LABEL_MAX];

private:
};
#endif
