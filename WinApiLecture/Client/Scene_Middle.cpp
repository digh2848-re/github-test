#include "pch.h"
#include "Scene_Middle.h"

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
#include "MiniMapUI.h"

#include "CResMgr.h"
#include "CSound.h"


Scene_Middle::Scene_Middle()
	: m_pSkillUI(nullptr)
	, m_pEquipUI(nullptr)
	, m_pItemUI(nullptr)
{
	IsFirst = true;
	StopRecreate = false;

	VibrateTime = 0.f;
	VibrateWaitTime = 0.f;
	changeCameraTarget = 0.f;
	PortalTargetTime = 0.f;
	VibrateStop = false;
	IsPortalTarget = false;
	StopDirect = false;
	Targetportal = nullptr;
}


Scene_Middle::~Scene_Middle()
{
}


void Scene_Middle::update()
{
	if (!StopRecreate)
	{
		// 몬스터 죽으면 일정시간후 재생성 해주기
		for (int i = 0; i < 7; i++)
		{
			// 죽은 몬스터 발견
			if (MonsterArray[i].monsterAddress == nullptr)
			{
				MonsterArray[i].createTime += fDT;

				// 죽은후 5초지나면 재생성
				if (MonsterArray[i].createTime > 5.)
				{
					MonsterArray[i].createTime = 0.;

					CMonster* pMon = CMonFactory::CreateMonster(MON_TYPE::NORMAL, MonsterArray[i].initialPos, 1);
					pMon->SetName(L"Monster");
					AddObject(pMon, GROUP_TYPE::MONSTER);
					MonsterArray[i].monsterAddress = pMon;
				}
			}
		}
	}
	else
	{
		if (!StopDirect)
		{
			// 몇초 뒤에 화면 흔들리면서  
			if (VibrateWaitTime > 2.f && !VibrateStop)
			{
				GetPlayer()->GetRigidBody()->SetVelocity(Vec2(0.f, 0.f));
				CCamera::GetInst()->SetVibration(2.f);
				VibrateStop = true;
			}
		
			VibrateWaitTime += fDT;
		
			if (VibrateStop && !IsPortalTarget)
			{
				if (VibrateTime > 3.f)
				{
					CCamera::GetInst()->SetTarget(Targetportal);
					IsPortalTarget = true;
				}
		
				VibrateTime += fDT;
			}
		
			if (IsPortalTarget)
			{
				if (PortalTargetTime > 2.f)
				{
					CCamera::GetInst()->SetTarget(GetPlayer());
					StopDirect = true;
				}
		
				PortalTargetTime += fDT;
			}
		}
		

		

	}

	// textUI 먼저 생성된거 죽던지 말던지 상관없고 나중에 생성된거 부터 위치값만 세팅해주자
	// 어차피 그리는 것도 7개만 그릴꺼임
	vector<CObject*>& textGroup = GetTextUIGroup();
	vector<CObject*>::reverse_iterator iter = textGroup.rbegin();

	int seven = 0;
	for (; iter != textGroup.rend(); )
	{
		if (seven <= 6)
		{
			(*iter)->SetPos(Vec2(980.f, (650.f - seven * 20.f)));
			seven++;
		}
		else
		{
			break;
		}

		++iter;
	}
	

	// 스킬창 강제로 띄우기
	if (KEY_TAP(KEY::E))
	{
		if (m_pSkillUI->GetIsOFF())
		{
			m_pSkillUI->SetUIOFF(false);
			CUIMgr::GetInst()->SetFocusedUI(m_pSkillUI);
			//m_pSkillUI->SetPos(Vec2(300.f, 300.f));
		}
		else
		{
			m_pSkillUI->SetUIOFF(true);
		}
	}


	if (KEY_TAP(KEY::R))
	{
		if (m_pEquipUI->GetIsOFF())
		{
			m_pEquipUI->SetUIOFF(false);
			CUIMgr::GetInst()->SetFocusedUI(m_pEquipUI);
		}
		else
		{
			m_pEquipUI->SetUIOFF(true);
		}
	}


	if (KEY_TAP(KEY::Y))
	{
		if (m_pItemUI->GetIsOFF())
		{
			m_pItemUI->SetUIOFF(false);
			CUIMgr::GetInst()->SetFocusedUI(m_pItemUI);
			//m_pItemUI->SetPos(Vec2(300.f, 500.f));
		}
		else
		{
			m_pItemUI->SetUIOFF(true);
		}
	}


	// player 프레임드랍으로 인해 맵밖에 갈 경우 세팅해줌 
	Vec2 pos = GetPlayer()->GetPos();
	if (pos.y > 780.f)
		pos.y = 700.f;
	GetPlayer()->SetPos(pos);

	vector<CObject*>& monGroup = GetMonsterGroup();
	vector<CObject*>::iterator it = monGroup.begin();
	
	for ( ;it != monGroup.end(); it++)
	{
		Vec2 pos = (*it)->GetPos();
		if (pos.y > 780.f)
			pos.y = 650.f;
		(*it)->SetPos(pos);

	}
	
	

	CScene::update();
}

