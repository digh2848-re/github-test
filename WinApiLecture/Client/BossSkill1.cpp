#include "pch.h"
#include "BossSkill1.h"

#include "CCollider.h"
#include "CAnimator.h"
#include "CAnimation.h"
#include "CResMgr.h"
#include "CTimeMgr.h"

BossSkill1::BossSkill1(Vec2 pos, int Dir)
{
	SetPos(pos);
	SetScale(Vec2(886.f, 417.f));
	m_dir = Dir;
	CreateCollider();

	GetCollider()->SetScale(Vec2(700.f, 300.f));

	CTexture* pSerenskill1right = CResMgr::GetInst()->LoadTexture(L"serenskill1_right_skill", L"texture\\Boss\\seren_skill1_right.bmp");
	CTexture* pSerenskillelft = CResMgr::GetInst()->LoadTexture(L"serenskill1_left_skill", L"texture\\Boss\\seren_skill1_left.bmp");

	CreateAnimator();

	GetAnimator()->CreateAnimation(L"SERENSKILL1_RIGHT_SKILL", pSerenskill1right, Vec2(0.f, 0.f), Vec2(886.f, 417.f), Vec2(886.f, 0.f), 0.05f, 6);
	GetAnimator()->CreateAnimation(L"SERENSKILL1_LEFT_SKILL", pSerenskillelft, Vec2(0.f, 0.f), Vec2(886.f, 417.f), Vec2(886.f, 0.f), 0.05f, 6);

	del_time = 0.;
}


BossSkill1::~BossSkill1()
{
}


void BossSkill1::update()
{
	Vec2 tempPos = GetPos();

	if (m_dir == -1)
	{
		tempPos.x -= 100.f * fDT;
		SetPos(tempPos);

		GetAnimator()->Play(L"SERENSKILL1_LEFT_SKILL", true);

		del_time += fDT;
	}
	else
	{
		tempPos.x += 300.f * fDT;
		SetPos(tempPos);

		GetAnimator()->Play(L"SERENSKILL1_RIGHT_SKILL", true);

		del_time += fDT;
	}


	if (del_time > 3.)
	{
		SetDead();
	}
}


void BossSkill1::render(HDC _dc)
{
	component_render(_dc);
}