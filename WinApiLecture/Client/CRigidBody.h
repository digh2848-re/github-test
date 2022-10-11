#pragma once

class CObject;

class CRigidBody
{
private:
	CObject* m_pOwner;

	// ���� ũ��, ����
	Vec2		m_vForce;
	// ���ӵ� ũ��, ����
	Vec2		m_vAccel;
	// ���ӵ� �߰� ����
	Vec2		m_vAccelA;
	// ����
	float		m_fMass;

	// �ӵ� ( ũ�� : �ӷ�, ����)
	Vec2		m_vVelocity;



	// �ִ� �ӵ�
	Vec2		m_vMaxVelocity;

	// ���� ���� : ���� �������̶� � �������� ���Ͻ���
	// ���� ���
	float		m_fFricCoeff;


	// F = M * A;
	// V += A * DT;

	// �����ִ� �ӵ� ������ �ð���ŭ�� �ٷ���
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

	// �߷°� ����
	void SetVelocity(Vec2 _v) { m_vVelocity = _v; }

	// �߰� ���ӵ�
	void SetAccelAlpha(Vec2 _vAccel)
	{
		m_vAccelA = _vAccel;
	}

	// �ʹ� �ӵ� ����
	void AddVelocity(Vec2 _v) { m_vVelocity += _v; }

	//  �ݹ߷� ����
	void SetMaxVelocity(Vec2 _v) { m_vMaxVelocity = _v; }

	
private:
	void Move();

public:
	CRigidBody();
	~CRigidBody();

	friend class CObject;
};
