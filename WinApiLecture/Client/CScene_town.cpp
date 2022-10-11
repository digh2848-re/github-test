#include "pch.h"
#include "CScene_town.h"

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
#include "NpcUI.h"
#include "Portal.h"
#include "BossMonster.h"
#include "MiniMapUI.h"


CScene_town::CScene_town()
	: m_pSkillUI(nullptr)
	, m_pEquipUI(nullptr)
	, m_pItemUI(nullptr)
	, IsFirst(true)
{
}


CScene_town::~CScene_town()
{
}

void CScene_town::update()
{
	//// 스킬창 강제로 띄우기
	//if (KEY_TAP(KEY::E))
	//{
	//	if (m_pSkillUI->GetIsOFF())
	//	{
	//		m_pSkillUI->SetUIOFF(false);
	//		CUIMgr::GetInst()->SetFocusedUI(m_pSkillUI);
	//	}
	//	else
	//	{
	//		m_pSkillUI->SetUIOFF(true);
	//	}
	//}
	//
	//
	//if (KEY_TAP(KEY::R))
	//{
	//	if (m_pEquipUI->GetIsOFF())
	//	{
	//		m_pEquipUI->SetUIOFF(false);
	//		CUIMgr::GetInst()->SetFocusedUI(m_pEquipUI);
	//	}
	//	else
	//	{
	//		m_pEquipUI->SetUIOFF(true);
	//	}
	//}
	//
	//
	//if (KEY_TAP(KEY::Y))
	//{
	//	if (m_pItemUI->GetIsOFF())
	//	{
	//		m_pItemUI->SetUIOFF(false);
	//		CUIMgr::GetInst()->SetFocusedUI(m_pItemUI);
	//	}
	//	else
	//	{
	//		m_pItemUI->SetUIOFF(true);
	//	}
	//}

	// player 프레임드랍으로 인해 맵밖에 갈 경우 세팅해줌 
	Vec2 pos = GetPlayer()->GetPos();
	if (pos.y > 1100.f)
		pos.y = 970.f;
	GetPlayer()->SetPos(pos);


	CScene::update();
}

