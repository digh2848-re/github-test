#include "pch.h"
#include "Scene_Phase1.h"

#include "CObject.h"
#include "BackGround.h"
#include "Map.h"
#include "CPlayer.h"
#include "CMonster.h"

#include "CCore.h"


#include "CPathMgr.h"
#include "CTexture.h"

#include "CCollisionMgr.h"

#include "CKeyMgr.h"
#include "CSceneMgr.h"
#include "CCamera.h"

#include "AI.h"
#include "CIdleState.h"
#include "CTraceState.h"

#include "CCollider.h"
#include "CRigidBody.h"
#include "SelectGDI.h"
#include "CTimeMgr.h"

#include "CGround.h"
#include "CLadder.h"
#include "SkillMotion.h"

#include "CUIMgr.h"
#include "CUI.h"
#include "MainUI.h"
#include "CPanelUI.h"
#include "CBtnUI.h"
#include "FixedUI.h"
#include "CMouseUI.h"
#include "TextUI.h"
#include "Portal.h"
#include "QuestTextUI.h"
#include "AnimationUI.h"
#include "FIexedTextUI.h"
#include "HpBarUI.h"
#include "BossMonster.h"
#include "MiniMapUI.h"

Scene_Phase1::Scene_Phase1()
{
	boss = nullptr;
	delayUI = nullptr;
	m_delayTime = 0.f;
}


Scene_Phase1::~Scene_Phase1()
{
}

void Scene_Phase1::update()
{
	if (boss->GetHp() < 0.f)
	{
		((MiniMapUI*)(delayUI))->setTextrender();

		if (m_delayTime > 10.f)
		{
			// 씬전환
			CObject* player = CSceneMgr::GetInst()->GetCurScene()->GetPlayer();
			player->GetRigidBody()->SetVelocity(Vec2(0.f, 0.f));
			player->SetPos(Vec2(200.f, 570.f));
			ChangeScene(SCENE_TYPE::BOSSSPHASE2);
		}
		
		m_delayTime += fDT;
	}

	// player 프레임드랍으로 인해 맵밖에 갈 경우 세팅해줌 
	Vec2 pos = GetPlayer()->GetPos();
	if (pos.y > 780.f)
		pos.y = 700.f;
	GetPlayer()->SetPos(pos);

	CScene::update();
}

void Scene_Phase1::Enter()
{
	// map 추가
	CObject* pMap = new Map(MAP_TYPE::BOSSSTAGE1, Vec2(2161.f, 858.f));
	AddObject(pMap, GROUP_TYPE::MAP);

	////// 이전씬의 플레이어 가지고 세팅해두기
	CObject* pObj = GetGroupObject(GROUP_TYPE::PLAYER).front();
	//pObj->SetPos(Vec2(5450.f, 920.f));
	RegisterPlayer(pObj);
	// 플레이어 생성할때 카메라를 플레이어에게 부착
	CCamera::GetInst()->SetCurLookAt(pObj->GetPos());

	////맵크기에따라 맵 밖은 보여주면 안됨
	CCamera::GetInst()->SetMapMin(650.f);
	CCamera::GetInst()->SetMapMax(1674.f);

	// 보스몬스터 배치
	CObject* pbossMonster = new BossMonster(1);
	pbossMonster->SetName(L"SerenMonster");
	pbossMonster->SetPos(Vec2(2000.f, 650.f));
	pbossMonster->SetScale(Vec2(429.f, 444.f));
	((BossMonster*)pbossMonster)->SetTarget(pObj);
	boss = (BossMonster*)pbossMonster;

	AddObject(pbossMonster, GROUP_TYPE::BOSSMONSTER);

	// 마우스 커서 UI
	CObject* pMouseUI = new CMouseUI;
	pMouseUI->SetName(L"MouseUI");
	pMouseUI->SetScale(Vec2(26.f, 30.f));

	AddObject(pMouseUI, GROUP_TYPE::MOUSEUI);

	CObject* pGroundOne1 = new CGround;
	pGroundOne1->SetName(L"GroundOne1");
	pGroundOne1->SetPos(Vec2(1206.f, 780.f));
	pGroundOne1->SetScale(Vec2(2407.f, 76.f));

	AddObject(pGroundOne1, GROUP_TYPE::GROUND);

	// 보스몬스터 status바 UI
	CUI* BossStatusBarUI = new FixedUI(FIXED_TEX::BOSS_STATE);
	BossStatusBarUI->SetName(L"BossStatusBarUI");
	BossStatusBarUI->SetScale(Vec2(801.f, 37.f));
	BossStatusBarUI->SetPos(Vec2(150.f, 50.f));

	// 보스몬스터 status바 UI 자식
	CUI* BossHpBarUI = new HpBarUI(-1);
	BossHpBarUI->SetName(L"BossHPBarUI");
	BossHpBarUI->SetScale(Vec2(756.f, 10.f));
	BossHpBarUI->SetPos(Vec2(40.f, 5.f));
	((HpBarUI*)BossHpBarUI)->SetBossMonster((BossMonster*)pbossMonster);

	BossStatusBarUI->AddChild(BossHpBarUI);

	AddObject(BossStatusBarUI, GROUP_TYPE::UI);

	// 미니맵 UI 세팅하기

	CUI* BossPhaseUI = new MiniMapUI(MINIUI_TEX::BOSSPHASE);
	BossPhaseUI->SetName(L"bossPhaseUI");
	BossPhaseUI->SetScale(Vec2(750.f, 103.f));
	BossPhaseUI->SetPos(Vec2(600.f, 150.f));
	delayUI = BossPhaseUI;

	AddObject(BossPhaseUI, GROUP_TYPE::MINIMAPUI);
	

	CCollisionMgr::GetInst()->CheckGroup(GROUP_TYPE::PLAYER, GROUP_TYPE::GROUND);
	CCollisionMgr::GetInst()->CheckGroup(GROUP_TYPE::PLAYER, GROUP_TYPE::BOSSMONSTER);
	CCollisionMgr::GetInst()->CheckGroup(GROUP_TYPE::PLAYER, GROUP_TYPE::BOSSSKILL);
	CCollisionMgr::GetInst()->CheckGroup(GROUP_TYPE::PET, GROUP_TYPE::GROUND);
	CCollisionMgr::GetInst()->CheckGroup(GROUP_TYPE::BOSSMONSTER, GROUP_TYPE::SKILL);
	CCollisionMgr::GetInst()->CheckGroup(GROUP_TYPE::BOSSMONSTER, GROUP_TYPE::WIDESKILL);

	start();
}

void Scene_Phase1::render(HDC _dc)
{
	CScene::render(_dc);
}

void Scene_Phase1::Exit()
{
	// 씬 내용물 다 삭제
	MyDeleteAll();

	// 충돌 그룹 해제
	CCollisionMgr::GetInst()->Reset();
}
