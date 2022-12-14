
#include "pch.h"
#include "CRigidBody.h"

#include "CObject.h"
#include "CTimeMgr.h"

CRigidBody::CRigidBody()
	: m_pOwner(nullptr)
	, m_fMass(1.f)
	, m_fFricCoeff(100.f)
	, m_vMaxVelocity(Vec2(200.f,600.f)) // x / y 축 제한속도 달리둠
{
	max_time = 0.;
}


CRigidBody::~CRigidBody()
{
}

void CRigidBody::finalupdate()
{
	if (m_vMaxVelocity.x > 500.f)
	{
		if (max_time > 1.)
		{
			m_vMaxVelocity=Vec2(200.f, 600.f);
			max_time = 0.;
		}

		max_time += DT;
	}
	else
	{
		max_time = 0.;
	}

	// 힘의 크기
	float fForce = m_vForce.Length();

	if (0.f != fForce)
	{
		// 힘의 방향
		m_vForce.Normalize();

		// 가속도의 크기
		float m_fAccel = fForce / m_fMass;

		// 가속도
		m_vAccel = m_vForce * m_fAccel;
		//m_vAccel = m_vForce / m_fMass;

	}

	// 힘이 있던 말던 해야하는 것들

	//0. 중력에 의한 추가 가속도
	m_vAccel += m_vAccelA;

	// 속도
	m_vVelocity += m_vAccel * fDT;

	// 1. 마찰력에 의한 반대방향으로의 가속도

	if (!m_vVelocity.IsZero())
	{
		Vec2 vFricDir = - m_vVelocity;
		vFricDir.Normalize();

		Vec2 vFriction = vFricDir * m_fFricCoeff * fDT;

		if (m_vVelocity.Length() <= vFriction.Length())
		{
			// 마찰 가속도가 본래 속도보다 더 큰 경우
			// 멈춘다
			m_vVelocity = Vec2(0.f, 0.f);
		}
		else
		{
			m_vVelocity += vFriction;
		}
	}


	// 2. 속도 제한 검사
	// 중력때문에 아랫쪽방향 y 제한속도는 좀 크게 두자
	if (abs(m_vMaxVelocity.x) < abs(m_vVelocity.x))
	{
		m_vVelocity.x = (m_vVelocity.x / abs(m_vVelocity.x)) * abs(m_vMaxVelocity.x);
	}

	if (abs(m_vMaxVelocity.y) < abs(m_vVelocity.y))
	{
		m_vVelocity.y = (m_vVelocity.y / abs(m_vVelocity.y)) * abs(m_vMaxVelocity.y);
	}


	// 속도에 따른 이동
	Move();

	// 프레임단위로 힘을 0으로 초기화 함
	m_vForce = Vec2(0.f, 0.f);
	// 가속도도 초기화
	m_vAccel = Vec2(0.f, 0.f);
	// 추가 가속도도 초기화
	m_vAccelA = Vec2(0.f, 0.f);
}

void CRigidBody::Move()
{
	// 이동 속력
	float fSpeed = m_vVelocity.Length();

	if (0.f != fSpeed)
	{
		// 이동 방향
		Vec2 vDir = m_vVelocity;
		vDir.Normalize();


		Vec2 vPos = m_pOwner->GetPos();

		//vPos += vDir * fSpeed * fDT;
		vPos += m_vVelocity * fDT;

		m_pOwner->SetPos(vPos);

	}


}