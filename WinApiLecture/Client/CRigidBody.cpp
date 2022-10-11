
#include "pch.h"
#include "CRigidBody.h"

#include "CObject.h"
#include "CTimeMgr.h"

CRigidBody::CRigidBody()
	: m_pOwner(nullptr)
	, m_fMass(1.f)
	, m_fFricCoeff(100.f)
	, m_vMaxVelocity(Vec2(200.f,600.f)) // x / y �� ���Ѽӵ� �޸���
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

	// ���� ũ��
	float fForce = m_vForce.Length();

	if (0.f != fForce)
	{
		// ���� ����
		m_vForce.Normalize();

		// ���ӵ��� ũ��
		float m_fAccel = fForce / m_fMass;

		// ���ӵ�
		m_vAccel = m_vForce * m_fAccel;
		//m_vAccel = m_vForce / m_fMass;

	}

	// ���� �ִ� ���� �ؾ��ϴ� �͵�

	//0. �߷¿� ���� �߰� ���ӵ�
	m_vAccel += m_vAccelA;

	// �ӵ�
	m_vVelocity += m_vAccel * fDT;

	// 1. �����¿� ���� �ݴ���������� ���ӵ�

	if (!m_vVelocity.IsZero())
	{
		Vec2 vFricDir = - m_vVelocity;
		vFricDir.Normalize();

		Vec2 vFriction = vFricDir * m_fFricCoeff * fDT;

		if (m_vVelocity.Length() <= vFriction.Length())
		{
			// ���� ���ӵ��� ���� �ӵ����� �� ū ���
			// �����
			m_vVelocity = Vec2(0.f, 0.f);
		}
		else
		{
			m_vVelocity += vFriction;
		}
	}


	// 2. �ӵ� ���� �˻�
	// �߷¶����� �Ʒ��ʹ��� y ���Ѽӵ��� �� ũ�� ����
	if (abs(m_vMaxVelocity.x) < abs(m_vVelocity.x))
	{
		m_vVelocity.x = (m_vVelocity.x / abs(m_vVelocity.x)) * abs(m_vMaxVelocity.x);
	}

	if (abs(m_vMaxVelocity.y) < abs(m_vVelocity.y))
	{
		m_vVelocity.y = (m_vVelocity.y / abs(m_vVelocity.y)) * abs(m_vMaxVelocity.y);
	}


	// �ӵ��� ���� �̵�
	Move();

	// �����Ӵ����� ���� 0���� �ʱ�ȭ ��
	m_vForce = Vec2(0.f, 0.f);
	// ���ӵ��� �ʱ�ȭ
	m_vAccel = Vec2(0.f, 0.f);
	// �߰� ���ӵ��� �ʱ�ȭ
	m_vAccelA = Vec2(0.f, 0.f);
}

void CRigidBody::Move()
{
	// �̵� �ӷ�
	float fSpeed = m_vVelocity.Length();

	if (0.f != fSpeed)
	{
		// �̵� ����
		Vec2 vDir = m_vVelocity;
		vDir.Normalize();


		Vec2 vPos = m_pOwner->GetPos();

		//vPos += vDir * fSpeed * fDT;
		vPos += m_vVelocity * fDT;

		m_pOwner->SetPos(vPos);

	}


}