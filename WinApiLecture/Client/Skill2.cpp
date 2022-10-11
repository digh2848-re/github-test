#include "pch.h"
#include "Skill2.h"

#include "CCollider.h"
#include "CAnimator.h"
#include "CAnimation.h"
#include "CResMgr.h"
#include "CTimeMgr.h"

Skill2::Skill2(Vec2 pos, int Dir)
{
	SetPos(pos);
	SetScale(Vec2(297.f, 204.f));
	m_dir = Dir;
	CreateCollider();

	GetCollider()->SetScale(Vec2(GetScale()));

	CTexture* pRightJump = CResMgr::GetInst()->LoadTexture(L"jump_skill_right", L"texture\\Skill\\jumpskillright.bmp");
	CTexture* pLeftJump = CResMgr::GetInst()->LoadTexture(L"jump_skill_left", L"texture\\Skill\\jumpskillleft.bmp");

	CreateAnimator();

	GetAnimator()->CreateAnimation(L"JUMP_RIGHT_SKILL", pRightJump, Vec2(2376.f, 0.f), Vec2(297.f, 204.f), Vec2(-297.f, 0.f), 0.05f, 9);

	GetAnimator()->CreateAnimation(L"JUMP_LEFT_SKILL", pLeftJump, Vec2(2376.f, 0.f), Vec2(297.f, 204.f), Vec2(-297.f, 0.f), 0.05f, 9);

	del_time = 0.;
}


Skill2::~Skill2()
{
}

void Skill2::update()
{
	if (m_dir==1)
	{
		GetAnimator()->Play(L"JUMP_RIGHT_SKILL", false);
	}
	else
	{
		GetAnimator()->Play(L"JUMP_LEFT_SKILL", false);
	}

	del_time += DT;

	if (del_time > 0.5)
	{
		SetDead();
	}
}


void Skill2::render(HDC _dc)
{
	component_render(_dc);
}
