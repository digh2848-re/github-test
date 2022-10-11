#include "pch.h"
#include "CScene_Start.h"

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
#include "Portal.h"
#include "QuestTextUI.h"
#include "AnimationUI.h"
#include "FIexedTextUI.h"
#include "HpBarUI.h"
#include "MiniMapUI.h"
#include "CResMgr.h"
#include "CSound.h"


CScene_Start::CScene_Start()
	: m_bUseForce(false)
	, m_fCurRadius(0.f)
	, m_fForceRadius(500.f)
	, m_fForce(500.f)
	, m_delaytime(0.)
	, m_motiondir(1)
	, m_pSkillUI(nullptr)
	, m_pEquipUI(nullptr)
	, m_pItemUI(nullptr)
{
	IsFirst = true;
}


CScene_Start::~CScene_Start()
{
}


void CScene_Start::update()
{

	// 몬스터 죽으면 일정시간후 재생성 해주기
	for (int i = 0; i < 13; i++)
	{
		// 죽은 몬스터 발견
		if (MonsterArray[i].monsterAddress == nullptr)
		{
			MonsterArray[i].createTime += fDT;

			// 죽은후 5초지나면 재생성
			if (MonsterArray[i].createTime > 5.)
			{
				MonsterArray[i].createTime = 0.;

				CMonster* pMon = CMonFactory::CreateMonster(MON_TYPE::NORMAL, MonsterArray[i].initialPos, -1);
				pMon->SetName(L"Monster");
				AddObject(pMon, GROUP_TYPE::MONSTER);
				MonsterArray[i].monsterAddress = pMon;
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


	if (KEY_TAP(KEY::T))
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


	if (KEY_TAP(KEY::Y))
	{
		if (m_EnforceUI->GetIsOFF())
		{
			m_EnforceUI->SetUIOFF(false);
			CUIMgr::GetInst()->SetFocusedUI(m_EnforceUI);
			//m_pItemUI->SetPos(Vec2(300.f, 500.f));
		}
		else
		{
			m_EnforceUI->SetUIOFF(true);
		}
	}

	// player 프레임드랍으로 인해 맵밖에 갈 경우 세팅해줌 
	Vec2 pos = GetPlayer()->GetPos();
	if (pos.y > 980.f)
		pos.y = 850.f;
	GetPlayer()->SetPos(pos);


	CScene::update();


}





void CScene_Start::render(HDC _dc)
{

	// render에서 제거하니깐 제거하기전에 몬스터 재생성을 위해 확인하자

	 vector<CObject*>& MonsterGroup = GetMonsterGroup();
	
	vector<CObject*>::iterator iter = MonsterGroup.begin();

	for (; iter != MonsterGroup.end(); ++iter)
	{
		// 혹시 벡터에 nullptr 있는 경우는 안할꺼임 그리고 죽는 몬스터라면
		if ((*iter)!=nullptr && (*iter)->IsDead())
		{
			for (int i = 0; i < 13; i++)
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
 
void CScene_Start::Enter()
{

	srand((unsigned int)time(nullptr));
	
	if (IsFirst)
	{
		CSound* pNewSound = CResMgr::GetInst()->FindSound(L"BGM_01");

		//pNewSound->Play();
		pNewSound->PlayToBGM(true); // 백그라운드 재생
		pNewSound->SetPosition(0.f); // 백분율, 소리 위치 설정
		pNewSound->SetVolume(10.f);

		IsFirst = false;

		// backGround 추가
		CObject* pBack = new BackGround;
		AddObject(pBack, GROUP_TYPE::BACKGROUND);

		// map 추가
		CObject* pMap = new Map(MAP_TYPE::HUNT, Vec2(1620.f, 1118.f));
		AddObject(pMap, GROUP_TYPE::MAP);

		// Portal 추가
		CObject* pPortal = new Portal;
		pPortal->SetName(L"Protalfirst");
		pPortal->SetScale(Vec2(89.f, 257.f));
		pPortal->SetPos(Vec2(110.f, 790.f));
		AddObject(pPortal, GROUP_TYPE::PORTAL);


		// Player 추가
		CObject* pObj = new CPlayer;
		pObj->SetName(L"Player");
		pObj->SetPos(Vec2(200.f, 100.f));
		pObj->SetScale(Vec2(50.f, 50.f));


		AddObject(pObj, GROUP_TYPE::PLAYER);

		RegisterPlayer(pObj);


		// 플레이어 생성할때 카메라를 플레이어에게 부착
		CCamera::GetInst()->SetTarget(pObj);
		// 맵크기에따라 맵 밖은 보여주면 안됨
		CCamera::GetInst()->SetMapMin(650.f);
		CCamera::GetInst()->SetMapMax(1020.f);

		//// 몬스터 배치
		CMonster* pMon = CMonFactory::CreateMonster(MON_TYPE::NORMAL, Vec2(1200.f, 700.f), -1);
		pMon->SetName(L"Monster");
		AddObject(pMon, GROUP_TYPE::MONSTER);

		MonsterArray[0].initialPos = Vec2(1200.f, 700.f);
		MonsterArray[0].monsterAddress = pMon;

		CMonster* pMon2 = CMonFactory::CreateMonster(MON_TYPE::NORMAL, Vec2(1000.f, 700.f), -1);
		pMon2->SetName(L"Monster");
		AddObject(pMon2, GROUP_TYPE::MONSTER);

		MonsterArray[1].initialPos = Vec2(1000.f, 700.f);
		MonsterArray[1].monsterAddress = pMon2;

		CMonster* pMon3 = CMonFactory::CreateMonster(MON_TYPE::NORMAL, Vec2(800.f, 700.f), -1);
		pMon3->SetName(L"Monster");
		AddObject(pMon3, GROUP_TYPE::MONSTER);

		MonsterArray[2].initialPos = Vec2(800.f, 700.f);
		MonsterArray[2].monsterAddress = pMon3;

		CMonster* pMon4 = CMonFactory::CreateMonster(MON_TYPE::NORMAL, Vec2(600.f, 700.f), -1);
		pMon4->SetName(L"Monster");
		AddObject(pMon4, GROUP_TYPE::MONSTER);

		MonsterArray[3].initialPos = Vec2(600.f, 700.f);
		MonsterArray[3].monsterAddress = pMon4;

		CMonster* pMon5 = CMonFactory::CreateMonster(MON_TYPE::NORMAL, Vec2(400.f, 700.f), -1);
		pMon5->SetName(L"Monster");
		AddObject(pMon5, GROUP_TYPE::MONSTER);

		MonsterArray[4].initialPos = Vec2(400.f, 700.f);
		MonsterArray[4].monsterAddress = pMon5;

		//------------

		CMonster* pMon6 = CMonFactory::CreateMonster(MON_TYPE::NORMAL, Vec2(1100.f, 500.f), -1);
		pMon6->SetName(L"Monster");
		AddObject(pMon6, GROUP_TYPE::MONSTER);

		MonsterArray[5].initialPos = Vec2(1100.f, 640.f);
		MonsterArray[5].monsterAddress = pMon6;

		CMonster* pMon7 = CMonFactory::CreateMonster(MON_TYPE::NORMAL, Vec2(1000.f, 500.f), -1);
		pMon7->SetName(L"Monster");
		AddObject(pMon7, GROUP_TYPE::MONSTER);

		MonsterArray[6].initialPos = Vec2(1000.f, 640.f);
		MonsterArray[6].monsterAddress = pMon7;

		CMonster* pMon8 = CMonFactory::CreateMonster(MON_TYPE::NORMAL, Vec2(800.f, 500.f), -1);
		pMon8->SetName(L"Monster");
		AddObject(pMon8, GROUP_TYPE::MONSTER);

		MonsterArray[7].initialPos = Vec2(800.f, 640.f);
		MonsterArray[7].monsterAddress = pMon8;



		CMonster* pMon9 = CMonFactory::CreateMonster(MON_TYPE::NORMAL, Vec2(600.f, 500.f), -1);
		pMon9->SetName(L"Monster");
		AddObject(pMon9, GROUP_TYPE::MONSTER);

		MonsterArray[8].initialPos = Vec2(600.f, 640.f);
		MonsterArray[8].monsterAddress = pMon9;

		//-------------

		CMonster* pMon10 = CMonFactory::CreateMonster(MON_TYPE::NORMAL, Vec2(1100.f, 450.f), -1);
		pMon10->SetName(L"Monster");
		AddObject(pMon10, GROUP_TYPE::MONSTER);

		MonsterArray[9].initialPos = Vec2(1100.f, 395.f);
		MonsterArray[9].monsterAddress = pMon10;

		CMonster* pMon11 = CMonFactory::CreateMonster(MON_TYPE::NORMAL, Vec2(1000.f, 450.f), -1);
		pMon11->SetName(L"Monster");
		AddObject(pMon11, GROUP_TYPE::MONSTER);

		MonsterArray[10].initialPos = Vec2(1000.f, 395.f);
		MonsterArray[10].monsterAddress = pMon11;


		CMonster* pMon12 = CMonFactory::CreateMonster(MON_TYPE::NORMAL, Vec2(800.f, 450.f), -1);
		pMon12->SetName(L"Monster");
		AddObject(pMon12, GROUP_TYPE::MONSTER);

		MonsterArray[11].initialPos = Vec2(800.f, 395.f);
		MonsterArray[11].monsterAddress = pMon12;


		CMonster* pMon13 = CMonFactory::CreateMonster(MON_TYPE::NORMAL, Vec2(600.f, 450.f), -1);
		pMon5->SetName(L"Monster");
		AddObject(pMon13, GROUP_TYPE::MONSTER);

		MonsterArray[12].initialPos = Vec2(600.f, 395.f);
		MonsterArray[12].monsterAddress = pMon13;

	

		// 땅 물체 배치


		CObject* pGroundOne1 = new CGround;
		pGroundOne1->SetName(L"GroundOne1");
		pGroundOne1->SetPos(Vec2(800.f, 948.f));
		pGroundOne1->SetScale(Vec2(1691.f, 80.f));

		AddObject(pGroundOne1, GROUP_TYPE::GROUND);

		CObject* pGroundSecond1 = new CGround;
		pGroundSecond1->SetName(L"GroundSecond1");
		pGroundSecond1->SetPos(Vec2(924.f, 698.f));
		pGroundSecond1->SetScale(Vec2(1068.f, 53.f));

		AddObject(pGroundSecond1, GROUP_TYPE::GROUND);


		CObject* pGroundSecond2 = new CGround;
		pGroundSecond2->SetName(L"GroundSecond2");
		pGroundSecond2->SetPos(Vec2(271.f, 643.f));
		pGroundSecond2->SetScale(Vec2(229.f, 74.f));

		AddObject(pGroundSecond2, GROUP_TYPE::GROUND);

		CObject* pGroundThird1 = new CGround;
		pGroundThird1->SetName(L"Ground");
		pGroundThird1->SetPos(Vec2(921.f, 453.f));
		pGroundThird1->SetScale(Vec2(1068.f, 53.f));

		AddObject(pGroundThird1, GROUP_TYPE::GROUND);

		CObject* pGroundThird2 = new CGround;
		pGroundThird2->SetName(L"Ground");
		pGroundThird2->SetPos(Vec2(271.f, 407.f));
		pGroundThird2->SetScale(Vec2(229.f, 74.f));

		AddObject(pGroundThird2, GROUP_TYPE::GROUND);

		CObject* pGroundRightWall = new CGround;
		pGroundRightWall->SetName(L"GroundOne1");
		pGroundRightWall->SetPos(Vec2(1726.f, 386.f));
		pGroundRightWall->SetScale(Vec2(209.f, 1469.f));

		AddObject(pGroundRightWall, GROUP_TYPE::GROUND);

		// 사다리 배치

		CObject* pLadder1 = new CLadder;
		pLadder1->SetName(L"Ladder1");
		pLadder1->SetPos(Vec2(278.f, 726.f));
		pLadder1->SetScale(Vec2(5.f, 240.f));

		AddObject(pLadder1, GROUP_TYPE::LADDER);


		CObject* pLadder2 = new CLadder;
		pLadder2->SetName(L"Ladder1");
		pLadder2->SetPos(Vec2(203.f, 445.f));
		pLadder2->SetScale(Vec2(5.f, 150.f));

		AddObject(pLadder2, GROUP_TYPE::LADDER);


		// UI 배치
		//Vec2 vResolution = CCore::GetInst()->GetResolution();

		// 빨리 찾기위해서  UI 컨테이너 앞에 둠( 삭제될 경우도 없어서)
		
		//====================
		// 퀘스트1 대화창모음

		CUI* Quest1Step1UI = new FixedUI(FIXED_TEX::QUEST1_STEP1);
		Quest1Step1UI->SetName(L"Quest1Step1UI");
		Quest1Step1UI->SetScale(Vec2(519.f, 190.f));
		Quest1Step1UI->SetPos(Vec2(200.f, 200.f));
		Quest1Step1UI->SetUIOFF(true);

		AddObject(Quest1Step1UI, GROUP_TYPE::UI);

		CUI* Quest1Step2UI = new FixedUI(FIXED_TEX::QUEST1_STEP2);
		Quest1Step2UI->SetName(L"Quest1Step2UI");
		Quest1Step2UI->SetScale(Vec2(519.f, 190.f));
		Quest1Step2UI->SetPos(Vec2(200.f, 200.f));
		Quest1Step2UI->SetUIOFF(true);

		AddObject(Quest1Step2UI, GROUP_TYPE::UI);
		
		//====================
		// 퀘스트2 대화창모음

		CUI* Quest2Step1UI = new FixedUI(FIXED_TEX::QUEST2_STEP1);
		Quest2Step1UI->SetName(L"Quest2Step1UI");
		Quest2Step1UI->SetScale(Vec2(519.f, 190.f));
		Quest2Step1UI->SetPos(Vec2(200.f, 200.f));
		Quest2Step1UI->SetUIOFF(true);

		AddObject(Quest2Step1UI, GROUP_TYPE::UI);

		CUI* Quest2Step2UI = new FixedUI(FIXED_TEX::QUEST2_STEP2);
		Quest2Step2UI->SetName(L"Quest2Step2UI");
		Quest2Step2UI->SetScale(Vec2(519.f, 190.f));
		Quest2Step2UI->SetPos(Vec2(200.f, 200.f));
		Quest2Step2UI->SetUIOFF(true);

		AddObject(Quest2Step2UI, GROUP_TYPE::UI);


		//====================
		// 퀘스트3 대화창모음

		CUI* Quest3Step1UI = new FixedUI(FIXED_TEX::QUEST3_STEP1);
		Quest3Step1UI->SetName(L"Quest3Step1UI");
		Quest3Step1UI->SetScale(Vec2(519.f, 190.f));
		Quest3Step1UI->SetPos(Vec2(200.f, 200.f));
		Quest3Step1UI->SetUIOFF(true);

		AddObject(Quest3Step1UI, GROUP_TYPE::UI);

		CUI* Quest3Step2UI = new FixedUI(FIXED_TEX::QUEST3_STEP2);
		Quest3Step2UI->SetName(L"Quest3Step2UI");
		Quest3Step2UI->SetScale(Vec2(519.f, 190.f));
		Quest3Step2UI->SetPos(Vec2(200.f, 200.f));
		Quest3Step2UI->SetUIOFF(true);

		AddObject(Quest3Step2UI, GROUP_TYPE::UI);



		// mainUI 틀(최상위부모)

		CUI* pMainUI = new MainUI;
		pMainUI->SetName(L"MainUI");
		pMainUI->SetScale(Vec2(1200.f, 90.f));
		pMainUI->SetPos(Vec2(0.f, 678.f));


		// 플레이어 status바 UI
		CUI* pStatusBarUI = new FixedUI(FIXED_TEX::PLAYER_STATE);
		pStatusBarUI->SetName(L"StatusBarUI");
		pStatusBarUI->SetScale(Vec2(202.f, 66.f));
		pStatusBarUI->SetPos(Vec2(499.f, 0.f));

		// 플레이어 status바 UI 자식
		CUI* pHpBarUI = new HpBarUI(1);
		pHpBarUI->SetName(L"HPBarUI");
		pHpBarUI->SetScale(Vec2(172.f,13.f));
		pHpBarUI->SetPos(Vec2(24.f, 28.f));

		pStatusBarUI->AddChild(pHpBarUI);

		// 레벨 / 이름 Text UI
		CUI* pLevelNameUI = new FixedUI(FIXED_TEX::TEXT_FIXED);
		pLevelNameUI->SetName(L"LevelNameUI");
		pLevelNameUI->SetScale(Vec2(100.f, 50.f));
		pLevelNameUI->SetPos(Vec2(10.f, 2.f));

		pStatusBarUI->AddChild(pLevelNameUI);



		pMainUI->AddChild(pStatusBarUI);

		// 부모가 계층적으로 호출해줌
		// 즉 obj 그룹리스트에선 최상위 부모끼리만 존재함
		AddObject(pMainUI, GROUP_TYPE::UI);

		//===================================

		// main화면에서 스킬 스롯은 따로 둘꺼임

		// 스킬스롯 UI (최상위 부모)
		CUI* pSkillSlotUI = new FixedUI(FIXED_TEX::SKILL_QUICK_SLOT);
		pSkillSlotUI->SetName(L"SkillSlotUI");
		pSkillSlotUI->SetScale(Vec2(243.f, 79.f));
		pSkillSlotUI->SetPos(Vec2(957.f, 680.f));

		// 스킬스롯 버튼 UI 들
		CBtnUI* SkillSlot1BtnUI = new CBtnUI(BUTTON_TEX::NONE);
		SkillSlot1BtnUI->SetName(L"SkillSlot1BtnUI");
		SkillSlot1BtnUI->SetScale(Vec2(32.f, 32.f));
		SkillSlot1BtnUI->SetPos(Vec2(6.f, 6.f));

		CBtnUI* SkillSlot2BtnUI = new CBtnUI(BUTTON_TEX::NONE);
		SkillSlot2BtnUI->SetName(L"SkillSlot2BtnUI");
		SkillSlot2BtnUI->SetScale(Vec2(32.f, 32.f));
		SkillSlot2BtnUI->SetPos(Vec2(38.f, 6.f));

		CBtnUI* SkillSlot3BtnUI = new CBtnUI(BUTTON_TEX::NONE);
		SkillSlot3BtnUI->SetName(L"SkillSlot3BtnUI");
		SkillSlot3BtnUI->SetScale(Vec2(32.f, 32.f));
		SkillSlot3BtnUI->SetPos(Vec2(70.f, 6.f));

		CBtnUI* SkillSlot4BtnUI = new CBtnUI(BUTTON_TEX::NONE);
		SkillSlot4BtnUI->SetName(L"SkillSlot4BtnUI");
		SkillSlot4BtnUI->SetScale(Vec2(32.f, 32.f));
		SkillSlot4BtnUI->SetPos(Vec2(102.f, 6.f));

		pSkillSlotUI->AddChild(SkillSlot1BtnUI);
		pSkillSlotUI->AddChild(SkillSlot2BtnUI);
		pSkillSlotUI->AddChild(SkillSlot3BtnUI);
		pSkillSlotUI->AddChild(SkillSlot4BtnUI);
		pSkillSlotUI->AddChildBtnUI(SkillSlot1BtnUI);
		pSkillSlotUI->AddChildBtnUI(SkillSlot2BtnUI);
		pSkillSlotUI->AddChildBtnUI(SkillSlot3BtnUI);
		pSkillSlotUI->AddChildBtnUI(SkillSlot4BtnUI);

		AddObject(pSkillSlotUI, GROUP_TYPE::UI);

		// PanelUI들 (최상위 부모)

		// 장비창 UI
		CUI* EquipMainUI = new CPanelUI(PANEL_TEX::EQUIP);
		EquipMainUI->SetName(L"equipmainUI");
		EquipMainUI->SetScale(Vec2(232.f, 354.f));
		EquipMainUI->SetPos(Vec2(0.f, 0.f));

		//  장비 옷 Slot 1 UI
		CBtnUI* EquipSlot1BtnUI = new CBtnUI(BUTTON_TEX::NONE);
		EquipSlot1BtnUI->SetName(L"EquipSlot1BtnUI");
		EquipSlot1BtnUI->SetScale(Vec2(28.f, 29.f));
		EquipSlot1BtnUI->SetPos(Vec2(100.f, 183.f));

		//  장비 무기 Slot 2 UI
		CBtnUI* EquipSlot2BtnUI = new CBtnUI(BUTTON_TEX::NONE);
		EquipSlot2BtnUI->SetName(L"EquipSlot2BtnUI");
		EquipSlot2BtnUI->SetScale(Vec2(28.f, 29.f));
		EquipSlot2BtnUI->SetPos(Vec2(60.f, 183.f));

		// 장비 Exit UI
		CBtnUI* EquipExitBtnUI = new CBtnUI(BUTTON_TEX::EXIT);
		EquipExitBtnUI->SetName(L"EquipExitBtnUI");
		EquipExitBtnUI->SetScale(Vec2(15.f, 15.f));
		EquipExitBtnUI->SetPos(Vec2(212.f, 3.f));

		EquipMainUI->AddChild(EquipSlot1BtnUI);
		EquipMainUI->AddChild(EquipSlot2BtnUI);
		EquipMainUI->AddChild(EquipExitBtnUI);
		EquipMainUI->AddChildBtnUI(EquipSlot1BtnUI);
		EquipMainUI->AddChildBtnUI(EquipSlot2BtnUI);
		EquipMainUI->AddChildBtnUI(EquipExitBtnUI);

		EquipMainUI->SetUIOFF(true);

		AddObject(EquipMainUI, GROUP_TYPE::UI);

		//============================
		// 아이템창 UI
		CUI* ItemMainUI = new CPanelUI(PANEL_TEX::ITEM);
		ItemMainUI->SetName(L"itemMainUI");
		ItemMainUI->SetScale(Vec2(197.f, 380.f));
		ItemMainUI->SetPos(Vec2(600.f, 100.f));


		// 아이템 Slot 1 UI
		CBtnUI* Slot1BtnUI = new CBtnUI(BUTTON_TEX::CLOTH);
		Slot1BtnUI->SetName(L"Slot1BtnUI");
		Slot1BtnUI->SetScale(Vec2(28.f, 29.f));
		Slot1BtnUI->SetPos(Vec2(16.f, 57.f));

		// 아이템 Slot 2 UI
		CBtnUI* Slot2BtnUI = new CBtnUI(BUTTON_TEX::WEAPON);
		Slot2BtnUI->SetName(L"Slot1BtnUI");
		Slot2BtnUI->SetScale(Vec2(28.f, 29.f));
		Slot2BtnUI->SetPos(Vec2(58.f, 57.f));

		// 아이템 Slot 3 UI
		CBtnUI* Slot3BtnUI = new CBtnUI(BUTTON_TEX::WEAPON);
		Slot3BtnUI->SetName(L"Slot1BtnUI");
		Slot3BtnUI->SetScale(Vec2(28.f, 29.f));
		Slot3BtnUI->SetPos(Vec2(100.f, 57.f));

		// 아이템 Slot 4 UI
		CBtnUI* Slot4BtnUI = new CBtnUI(BUTTON_TEX::MP);
		Slot4BtnUI->SetName(L"Slot1BtnUI");
		Slot4BtnUI->SetScale(Vec2(28.f, 29.f));
		Slot4BtnUI->SetPos(Vec2(142.f, 57.f));

		// 아이템 Slot 5 UI
		CBtnUI* Slot5BtnUI = new CBtnUI(BUTTON_TEX::HP);
		Slot5BtnUI->SetName(L"Slot1BtnUI");
		Slot5BtnUI->SetScale(Vec2(28.f, 29.f));
		Slot5BtnUI->SetPos(Vec2(16.f, 99.f));

		// 아이템 Slot 6 UI
		CBtnUI* Slot6BtnUI = new CBtnUI(BUTTON_TEX::FORCEITEM);
		Slot6BtnUI->SetName(L"Slot1BtnUI");
		Slot6BtnUI->SetScale(Vec2(28.f, 29.f));
		Slot6BtnUI->SetPos(Vec2(58.f, 99.f));

		// 아이템 Slot 7 UI
		CBtnUI* Slot7BtnUI = new CBtnUI(BUTTON_TEX::NONE);
		Slot7BtnUI->SetName(L"Slot1BtnUI");
		Slot7BtnUI->SetScale(Vec2(28.f, 29.f));
		Slot7BtnUI->SetPos(Vec2(100.f, 99.f));

		// 아이템 Slot 8 UI
		CBtnUI* Slot8BtnUI = new CBtnUI(BUTTON_TEX::NONE);
		Slot8BtnUI->SetName(L"Slot1BtnUI");
		Slot8BtnUI->SetScale(Vec2(28.f, 29.f));
		Slot8BtnUI->SetPos(Vec2(142.f, 99.f));

		// 아이템 Slot Exit UI
		CBtnUI* ItemExitBtnUI = new CBtnUI(BUTTON_TEX::EXIT);
		ItemExitBtnUI->SetName(L"ItemExitBtnUI");
		ItemExitBtnUI->SetScale(Vec2(15.f, 15.f));
		ItemExitBtnUI->SetPos(Vec2(175.f, 5.f));

		// 메소 출력 UI
		CUI* pMesoTextUI = new FixedUI(FIXED_TEX::INVENTORY_MESO);
		pMesoTextUI->SetName(L"pMesoTextUI");
		pMesoTextUI->SetScale(Vec2(100.f, 50.f));
		pMesoTextUI->SetPos(Vec2(15.f, 307.f));


		ItemMainUI->AddChild(Slot1BtnUI);
		ItemMainUI->AddChild(Slot2BtnUI);
		ItemMainUI->AddChild(Slot3BtnUI);
		ItemMainUI->AddChild(Slot4BtnUI);
		ItemMainUI->AddChild(Slot5BtnUI);
		ItemMainUI->AddChild(Slot6BtnUI);
		ItemMainUI->AddChild(Slot7BtnUI);
		ItemMainUI->AddChild(Slot8BtnUI);
		ItemMainUI->AddChild(ItemExitBtnUI);
		ItemMainUI->AddChild(pMesoTextUI);
		ItemMainUI->AddChildBtnUI(Slot1BtnUI);
		ItemMainUI->AddChildBtnUI(Slot2BtnUI);
		ItemMainUI->AddChildBtnUI(Slot3BtnUI);
		ItemMainUI->AddChildBtnUI(Slot4BtnUI);
		ItemMainUI->AddChildBtnUI(Slot5BtnUI);
		ItemMainUI->AddChildBtnUI(Slot6BtnUI);
		ItemMainUI->AddChildBtnUI(Slot7BtnUI);
		ItemMainUI->AddChildBtnUI(Slot8BtnUI);
		ItemMainUI->AddChildBtnUI(ItemExitBtnUI);

		ItemMainUI->SetUIOFF(true);


		AddObject(ItemMainUI, GROUP_TYPE::UI);

		//============================
		// 스킬창 UI
		CUI* SkillMainUI = new CPanelUI(PANEL_TEX::SKILL);
		SkillMainUI->SetName(L"skillMainUI");
		SkillMainUI->SetScale(Vec2(174.f, 300.f));
		SkillMainUI->SetPos(Vec2(800.f, 300.f));

		// 스킬1 Slot 1 UI
		CBtnUI* Skill1BtnUI = new CBtnUI(BUTTON_TEX::SKILL1);
		Skill1BtnUI->SetName(L"SKILL1BtnUI");
		Skill1BtnUI->SetScale(Vec2(32.f, 32.f));
		Skill1BtnUI->SetPos(Vec2(11.f, 94.f));

		// 스킬1 버튼 Slot 1 UI
		CBtnUI* Skill1ClickBtnUI = new CBtnUI(BUTTON_TEX::SKILL1CLICK);
		Skill1ClickBtnUI->SetName(L"SKILL1ClickBtnUI");
		Skill1ClickBtnUI->SetScale(Vec2(14.f, 12.f));
		Skill1ClickBtnUI->SetPos(Vec2(133.f, 111.f));

		// 스킬1 text UI
		CUI* Skill1TextUI = new FixedUI(FIXED_TEX::SKILL1_TEXT);
		Skill1TextUI->SetName(L"skill1TextUI");
		Skill1TextUI->SetScale(Vec2(50.f, 30.f));
		Skill1TextUI->SetPos(Vec2(50.f, 96.f));

		// 스킬2 Slot 2 UI
		CBtnUI* Skill2BtnUI = new CBtnUI(BUTTON_TEX::SKILL2);
		Skill2BtnUI->SetName(L"SKILL2BtnUI");
		Skill2BtnUI->SetScale(Vec2(32.f, 32.f));
		Skill2BtnUI->SetPos(Vec2(11.f, 133.f));

		// 스킬2 버튼 Slot 2 UI
		CBtnUI* Skill2ClickBtnUI = new CBtnUI(BUTTON_TEX::SKILL2CLICK);
		Skill2ClickBtnUI->SetName(L"SKILL2ClickBtnUI");
		Skill2ClickBtnUI->SetScale(Vec2(14.f, 12.f));
		Skill2ClickBtnUI->SetPos(Vec2(133.f, 152.f));

		// 스킬2 text UI
		CUI* Skill2TextUI = new FixedUI(FIXED_TEX::SKILL2_TEXT);
		Skill2TextUI->SetName(L"skill2TextUI");
		Skill2TextUI->SetScale(Vec2(80.f, 30.f));
		Skill2TextUI->SetPos(Vec2(50.f, 135.f));

		// 스킬3 Slot 3 UI
		CBtnUI* Skill3BtnUI = new CBtnUI(BUTTON_TEX::SKILL3);
		Skill3BtnUI->SetName(L"SKILL3BtnUI");
		Skill3BtnUI->SetScale(Vec2(32.f, 32.f));
		Skill3BtnUI->SetPos(Vec2(11.f, 172.f));

		// 스킬3 버튼 Slot 3 UI
		CBtnUI* Skill3ClickBtnUI = new CBtnUI(BUTTON_TEX::SKILL3CLICK);
		Skill3ClickBtnUI->SetName(L"SKILL3ClickBtnUI");
		Skill3ClickBtnUI->SetScale(Vec2(14.f, 12.f));
		Skill3ClickBtnUI->SetPos(Vec2(133.f, 193.f));

		// 스킬3 text UI
		CUI* Skill3TextUI = new FixedUI(FIXED_TEX::SKILL3_TEXT);
		Skill3TextUI->SetName(L"skill3TextUI");
		Skill3TextUI->SetScale(Vec2(80.f, 30.f));
		Skill3TextUI->SetPos(Vec2(50.f, 175.f));

		// 스킬4 Slot 4 UI
		CBtnUI* Skill4BtnUI = new CBtnUI(BUTTON_TEX::SKILL4);
		Skill4BtnUI->SetName(L"SKILL4BtnUI");
		Skill4BtnUI->SetScale(Vec2(32.f, 32.f));
		Skill4BtnUI->SetPos(Vec2(11.f, 211.f));

		// 스킬4 버튼 Slot 4 UI
		CBtnUI* Skill4ClickBtnUI = new CBtnUI(BUTTON_TEX::SKILL4CLICK);
		Skill4ClickBtnUI->SetName(L"SKILL4ClickBtnUI");
		Skill4ClickBtnUI->SetScale(Vec2(14.f, 12.f));
		Skill4ClickBtnUI->SetPos(Vec2(133.f, 234.f));

		// 스킬4 text UI
		CUI* Skill4TextUI = new FixedUI(FIXED_TEX::SKILL4_TEXT);
		Skill4TextUI->SetName(L"skill4TextUI");
		Skill4TextUI->SetScale(Vec2(80.f, 30.f));
		Skill4TextUI->SetPos(Vec2(50.f, 215.f));

		// 스킬창 Exit UI
		CBtnUI* SkillExitBtnUI = new CBtnUI(BUTTON_TEX::EXIT);
		SkillExitBtnUI->SetName(L"SkillExitBtnUI");
		SkillExitBtnUI->SetScale(Vec2(15.f, 15.f));
		SkillExitBtnUI->SetPos(Vec2(153.f, 5.f));

		SkillMainUI->AddChild(Skill1BtnUI);
		SkillMainUI->AddChild(Skill1ClickBtnUI);
		SkillMainUI->AddChild(Skill1TextUI);
		SkillMainUI->AddChild(Skill2BtnUI);
		SkillMainUI->AddChild(Skill2ClickBtnUI);
		SkillMainUI->AddChild(Skill2TextUI);

		SkillMainUI->AddChild(Skill3BtnUI);
		SkillMainUI->AddChild(Skill3ClickBtnUI);
		SkillMainUI->AddChild(Skill3TextUI);

		SkillMainUI->AddChild(Skill4BtnUI);
		SkillMainUI->AddChild(Skill4ClickBtnUI);
		SkillMainUI->AddChild(Skill4TextUI);

		SkillMainUI->AddChild(SkillExitBtnUI);
		SkillMainUI->AddChildBtnUI(Skill1BtnUI);
		SkillMainUI->AddChildBtnUI(Skill1ClickBtnUI);
		SkillMainUI->AddChildBtnUI(Skill2BtnUI);
		SkillMainUI->AddChildBtnUI(Skill2ClickBtnUI);
		SkillMainUI->AddChildBtnUI(Skill3BtnUI);
		SkillMainUI->AddChildBtnUI(Skill3ClickBtnUI);
		SkillMainUI->AddChildBtnUI(Skill4BtnUI);
		SkillMainUI->AddChildBtnUI(Skill4ClickBtnUI);
		SkillMainUI->AddChildBtnUI(SkillExitBtnUI);


		SkillMainUI->SetUIOFF(true);

		AddObject(SkillMainUI, GROUP_TYPE::UI);

		//===========================================
		// Quest UI
		CUI* QuestMainUI = new CPanelUI(PANEL_TEX::QUEST);
		QuestMainUI->SetName(L"questMainUI");
		QuestMainUI->SetScale(Vec2(200.f, 100.f));
		QuestMainUI->SetPos(Vec2(0.f, 200.f));

		CUI* PquestTextUI = new QuestTextUI;
		PquestTextUI->SetName(L"questTextUI");
		PquestTextUI->SetScale(Vec2(150.f, 100.f));
		PquestTextUI->SetPos(Vec2(20.f, 20.f));

		QuestMainUI->AddChild(PquestTextUI);

		AddObject(QuestMainUI, GROUP_TYPE::UI);

		//=====================================

		// 강화 UI(최상위 부모) STEP1
		CUI* MainEnforceStep1UI = new CPanelUI(PANEL_TEX::ENFORCESTEP1);
		MainEnforceStep1UI->SetName(L"MainEnforceStep1UI");
		MainEnforceStep1UI->SetScale(Vec2(332.f, 260.f));
		MainEnforceStep1UI->SetPos(Vec2(400.f, 200.f));

		// 강화  UI STEP1 버튼 자식 UI(텍스쳐 바뀔지 확인하는 방식)
		CBtnUI* ForceStep1BtnUI = new CBtnUI(BUTTON_TEX::NONE);
		ForceStep1BtnUI->SetName(L"ForceStep1BtnUI");
		ForceStep1BtnUI->SetScale(Vec2(100.f, 100.f));
		ForceStep1BtnUI->SetPos(Vec2(115.f, 95.f));

		MainEnforceStep1UI->AddChild(ForceStep1BtnUI);
		MainEnforceStep1UI->AddChildBtnUI(ForceStep1BtnUI);

		MainEnforceStep1UI->SetUIOFF(true);

		AddObject(MainEnforceStep1UI, GROUP_TYPE::UI);

		//==============================================
		// 강화 UI(최상위 부모) STEP2
		// 자식 : 확인 버튼 하나 / 취소 버튼 하나 / 로고 띄우는 

		CUI* MainEnforceStep2UI = new CPanelUI(PANEL_TEX::ENFORCESTEP2);
		MainEnforceStep2UI->SetName(L"MainEnforceStep2UI");
		MainEnforceStep2UI->SetScale(Vec2(344.f, 298.f));
		MainEnforceStep2UI->SetPos(Vec2(400.f, 200.f));

		CBtnUI* StepOkBtnUI = new CBtnUI(BUTTON_TEX::NONE);
		StepOkBtnUI->SetName(L"stepOkBtnUI");
		StepOkBtnUI->SetScale(Vec2(80.f, 25.f));
		StepOkBtnUI->SetPos(Vec2(80.f, 257.f));

		CBtnUI* StepCancelBtnUI = new CBtnUI(BUTTON_TEX::NONE);
		StepCancelBtnUI->SetName(L"stepCancelBtnUI");
		StepCancelBtnUI->SetScale(Vec2(80.f, 25.f));
		StepCancelBtnUI->SetPos(Vec2(180.f, 257.f));

		FIexedTextUI* Step2ForceNumUI = new FIexedTextUI();
		Step2ForceNumUI->SetName(L"step2ForceNumUI");
		Step2ForceNumUI->SetScale(Vec2(50.f, 20.f));
		Step2ForceNumUI->SetPos(Vec2(35.f, 95.f));

		FIexedTextUI* Step2ForceStatusUI = new FIexedTextUI();
		Step2ForceStatusUI->SetName(L"step2ForceStatusUI");
		Step2ForceStatusUI->SetScale(Vec2(200.f,100.f));
		Step2ForceStatusUI->SetPos(Vec2(150.f, 95.f));
		
		MainEnforceStep2UI->AddChild(Step2ForceNumUI);
		MainEnforceStep2UI->AddChild(StepOkBtnUI);
		MainEnforceStep2UI->AddChild(StepCancelBtnUI);
		MainEnforceStep2UI->AddChild(Step2ForceStatusUI);
		MainEnforceStep2UI->AddChildBtnUI(StepOkBtnUI);
		MainEnforceStep2UI->AddChildBtnUI(StepCancelBtnUI);

		MainEnforceStep2UI->SetUIOFF(true);

		AddObject(MainEnforceStep2UI, GROUP_TYPE::UI);
		//==========================================
		// 강화 UI(최상위 부모) STEP3

		CUI* MainEnforceStep3UI = new CPanelUI(PANEL_TEX::ENFORCESTEP3);
		MainEnforceStep3UI->SetName(L"MainEnforceStep3UI");
		MainEnforceStep3UI->SetScale(Vec2(178.f, 150.f));
		MainEnforceStep3UI->SetPos(Vec2(-1000.f, -1000.f));

		CUI* MoveStarUI = new FixedUI(FIXED_TEX::STAR);
		MoveStarUI->SetName(L"moveStarUI");
		MoveStarUI->SetScale(Vec2(25.f, 24.f));
		MoveStarUI->SetPos(Vec2(0.f, 120.f));

		MainEnforceStep3UI->AddChild(MoveStarUI);

		MainEnforceStep3UI->SetUIOFF(true);

		AddObject(MainEnforceStep3UI, GROUP_TYPE::UI);

		//===========================================
		// 강화 SUCCEESS(최상위 부모) STEP4
		CUI* MainEnforcSuccesseStep4UI = new AnimationUI(ANIMUI_TYPE::ENFORCESUCCESS);
		MainEnforcSuccesseStep4UI->SetName(L"MainSuccessStep4UI");
		MainEnforcSuccesseStep4UI->SetScale(Vec2(279.f, 151.f));
		MainEnforcSuccesseStep4UI->SetPos(Vec2(400.f, 200.f));

		MainEnforcSuccesseStep4UI->SetUIOFF(true);

		AddObject(MainEnforcSuccesseStep4UI, GROUP_TYPE::UI);

		//===========================================
		// 강화 SUCCEESS(최상위 부모) STEP4
		CUI* MainEnforceFailStep4UI = new AnimationUI(ANIMUI_TYPE::ENFORCEFAIL);
		MainEnforceFailStep4UI->SetName(L"MainFailStep4UI");
		MainEnforceFailStep4UI->SetScale(Vec2(279.f, 151.f));
		MainEnforceFailStep4UI->SetPos(Vec2(400.f, 200.f));

		MainEnforceFailStep4UI->SetUIOFF(true);

		AddObject(MainEnforceFailStep4UI, GROUP_TYPE::UI);
		//==========================================
		// Dead 시 UI 포커싱 및 OFF 취소하기

		// 강화 UI(최상위 부모) STEP1
		CUI* MainDeadUI = new CPanelUI(PANEL_TEX::DEAD);
		MainDeadUI->SetName(L"MainDeadUI");
		MainDeadUI->SetScale(Vec2(416.f, 180.f));
		MainDeadUI->SetPos(Vec2(300.f, 200.f));

		// 강화  UI STEP1 버튼 자식 UI(텍스쳐 바뀔지 확인하는 방식)
		CBtnUI* DeadBtnUI = new CBtnUI(BUTTON_TEX::NONE);
		DeadBtnUI->SetName(L"DeadBtnUI");
		DeadBtnUI->SetScale(Vec2(80.f, 35.f));
		DeadBtnUI->SetPos(Vec2(320.f, 130.f));

		MainDeadUI->AddChild(DeadBtnUI);
		MainDeadUI->AddChildBtnUI(DeadBtnUI);

		MainDeadUI->SetUIOFF(true);

		AddObject(MainDeadUI, GROUP_TYPE::UI);
		//==============================================
		// 미니맵 UI 세팅하기

		CUI* MiniField1UI = new MiniMapUI(MINIUI_TEX::FIELD1);
		MiniField1UI->SetName(L"MiniMapField1UI");
		MiniField1UI->SetScale(Vec2(108.f, 75.f));
		MiniField1UI->SetPos(Vec2(0.f, 0.f));

		CUI* MiniPlayerUI = new MiniMapUI(MINIUI_TEX::CHILD);
		MiniPlayerUI->SetName(L"MiniplayerUI");
		MiniPlayerUI->SetScale(Vec2(5.f, 5.f));
		MiniPlayerUI->SetPos(Vec2(0.f, 0.f));

		MiniField1UI->AddChild(MiniPlayerUI);

		AddObject(MiniField1UI, GROUP_TYPE::MINIMAPUI);

		//==========================================
		// 마우스 커서 UI
		CObject* pMouseUI = new CMouseUI;
		pMouseUI->SetName(L"MouseUI");
		pMouseUI->SetScale(Vec2(26.f, 30.f));

		AddObject(pMouseUI, GROUP_TYPE::MOUSEUI);

		//==========================================

		// 아이템 획득 TextUI 틀 



		//================================================

		// 특정키 눌릴떄 포커싱 해볼려고
		m_pSkillUI = SkillMainUI;
		m_pEquipUI = EquipMainUI;
		m_pItemUI = ItemMainUI;
		m_EnforceUI = MainEnforceStep1UI;

		// 타일 로딩
		//LoadTile(L"Tile\\Start.tile");

		// 충돌 그룹만 넣어주고 나머지 로직 처리는 collisionMgr에게 넘겨버림 
		// Player 그룹과 Monster 그룹 간의 충돌체크
		CCollisionMgr::GetInst()->CheckGroup(GROUP_TYPE::PLAYER, GROUP_TYPE::MONSTER);
		CCollisionMgr::GetInst()->CheckGroup(GROUP_TYPE::MONSTER, GROUP_TYPE::SKILL);
		CCollisionMgr::GetInst()->CheckGroup(GROUP_TYPE::MONSTER, GROUP_TYPE::LEVELSKILL);
		CCollisionMgr::GetInst()->CheckGroup(GROUP_TYPE::MONSTER, GROUP_TYPE::WIDESKILL);
		CCollisionMgr::GetInst()->CheckGroup(GROUP_TYPE::PLAYER, GROUP_TYPE::GROUND);
		CCollisionMgr::GetInst()->CheckGroup(GROUP_TYPE::PLAYER, GROUP_TYPE::PORTAL);
		CCollisionMgr::GetInst()->CheckGroup(GROUP_TYPE::MONSTER, GROUP_TYPE::GROUND);
		CCollisionMgr::GetInst()->CheckGroup(GROUP_TYPE::PET, GROUP_TYPE::GROUND);
		CCollisionMgr::GetInst()->CheckGroup(GROUP_TYPE::PLAYER, GROUP_TYPE::LADDER);
		CCollisionMgr::GetInst()->CheckGroup(GROUP_TYPE::ITEM, GROUP_TYPE::GROUND);
		CCollisionMgr::GetInst()->CheckGroup(GROUP_TYPE::ITEM, GROUP_TYPE::PET);
		//CCollisionMgr::GetInst()->CheckGroup(GROUP_TYPE::GROUND, GROUP_TYPE::DAMAGE_EFFECT);
		// Camera Look 지정
		// 해상도 절반 위치	
		//CCamera::GetInst()->SetLookAt(Vec2(1150.f,700.f));

		// Camera 효과 지정
		// CCamera::GetInst()->subFadeOut(2.f);
		// CCamera::GetInst()->subFadeIn(2.f);
	}
	else
	{

		// backGround 추가
		CObject* pBack = new BackGround;
		AddObject(pBack, GROUP_TYPE::BACKGROUND);

		// map 추가
		CObject* pMap = new Map(MAP_TYPE::HUNT, Vec2(1620.f, 1118.f));
		AddObject(pMap, GROUP_TYPE::MAP);

		// Portal 추가
		CObject* pPortal = new Portal;
		pPortal->SetName(L"Protalfirst");
		pPortal->SetScale(Vec2(89.f, 257.f));
		pPortal->SetPos(Vec2(110.f, 790.f));
		AddObject(pPortal, GROUP_TYPE::PORTAL);

		// Player 추가
		CObject* pObj = GetGroupObject(GROUP_TYPE::PLAYER).front();
		RegisterPlayer(pObj);

		// 플레이어 생성할때 카메라를 플레이어에게 부착
		CCamera::GetInst()->SetTarget(pObj);
		// 맵크기에따라 맵 밖은 보여주면 안됨
		CCamera::GetInst()->SetMapMin(650.f);
		CCamera::GetInst()->SetMapMax(1020.f);


		//// 몬스터 배치
		CMonster* pMon = CMonFactory::CreateMonster(MON_TYPE::NORMAL, Vec2(1200.f, 700.f), -1);
		pMon->SetName(L"Monster");
		AddObject(pMon, GROUP_TYPE::MONSTER);

		MonsterArray[0].initialPos = Vec2(1200.f, 700.f);
		MonsterArray[0].monsterAddress = pMon;

		CMonster* pMon2 = CMonFactory::CreateMonster(MON_TYPE::NORMAL, Vec2(1000.f, 700.f), -1);
		pMon2->SetName(L"Monster");
		AddObject(pMon2, GROUP_TYPE::MONSTER);

		MonsterArray[1].initialPos = Vec2(1000.f, 700.f);
		MonsterArray[1].monsterAddress = pMon2;

		CMonster* pMon3 = CMonFactory::CreateMonster(MON_TYPE::NORMAL, Vec2(800.f, 700.f), -1);
		pMon3->SetName(L"Monster");
		AddObject(pMon3, GROUP_TYPE::MONSTER);

		MonsterArray[2].initialPos = Vec2(800.f, 700.f);
		MonsterArray[2].monsterAddress = pMon3;

		CMonster* pMon4 = CMonFactory::CreateMonster(MON_TYPE::NORMAL, Vec2(600.f, 700.f), -1);
		pMon4->SetName(L"Monster");
		AddObject(pMon4, GROUP_TYPE::MONSTER);

		MonsterArray[3].initialPos = Vec2(600.f, 700.f);
		MonsterArray[3].monsterAddress = pMon4;

		CMonster* pMon5 = CMonFactory::CreateMonster(MON_TYPE::NORMAL, Vec2(400.f, 700.f), -1);
		pMon5->SetName(L"Monster");
		AddObject(pMon5, GROUP_TYPE::MONSTER);

		MonsterArray[4].initialPos = Vec2(400.f, 700.f);
		MonsterArray[4].monsterAddress = pMon5;

		//------------

		CMonster* pMon6 = CMonFactory::CreateMonster(MON_TYPE::NORMAL, Vec2(1100.f, 500.f), -1);
		pMon6->SetName(L"Monster");
		AddObject(pMon6, GROUP_TYPE::MONSTER);

		MonsterArray[5].initialPos = Vec2(1100.f, 640.f);
		MonsterArray[5].monsterAddress = pMon6;

		CMonster* pMon7 = CMonFactory::CreateMonster(MON_TYPE::NORMAL, Vec2(1000.f, 500.f), -1);
		pMon7->SetName(L"Monster");
		AddObject(pMon7, GROUP_TYPE::MONSTER);

		MonsterArray[6].initialPos = Vec2(1000.f, 640.f);
		MonsterArray[6].monsterAddress = pMon7;

		CMonster* pMon8 = CMonFactory::CreateMonster(MON_TYPE::NORMAL, Vec2(800.f, 500.f), -1);
		pMon8->SetName(L"Monster");
		AddObject(pMon8, GROUP_TYPE::MONSTER);

		MonsterArray[7].initialPos = Vec2(800.f, 640.f);
		MonsterArray[7].monsterAddress = pMon8;



		CMonster* pMon9 = CMonFactory::CreateMonster(MON_TYPE::NORMAL, Vec2(600.f, 500.f), -1);
		pMon9->SetName(L"Monster");
		AddObject(pMon9, GROUP_TYPE::MONSTER);

		MonsterArray[8].initialPos = Vec2(600.f, 640.f);
		MonsterArray[8].monsterAddress = pMon9;

		//-------------

		CMonster* pMon10 = CMonFactory::CreateMonster(MON_TYPE::NORMAL, Vec2(1100.f, 200.f), -1);
		pMon10->SetName(L"Monster");
		AddObject(pMon10, GROUP_TYPE::MONSTER);

		MonsterArray[9].initialPos = Vec2(1100.f, 395.f);
		MonsterArray[9].monsterAddress = pMon10;

		CMonster* pMon11 = CMonFactory::CreateMonster(MON_TYPE::NORMAL, Vec2(1000.f, 200.f), -1);
		pMon11->SetName(L"Monster");
		AddObject(pMon11, GROUP_TYPE::MONSTER);

		MonsterArray[10].initialPos = Vec2(1000.f, 395.f);
		MonsterArray[10].monsterAddress = pMon11;


		CMonster* pMon12 = CMonFactory::CreateMonster(MON_TYPE::NORMAL, Vec2(900.f, 200.f), -1);
		pMon12->SetName(L"Monster");
		AddObject(pMon12, GROUP_TYPE::MONSTER);

		MonsterArray[11].initialPos = Vec2(800.f, 395.f);
		MonsterArray[11].monsterAddress = pMon12;


		CMonster* pMon13 = CMonFactory::CreateMonster(MON_TYPE::NORMAL, Vec2(800.f, 200.f), -1);
		pMon5->SetName(L"Monster");
		AddObject(pMon13, GROUP_TYPE::MONSTER);

		MonsterArray[12].initialPos = Vec2(600.f, 395.f);
		MonsterArray[12].monsterAddress = pMon13;


		// 땅 물체 배치
		CObject* pGroundOne1 = new CGround;
		pGroundOne1->SetName(L"GroundOne1");
		pGroundOne1->SetPos(Vec2(800.f, 948.f));
		pGroundOne1->SetScale(Vec2(1691.f, 80.f));

		AddObject(pGroundOne1, GROUP_TYPE::GROUND);

		CObject* pGroundSecond1 = new CGround;
		pGroundSecond1->SetName(L"GroundSecond1");
		pGroundSecond1->SetPos(Vec2(924.f, 698.f));
		pGroundSecond1->SetScale(Vec2(1068.f, 53.f));

		AddObject(pGroundSecond1, GROUP_TYPE::GROUND);


		CObject* pGroundSecond2 = new CGround;
		pGroundSecond2->SetName(L"GroundSecond2");
		pGroundSecond2->SetPos(Vec2(271.f, 643.f));
		pGroundSecond2->SetScale(Vec2(229.f, 74.f));

		AddObject(pGroundSecond2, GROUP_TYPE::GROUND);

		CObject* pGroundThird1 = new CGround;
		pGroundThird1->SetName(L"Ground");
		pGroundThird1->SetPos(Vec2(921.f, 453.f));
		pGroundThird1->SetScale(Vec2(1068.f, 53.f));

		AddObject(pGroundThird1, GROUP_TYPE::GROUND);

		CObject* pGroundThird2 = new CGround;
		pGroundThird2->SetName(L"Ground");
		pGroundThird2->SetPos(Vec2(271.f, 407.f));
		pGroundThird2->SetScale(Vec2(229.f, 74.f));

		AddObject(pGroundThird2, GROUP_TYPE::GROUND);

		CObject* pGroundRightWall = new CGround;
		pGroundRightWall->SetName(L"GroundOne1");
		pGroundRightWall->SetPos(Vec2(1726.f, 386.f));
		pGroundRightWall->SetScale(Vec2(209.f, 1469.f));

		AddObject(pGroundRightWall, GROUP_TYPE::GROUND);

		// 사다리 배치

		CObject* pLadder1 = new CLadder;
		pLadder1->SetName(L"Ladder1");
		pLadder1->SetPos(Vec2(278.f, 731.f));
		pLadder1->SetScale(Vec2(5.f, 250.f));

		AddObject(pLadder1, GROUP_TYPE::GROUND);


		CObject* pLadder2 = new CLadder;
		pLadder2->SetName(L"Ladder1");
		pLadder2->SetPos(Vec2(203.f, 445.f));
		pLadder2->SetScale(Vec2(5.f, 150.f));

		AddObject(pLadder2, GROUP_TYPE::LADDER);


		//==============================================
		// 미니맵 UI 세팅하기

		CUI* MiniField1UI = new MiniMapUI(MINIUI_TEX::FIELD1);
		MiniField1UI->SetName(L"MiniMapField1UI");
		MiniField1UI->SetScale(Vec2(108.f, 75.f));
		MiniField1UI->SetPos(Vec2(0.f, 0.f));

		CUI* MiniPlayerUI = new MiniMapUI(MINIUI_TEX::CHILD);
		MiniPlayerUI->SetName(L"MiniplayerUI");
		MiniPlayerUI->SetScale(Vec2(5.f, 5.f));
		MiniPlayerUI->SetPos(Vec2(0.f, 0.f));

		MiniField1UI->AddChild(MiniPlayerUI);

		AddObject(MiniField1UI, GROUP_TYPE::MINIMAPUI);


		//===========================================

		// 마우스 커서 UI
		CObject* pMouseUI = new CMouseUI;
		pMouseUI->SetName(L"MouseUI");
		pMouseUI->SetScale(Vec2(26.f, 30.f));



		AddObject(pMouseUI, GROUP_TYPE::MOUSEUI);

		//==========================================

		// 아이템 획득 TextUI 틀 


		//================================================

		//// 특정키 눌릴떄 포커싱 해볼려고
		//m_pSkillUI = SkillMainUI;
		//m_pEquipUI = EquipMainUI;
		//m_pItemUI = ItemMainUI;
		//m_EnforceUI = MainDeadUI;
	
		CCollisionMgr::GetInst()->CheckGroup(GROUP_TYPE::MONSTER, GROUP_TYPE::SKILL);
		CCollisionMgr::GetInst()->CheckGroup(GROUP_TYPE::MONSTER, GROUP_TYPE::LEVELSKILL);
		CCollisionMgr::GetInst()->CheckGroup(GROUP_TYPE::MONSTER, GROUP_TYPE::WIDESKILL);
		CCollisionMgr::GetInst()->CheckGroup(GROUP_TYPE::PLAYER, GROUP_TYPE::GROUND);
		CCollisionMgr::GetInst()->CheckGroup(GROUP_TYPE::PLAYER, GROUP_TYPE::PORTAL);
		CCollisionMgr::GetInst()->CheckGroup(GROUP_TYPE::MONSTER, GROUP_TYPE::GROUND);
		CCollisionMgr::GetInst()->CheckGroup(GROUP_TYPE::PET, GROUP_TYPE::GROUND);
		CCollisionMgr::GetInst()->CheckGroup(GROUP_TYPE::PLAYER, GROUP_TYPE::LADDER);
		CCollisionMgr::GetInst()->CheckGroup(GROUP_TYPE::ITEM, GROUP_TYPE::GROUND);
		CCollisionMgr::GetInst()->CheckGroup(GROUP_TYPE::ITEM, GROUP_TYPE::PET);


		// Camera 효과 지정
		// CCamera::GetInst()->subFadeOut(2.f);
		// CCamera::GetInst()->subFadeIn(2.f);
		 //Camera 효과 지정
		//CCamera::GetInst()->FadeOut(0.01f);
		CCamera::GetInst()->FadeIn(7.f);


		// 플레이어 생성할때 카메라를 플레이어에게 부착
		CCamera::GetInst()->SetCurLookAt(pObj->GetPos());

		

	}
	

	// 씬 update하기전 오브젝트 초기값들 세팅
	start();
}



void CScene_Start::Exit()
{
	// 씬 내용물 다 삭제
	MyDeleteAll();

	// 충돌 그룹 해제
	CCollisionMgr::GetInst()->Reset();
}

void CScene_Start::CreateForce()
{
	m_vForcePos = CCamera::GetInst()->GetRealPos(MOUSE_POS);


}