#include "pch.h"
#include "Skill3.h"

#include "CCollider.h"
#include "CAnimator.h"
#include "CAnimation.h"
#include "CResMgr.h"
#include "CTimeMgr.h"
#include "CSound.h"

Skill3::Skill3(Vec2 pos, int Dir)
{
	SetPos(pos);
	SetScale(Vec2(743.f, 339.f));
	m_dir = Dir;
	CreateCollider();

	GetCollider()->SetScale(Vec2(600.f, 300.f));

	CTexture* ReadyRight = CResMgr::GetInst()->LoadTexture(L"skill3_ready_right", L"texture\\Skill\\skill3_Ready_Right.bmp");
	CTexture* ReadyLeft = CResMgr::GetInst()->LoadTexture(L"skill3_ready_left", L"texture\\Skill\\skill3_Ready_Left.bmp");
	CTexture* PlayRight = CResMgr::GetInst()->LoadTexture(L"skill3_play_right", L"texture\\Skill\\skill3_Player_Right.bmp");
	CTexture* PlayLeft = CResMgr::GetInst()->LoadTexture(L"skill3_play_left", L"texture\\Skill\\skill3_Player_Left.bmp");

	CreateAnimator();

	GetAnimator()->CreateAnimation(L"SKILL3_READY_RIGHT",	ReadyRight, Vec2(0.f, 0.f), Vec2(743.f, 339.f), Vec2(0.f, 339.f), 0.1f, 17);
	GetAnimator()->CreateAnimation(L"SKILL3_READY_LEFT",	ReadyLeft, Vec2(0.f, 0.f), Vec2(743.f, 339.f), Vec2(0.f, 339.f), 0.1f, 17);
	GetAnimator()->CreateAnimation(L"SKILL3_PLAY_RIGHT",	PlayRight, Vec2(0.f, 0.f), Vec2(743.f, 339.f), Vec2(0.f, 339.f), 0.1f, 7);
	GetAnimator()->CreateAnimation(L"SKILL3_PLAY_LEFT",		PlayLeft, Vec2(0.f, 0.f), Vec2(743.f, 339.f), Vec2(0.f, 339.f), 0.1f, 7);

	del_time = 0.;
	change_time = 0.f;
	IsTarget = false;

	m_skillSound = CResMgr::GetInst()->FindSound(L"SKILL3_SOUND");

	sound_time = 0.f;
	IsSoundOn = false;
}


Skill3::~Skill3()
{
}

void Skill3::update()
{
	Vec2 tempPos = GetPos();

	if (m_dir == -1)
	{
		//tempPos.x -= 100.f * fDT;
		//SetPos(tempPos);
		if (change_time > 1.65f)
		{			
			GetAnimator()->Play(L"SKILL3_PLAY_LEFT", true);
			IsTarget = true;
		}
		else
		{
			GetAnimator()->Play(L"SKILL3_READY_LEFT", false);
			change_time += fDT;
		}
		

		del_time += fDT;
	}
	else
	{
		//tempPos.x += 100.f * fDT;
		//SetPos(tempPos);

		if (change_time > 1.65f)
		{
			
			GetAnimator()->Play(L"SKILL3_PLAY_RIGHT", true);
			IsTarget = true;
		}
		else
		{
			GetAnimator()->Play(L"SKILL3_READY_RIGHT", false);
			change_time += fDT;
		}

		del_time += fDT;
	}

	if (sound_time > 1.f && !IsSoundOn)
	{
		IsSoundOn = true;
		m_skillSound->Play();
		m_skillSound->SetVolume(100.f);
	}

	sound_time += fDT;

	if (del_time > 5.)
	{
		SetDead();
	}
}


void Skill3::render(HDC _dc)
{
	component_render(_dc);
}
