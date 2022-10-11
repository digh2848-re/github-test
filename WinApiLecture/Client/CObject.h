#pragma once

#include "global.h"

// 카메라는 모든 오브젝트에서 항상 쓸꺼니깐
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
	// 밧줄 탔을때 gravity 및 rigidbody 꺼버리고 속도 0으로 초기화
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

	// 사다리 
	bool GetIsLadder() { return m_IsLadder; }
	void SetIsLadder(bool _Isladder) { m_IsLadder = _Isladder;  }

	// 중력, 강체 끄기
	void SetOffGraviRigid(bool _offGraviRigid) { m_OffGraviRigid = _offGraviRigid; }

	// 자식이나 아무 곳이나 함부로 죽이지 못하게 
	// 스킬 자동적으로 없어지게하기위해서 일단 protected 함
protected:
	void SetDead() { m_bAlive = false; }

public:
	virtual void start() { } // Scene 이 시작되기 직전에 호출되는 함수
	virtual void update() = 0;
	// 자식쪽으로 오버라이딩 못하게 final 선언
	// UI떄매 일단 보류
	virtual void finalupdate();
	virtual void render(HDC _dc);

	// 컴포넌트 렌더링 (디버깅 모드시 사용)
	void component_render(HDC _dc);

	// 나 자신을 복제버전을 되돌려주는 함수
	// 자식 객체에서만 복사 받으라고 순수 가상 함수로 만듬
	virtual CObject* Clone() = 0;
public:

	CObject();

	// 복사 생성자(깊은 복사)
	CObject(const CObject& _origin);

	virtual ~CObject();

	friend class CEventMgr;
};

