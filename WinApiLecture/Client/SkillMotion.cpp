
#include "pch.h"
#include "SkillMotion.h"
#include "Skill.h"

#include "CCollider.h"
#include "CAnimator.h"
#include "CAnimation.h"
#include "CResMgr.h"
#include "CTimeMgr.h"

SkillMotion::SkillMotion(Vec2 pos)
{
	SetPos(pos);
	SetScale(Vec2(146.f, 96.f));
	
	CreateCollider();

	GetCollider()->SetScale(Vec2(GetScale()));

	CTexture* pskillMotion = CResMgr::GetInst()->LoadTexture(L"skill2_motion", L"texture\\skill2_motion.bmp");
	

	CreateAnimator();

	GetAnimator()->CreateAnimation(L"SKILL2_MOTION", pskillMotion, Vec2(0.f, 0.f), Vec2(146.5f, 96.f), Vec2(146.5f, 0.f), 0.05f, 7);

	

	del_time = 0.;
}


SkillMotion::~SkillMotion()
{
}

void SkillMotion::update()
{
	Vec2 tempPos = GetPos();


	GetAnimator()->Play(L"SKILL2_MOTION", false);

	del_time += fDT;

	if (del_time > 0.4)
	{
		SetDead();
	}
}


void SkillMotion::render(HDC _dc)
{
	component_render(_dc);
}
