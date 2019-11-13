//====================================================================================================
//
// �Q�[������ (Game.h)
// Author  Kimura Kouta
//
//====================================================================================================
#ifndef _GAME_H_
#define _GAME_H_

#define DIRECTINPUT_VERSION	(0x0800)
//====================================================================================================
//�C���N���[�h�t�@�C��
//====================================================================================================
#include"main.h"

class CManager;

class CScore;
class CTime;
class CLife;
class CRenderer;
class CSave;
class CRoad;

//================================================================
// �����_�����O�N���X
//================================================================
class CGame
{
public:

	// �v���g�^�C�v�錾
	CGame();
	~CGame();

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	static CTime*GetTime(void);

	static CGame * Create();
	void stage1(void);

private:


	static CScore *pScore;
	static CTime *pTime;
	static CLife *pLife;
	static CManager*m_pManager;
	static CSave *pSave;
	static CRoad*pLoad;

	static	int m_nSpownCnt;

};
#endif