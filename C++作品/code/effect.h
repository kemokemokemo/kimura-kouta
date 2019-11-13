//=============================================================================
//
// �G�t�F�N�g�̏��� [effect.h]
// Author : KIMURA KOUTA
//
//=============================================================================
#ifndef _EFFECT_H_
#define _EFFECT_H_

#define _CRT_SECURE_NO_WARNINGS

//=============================================================================
// �C���N���[�h�t�@�C��
//=============================================================================
#include "main.h"
#include "Scene2D.h"

//=============================================================================
// �}�N����`
//=============================================================================
#define	TEXTURE_EFFECT		"DATA/TEX/effect000.jpg"		// �ǂݍ��ރe�N�X�`���t�@�C����
#define	TEXTURE_EFFECT2		"DATA/TEX/effect001.jpg"		// �ǂݍ��ރe�N�X�`���t�@�C����
#define	TEXTURE_EFFECT3		"DATA/TEX/efect002.jpg"		// �ǂݍ��ރe�N�X�`���t�@�C����
#define	TEXTURE_EFFECT4		"DATA/TEX/effect003.jpg"		// �ǂݍ��ރe�N�X�`���t�@�C����
#define	TEXTURE_EFFECT5		"DATA/TEX/effect004.jpg"		// �ǂݍ��ރe�N�X�`���t�@�C����
#define	TEXTURE_EFFECT6		"DATA/TEX/effect005.jpg"		// �ǂݍ��ރe�N�X�`���t�@�C����
#define	MAX_EFFECT			(256)							// �G�t�F�N�g�̍ő吔
#define	MAX_EFFECTTEX		(1)							// �G�t�F�N�g�̍ő吔


//================================================================
// �����_�����O�N���X
//================================================================
class CEffect :public CScene
{
public:

	//=============================================================================
	// �v���g�^�C�v�錾
	//=============================================================================
	CEffect(OBJTYPE type);
	CEffect();
	~CEffect();
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static CEffect *Create();
	static HRESULT Load(void);
	static void Unload(void);
	static void MakeVertex(void);
	static void SetEffect(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXCOLOR col, int nLife);

private:

	// �\���̒�`
	typedef struct
	{
		D3DXVECTOR3 pos;		// �ʒu
		D3DXVECTOR3 move;		// �ړ���
		D3DXCOLOR col;			// �F
		float fRadius;			// ���a
		int nLife;				// �̗�
		bool bUse;				// �g�p���Ă��邩�ǂ���
	} EFFECT;

	static LPDIRECT3DTEXTURE9 m_pTextureEffect[MAX_EFFECTTEX];		// �e�N�X�`���ւ̃|�C���^
	static LPDIRECT3DVERTEXBUFFER9 m_pVtxBuffEffect;	// ���_�o�b�t�@�ւ̃|�C���^
	static EFFECT m_aEffect[MAX_EFFECT];				// �G�t�F�N�g���

};

#endif