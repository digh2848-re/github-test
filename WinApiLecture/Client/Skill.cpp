#include "pch.h"
#include "Skill.h"

#include "CCollider.h"
#include "CAnimator.h"
#include "CAnimation.h"
#include "CResMgr.h"
#include "CTimeMgr.h"

Skill::Skill(Vec2 pos,int Dir)
{
	SetPos(pos);
	SetScale(Vec2(468.f, 304.f));
	m_dir = Dir;
	CreateCollider();

	GetCollider()->SetScale(Vec2(GetScale()));

	CTexture* pLeftShoot = CResMgr::GetInst()->LoadTexture(L"move_left_skill", L"texture\\Skill\\skill1_Left.bmp");
	CTexture* pRightShoot = CResMgr::GetInst()->LoadTexture(L"move_right_skill", L"texture\\Skill\\skill1_Right.bmp");

	CreateAnimator();

	GetAnimator()->CreateAnimation(L"MOVE_RIGHT_SKILL", pRightShoot, Vec2(0.f, 0.f), Vec2(468.f, 304.f), Vec2(468.f, 0.f), 0.1f, 8);

	GetAnimator()->CreateAnimation(L"MOVE_LEFT_SKILL", pLeftShoot, Vec2(0.f, 0.f), Vec2(468.f, 304.f), Vec2(468.f, 0.f), 0.1f, 8);

	del_time = 0.;
}


Skill::~Skill()
{
}

void Skill::update()
{
	Vec2 tempPos = GetPos();

	if (m_dir == -1)
	{
		tempPos.x -= 100.f * fDT;
		SetPos(tempPos);

		GetAnimator()->Play(L"MOVE_LEFT_SKILL", true);

		del_time += fDT;
	}
	else
	{
		tempPos.x += 100.f * fDT;
		SetPos(tempPos);

		GetAnimator()->Play(L"MOVE_RIGHT_SKILL", true);

		del_time += fDT;
	}


	if(del_time > 5.)
	{
		SetDead();
	}
}


void Skill::render(HDC _dc)
{
	component_render(_dc);
}
