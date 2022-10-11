#include "pch.h"
#include "CLadder.h"

#include "CCollider.h"
#include "CGravity.h"
#include "CRigidBody.h"
#include "CKeyMgr.h"
#include "CTimeMgr.h"


CLadder::CLadder()
{
	CreateCollider();
	m_1secondAcc = 0.;
}


CLadder::~CLadder()
{
}


void CLadder::start()
{
	// 자기 크기만큼 충돌체 크기 지정
	//GetCollider()->SetScale(Vec2(GetScale()));
	//GetCollider()->SetOffsetPos(Vec2(0.f, 0.f));
	GetCollider()->SetScale(Vec2(GetScale()));
	//Vec2(200.f, 60.f)
}

void CLadder::update()
{
	/*
#ifdef _DEBUG
	Vec2 pos = GetPos();
	Vec2 scal = GetScale();

	if (KEY_TAP(KEY::O))
	{
		scal.x -= 1.f;
	}

	if (KEY_TAP(KEY::P))
	{
		scal.x += 1.f;
	}

	if (KEY_HOLD(KEY::O))
	{
		scal.x -= 1.f;
	}

	if (KEY_HOLD(KEY::P))
	{
		scal.x += 1.f;
	}

	if (KEY_TAP(KEY::N))
	{
		scal.y -= 1.f;
	}

	if (KEY_TAP(KEY::M))
	{
		scal.y += 1.f;
	}

	if (KEY_HOLD(KEY::N))
	{
		scal.y -= 1.f;
	}

	if (KEY_HOLD(KEY::M))
	{
		scal.y += 1.f;
	}

	//--------------------

	if (KEY_TAP(KEY::J))
	{
		pos.x -= 1.f;
	}

	if (KEY_TAP(KEY::I))
	{
		pos.y -= 1.f;
	}

	if (KEY_TAP(KEY::K))
	{
		pos.y += 1.f;
	}

	if (KEY_TAP(KEY::L))
	{
		pos.x += 1.f;
	}

	if (KEY_HOLD(KEY::J))
	{
		pos.x -= 1.f;
	}

	if (KEY_HOLD(KEY::I))
	{
		pos.y -= 1.f;
	}

	if (KEY_HOLD(KEY::K))
	{
		pos.y += 1.f;
	}

	if (KEY_HOLD(KEY::L))
	{
		pos.x += 1.f;
	}

	SetPos(pos);
	SetScale(scal);

	m_1secondAcc += fDT;

	if (m_1secondAcc > 2.)
	{
		m_1secondAcc = 0.;
		cout << "사다리 좌표 : " << GetPos().x << "           " << GetPos().y << '\n';
		cout << "사다리 size : " << GetScale().x << "           " << GetScale().y << '\n';
	}

#endif
	*/
	
}

void CLadder::render(HDC _dc)
{
	component_render(_dc);
}
