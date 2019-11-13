//=============================================================================
//
// �����̏��� [explosion.h]
// Author : KIMURA KOUTA
//
//=============================================================================
#ifndef _EXPLOSION_H_
#define _EXPLOSION_H_

#define _CRT_SECURE_NO_WARNINGS

//=============================================================================
// �C���N���[�h�t�@�C��
//=============================================================================
#include "main.h"
#include "Scene2D.h"

//=============================================================================
// �}�N����`
//=============================================================================
#define MAX_TEXE (1)

//=============================================================================
// �\���̒�`
//=============================================================================
typedef struct
{
	D3DXVECTOR3 pos;		// �ʒu
	D3DXVECTOR3 move;		// �ړ�
	D3DXMATRIX  mtxWorldWall;			//���[���h�}�g���b�N�X
	D3DXCOLOR col;			// �F
	float fRadius;			// ���a
	int nLife;				// ���C�t
	int nType;
	int ParticlenType;
	bool bUse;				// �g�p���Ă��邩�ǂ���
} EFFECT;

//================================================================
// �����_�����O�N���X
//================================================================
class CExplosion : public CScene2D
{
public:

	//=============================================================================
	// �v���g�^�C�v�錾
	//=============================================================================
	CExplosion(OBJTYPE type);
	~CExplosion();

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	static CExplosion *Create();
	static HRESULT Load(void);
	static void Unload(void);
	static void SetParticle(void);

private:

	static LPDIRECT3DTEXTURE9 m_pTextureExplosion[MAX_TEXE];
	int m_nLife;
};

#endif