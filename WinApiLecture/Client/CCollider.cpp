#include "pch.h"
#include "CCollider.h"
#include "CObject.h"
#include "CCore.h"
#include "CCamera.h"

#include "SelectGDI.h"

UINT CCollider::g_iNextID = 0;

CCollider::CCollider()
	: m_pOwner(nullptr)
	, m_iID(g_iNextID++)
	, m_iCol(0)
	, m_bActive(true)
{

}

CCollider::CCollider(const CCollider& _origin)
	: m_pOwner(nullptr) // 복사생성자 구현 이유 -> nullptr 하고나서 소유오브젝트 주소 넣어야함
	, m_vOffsetPos(_origin.m_vOffsetPos)
	, m_vScale(_origin.m_vScale)
	, m_iID(g_iNextID++) // 복사생성자 구현 이유 -> 얕은 복사로 인해 같은 ID값을 가지는거 방지함
	, m_bActive(_origin.m_bActive)
{

}


CCollider::~CCollider()
{
}


void CCollider::finalupdate()
{
	// finalpos 갱신하기전에 이전 프레임 위치값 저장
	m_vPreFrameFinalPos = m_vFinalPos;


	// Object 의 위치를 따라간다.

	Vec2 vObjectPos = m_pOwner->GetPos();
	m_vFinalPos = vObjectPos + m_vOffsetPos;

	// debug 모드
	//Vec2 vObjectSacle = m_pOwner->GetScale();
	//m_vScale = vObjectSacle;

	// 음수가 되면 말도 안되는 상황이라 assert
	assert(0 <= m_iCol);

	// 모서리부분 충돌 처리를 위한 이전 프레임 bottom 값 저장하자
	float _bottom = m_vFinalPos.y + m_vScale.y / 2.f;
}

void CCollider::render(HDC _dc)
{
	//PEN_TYPE ePen = PEN_TYPE::GREEN;
	//
	//// 하나라도 충돌하고 있는 경우면 빨간색
	//if (m_iCol)
	//	ePen = PEN_TYPE::RED;
	//
	//SelectGDI p(_dc, ePen);
	//SelectGDI b(_dc, BRUSH_TYPE::HOLLOW);
	//
	//Vec2 vRenderPos = CCamera::GetInst()->GetRenderPos(m_vFinalPos);
	//
	//
	//Rectangle(_dc
	//	, (int)(vRenderPos.x - m_vScale.x / 2.f)
	//	, (int)(vRenderPos.y - m_vScale.y / 2.f)
	//	, (int)(vRenderPos.x + m_vScale.x / 2.f)
	//	, (int)(vRenderPos.y + m_vScale.y / 2.f));
	
}


void CCollider::OnCollision(CCollider* _pOther)
{
	m_pOwner->OnCollision(_pOther);
}


void CCollider::OnCollisionEnter(CCollider* _pOther)
{
	++m_iCol;
	m_pOwner->OnCollisionEnter(_pOther);
}

void CCollider::OnCollisionExit(CCollider* _pOther)
{
	--m_iCol;
	m_pOwner->OnCollisionExit(_pOther);
}