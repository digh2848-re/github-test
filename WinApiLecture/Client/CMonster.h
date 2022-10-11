#pragma once
#include "CObject.h"


enum class MONSTER_STATE
{
	IDLE,
	WALK,
	INJURE,
	DEAD
};

// ���͸� �������� ����
struct tMonInfo
{
	float		m_fSpeed;
	float		m_fHp;

	// Idle ���� ���� ����
	// �߽���
	Vec2 m_vCenterPos;
	// �ݺ��Ÿ� ��ƴ
	float m_fMaxDistance;
	// 1, -1 ����
	int m_iDir;
	// Idle / Walk �ٲ�� �ѽð�
	double m_MaxChangetime;


	// �νĹ���
	float		m_fRecogRange;
	// ���� ����
	float		m_fAttRnagle;
	// ���ݷ�
	float		m_fAtt;
	
};

class AI;
class CSound;

class CMonster :
	public CObject
{
public:
	CMonster();
	CMonster(int n);
	~CMonster();
public:
	float GetSpeed(){ return m_tInfo.m_fSpeed; }
	void SetSpeed(float _f) { m_tInfo.m_fSpeed = _f; }
	//void SetMoveDistance(float _f) { m_fMaxDistance = _f; }
	//void SetCenterPos(Vec2 _vPos) { m_vCenterPos = _vPos; }
	void SetAI(AI* _AI);



	const tMonInfo& GetInfo() { return m_tInfo; }

	// ��� ���⼳�������� public�� ��
	void SetMonInfo(const tMonInfo& _info) { m_tInfo = _info; }
	void SetCurState(MONSTER_STATE _state) { m_eCurState = _state; }
private:
	void update_state();
	void update_animation();

public:
	virtual void OnCollisionEnter(CCollider* _pOther);
	virtual void OnCollision(CCollider* _pOther);
	virtual void OnCollisionExit(CCollider* _pOther);

private:
	void CreateEffect();
	void CreateDamageUI();
	void CreateItem();
public:
	virtual void update();
	virtual void render(HDC _dc);
	CLONE(CMonster);
	
private:
	tMonInfo		m_tInfo;
	AI*				m_pAI;

	// �����̴� ���⿡ ���� �ִϸ��̼� �� ����
	int					m_iCurDir;		// ������ ���� ���� ����
	int					m_iPreDir;		// ������ ���� ���� ����

	MONSTER_STATE		m_eCurState;	// ������ ���� ���� ����
	MONSTER_STATE		m_ePrevState;	// ������ ���� ���� ����

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

	CSound* m_HitSound[10];
	int sound_index;

	friend class CMonFactory;
};

