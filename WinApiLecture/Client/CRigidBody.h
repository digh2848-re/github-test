#pragma once

class CObject;

class CRigidBody
{
private:
	CObject* m_pOwner;

	// 힘의 크기, 방향
	Vec2		m_vForce;
	// 가속도 크기, 방향
	Vec2		m_vAccel;
	// 가속도 추가 알파
	Vec2		m_vAccelA;
	// 질량
	float		m_fMass;

	// 속도 ( 크기 : 속력, 방향)
	Vec2		m_vVelocity;



	// 최대 속도
	Vec2		m_vMaxVelocity;

	// 전제 조건 : 정지 마찰력이랑 운동 마찰력을 동일시함
	// 마찰 계수
	float		m_fFricCoeff;


	// F = M * A;
	// V += A * DT;

	// 순간최대 속도 일정한 시간만큼만 줄려고
	double max_time;
	

public:
	void finalupdate();

public:
	void AddForce(Vec2 _vF)
	{
		m_vForce += _vF;
	}

	void SetMass(float _fMass)
	{
		m_fMass = _fMass;
	}

	float GetMass() { return m_fMass; }

	float GetSpeed() { return (float)m_vVelocity.Length(); }

	Vec2 GetVelocity() { return m_vVelocity; }

	// 중력과 관련
	void SetVelocity(Vec2 _v) { m_vVelocity = _v; }

	// 추가 가속도
	void SetAccelAlpha(Vec2 _vAccel)
	{
		m_vAccelA = _vAccel;
	}

	// 초반 속도 보정
	void AddVelocity(Vec2 _v) { m_vVelocity += _v; }

	//  반발력 관련
	void SetMaxVelocity(Vec2 _v) { m_vMaxVelocity = _v; }

	
private:
	void Move();

public:
	CRigidBody();
	~CRigidBody();

	friend class CObject;
};
