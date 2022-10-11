#include "pch.h"
#include "Tomb.h"

#include "CTimeMgr.h"
#include "CCollider.h"
#include "CAnimator.h"
#include "CSceneMgr.h"
#include "CScene.h"
#include "CResMgr.h"
#include "CTexture.h"

Tomb::Tomb(Vec2 _pos)
{
	SetScale(Vec2(101.f, 47.f));

	CreateAnimator();

	CTexture* TombTex = CResMgr::GetInst()->LoadTexture(L"Tomb", L"texture\\Player\\condition_dead.bmp");
	m_finalTex = CResMgr::GetInst()->LoadTexture(L"FinalTomb", L"texture\\Player\\Tomb.bmp");


	GetAnimator()->CreateAnimation(L"TOMB_ANIM", TombTex, Vec2(0.f, 0.f), Vec2(101.f, 47.f), Vec2(101.f, 0.f), 0.05f, 20);
	

	PausePos = _pos;

	_pos.y -= 200.f;
	SetPos(_pos);
	m_time = 0.;
}


Tomb::~Tomb()
{
}


void Tomb::update()
{
	Vec2 mypos = GetPos();

	if (PausePos.y < mypos.y)
	{
		mypos.y = PausePos.y ;
	}
	else
	{
		mypos.y += 300.f * fDT;
	}

	mypos.x = PausePos.x+20.f;

	SetPos(mypos);

	GetAnimator()->Play(L"TOMB_ANIM", false);

	m_time += DT;
}

void Tomb::render(HDC _dc)
{
	
	component_render(_dc);
	
}