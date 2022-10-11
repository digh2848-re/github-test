#include "pch.h"
#include "CObject.h"

#include "CKeyMgr.h"
#include "CTimeMgr.h"
#include "CCollider.h"
#include "CAnimator.h"
#include "CRigidBody.h"
#include "CGravity.h"

CObject::CObject()
	: m_vPos{}
	, m_vScale{}
	, m_pCollider(nullptr)
	, m_pAnimator(nullptr)
	, m_pRigidBody(nullptr)
	, m_pGravity(nullptr)
	, m_bAlive(true)
	, m_IsLadder(false)
	, m_IspushLadder(false)
	, m_OffGraviRigid(false)
{

}

// 복사생성자 구현 -> 자식쪽은 디폴트 복사생성자 할꺼임
CObject::CObject(const CObject& _origin)
	: m_strName(_origin.m_strName)
	, m_vPos(_origin.m_vPos)
	, m_vScale(_origin.m_vScale)
	, m_pCollider(nullptr)
	, m_pAnimator(nullptr)
	, m_pRigidBody(nullptr)
	, m_pGravity(nullptr)
	, m_bAlive(true)
	, m_IsLadder(false)
	, m_IspushLadder(false)
	, m_OffGraviRigid(false)
{
	// 복사 원본 객체가 콜라이더가 있을경우만
	if (_origin.m_pCollider)
	{
		m_pCollider = new CCollider(*_origin.m_pCollider);
		m_pCollider->m_pOwner = this;
	}


	// 애니메이터도 깊은 복사
	if (_origin.m_pAnimator)
	{
		m_pAnimator = new CAnimator(*_origin.m_pAnimator);
		m_pAnimator->m_pOwner = this;
	}

	if (_origin.m_pGravity)
	{
		m_pGravity = new CGravity(*_origin.m_pGravity);
		m_pGravity->m_pOwner = this;
	}


	// 리지드바디도 깊은 복사
	if (_origin.m_pRigidBody)
	{
		m_pRigidBody = new CRigidBody(*_origin.m_pRigidBody);
		m_pRigidBody->m_pOwner = this;
	}

}


CObject::~CObject()
{
	if (nullptr != m_pCollider)
		delete m_pCollider;

	if (nullptr != m_pAnimator)
		delete m_pAnimator;

	if (nullptr != m_pGravity)
		delete m_pGravity;

	if (nullptr != m_pRigidBody)
		delete m_pRigidBody;
}


void CObject::finalupdate()
{
	
	if (m_pAnimator)
		m_pAnimator->finalupdate();

	// 사다리 타게 된다면 중력과 리지드바디 영향 없앰
	if (!m_IsLadder && !m_OffGraviRigid)
	{
		// 중력 finalupdate가 리지드바디보다 먼저 되어야함
		if (m_pGravity)
			m_pGravity->finalupdate();

		if (m_pRigidBody)
			m_pRigidBody->finalupdate();
	}
	

	if (m_pCollider)
		m_pCollider->finalupdate();

}


void CObject::render(HDC _dc)
{
	// 카메라의 렌더링 좌표
	Vec2 vRenderPos = CCamera::GetInst()->GetRenderPos(m_vPos);

	Rectangle(_dc
		, (int)(vRenderPos.x - m_vScale.x / 2.f)
		, (int)(vRenderPos.y - m_vScale.y / 2.f)
		, (int)(vRenderPos.x + m_vScale.x / 2.f)
		, (int)(vRenderPos.y + m_vScale.y / 2.f));

	// 컴포넌트 렌더링
	component_render(_dc);
}

void CObject::component_render(HDC _dc)
{
	
	if (m_pAnimator != nullptr)
	{
		m_pAnimator->render(_dc);
	}
	
	if (m_pCollider != nullptr)
	{
		m_pCollider->render(_dc);
	}
}

void CObject::CreateCollider()
{
	m_pCollider = new CCollider;
	m_pCollider->m_pOwner = this;
}

void CObject::CreateAnimator()
{
	m_pAnimator = new CAnimator;
	m_pAnimator->m_pOwner = this;
}

void CObject::CreateRigidBody()
{
	m_pRigidBody = new CRigidBody;
	m_pRigidBody->m_pOwner = this;
}

void CObject::CreateGravity()
{
	m_pGravity = new CGravity;
	m_pGravity->m_pOwner = this;
}