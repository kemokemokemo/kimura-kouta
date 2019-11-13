//=============================================================================
//
// �T�E���h���� [sound.h]
// Author :kimura kouta
//
//=============================================================================
#ifndef _SOUND_H_
#define _SOUND_H_

#include "main.h"
#include"xaudio2.h"

//=============================================================================
// �T�E���h�t�@�C��
//=============================================================================
typedef enum
{
	SOUND_LABEL_BGM000 = 0,		// BGM0
	SOUND_LABEL_BGM001,			// BGM1
	SOUND_LABEL_BGM002,			// BGM2
	SOUND_LABEL_BGM003,			// BGM3
	SOUND_LABEL_BGM004,			// BGM4
	SOUND_LABEL_BGM005,			// BGM5
	SOUND_LABEL_SE_SHOT,		// �e���ˉ�
	SOUND_LABEL_SE_HIT,			// �q�b�g��
	SOUND_LABEL_SE_EXPLOSION,	// ������
	SOUND_LABEL_SE_ENTER,		//ENTER�̌��艹
	SOUND_LABEL_SE_SUCORUP,		//�X�R�A�A�b�v��
	SOUND_LABEL_SE_SUCORDOWN,	//�X�R�A�_�E����
	SOUND_LABEL_SE_KYOUKA,		//������
	SOUND_LABEL_SE_BULLETMOVE,	//������
	SOUND_LABEL_MAX,
} SOUND_LABEL;

//================================================================
// �����_�����O�N���X
//================================================================
class CSound
{
public:

	//=============================================================================
	// �v���g�^�C�v�錾
	//=============================================================================
	HRESULT InitSound(HWND hWnd);
	void UninitSound(void);

	HRESULT PlaySound(SOUND_LABEL label);
	void StopSound(SOUND_LABEL label);
	void StopSound(void);


	//=============================================================================
	// �p�����[�^�\���̒�`
	//=============================================================================
	typedef struct
	{
		char *pFilename;	// �t�@�C����
		int nCntLoop;		// ���[�v�J�E���g
	} SOUNDPARAM;

	//=============================================================================
	// �v���g�^�C�v�錾
	//=============================================================================
	HRESULT CheckChunk(HANDLE hFile, DWORD format, DWORD *pChunkSize, DWORD *pChunkDataPosition);
	HRESULT ReadChunkData(HANDLE hFile, void *pBuffer, DWORD dwBuffersize, DWORD dwBufferoffset);

	//=============================================================================
	// �O���[�o���ϐ�
	//=============================================================================
	static IXAudio2 *m_pXAudio2;							// XAudio2�I�u�W�F�N�g�ւ̃C���^�[�t�F�C�X
	static IXAudio2MasteringVoice *m_pMasteringVoice;			// �}�X�^�[�{�C�X
	static IXAudio2SourceVoice *m_apSourceVoice[SOUND_LABEL_MAX];	// �\�[�X�{�C�X
	static BYTE *m_apDataAudio[SOUND_LABEL_MAX];					// �I�[�f�B�I�f�[�^
	static DWORD m_aSizeAudio[SOUND_LABEL_MAX];					// �I�[�f�B�I�f�[�^�T�C�Y

																// �e���f�ނ̃p�����[�^
	static SOUNDPARAM m_aParam[SOUND_LABEL_MAX];

private:
};
#endif
