#include "pch.h"
#include "CGravity.h"
#include "CObject.h"
#include "CRigidBody.h"


CGravity::CGravity()
	: m_pOwner(nullptr)
	, m_bGround(false)
{

}


CGravity::~CGravity()
{
}


void CGravity::SetGround(bool _b)
{
	m_bGround = _b;

	// 땅이면
	if (m_bGround)
	{
		// 속도 값 얻어와서 Y 축 속도는 0으로 초기화시킴
		Vec2 vV = m_pOwner->GetRigidBody()->GetVelocity();
		m_pOwner->GetRigidBody()->SetVelocity(Vec2(vV.x, 0.f));
	}
}


void CGravity::finalupdate()
{
	// ladder 상태이면 가속도 안받도록
	m_pOwner->GetRigidBody()->SetAccelAlpha(Vec2(0.f, 800.f));

}