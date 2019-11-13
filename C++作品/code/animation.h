//=============================================================================
//
// �A�j���[�V�����̏��� [animation.h]
// Author : KIMURA KOUTA
//
//=============================================================================
#ifndef _ANIMATION_H_
#define _ANIMATION_H_

#define _CRT_SECURE_NO_WARNINGS

//=============================================================================
// �C���N���[�h�t�@�C��
//=============================================================================
#include "main.h"
#include "Scene2D.h"

//=============================================================================
// �}�N����`
//=============================================================================
#define MAX_ANIMATION (6)

//================================================================
// �����_�����O�N���X
//================================================================
class CAnimation : public CScene2D
{
public:

	typedef enum
	{
		ANIMATION_ENEMY = 0,
		ANIMATION_PLAYER,
		ANIMATION_NET,
		ANIMATION_POWERUP,
		ANIMATION_PRESSENTER,
		ANIMATION_TITLEBIRD,
		ANIMATION_MAX,
	} ANIM;

	//=============================================================================
	// �v���g�^�C�v�錾
	//=============================================================================
	CAnimation(OBJTYPE type);
	~CAnimation();

	HRESULT Init(D3DXVECTOR3 pos, ANIM Type, int nLife);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	static CAnimation *Create(D3DXVECTOR3 pos, ANIM nType, int nLife);
	static HRESULT Load(void);
	static void Unload(void);

private:

	static LPDIRECT3DTEXTURE9 m_pTextureAnimation[MAX_ANIMATION];
	int m_nLife;
	int m_EnterCnt;
	D3DXVECTOR3 m_pos;
	D3DXVECTOR3 m_move;
	ANIM m_Anim;
};

#endif