//====================================================================================================
//
// �v���C���[���� (player.h)
// Author (Kimura kouta)
//
//====================================================================================================
#ifndef _PLAYER_H_
#define _PLAYER_H_

//====================================================================================================
//�C���N���[�h�t�@�C��
//====================================================================================================
#include"main.h"
#include"Scene2D.h"

class CBullet;
//================================================================
// �����_�����O�N���X
//================================================================
class CPlayer : public CScene2D
{
public:
	typedef enum
	{
		PLAYERSTATE_NORMAL = 0,
		PLAYERSTATE_DAMAGE,
		PLAYERSTATE_DEATH,
		PLAYERSTATE_MAX,
	} PLAYERSTATE;

	//================================================================
	// �v���g�^�C�v�錾
	//================================================================
	CPlayer(OBJTYPE type);
	CPlayer();
	~CPlayer();

	HRESULT Init(D3DXVECTOR3 pos);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	void PlayerMove(void);

	static CPlayer *Create(D3DXVECTOR3 pos);
	static HRESULT Load(void);
	static void Unload(void);
	static CBullet *GetBullet(void);
	D3DXVECTOR3 GetPlayerPos(void);
	void PlayerDamage(int nDamage);
	void Damage(void);
	void MoveLimit(void);
	static int GetLife(void);

private:

	VERTEX_2D m_Vertex[4];
	static LPDIRECT3DTEXTURE9 m_pTexturePlayer;
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuffPlayer = NULL;		// ���_�o�b�t�@�ւ̃|�C���^

	D3DXVECTOR3 m_PlayerPos;		//�v���C���[�̃|�W�V����
	static int m_nLife;				//�v���C���[�̃��C�t
	PLAYERSTATE m_PlayerState;		//�v���C���[�̏��
	int m_PlayerStateCount;
	int m_DeathCount;
	int BulletLimit;
};

//====================================================================================================
// �}�N����`
//==================================================================================================== 
#endif
