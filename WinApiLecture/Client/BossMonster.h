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
	float RecognField;				// �ν� ����
	B0SS_MONSTER_STATE state;		// ����� ���� ���� 
	float delaytime;				// ���ϳ����� ���� �������� ������ ������ �ð�
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
	// �ڱ� �ڽ� ���� ������ִ� �Լ� ����
	CLONE(BossMonster);
private:
	int m_dividePhase;

	CPlayer* target_player;
	// �����̴� ���⿡ ���� �ִϸ��̼� �� ����
	int			m_iCurDir;
	int			m_iPreDir;

	B0SS_MONSTER_STATE	m_eCurState;
	B0SS_MONSTER_STATE	m_ePreState;

	// �ǰݴ��ҽ�
	bool	IsInjure;
	double InjureTime;

	// ��ų ����Ʈ ������
	double m_delaytime;
	// ��ų �¿�� �Ǳ����ؼ�
	int m_motiondir;

	// ������ ����Ʈ ������
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

