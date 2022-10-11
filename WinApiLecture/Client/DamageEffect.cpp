#include "pch.h"
#include "DamageEffect.h"
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

DamageEffect::DamageEffect(Vec2 pos, EFFECT_TYPE _type, int _dir)
{
	pos.x -= 100.f;
	SetPos(pos);
	
	del_time = 0.;

	CreateCollider();
	GetCollider()->SetOffsetPos(Vec2(0.f, 0.f));
	GetCollider()->SetScale(Vec2(50.f, 60.f));;

	m_pTex[0] = CResMgr::GetInst()->LoadTexture(L"CriticalEffect", L"texture\\Damage\\CriticalDamageEffect.bmp");
	m_pTex[1] = CResMgr::GetInst()->LoadTexture(L"oneEffect", L"texture\\Damage\\1DamageEffect.bmp");
	m_pTex[2] = CResMgr::GetInst()->LoadTexture(L"twoEffect", L"texture\\Damage\\2DamageEffect.bmp");
	m_pTex[3] = CResMgr::GetInst()->LoadTexture(L"threeEffect", L"texture\\Damage\\3DamageEffect.bmp");
	m_pTex[4] = CResMgr::GetInst()->LoadTexture(L"fourEffect", L"texture\\Damage\\4DamageEffect.bmp");
	m_pTex[5] = CResMgr::GetInst()->LoadTexture(L"fiveEffect", L"texture\\Damage\\5DamageEffect.bmp");
	m_pTex[6] = CResMgr::GetInst()->LoadTexture(L"sixthEffect", L"texture\\Damage\\6DamageEffect.bmp");
	m_pTex[7] = CResMgr::GetInst()->LoadTexture(L"sevenEffect", L"texture\\Damage\\7DamageEffect.bmp");
	m_pTex[8] = CResMgr::GetInst()->LoadTexture(L"eightEffect", L"texture\\Damage\\8DamageEffect.bmp");
	m_pTex[9] = CResMgr::GetInst()->LoadTexture(L"nineEffect", L"texture\\Damage\\9DamageEffect.bmp");

	m_type = _type;

	if (m_type == EFFECT_TYPE::VOLCANO)
	{
		CreateRigidBody();
		CreateGravity();
	}

	m_volcanoDir = _dir;
	IsOnetime = true;
	
	
	//srand((UINT)time(nullptr));

	for (int i = 0; i < 6; i++)
	{
		randArray[i] = (rand() % 9) + 1;
	}
}	


DamageEffect::~DamageEffect()
{
}


void DamageEffect::update()
{

	switch (m_type)
	{
	case EFFECT_TYPE::NORMAL:
	{
		Vec2 tempPos = GetPos();
		tempPos.y -= 50.f * fDT;
		SetPos(tempPos);

	}
	break;
	case EFFECT_TYPE::VOLCANO:
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
	if (del_time > 3.)
	{
		SetDead();
	}
}

void DamageEffect::render(HDC _dc)
{
	// 카메라의 렌더링 좌표로 변환
	Vec2 vPos = CCamera::GetInst()->GetRenderPos(GetPos());

	TransparentBlt(_dc
		// 실제 좌상단 위치와 크기
		, (int)vPos.x
		, (int)vPos.y
		, 63
		, 73
		// 텍스쳐 정보
		, m_pTex[0]->GetDC()
		// bmp 파일 내에서 자를 좌상단
		, (int)0
		, (int)0
		, (int)63
		, (int)73
		, RGB(255, 0, 255));

	


	for (int i = 1; i < 6; i++)
	{
		 TransparentBlt(_dc
			// 실제 좌상단 위치와 크기
			, (int)vPos.x + 30 * i
			, (int)vPos.y
			, 63
			, 73
			// 텍스쳐 정보
			, m_pTex[randArray[i-1]]->GetDC()
			// bmp 파일 내에서 자를 좌상단
			, (int)0
			, (int)0
			, (int)63
			, (int)73
			, RGB(255, 0, 255));
	}

}