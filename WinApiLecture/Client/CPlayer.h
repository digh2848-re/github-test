#pragma once

#include "CObject.h"



enum class PLAYER_STATE
{
	IDLE,
	WALK,
	LADDER,
	ATTACK,
	JUMP,
	INJURE,
	DEAD,
};

enum class PlAYER_ATTACK_STATE
{
	NORMAL_ATT_1,
	NORMAL_ATT_2,
	NORMAL_ATT_3,

	SKILL_ATT_1,
	//..
};

enum class PlayerWearState
{
	NO_WEAR,
	WEAPON_WEAR,
	ALL_WEAR
};

class CTexture;
class CSound;
class Pet;

class CPlayer
	: public CObject
{
public:
	CPlayer();
	~CPlayer();

public:

	virtual void update();
	virtual void render(HDC _dc);

private:
	void CreateMissile();
	void CreateMoveSkill();
	void CreateJumpSkill();
	void CreateLevelSkill();
	void CreateWideSkill();
	void CreateSkill3();
	void CreatePet();
	void update_state();
	void update_move();
	void update_animation();
	void update_gravity();

	virtual void OnCollisionEnter(CCollider* _pOther);
	virtual void OnCollision(CCollider* _pOther);
	virtual void OnCollisionExit(CCollider* _pOther);
public:

	void CreatePlayerEffect();

	// �ؽ��� ���� �ٲ��ִ� �Լ�
	void SetWearState(PlayerWearState _curWearState);

	UINT GetLevel() { return m_Level; }

	// ����ġ ������Ű�� �Լ�
	void AddExp() { m_Exp += 10; }

	CObject* GetPet() {
		assert(m_mypet1);
		return m_mypet1;
	}

	bool GetIsDead() { return IsDead; }
	int GetHp() { return m_HP; }
	void SetDead(bool _Dead) { IsDead = _Dead;  }
	void SetHp(int _Hp) { m_HP = _Hp; }
	int GetMeso() { return m_Meso; }
	void SetMeso(int _meso) { m_Meso = _meso; }

	// �ڱ� �ڽ� ���� ������ִ� �Լ� ����
	CLONE(CPlayer);
	
private:
	CTexture* m_pTex;
	CSound* m_levelupSound;
	CSound* m_tombSound;
	vector<CObject*>		m_vecColObj;

	// �����̴� ���⿡ ���� �ִϸ��̼� �� ����
	int					m_iCurDir;		// �÷��̾��� ���� ���� ����
	int					m_iPreDir;		// �÷��̾��� ���� ���� ����

	PLAYER_STATE		m_eCurState;	// �÷��̾��� ���� ���� ����
	PLAYER_STATE		m_ePrevState;	// �÷��̾��� ���� ���� ����
	bool				m_IsInJury;		// �������� ���� �����ΰ�?
	double				InjureTime;		// �λ��Դµ��� ������

	PlayerWearState		curWearState;
	bool				changeWear;
	bool				jumpDelay;

	// ������ ����ġ ����
	unsigned int m_Level;
	unsigned int m_Exp;
	unsigned int m_MaxExp;

	// HP
	int m_HP;
	bool IsDead;
	CTexture* DeadTex;
	Vec2 DeadSize;

	// �� ����
	CObject* m_mypet1;


	// �޼�
	int m_Meso;
};

