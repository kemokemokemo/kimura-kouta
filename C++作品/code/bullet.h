//====================================================================================================
//
// �e���� (bullet.h)
// Author (Kimura kouta)
//
//====================================================================================================
#ifndef _BULLET_H_
#define _BULLET_H_

//====================================================================================================
//�C���N���[�h�t�@�C��
//====================================================================================================
#include"main.h"
#include"Scene2D.h"

#define MAX_TEXBULLET (2)	//�ǂݍ��ރe�N�X�`���t�@�C����
class CBullet;

//================================================================
// �����_�����O�N���X
//================================================================
class CBullet : public CScene2D
{
public:

	//====================================================================================================
	// �񋓌^��`
	//=====================================================================================================
	typedef enum
	{
		BULLETTYPE_PLAYER = 0,
		BULLETTYPE_ENEMY,
		BULLETTYPE_BOSS,
		BULLETTYPE_MAX,
	} BULLETTYPE;

	typedef enum
	{
		BULLETTEX_PLAYER = 0,
		BULLETTEX_BOSS_NORMAL,
		BULLETTEX_MAX,
	} BULLETTEX;

	//================================================================
	// �v���g�^�C�v�錾
	//================================================================
	CBullet(OBJTYPE type);
	CBullet();
	~CBullet();

	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 move, BULLETTEX BulletTex, int nLife);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	void SetMove(D3DXVECTOR3 move);
	int GetLife();
	static CBullet *Create(D3DXVECTOR3 pos, D3DXVECTOR3 move, BULLETTYPE BulletType, BULLETTEX BulletTex,int nLife);
	static HRESULT Load(void);
	static void Unload(void);
	void BulletType(BULLETTYPE BulletType);		//�����ƒe�̓����蔻��
	void EnemyCollision(void);					//�G�ƒe�̓����蔻��
	void PlayerCollision(void);					//�����ƒe�̓����蔻��
	void NeutralCollision(void);				//�����ƒe�̓����蔻��
	void BossCollision(void);

private:

	VERTEX_2D m_Vertex[4];
	static LPDIRECT3DTEXTURE9 m_pTextureBullet[MAX_TEXBULLET];
	D3DXVECTOR3 m_move;
	D3DXVECTOR3 m_pos;
	float Size;
	int m_nLife;
	BULLETTYPE m_BulletType;
	BULLETTEX m_BulletTex;
};

//====================================================================================================
// �}�N����`
//==================================================================================================== 
#endif