void CScene_town::Enter()
{
	if (IsFirst)
	{
		IsFirst = false;

		// backGround 추가
		CObject* pBack = new BackGround;
		AddObject(pBack, GROUP_TYPE::BACKGROUND);

		// map 추가
		CObject* pMap = new Map(MAP_TYPE::TOWN, Vec2(5830.f, 1299.f));
		AddObject(pMap, GROUP_TYPE::MAP);

		
		//// Portal 추가
		CObject* pPortal = new Portal;
		pPortal->SetName(L"Protalfirst");
		pPortal->SetScale(Vec2(89.f, 257.f));
		pPortal->SetPos(Vec2(5400.f, 900.f));
		AddObject(pPortal, GROUP_TYPE::PORTAL);

		//// Portal 추가
		CObject* pPortal2 = new Portal;
		pPortal2->SetName(L"Protalsecond");
		pPortal2->SetScale(Vec2(89.f, 257.f));
		pPortal2->SetPos(Vec2(3350.f, 570.f));
		AddObject(pPortal2, GROUP_TYPE::PORTAL);

		//// 이전씬의 플레이어 가지고 세팅해두기
		CObject* pObj = GetGroupObject(GROUP_TYPE::PLAYER).front();
		RegisterPlayer(pObj);
		// 플레이어 생성할때 카메라를 플레이어에게 부착
		CCamera::GetInst()->SetCurLookAt(pObj->GetPos());
		
		//맵크기에따라 맵 밖은 보여주면 안됨
		CCamera::GetInst()->SetMapMin(650.f);
		CCamera::GetInst()->SetMapMax(5200.f);

		CObject* pGroundbottom1 = new CGround;
		pGroundbottom1->SetName(L"GroundBottom1");
		pGroundbottom1->SetPos(Vec2(4812.f, 1066.f));
		pGroundbottom1->SetScale(Vec2(3214.f, 80.f));
		
		AddObject(pGroundbottom1, GROUP_TYPE::GROUND);

		CObject* pGroundbottom2 = new CGround;
		pGroundbottom2->SetName(L"GroundBottom2");
		pGroundbottom2->SetPos(Vec2(3122.f, 1066.f));
		pGroundbottom2->SetScale(Vec2(200.f, 200.f));
		
		AddObject(pGroundbottom2 , GROUP_TYPE::GROUND);
		
		CObject* pGroundbottom3 = new CGround;
		pGroundbottom3->SetName(L"GroundBottom3");
		pGroundbottom3->SetPos(Vec2(2684.f, 976.f));
		pGroundbottom3->SetScale(Vec2(716.f, 139.f));
		
		AddObject(pGroundbottom3, GROUP_TYPE::GROUND);
		
		CObject* pGroundTop1 = new CGround;
		pGroundTop1->SetName(L"GroundTop1");
		pGroundTop1->SetPos(Vec2(3368.f, 731.f));
		pGroundTop1->SetScale(Vec2(941.f, 63.f));
		
		AddObject(pGroundTop1, GROUP_TYPE::GROUND);
		
		// 사다리 배치

		CObject* pLadder11 = new CLadder;
		pLadder11->SetName(L"Ladder1");
		pLadder11->SetPos(Vec2(2951.f, 782.f));
		pLadder11->SetScale(Vec2(35.f, 182.f));

		AddObject(pLadder11, GROUP_TYPE::LADDER);


	//// 보스몬스터 배치
	//CObject* pbossMonster = new BossMonster;
	//pbossMonster->SetName(L"SerenMonster");
	//pbossMonster->SetPos(Vec2(4700.f, 850.f));
	//pbossMonster->SetScale(Vec2(429.f,444.f));
	//((BossMonster*)pbossMonster)->SetTarget(pObj);
	//
	//AddObject(pbossMonster, GROUP_TYPE::BOSSMONSTER);

		CUI* npc1ClickUI = new NpcUI(NPCUI_TYPE::NPC1, 0);
		npc1ClickUI->SetName(L"NpcclickUI");
		npc1ClickUI->SetPos(Vec2(4500.f, 980.f));
		npc1ClickUI->SetScale(Vec2(59.f, 69.f));

		CUI* npcRequestUI = new NpcUI(NPCUI_TYPE::NONE);
		npcRequestUI->SetName(L"NPCRequestUI");
		npcRequestUI->SetPos(Vec2(4510.f, 920.f));
		npcRequestUI->SetScale(Vec2(44.f, 46.f));

		npc1ClickUI->AddChild(npcRequestUI);

		AddObject(npc1ClickUI, GROUP_TYPE::UI);

		CUI* npc2ClickUI = new NpcUI(NPCUI_TYPE::NPC2, 1);
		npc2ClickUI->SetName(L"NpcclickUI");
		npc2ClickUI->SetPos(Vec2(4200.f, 980.f));
		npc2ClickUI->SetScale(Vec2(56.f, 55.f));

		CUI* npc2RequestUI = new NpcUI(NPCUI_TYPE::NONE);
		npc2RequestUI->SetName(L"NPCRequestUI");
		npc2RequestUI->SetPos(Vec2(4210.f, 920.f));
		npc2RequestUI->SetScale(Vec2(44.f, 46.f));

		npc2ClickUI->AddChild(npc2RequestUI);

		AddObject(npc2ClickUI, GROUP_TYPE::UI);

		CUI* npc3ClickUI = new NpcUI(NPCUI_TYPE::NPC3, 2);
		npc3ClickUI->SetName(L"NpcclickUI");
		npc3ClickUI->SetPos(Vec2(3900.f, 980.f));
		npc3ClickUI->SetScale(Vec2(60.f, 80.f));

		CUI* npc3RequestUI = new NpcUI(NPCUI_TYPE::NONE);
		npc3RequestUI->SetName(L"NPCRequestUI");
		npc3RequestUI->SetPos(Vec2(3910.f, 920.f));
		npc3RequestUI->SetScale(Vec2(44.f, 46.f));

		npc3ClickUI->AddChild(npc3RequestUI);

		AddObject(npc3ClickUI, GROUP_TYPE::UI);

		// 미니맵 설계
		CUI* MiniMapDownTownUI = new MiniMapUI(MINIUI_TEX::DOWNTOWN);
		MiniMapDownTownUI->SetName(L"MiniMapTownUI");
		MiniMapDownTownUI->SetScale(Vec2(388.f, 86.f));
		MiniMapDownTownUI->SetPos(Vec2(0.f, 0.f));

		CUI* MiniPlayerUI = new MiniMapUI(MINIUI_TEX::CHILD);
		MiniPlayerUI->SetName(L"MiniplayerUI");
		MiniPlayerUI->SetScale(Vec2(5.f, 5.f));
		MiniPlayerUI->SetPos(Vec2(0.f, 0.f));

		MiniMapDownTownUI->AddChild(MiniPlayerUI);

		AddObject(MiniMapDownTownUI, GROUP_TYPE::MINIMAPUI);


		// 마우스 커서 UI
		CObject* pMouseUI = new CMouseUI;
		pMouseUI->SetName(L"MouseUI");
		pMouseUI->SetScale(Vec2(26.f, 30.f));



		AddObject(pMouseUI, GROUP_TYPE::MOUSEUI);

		CCollisionMgr::GetInst()->CheckGroup(GROUP_TYPE::MONSTER, GROUP_TYPE::SKILL);
		CCollisionMgr::GetInst()->CheckGroup(GROUP_TYPE::MONSTER, GROUP_TYPE::LEVELSKILL);
		CCollisionMgr::GetInst()->CheckGroup(GROUP_TYPE::MONSTER, GROUP_TYPE::WIDESKILL);
		CCollisionMgr::GetInst()->CheckGroup(GROUP_TYPE::PLAYER, GROUP_TYPE::GROUND);
		CCollisionMgr::GetInst()->CheckGroup(GROUP_TYPE::PLAYER, GROUP_TYPE::PORTAL);
		CCollisionMgr::GetInst()->CheckGroup(GROUP_TYPE::MONSTER, GROUP_TYPE::GROUND);
		CCollisionMgr::GetInst()->CheckGroup(GROUP_TYPE::PET, GROUP_TYPE::GROUND);
		CCollisionMgr::GetInst()->CheckGroup(GROUP_TYPE::PLAYER, GROUP_TYPE::LADDER);
		CCollisionMgr::GetInst()->CheckGroup(GROUP_TYPE::PLAYER, GROUP_TYPE::BOSSMONSTER);
		CCollisionMgr::GetInst()->CheckGroup(GROUP_TYPE::ITEM, GROUP_TYPE::GROUND);
		CCollisionMgr::GetInst()->CheckGroup(GROUP_TYPE::ITEM, GROUP_TYPE::PET);
	}
	else
	{
	// backGround 추가
	CObject* pBack = new BackGround;
	AddObject(pBack, GROUP_TYPE::BACKGROUND);

	// map 추가
	CObject* pMap = new Map(MAP_TYPE::TOWN, Vec2(5830.f, 1299.f));
	AddObject(pMap, GROUP_TYPE::MAP);

	//// Portal 추가
	CObject* pPortal = new Portal;
	pPortal->SetName(L"Protalfirst");
	pPortal->SetScale(Vec2(89.f, 257.f));
	pPortal->SetPos(Vec2(5400.f, 900.f));
	AddObject(pPortal, GROUP_TYPE::PORTAL);

	//// Portal 추가
	CObject* pPortal2 = new Portal;
	pPortal2->SetName(L"Protalsecond");
	pPortal2->SetScale(Vec2(89.f, 257.f));
	pPortal2->SetPos(Vec2(3350.f, 570.f));
	AddObject(pPortal2, GROUP_TYPE::PORTAL);

	
	//// 이전씬의 플레이어 가지고 세팅해두기
	CObject* pObj = GetGroupObject(GROUP_TYPE::PLAYER).front();
	RegisterPlayer(pObj);
	// 플레이어 생성할때 카메라를 플레이어에게 부착
	CCamera::GetInst()->SetCurLookAt(pObj->GetPos());

	//맵크기에따라 맵 밖은 보여주면 안됨
	CCamera::GetInst()->SetMapMin(650.f);
	CCamera::GetInst()->SetMapMax(5200.f);

	CObject* pGroundbottom1 = new CGround;
	pGroundbottom1->SetName(L"GroundBottom1");
	pGroundbottom1->SetPos(Vec2(4812.f, 1066.f));
	pGroundbottom1->SetScale(Vec2(3214.f, 80.f));

	AddObject(pGroundbottom1, GROUP_TYPE::GROUND);

	CObject* pGroundbottom2 = new CGround;
	pGroundbottom2->SetName(L"GroundBottom2");
	pGroundbottom2->SetPos(Vec2(3122.f, 1066.f));
	pGroundbottom2->SetScale(Vec2(200.f, 200.f));

	AddObject(pGroundbottom2, GROUP_TYPE::GROUND);

	CObject* pGroundbottom3 = new CGround;
	pGroundbottom3->SetName(L"GroundBottom3");
	pGroundbottom3->SetPos(Vec2(2684.f, 976.f));
	pGroundbottom3->SetScale(Vec2(716.f, 139.f));

	AddObject(pGroundbottom3, GROUP_TYPE::GROUND);

	CObject* pGroundTop1 = new CGround;
	pGroundTop1->SetName(L"GroundTop1");
	pGroundTop1->SetPos(Vec2(3368.f, 731.f));
	pGroundTop1->SetScale(Vec2(941.f, 63.f));

	AddObject(pGroundTop1, GROUP_TYPE::GROUND);

	// 사다리 배치

	CObject* pLadder11 = new CLadder;
	pLadder11->SetName(L"Ladder1");
	pLadder11->SetPos(Vec2(2951.f, 782.f));
	pLadder11->SetScale(Vec2(35.f, 182.f));

	AddObject(pLadder11, GROUP_TYPE::LADDER);

	//// 보스몬스터 배치
	//CObject* pbossMonster = new BossMonster;
	//pbossMonster->SetName(L"SerenMonster");
	//pbossMonster->SetPos(Vec2(4700.f, 850.f));
	//pbossMonster->SetScale(Vec2(429.f, 444.f));
	//((BossMonster*)pbossMonster)->SetTarget(pObj);
	//
	//AddObject(pbossMonster, GROUP_TYPE::BOSSMONSTER);

	
	// 미니맵 UI 세팅하기


	CUI* MiniMapDownTownUI = new MiniMapUI(MINIUI_TEX::DOWNTOWN);
	MiniMapDownTownUI->SetName(L"MiniMapTownUI");
	MiniMapDownTownUI->SetScale(Vec2(388.f, 86.f));
	MiniMapDownTownUI->SetPos(Vec2(0.f, 0.f));

	CUI* MiniPlayerUI = new MiniMapUI(MINIUI_TEX::CHILD);
	MiniPlayerUI->SetName(L"MiniplayerUI");
	MiniPlayerUI->SetScale(Vec2(5.f, 5.f));
	MiniPlayerUI->SetPos(Vec2(0.f, 0.f));

	MiniMapDownTownUI->AddChild(MiniPlayerUI);

	AddObject(MiniMapDownTownUI, GROUP_TYPE::MINIMAPUI);


	// 마우스 커서 UI
	CObject* pMouseUI = new CMouseUI;
	pMouseUI->SetName(L"MouseUI");
	pMouseUI->SetScale(Vec2(26.f, 30.f));



	AddObject(pMouseUI, GROUP_TYPE::MOUSEUI);

	CCollisionMgr::GetInst()->CheckGroup(GROUP_TYPE::MONSTER, GROUP_TYPE::SKILL);
	CCollisionMgr::GetInst()->CheckGroup(GROUP_TYPE::MONSTER, GROUP_TYPE::LEVELSKILL);
	CCollisionMgr::GetInst()->CheckGroup(GROUP_TYPE::MONSTER, GROUP_TYPE::WIDESKILL);
	CCollisionMgr::GetInst()->CheckGroup(GROUP_TYPE::PLAYER, GROUP_TYPE::GROUND);
	CCollisionMgr::GetInst()->CheckGroup(GROUP_TYPE::PLAYER, GROUP_TYPE::PORTAL);
	CCollisionMgr::GetInst()->CheckGroup(GROUP_TYPE::MONSTER, GROUP_TYPE::GROUND);
	CCollisionMgr::GetInst()->CheckGroup(GROUP_TYPE::PET, GROUP_TYPE::GROUND);
	CCollisionMgr::GetInst()->CheckGroup(GROUP_TYPE::PLAYER, GROUP_TYPE::LADDER);
	CCollisionMgr::GetInst()->CheckGroup(GROUP_TYPE::PLAYER, GROUP_TYPE::BOSSMONSTER);
	CCollisionMgr::GetInst()->CheckGroup(GROUP_TYPE::ITEM, GROUP_TYPE::GROUND);
	CCollisionMgr::GetInst()->CheckGroup(GROUP_TYPE::ITEM, GROUP_TYPE::PET);
	}


	 //Camera 효과 지정
	 //CCamera::GetInst()->FadeOut(0.01f);
	 CCamera::GetInst()->FadeIn(7.f);

	start();
}



void CScene_town::render(HDC _dc)
{
	CScene::render(_dc);
}

void CScene_town::Exit()
{
	// 씬 내용물 다 삭제
	MyDeleteAll();

	// 충돌 그룹 해제
	CCollisionMgr::GetInst()->Reset();
}