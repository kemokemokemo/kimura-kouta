//=============================================================================
//
// �X�R�A���� [score.h]
// Author :KIMURA KOUTA
//
//=============================================================================
#ifndef _SCORE_H_
#define _SCORE_H_

//=============================================================================
// �C���N���[�h�t�@�C��
//=============================================================================
#include "main.h"
#include "Scene.h"
#include "Number.h"

#define MAX_SCORE   (8)

class CNumber;

//================================================================
// �����_�����O�N���X
//================================================================
class CScore : public CScene
{
public:

	//================================================================
	// �v���g�^�C�v�錾
	//================================================================
	CScore(OBJTYPE nPriority);
	~CScore();

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	static CScore *Create(int nScore);
	static int GetScore();
	static CNumber *GetaScore();
	void AddScore(int nNumber);
	void SetScore(int nScore);

private:

	static CNumber *m_apScore[MAX_SCORE];
	static int m_nScore;
};

//====================================================================================================
// �}�N����`
//==================================================================================================== 

#endif
