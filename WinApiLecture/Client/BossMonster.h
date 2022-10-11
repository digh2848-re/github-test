#pragma once
#include "CObject.h"

enum class B0SS_MONSTER_STATE
{
	IDLE,
	ATTACK1,
	ATTACK2,
	ATTACK3,
	ATTACK4,
	ATTACK5,
	END,

};

struct Pattern
{
	float RecognField;				// 인식 범위
	B0SS_MONSTER_STATE state;		// 변경될 패턴 상태 
	float delaytime;				// 패턴끝나고 다음 패턴으로 가기전 딜레이 시간
};

class CPlayer;
class CTexture;

class BossMonster :
	public CObject
{
public:
	BossMonster(int _dividePhase);
	virtual ~BossMonster();
public:
	virtual void update();
	virtual void render(HDC _dc);
public:
	void update_action();
	void update_animation();
	void SetTarget(CObject* _target) { target_player = (CPlayer*)_target; }

	void CreateSkill1();
	void CreateSkill2(int _Order);

	void CreateEffect();
	void CreateDamageUI();

	virtual void OnCollisionEnter(CCollider* _pOther);
	virtual void OnCollision(CCollider* _pOther);
	virtual void OnCollisionExit(CCollider* _pOther);
public:
	float GetHp() { return m_BossHP; }
	void SetHp(int _Hp) { m_BossHP = _Hp; }
	// 자기 자신 복제 내뱉어주는 함수 구현
	CLONE(BossMonster);
private:
	int m_dividePhase;

	CPlayer* target_player;
	// 움직이는 방향에 따라 애니메이션 등 변경
	int			m_iCurDir;
	int			m_iPreDir;

	B0SS_MONSTER_STATE	m_eCurState;
	B0SS_MONSTER_STATE	m_ePreState;

	// 피격당할시
	bool	IsInjure;
	double InjureTime;

	// 스킬 이펙트 딜레이
	double m_delaytime;
	// 스킬 좌우로 되기위해서
	int m_motiondir;

	// 데미지 이펙트 딜레이
	double m_damagetime1;
	double m_damagetime2;
	Vec2 m_damagepos;
	int m_i;
	int m_damagedir;
	bool onemoreItem;
	int DamageEffectNum;
	float m_BossHP;


	CSound* m_HitSound[15];
	int sound_index;




	
	float m_SKill1time;
	float m_Skill1Delaytime;
	float m_SKill2time;
	float m_Skill2Delaytime;
	float m_SKill3time;
	float m_Skill3Delaytime;
	float m_SKill4time;
	float m_Skill4Delaytime;
	float m_SKill5time;
	float m_Skill5Delaytime;

	Pattern pattern[10];
	float m_patternDelayTime;
	int m_patternIndex;

	int m_attack5State;
	int m_attack5dir;
};

