#pragma once
#include "CObject.h"


enum class MONSTER_STATE
{
	IDLE,
	WALK,
	INJURE,
	DEAD
};

// 몬스터면 가져야할 정보
struct tMonInfo
{
	float		m_fSpeed;
	float		m_fHp;

	// Idle 상태 위한 변수
	// 중심점
	Vec2 m_vCenterPos;
	// 반복거리 반틈
	float m_fMaxDistance;
	// 1, -1 방향
	int m_iDir;
	// Idle / Walk 바뀌는 총시간
	double m_MaxChangetime;


	// 인식범위
	float		m_fRecogRange;
	// 공격 범위
	float		m_fAttRnagle;
	// 공격력
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

	// 잠깐 방향설정때문에 public에 씀
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

	// 움직이는 방향에 따라 애니메이션 등 변경
	int					m_iCurDir;		// 몬스터의 현재 방향 정보
	int					m_iPreDir;		// 몬스터의 이전 방향 정보

	MONSTER_STATE		m_eCurState;	// 몬스터의 현재 상태 관리
	MONSTER_STATE		m_ePrevState;	// 몬스터의 이전 상태 관리

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

	CSound* m_HitSound[10];
	int sound_index;

	friend class CMonFactory;
};

