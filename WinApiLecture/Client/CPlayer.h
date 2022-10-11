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

	// 텍스쳐 상태 바꿔주는 함수
	void SetWearState(PlayerWearState _curWearState);

	UINT GetLevel() { return m_Level; }

	// 경험치 증가시키는 함수
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

	// 자기 자신 복제 내뱉어주는 함수 구현
	CLONE(CPlayer);
	
private:
	CTexture* m_pTex;
	CSound* m_levelupSound;
	CSound* m_tombSound;
	vector<CObject*>		m_vecColObj;

	// 움직이는 방향에 따라 애니메이션 등 변경
	int					m_iCurDir;		// 플레이어의 현재 방향 정보
	int					m_iPreDir;		// 플레이어의 이전 방향 정보

	PLAYER_STATE		m_eCurState;	// 플레이어의 현재 상태 관리
	PLAYER_STATE		m_ePrevState;	// 플레이어의 이전 상태 관리
	bool				m_IsInJury;		// 데미지를 입은 상태인가?
	double				InjureTime;		// 부상입는동안 딜레이

	PlayerWearState		curWearState;
	bool				changeWear;
	bool				jumpDelay;

	// 레벨과 경험치 변수
	unsigned int m_Level;
	unsigned int m_Exp;
	unsigned int m_MaxExp;

	// HP
	int m_HP;
	bool IsDead;
	CTexture* DeadTex;
	Vec2 DeadSize;

	// 펫 변수
	CObject* m_mypet1;


	// 메소
	int m_Meso;
};

