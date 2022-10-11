#include "pch.h"
#include "WideSkill.h"

#include "CCamera.h"
#include "CCollider.h"
#include "CAnimator.h"
#include "CAnimation.h"
#include "CSceneMgr.h"
#include "CScene.h"
#include "CResMgr.h"
#include "CTimeMgr.h"
#include "CSceneMgr.h"
#include "CSound.h"

WideSkill::WideSkill(Vec2 pos)
{
	SetPos(Vec2(150.f,0.f));
	SetScale(Vec2(950.f, 768.f));
	
	CTexture* pWideSkill = CResMgr::GetInst()->LoadTexture(L"Wide_skill", L"texture\\Skill\\WideSkill.bmp");
	

	CreateAnimator();

	GetAnimator()->CreateAnimation(L"WIDE_SKILL", pWideSkill, Vec2(0.f, 0.f), Vec2(950.f, 768.f), Vec2(950.f, 0.f), 0.1f, 31);

	
	m_oneTime = false;
	m_collioneTime = false;
	del_time = 0.;
	del_collidertime = 0.;

	m_Skill3Sound = CResMgr::GetInst()->FindSound(L"SKILL2_SOUND");
}


WideSkill::~WideSkill()
{
}

void WideSkill::update()
{
	CObject* player = CSceneMgr::GetInst()->GetCurScene()->GetPlayer();
	Vec2 pos = player->GetPos();
	pos.y -= 200.f;
	SetPos(pos);


	GetAnimator()->Play(L"WIDE_SKILL", false);

	if (!m_oneTime)
	{
		CCamera::GetInst()->subFadeOut(2.f);
		CCamera::GetInst()->subFadeIn(2.f);
		m_oneTime = true;
	}

	if (del_collidertime > 1.5f)
	{
		if (!m_collioneTime)
		{
			// 소리
			m_Skill3Sound->Play();
			m_Skill3Sound->SetVolume(100.f);

			// 진동
			CCamera::GetInst()->SetVibration(1.);
			CreateCollider();

			GetCollider()->SetScale(Vec2(2000.f, 2000.f));

			m_collioneTime = true;
		}

	}

	if (del_time > 3.2)
	{
		SetDead();
	}

	del_collidertime += DT;
	del_time += DT;
}


void WideSkill::render(HDC _dc)
{
	component_render(_dc);
}