void Scene_Middle::Enter()
{
	if (IsFirst)
	{
		CSound* pNewSound = CResMgr::GetInst()->FindSound(L"BGM_03");

		//pNewSound->Play();
		pNewSound->PlayToBGM(true); // 백그라운드 재생
		pNewSound->SetPosition(0.f); // 백분율, 소리 위치 설정
		pNewSound->SetVolume(10.f);

		IsFirst = false;

		//// backGround 추가
		//CObject* pBack = new BackGround;
		//AddObject(pBack, GROUP_TYPE::BACKGROUND);

		// map 추가
		CObject* pMap = new Map(MAP_TYPE::MIDDLE, Vec2(2274.f, 858.f));
		AddObject(pMap, GROUP_TYPE::MAP);

		// Portal 추가
		CObject* pPortal = new Portal;
		pPortal->SetName(L"Protalsecond");
		pPortal->SetScale(Vec2(89.f, 257.f));
		pPortal->SetPos(Vec2(200.f, 620.f));
		AddObject(pPortal, GROUP_TYPE::PORTAL);

		////// 이전씬의 플레이어 가지고 세팅해두기
		CObject* pObj = GetGroupObject(GROUP_TYPE::PLAYER).front();
		//pObj->SetPos(Vec2(5450.f, 920.f));
		RegisterPlayer(pObj);
		// 플레이어 생성할때 카메라를 플레이어에게 부착
		CCamera::GetInst()->SetCurLookAt(pObj->GetPos());

		////맵크기에따라 맵 밖은 보여주면 안됨
		CCamera::GetInst()->SetMapMin(650.f);
		CCamera::GetInst()->SetMapMax(1674.f);

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

		//// 몬스터 배치
		CMonster* pMon = CMonFactory::CreateMonster(MON_TYPE::NORMAL, Vec2(600.f, 650.f),1);
		pMon->SetName(L"Monster");
		AddObject(pMon, GROUP_TYPE::MONSTER);

		MonsterArray[0].initialPos = Vec2(600.f, 650.f);
		MonsterArray[0].monsterAddress = pMon;

		//// 몬스터 배치
		CMonster* pMon1 = CMonFactory::CreateMonster(MON_TYPE::NORMAL, Vec2(750.f, 650.f),1);
		pMon1->SetName(L"Monster");
		AddObject(pMon1, GROUP_TYPE::MONSTER);

		MonsterArray[1].initialPos = Vec2(750.f, 650.f);
		MonsterArray[1].monsterAddress = pMon1;

		//// 몬스터 배치
		CMonster* pMon2 = CMonFactory::CreateMonster(MON_TYPE::NORMAL, Vec2(900.f, 650.f), 1);
		pMon2->SetName(L"Monster");
		AddObject(pMon2, GROUP_TYPE::MONSTER);

		MonsterArray[2].initialPos = Vec2(900.f, 650.f);
		MonsterArray[2].monsterAddress = pMon2;

		//// 몬스터 배치
		CMonster* pMon3 = CMonFactory::CreateMonster(MON_TYPE::NORMAL, Vec2(1050.f, 650.f), 1);
		pMon3->SetName(L"Monster");
		AddObject(pMon3, GROUP_TYPE::MONSTER);

		MonsterArray[3].initialPos = Vec2(1050.f, 650.f);
		MonsterArray[3].monsterAddress = pMon3;


		//// 몬스터 배치
		CMonster* pMon4 = CMonFactory::CreateMonster(MON_TYPE::NORMAL, Vec2(1200.f, 650.f), 1);
		pMon4->SetName(L"Monster");
		AddObject(pMon4, GROUP_TYPE::MONSTER);

		MonsterArray[4].initialPos = Vec2(1200.f, 650.f);
		MonsterArray[4].monsterAddress = pMon4;

		//// 몬스터 배치
		CMonster* pMon5 = CMonFactory::CreateMonster(MON_TYPE::NORMAL, Vec2(1350.f, 650.f), 1);
		pMon5->SetName(L"Monster");
		AddObject(pMon5, GROUP_TYPE::MONSTER);

		MonsterArray[5].initialPos = Vec2(1350.f, 650.f);
		MonsterArray[5].monsterAddress = pMon5;

		//// 몬스터 배치
		CMonster* pMon6 = CMonFactory::CreateMonster(MON_TYPE::NORMAL, Vec2(1500.f, 650.f), 1);
		pMon6->SetName(L"Monster");
		AddObject(pMon6, GROUP_TYPE::MONSTER);

		MonsterArray[6].initialPos = Vec2(1500.f, 650.f);
		MonsterArray[6].monsterAddress = pMon6;

		// 미니맵 설계
		CUI* MiniMapField2TownUI = new MiniMapUI(MINIUI_TEX::FIELD2);
		MiniMapField2TownUI->SetName(L"MiniMapfield2TownUI");
		MiniMapField2TownUI->SetScale(Vec2(144.f, 57.f));
		MiniMapField2TownUI->SetPos(Vec2(0.f, 0.f));

		CUI* MiniPlayerUI = new MiniMapUI(MINIUI_TEX::CHILD);
		MiniPlayerUI->SetName(L"MiniplayerUI");
		MiniPlayerUI->SetScale(Vec2(5.f, 5.f));
		MiniPlayerUI->SetPos(Vec2(0.f, 0.f));

		MiniMapField2TownUI->AddChild(MiniPlayerUI);

		AddObject(MiniMapField2TownUI, GROUP_TYPE::MINIMAPUI);


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
		CSound* pNewSound = CResMgr::GetInst()->FindSound(L"BGM_04");

		//pNewSound->Play();
		pNewSound->PlayToBGM(true); // 백그라운드 재생
		pNewSound->SetPosition(0.f); // 백분율, 소리 위치 설정
		pNewSound->SetVolume(10.f);

		// map 추가
		CObject* pMap = new Map(MAP_TYPE::MIDDLE, Vec2(2274.f, 858.f));
		AddObject(pMap, GROUP_TYPE::MAP);

		
		// Portal 추가
		CObject* pPortal = new Portal;
		pPortal->SetName(L"Protalsecond");
		pPortal->SetScale(Vec2(89.f, 257.f));
		pPortal->SetPos(Vec2(200.f, 620.f));
		AddObject(pPortal, GROUP_TYPE::PORTAL);

		// Portal 추가
		CObject* pPortal3 = new Portal;
		pPortal3->SetName(L"Protalthird");
		pPortal3->SetScale(Vec2(89.f, 257.f));
		pPortal3->SetPos(Vec2(2000.f, 620.f));
		AddObject(pPortal3, GROUP_TYPE::PORTAL);
		// 연출을 위해 타켓팅 해둠
		Targetportal = pPortal3;

		////// 이전씬의 플레이어 가지고 세팅해두기
		CObject* pObj = GetGroupObject(GROUP_TYPE::PLAYER).front();
		RegisterPlayer(pObj);
		// 플레이어 생성할때 카메라를 플레이어에게 부착
		CCamera::GetInst()->SetCurLookAt(pObj->GetPos());

		////맵크기에따라 맵 밖은 보여주면 안됨
		CCamera::GetInst()->SetMapMin(650.f);
		CCamera::GetInst()->SetMapMax(1674.f);

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

		// 미니맵 설계
		CUI* MiniMapField2TownUI = new MiniMapUI(MINIUI_TEX::FIELD2);
		MiniMapField2TownUI->SetName(L"MiniMapfield2TownUI");
		MiniMapField2TownUI->SetScale(Vec2(144.f, 57.f));
		MiniMapField2TownUI->SetPos(Vec2(0.f, 0.f));

		CUI* MiniPlayerUI = new MiniMapUI(MINIUI_TEX::CHILD);
		MiniPlayerUI->SetName(L"MiniplayerUI");
		MiniPlayerUI->SetScale(Vec2(5.f, 5.f));
		MiniPlayerUI->SetPos(Vec2(0.f, 0.f));

		MiniMapField2TownUI->AddChild(MiniPlayerUI);

		AddObject(MiniMapField2TownUI, GROUP_TYPE::MINIMAPUI);

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

	start();
}

void Scene_Middle::render(HDC _dc)
{
	// render에서 제거하니깐 제거하기전에 몬스터 재생성을 위해 확인하자
	
	vector<CObject*>& MonsterGroup = GetMonsterGroup();
	
	vector<CObject*>::iterator iter = MonsterGroup.begin();
	
	for (; iter != MonsterGroup.end(); ++iter)
	{
		// 혹시 벡터에 nullptr 있는 경우는 안할꺼임 그리고 죽는 몬스터라면
		if ((*iter) != nullptr && (*iter)->IsDead())
		{
			for (int i = 0; i < 7; i++)
			{
				// 객체를 가리키는 주소가 같다면 동일한거
				if (MonsterArray[i].monsterAddress == (*iter))
				{
					// 죽은걸로 일단 체크해줌
					MonsterArray[i].monsterAddress = nullptr;
				}
			}
		}
	
	}

	CScene::render(_dc);

}



void Scene_Middle::Exit()
{
	StopRecreate = true;

	// 씬 내용물 다 삭제
	MyDeleteAll();

	// 충돌 그룹 해제
	CCollisionMgr::GetInst()->Reset();
}

