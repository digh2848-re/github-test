#include "pch.h"
#include "PlayerDamageEffect.h"
#include "Skill.h"

#include "CCollider.h"
#include "CAnimator.h"
#include "CAnimation.h"
#include "CResMgr.h"
#include "CTimeMgr.h"
#include "CTexture.h"
#include "CRigidBody.h"
#include "CGravity.h"
#include "CSound.h"

PlayerDamageEffect::PlayerDamageEffect(Vec2 pos, PLAYER_EFFECT_TYPE _type, int _dir)
{
	//pos.x -= 100.f;
	SetPos(pos);

	del_time = 0.;

	CreateCollider();
	GetCollider()->SetOffsetPos(Vec2(0.f, 0.f));
	GetCollider()->SetScale(Vec2(31.f, 33.f));;

	m_pTex[0] = CResMgr::GetInst()->LoadTexture(L"PlayerEffect1", L"texture\\Damage\\Damage0.bmp");
	m_pTex[1] = CResMgr::GetInst()->LoadTexture(L"PlayerEffect2", L"texture\\Damage\\Damage1.bmp");
	m_pTex[2] = CResMgr::GetInst()->LoadTexture(L"PlayerEffect3", L"texture\\Damage\\Damage2.bmp");
	

	m_type = _type;

	if (m_type == PLAYER_EFFECT_TYPE::VOLCANO)
	{
		CreateRigidBody();
		CreateGravity();
	}

	m_volcanoDir = _dir;
	IsOnetime = true;


	//srand((UINT)time(nullptr));

}


PlayerDamageEffect::~PlayerDamageEffect()
{
}


void PlayerDamageEffect::update()
{

	switch (m_type)
	{
	case PLAYER_EFFECT_TYPE::NORMAL:
	{
		Vec2 tempPos = GetPos();
		tempPos.y -= 50.f * fDT;
		SetPos(tempPos);

	}
	break;
	case PLAYER_EFFECT_TYPE::VOLCANO:
	{
		// 한번만 세팅할꺼임
		if (IsOnetime == true)
		{
			IsOnetime = false;
			if (m_volcanoDir == 1)
			{
				GetRigidBody()->SetVelocity(Vec2(200.f, -600.f));
			}
			else
			{
				GetRigidBody()->SetVelocity(Vec2(-200.f, -600.f));
			}
		}

	}
	break;
	}

	del_time += fDT;
	if (del_time > 1.5)
	{
		SetDead();
	}
}

void PlayerDamageEffect::render(HDC _dc)
{
	// 카메라의 렌더링 좌표로 변환
	Vec2 vPos = CCamera::GetInst()->GetRenderPos(GetPos());

	TransparentBlt(_dc
		// 실제 좌상단 위치와 크기
		, (int)vPos.x
		, (int)vPos.y
		, 31
		, 33
		// 텍스쳐 정보
		, m_pTex[1]->GetDC()
		// bmp 파일 내에서 자를 좌상단
		, (int)0
		, (int)0
		, (int)31
		, (int)33
		, RGB(255, 0, 255));

	TransparentBlt(_dc
		// 실제 좌상단 위치와 크기
		, (int)vPos.x +20
		, (int)vPos.y
		, 31
		, 33
		// 텍스쳐 정보
		, m_pTex[2]->GetDC()
		// bmp 파일 내에서 자를 좌상단
		, (int)0
		, (int)0
		, (int)31
		, (int)33
		, RGB(255, 0, 255));

	TransparentBlt(_dc
		// 실제 좌상단 위치와 크기
		, (int)vPos.x + 40
		, (int)vPos.y
		, 31
		, 33
		// 텍스쳐 정보
		, m_pTex[0]->GetDC()
		// bmp 파일 내에서 자를 좌상단
		, (int)0
		, (int)0
		, (int)31
		, (int)33
		, RGB(255, 0, 255));


}