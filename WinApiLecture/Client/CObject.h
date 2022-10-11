#pragma once

#include "global.h"

// ī�޶�� ��� ������Ʈ���� �׻� �����ϱ�
#include "CCamera.h"
class CCollider;
class CAnimator;
class CRigidBody;
class CGravity;
 
class CObject
{
private:
	wstring m_strName;

	Vec2 m_vPos;
	Vec2 m_vScale;

	// Component
	CCollider*			m_pCollider;
	CAnimator*			m_pAnimator;
	CRigidBody*			m_pRigidBody;
	CGravity*			m_pGravity;

	bool m_bAlive;
protected:
	// ���� ������ gravity �� rigidbody �������� �ӵ� 0���� �ʱ�ȭ
	bool	m_IspushLadder;
	bool	m_IsLadder;
	bool	m_OffGraviRigid;

public:

	void SetPos(Vec2 _vPos) { m_vPos = _vPos; }
	void SetScale(Vec2 _vScale) {m_vScale = _vScale;}

	Vec2 GetPos() { return m_vPos; }
	Vec2 GetScale() { return m_vScale; }


	void SetName(const wstring& _strName) { m_strName = _strName;  }
	const wstring& GetName() { return m_strName;  }


	CCollider* GetCollider() { return m_pCollider; }
	CAnimator* GetAnimator() { return m_pAnimator; }
	CRigidBody* GetRigidBody() { return m_pRigidBody; }
	CGravity*   GetGravity() { return m_pGravity; }

	bool IsDead() { return !m_bAlive; }

	void CreateCollider();
	void CreateAnimator();
	void CreateRigidBody();
	void CreateGravity();

	virtual void OnCollision(CCollider* _pOther) {}
	virtual void OnCollisionEnter(CCollider* _pOther) {}
	virtual void OnCollisionExit(CCollider* _pOther){}

	// ��ٸ� 
	bool GetIsLadder() { return m_IsLadder; }
	void SetIsLadder(bool _Isladder) { m_IsLadder = _Isladder;  }

	// �߷�, ��ü ����
	void SetOffGraviRigid(bool _offGraviRigid) { m_OffGraviRigid = _offGraviRigid; }

	// �ڽ��̳� �ƹ� ���̳� �Ժη� ������ ���ϰ� 
	// ��ų �ڵ������� ���������ϱ����ؼ� �ϴ� protected ��
protected:
	void SetDead() { m_bAlive = false; }

public:
	virtual void start() { } // Scene �� ���۵Ǳ� ������ ȣ��Ǵ� �Լ�
	virtual void update() = 0;
	// �ڽ������� �������̵� ���ϰ� final ����
	// UI���� �ϴ� ����
	virtual void finalupdate();
	virtual void render(HDC _dc);

	// ������Ʈ ������ (����� ���� ���)
	void component_render(HDC _dc);

	// �� �ڽ��� ���������� �ǵ����ִ� �Լ�
	// �ڽ� ��ü������ ���� ������� ���� ���� �Լ��� ����
	virtual CObject* Clone() = 0;
public:

	CObject();

	// ���� ������(���� ����)
	CObject(const CObject& _origin);

	virtual ~CObject();

	friend class CEventMgr;
};

