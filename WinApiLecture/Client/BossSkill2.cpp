#include "pch.h"
#include "BossSkill2.h"

#include "CCollider.h"
#include "CAnimator.h"
#include "CAnimation.h"
#include "CResMgr.h"
#include "CTimeMgr.h"

BossSkill2::BossSkill2(Vec2 pos, int _dir)
{
	m_dir = _dir;
	SetPos(pos);
	SetScale(Vec2(152.f, 164.f));
	CreateCollider();

	GetCollider()->SetScale(Vec2(156.f, 157.f));

	CTexture* pSerenskill2Start = CResMgr::GetInst()->LoadTexture(L"serenskill1_start", L"texture\\Boss\\Obstacle_Start.bmp");
	CTexture* pSerenskill2fall = CResMgr::GetInst()->LoadTexture(L"serenskill1_fall", L"texture\\Boss\\Obstacle_Falling.bmp");
	CTexture* pSerenskill2end = CResMgr::GetInst()->LoadTexture(L"serenskill1_end", L"texture\\Boss\\Obstacle_End.bmp");
	
	CreateAnimator();

	GetAnimator()->CreateAnimation(L"SERENSKILL1_START", pSerenskill2Start, Vec2(0.f, 0.f), Vec2(152.f, 164.f), Vec2(152.f, 0.f), 0.1f, 9);
	GetAnimator()->CreateAnimation(L"SERENSKILL1_FALL", pSerenskill2fall, Vec2(0.f, 0.f), Vec2(156.f, 157.f), Vec2(156.f, 0.f), 0.05f, 15);
	GetAnimator()->CreateAnimation(L"SERENSKILL1_END", pSerenskill2end, Vec2(0.f, 0.f), Vec2(169.f, 168.f), Vec2(169.f, 0.f), 0.1f, 6);

	start_time = 0.f;
	dead_time = 0.f;
	IsSkillDead = false;
}


BossSkill2::~BossSkill2()
{
}

void BossSkill2::update()
{

	// 시작위치부터 태어나는 애니메이션
	if (start_time < 0.9f)
	{
		start_time += fDT;
		GetAnimator()->Play(L"SERENSKILL1_START", true);
	}
	else if (IsSkillDead)
	{
		if (dead_time > 0.6f)
		{
			SetDead();
		}
		else
		{
			dead_time += fDT;
			// Y축 어느지점에 도착하면 END하는 애미메이션 후 삭제
			GetAnimator()->Play(L"SERENSKILL1_END", true);
		}
	}
	else
	{
		GetAnimator()->Play(L"SERENSKILL1_FALL", true);
		Vec2 tempPos = GetPos();

		if (tempPos.y > 1000.f)
		{
			IsSkillDead = true;
		}
		// 움직이면서 FALLING 하는 애니메이션
		if (m_dir==1)
		{
			tempPos.x += (500.f * fDT);
			tempPos.y += (500.f * fDT);
		}
		else
		{
			tempPos.x -= (500.f * fDT);
			tempPos.y += (500.f * fDT);
		}

		
		SetPos(tempPos);
	}



}


void BossSkill2::render(HDC _dc)
{
	component_render(_dc);
}