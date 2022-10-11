#include "LevelSkill.h"

#include "CCollider.h"
#include "CAnimator.h"
#include "CAnimation.h"
#include "CSceneMgr.h"
#include "CScene.h"
#include "CObject.h"
#include "CResMgr.h"
#include "CTimeMgr.h"

LevelSkill::LevelSkill(Vec2 pos)
{
	SetPos(pos);
	del_time = 0.;
	CreateCollider();

	GetCollider()->SetScale(Vec2(2000.f,2000.f));

	CTexture* pLevelSkill = CResMgr::GetInst()->LoadTexture(L"Level_Skill1", L"texture\\Skill\\levelupSkill.bmp");

	CreateAnimator();

	GetAnimator()->CreateAnimation(L"LEVELUP_SKILL", pLevelSkill, Vec2(0.f, 0.f), Vec2(904.f, 904.f), Vec2(904.f, 0.f), 0.1f, 18);
}


LevelSkill::~LevelSkill()
{
}


void LevelSkill::update()
{
	CObject* player = CSceneMgr::GetInst()->GetCurScene()->GetPlayer();
	Vec2 pos = player->GetPos();
	pos.y -= 150.f;

	SetPos(pos);

	GetAnimator()->Play(L"LEVELUP_SKILL", false);


	if (del_time > 2.)
	{
		SetDead();
	}

	del_time += DT;
}

void LevelSkill::render(HDC _dc)
{
	component_render(_dc);
}