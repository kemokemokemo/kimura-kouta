//====================================================================================================
//
// �{�X���� (boss.h)
// Author (Kimura kouta)
//
//====================================================================================================
#ifndef _BOSS_H_
#define _BOSS_H_

//====================================================================================================
//�C���N���[�h�t�@�C��
//====================================================================================================
#include"main.h"
#include"enemy.h"
#include"Scene2D.h"

#define MAX_TEXBOSS (1)	//�ǂݍ��ރe�N�X�`���t�@�C����

//================================================================
// �����_�����O�N���X
//================================================================
class CBoss : public CScene2D
{
public:

	typedef enum
	{
		BOSSSTATE_NORMAL = 0,		//�{�X�̒ʏ���
		BOSSSTATE_DAMAGE,			//�{�X�̖��G���
		BOSSSTATE_MAX,
	} BOSSSTATE;

	typedef enum
	{
		BOSSPATTERN_01 = 0,
		BOSSPATTERN_02,
		BOSSPATTERN_03,
		BOSSPATTERN_04,
		BOSSPATTERN_MAX,
	} BOSSPATTERN;

	//================================================================
	// �v���g�^�C�v�錾
	//================================================================
	CBoss(OBJTYPE type);		// �`�揇�Ԃ̐ݒ�
	CBoss();					// �R���X�g���N�^
	~CBoss();					// �f�X�g���N�^

	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 move);		// ������
	void Uninit(void);										// �I��
	void Update(void);										// �X�V
	void Draw(void);										// �`��



	static CBoss *Create(D3DXVECTOR3 pos, D3DXVECTOR3 move);		// �{�X�̐���
	static HRESULT Load(void);										// �e�N�X�`���̓ǂݍ���
	static void Unload(void);										// �e�N�X�`���̔j��

	static D3DXVECTOR3 GetEPos(void);				// �{�X�̈ʒu���̎擾
	static D3DXVECTOR3 GetMove(void);				// �{�X�̈ړ��l�̎擾
	static int GetLife(void);						// �{�X��HP�̎擾

	void SetMove(D3DXVECTOR3 move);					// �{�X�̈ړ��l�̊l��

	void BossDamage(int nDamage);					// �{�X�̃_���[�W����
	void CollisionB_PL(void);						// �{�X�ƃv���C���[�̓����蔻��
	void MoveAI(void);								// �{�X�̈ړ�����
	void BossAI01(void);							// �{�X��AI�p�^�[��
	void BossAI02(void);							// �{�X��AI�p�^�[��
	void BossAI03(void);							// �{�X��AI�p�^�[��
	void BossAI04(void);							// �{�X��AI�p�^�[��
	void BossAI05(void);							// �{�X��AI�p�^�[��

private:

	static LPDIRECT3DTEXTURE9 m_pTextureBoss[MAX_TEXBOSS];		// �{�X�̃e�N�X�`���̏��
	static D3DXVECTOR3 m_move;									// �{�X�̈ړ��l
	static D3DXVECTOR3 m_pos;									// �{�X�̈ʒu
	static int m_nLife;											// �{�X�̃��C�t

	BOSSSTATE m_BossState;			// �v���C���[�̏��
	BOSSPATTERN m_BossPattern;		// �{�X��AI�p�^�[��

	int m_nBossCnt;					//�{�X�o��̃J�E���g
	int m_nBulletCnt;				//�{�X�̒e���˃J�E���g
	int m_nBulletCnt2;				//�{�X�̒e���˃J�E���g

	bool m_bBossT;					// �{�X�̃p�^�[���擾�Ǘ�
	bool m_bBossB;					// �{�X�̃o���A�����Ǘ�
	bool m_bBossM;					// �{�X�̈ړ��Ǘ�

	float m_fRangeX;				// �G�ƃv���C���[�̋���X
	float m_fRangeY;				// �G�ƃv���C���[�̋���Y
	float m_fAnglePlayer;			// �v���C���[�ւ̒e�̔��ˊp�x
	float m_fAngleBoss;				// �p�x�v�Z�p�ϐ�
	float m_fAngle;					// �e�̔��ˊp�x
	float m_fRadius;				// ���a�p�ϐ�
	float m_fAdd_x;					// X���v�Z�ϐ�
	float m_fAdd_y;					// Y���v�Z�ϐ�
	
};

//====================================================================================================
// �}�N����`
//==================================================================================================== 
#endif
