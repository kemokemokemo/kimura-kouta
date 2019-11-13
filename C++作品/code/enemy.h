//====================================================================================================
//
// �G���� (enemy.h)
// Author (Kimura kouta)
//
//====================================================================================================
#ifndef _ENEMY_H_
#define _ENEMY_H_

//====================================================================================================
//�C���N���[�h�t�@�C��
//====================================================================================================
#include"main.h"
#include"Scene2D.h"

#define MAX_TEXENEMY (2)	//�ǂݍ��ރe�N�X�`���t�@�C����

//================================================================
// �����_�����O�N���X
//================================================================
class CEnemy : public CScene2D
{
public:

	typedef enum
	{
		ENEMYSTATE_NORMAL = 0,
		ENEMYSTATE_DAMAGE,
		ENEMYSTATE_DEATH,
		ENEMYSTATE_MAX,
	} ENEMYSTATE;

	typedef enum
	{
		AIPATTERN_1 = 0,
		AIPATTERN_2,
		AIPATTERN_3,
		AIPATTERN_4,
		AIPATTERN_5,
		AIPATTERN_MAX,
	} AIPATTERN;

	typedef enum
	{
		ENEMY_RIGHT = 0,
		ENEMY_LEFT,
		ENEMY_MAX,
	} ENEMY;

	//================================================================
	// �v���g�^�C�v�錾
	//================================================================
	CEnemy(OBJTYPE type);	//�`�揇�Ԃ̐ݒ�
	CEnemy();				//�R���X�g���N�^
	~CEnemy();				//�f�X�g���N�^

	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 move, int nLife, AIPATTERN Pattern, int nType);	//������
	void Uninit(void);			// �I��
	void Update(void);			// �X�V
	void Draw(void);			// �`��

	static CEnemy *Create(D3DXVECTOR3 pos, D3DXVECTOR3 move, int nLife, AIPATTERN Pattern, int nType);	// �G�̐���
	static HRESULT Load(void);				// �e�N�X�`���̓ǂݍ���
	static void Unload(void);				// �e�N�X�`���̔j��

	D3DXVECTOR3 GetEPos(void);				// �G�̃|�W�V�����̎擾
	D3DXVECTOR3 GetEMove(void);				// �G�̈ړ��l�̎擾

	void SetMove(D3DXVECTOR3 move);			// �ړ��l�̊l��
	void EnemyDamage(int nDamage);			// �G�̃_���[�W����
	void CollisionEN_PL(void);				// �G�ƃv���C���[�̓����蔻��
	void OffScreen(void);					// ��ʊO�̏���
	void Damage(void);						// �_���[�W���󂯂����̓_�ŏ���
	void MoveAI(void);						// �G�̈ړ�


	int GetType(void);						// �G�̎�ނ̎擾
	int GetELife(void);						// �G��HP�̎擾

private:

	static LPDIRECT3DTEXTURE9 m_pTextureEnemy[MAX_TEXENEMY];

	ENEMYSTATE m_EnemyState;	// �G�̏��
	AIPATTERN m_AiPattern;		// AI�p�^�[��
	ENEMY m_Enemy;				// �G�̕����̏��
	D3DXVECTOR3 m_move;			// �G�̈ړ��l���
	D3DXVECTOR3 m_pos;			// �G�̈ʒu���

	int m_nLife;				// HP�̏��
	int m_nBulletCount;			// �o���b�g�̔��ː���
	int m_Type;					// �G�̎��
	int m_EnemyStateCount;		// �G�̏�Ԃ̃J�E���g

	float m_fDistanceX;			// X���̌v�Z�p�ϐ�
	float m_fDistanceY;			// Y���̌v�Z�p�ϐ�
	float m_fDistance;			// ����
};

//====================================================================================================
// �}�N����`
//==================================================================================================== 
#endif
