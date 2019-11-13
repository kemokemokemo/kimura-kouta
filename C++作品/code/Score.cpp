//=============================================================================
//
// �X�R�A���� [score.cpp]
// Author : KIMURA KOUTA
//
//=============================================================================
#include "Score.h"
#include "renderer.h"
#include "manager.h"

//=============================================================================
// �}�N����`
//=============================================================================
#define	TEXTURE_SCORE		"DATA/TEX/number000.png"	// �ǂݍ��ރe�N�X�`���t�@�C����
#define SCORE_POS_X	(0)			    //�|���S���̕\���ʒu(����X)
#define SCORE_POS_Y	(0)			    //�|���S���̕\���ʒu(����Y)
#define SCORE_SIZE_X	(20)			//�|���S���̃T�C�Y(����)
#define SCORE_SIZE_Y	(30)			//�|���S���̃T�C�Y(����)
#define SCORECOLOR_TEX   (255)

//=============================================================================
// �O���錾�̏�����
//=============================================================================
CNumber *CScore::m_apScore[MAX_SCORE] = {};
int CScore::m_nScore = NULL;

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CScore::CScore(OBJTYPE nPriority) : CScene(nPriority)
{
	int m_nScore = 0;
}

//=============================================================================
// ����������
//=============================================================================
HRESULT CScore::Init(void)
{
	int nScore = CScore::GetScore();

	D3DXVECTOR3 pos;

	for (int nCntScore = 0; nCntScore < MAX_SCORE; nCntScore++)
	{
		pos = D3DXVECTOR3(1000.0f + (SCORE_SIZE_X +15.0f)*nCntScore, 10.0f + SCORE_SIZE_Y, 0.0f);

		int nDigits = nScore % (int)powf(10.0f,(float)MAX_SCORE - nCntScore) / (int)powf(10.0f, (float)MAX_SCORE - 1.0f - nCntScore);

		m_apScore[nCntScore] = CNumber::Create(pos, SCORE_SIZE_X, SCORE_SIZE_Y, nDigits);
	}

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void CScore::Uninit(void)
{
	for (int nCntScore = 0; nCntScore < MAX_SCORE; nCntScore++)
	{
		m_apScore[nCntScore]->Uninit();
	}
}

//=============================================================================
// �X�V����
//=============================================================================
void CScore::Update(void)
{
	for (int nCntScore = 0; nCntScore < MAX_SCORE; nCntScore++)
	{
		m_apScore[nCntScore]->Update();
	}
}

//=============================================================================
// �`�揈��
//=============================================================================
void CScore::Draw(void)
{
	for (int nCntScore = 0; nCntScore < MAX_SCORE; nCntScore++)
	{
		m_apScore[nCntScore]->Draw();
	}

}
//=============================================================================
// �X�R�A�̕ύX
//=============================================================================
CScore * CScore::Create(int nScore)
{
	
	CScore *pScore;

	pScore = new CScore(OBJTYPE_SCORE);

	pScore->SetScore(nScore);

	pScore->Init();

	return pScore;
}

//=============================================================================
// �X�R�A�̎擾
//=============================================================================
int CScore::GetScore()
{
	return m_nScore;
}

//=============================================================================
// �X�R�A�̎擾
//=============================================================================
CNumber *CScore::GetaScore()
{
	return m_apScore[MAX_SCORE];
}

//=============================================================================
// �X�R�A�̉��Z
//=============================================================================
void CScore::AddScore(int nNumber)
{
	m_nScore += nNumber;

	if (m_nScore <= 0)
	{
		m_nScore = 0;
	}

	for (int nCntScore = 0; nCntScore < MAX_SCORE; nCntScore++)
	{
		int nDigits = m_nScore % (int)powf(10.0f, (float)MAX_SCORE + nCntScore) / (int)powf(10.0f, (float)MAX_SCORE - 1.0f - nCntScore);

		m_apScore[nCntScore]->SetTex(nDigits);
	}
}

//=============================================================================
// �X�R�A�̃Z�b�g
//=============================================================================
void CScore::SetScore(int nScore)
{
	m_nScore = nScore;
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CScore::~CScore()
{

}