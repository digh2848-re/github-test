#include "pch.h"
#include "CPanelUI.h"

#include "CKeyMgr.h"

#include "CTexture.h"
#include "CResMgr.h"
#include "CBtnUI.h"
#include "CSceneMgr.h"
#include "CPlayer.h"
#include "CUIMgr.h"
#include "FIexedTextUI.h"
#include "CSound.h"

CPanelUI::CPanelUI()
	: CUI(false) // 카메라 영향 안받음
	, FirstMouseDown(true)
{
	m_vDragStart = Vec2(0.f, 0.f);
}

CPanelUI::CPanelUI(PANEL_TEX _index)
	: CUI(false) // 카메라 영향 안받음
	, FirstMouseDown(true)
{
	texArr[0] = CResMgr::GetInst()->LoadTexture(L"equipmainUI", L"texture\\PanelUI\\EquipMainUI.bmp");
	texArr[1] = CResMgr::GetInst()->LoadTexture(L"itemMainUI", L"texture\\PanelUI\\ItemMainUI.bmp");
	texArr[2] = CResMgr::GetInst()->LoadTexture(L"skillMainUI", L"texture\\PanelUI\\SkillMainUI.bmp");
	texArr[3] = CResMgr::GetInst()->LoadTexture(L"questMainUI", L"texture\\PanelUI\\QuestUI.bmp");
	texArr[4] = CResMgr::GetInst()->LoadTexture(L"forceMainStep1UI", L"texture\\ForceUI\\Step1.bmp");
	texArr[5] = CResMgr::GetInst()->LoadTexture(L"forceMainStep2UI", L"texture\\ForceUI\\Step2.bmp");
	texArr[6] = CResMgr::GetInst()->LoadTexture(L"forceMainStep3UI", L"texture\\ForceUI\\Step3.bmp");
	texArr[7] = CResMgr::GetInst()->LoadTexture(L"forceSUCCESSStep4UI", L"texture\\ForceUI\\success.bmp");
	texArr[8] = CResMgr::GetInst()->LoadTexture(L"forceFAILStep4UI", L"texture\\ForceUI\\fail.bmp");
	texArr[9] = CResMgr::GetInst()->LoadTexture(L"MainDeadUI", L"texture\\PanelUI\\Dead.bmp");

	m_index = _index;
	m_vDragStart = Vec2(0.f, 0.f);


	m_SuccessSound = CResMgr::GetInst()->FindSound(L"SUCCESS_SOUND");
	m_FailSound = CResMgr::GetInst()->FindSound(L"FAIL_SOUND");
}


CPanelUI::~CPanelUI()
{

}

void CPanelUI::start()
{
	Vec2 vPos = GetPos();
	vPos = CCamera::GetInst()->GetRenderPos(vPos);
	m_vDragStart = vPos;

	CUI::start();
}


void CPanelUI::update()
{
	if (IsOFF)
	{
		return;
	}

	// 자신이 장비창 UI이면
	if (GetName().compare(L"equipmainUI") == 0)
	{
		// 자식중에 버튼 UI 찾으면서
		vector<CUI*>& veccheck = GetChildBtnUI();
		vector<CUI*>::iterator it = veccheck.begin();

		bool IsWeapon = false;
		bool IsCloth = false;

		// 전체 순회하고 나서
		for (; it != veccheck.end(); ++it)
		{
			CBtnUI* temp = dynamic_cast<CBtnUI*>(*it);
			// 무기 텍스쳐 버튼 있음?
			if (temp->GetTexindex() == BUTTON_TEX::WEAPON)
			{
				IsWeapon = true;
			}// 옷 텍스쳐 버튼 있음?
			else if (temp->GetTexindex() == BUTTON_TEX::CLOTH)
			{
				IsCloth = true;
			}

		}

		CPlayer* player = (CPlayer*)(CSceneMgr::GetInst()->GetCurScene()->GetPlayer());

		// 1. 아무것도 없으면 - NOWEAR 변경
		if (!IsWeapon && !IsCloth)
		{
			player->SetWearState(PlayerWearState::NO_WEAR);
		} // 2. 무기만 있을경우- WEAPON으로 변경
		else if (IsWeapon && !IsCloth)
		{
			player->SetWearState(PlayerWearState::WEAPON_WEAR);
		} // 둘다 있을 경우 - all로 변경
		else if (IsWeapon && IsCloth)
		{
			player->SetWearState(PlayerWearState::ALL_WEAR);
		}
		// 옷만있을경우 처리안할꺼임

	}

	// 자신이 강화step1 UI이면
	// 일단 야매로 마우스 UP버튼 누를시 Enforcestep1이면 이벤트 발생
	if (m_index == PANEL_TEX::ENFORCESTEP1)
	{
		vector<CUI*> Step1ChildUI = GetChildBtnUI();

		if (BUTTON_TEX::FORCEITEM == ((CBtnUI*)Step1ChildUI.front())->GetTexindex())
		{
			// 자식 버튼 UI 다시 NONE으로 초기화 시켜주기
			((CBtnUI*)Step1ChildUI.front())->SetTex_index(BUTTON_TEX::NONE);

			// 1.  자기자신 꺼지고
			SetUIOFF(true);
			
			// 2. STEP2 UI 강제 포커싱하기
			
			// 2-1. 전체 UI그룹가지고와 FORCE STEP2 UI 찾아서 
			vector<CObject*> UIvec = CSceneMgr::GetInst()->GetCurScene()->GetUIGroup();
			vector<CObject*>::iterator it = UIvec.begin();

			for (; it != UIvec.end(); ++it)
			{
				// step2찾으면
				if ((*it)->GetName() == L"MainEnforceStep2UI")
				{
					((CUI*)(*it))->SetUIOFF(false);
					CUIMgr::GetInst()->SetFocusedUI((CUI*)(*it));
					break;
				}
			}


		}

	}

	CUI::update();

}

void CPanelUI::render(HDC _dc)
{
	if (IsOFF)
		return;

	// UI도 Tile과 비슷하게 좌상단 위치를 좌표로 할 것임
	Vec2 vPos = GetFinalPos();
	Vec2 vScale = GetScale();
	
	

	// 카메라 영향 받으면
	if (GetCamAffected())
	{
		// 렌더링 좌표로 받아와야한다.
		vPos = CCamera::GetInst()->GetRenderPos(vPos);
	}

	TransparentBlt(_dc
		// 실제 좌상단 위치와 크기
		, (int)vPos.x
		, (int)vPos.y
		, vScale.x
		, vScale.y
		// 텍스쳐 정보
		, texArr[(UINT)m_index]->GetDC()
		// bmp 파일 내에서 자를 좌상단
		, (int)0
		, (int)0
		, vScale.x
		, vScale.y
		, RGB(255, 0, 255));
	
	//BitBlt(_dc
	//	, (int)vPos.x
	//	, (int)vPos.y
	//	, vScale.x
	//	, vScale.y
	//	, texArr[m_index]->GetDC()
	//	,
	//	0, 0, SRCCOPY);

	CUI::render(_dc);
}

void CPanelUI::MouseOn()
{
	if (IsOFF)
		return;

	// Drag 중
	// 마우스 누른순간
	if (IsLbtnDown())
	{
		if (FirstMouseDown)
		{
			m_vDragStart = MOUSE_POS;
			FirstMouseDown = false;
		}
			

		// 차이값 계산
		Vec2 vDiff = MOUSE_POS - m_vDragStart;

		Vec2 vCurPos = GetPos();
		// 차이값 더해줌
		vCurPos += vDiff;

		//if (vCurPos.x + GetScale().x < 1024.f || vCurPos.x >= 0 || vCurPos.y >=0 || vCurPos.y + GetScale().y < 768.f)
		//{
		//	SetPos(vCurPos);
		//}

		SetPos(vCurPos);

		// 그리고 다시 시작위치 변한 값으로 세팅
		m_vDragStart = MOUSE_POS;
	}
}

void CPanelUI::MouseLbtnDown()
{
	if (IsOFF)
		return;

	// 마우스 누른순간 위치값
	m_vDragStart = MOUSE_POS;



}


void CPanelUI::MouseLbtnUp()
{
	if (IsOFF)
		return;

}

void CPanelUI::MouseLbtnClicked()
{
	

	// 강화 step3UI 이면
	if (GetName() == L"MainEnforceStep3UI")
	{	
		

		srand((UINT)time(nullptr));
		int randnum = (rand() % 100) + 1;


		// 일단 성공만 부르자
		vector<CObject*>& groupvec = (CSceneMgr::GetInst()->GetCurScene())->GetUIGroup();
		vector<CObject*>::iterator it2 = groupvec.begin();
		CUI* step2UI = nullptr ; 
		FIexedTextUI* step2childnumUI= nullptr ;
		FIexedTextUI* step2childstatusUI = nullptr ;

		for (; it2 != groupvec.end(); ++it2)
		{
			if ((*it2)->GetName() == L"MainEnforceStep2UI")
			{
				step2UI = (CUI*)(*it2);

				// 일단 반복자 이중순회 쓰기 싫어서 하드코딩으로 박아둠
				step2childnumUI = (FIexedTextUI*)(step2UI->GetChildUI().front());
				step2childstatusUI = (FIexedTextUI*)(step2UI->GetChildUI().back());
			}
		}


		// 예외처리
		if (step2UI == nullptr || step2childnumUI == nullptr || step2childstatusUI == nullptr)
		{
			assert(true);
		}

		vector<CObject*>::iterator it = groupvec.begin();



		for (; it != groupvec.end(); ++it)
		{
			

			if (randnum <= step2childstatusUI->GetSuccessPercent())
			{
				// 성공확률이 되면
				if ((*it)->GetName() == L"MainSuccessStep4UI")
				{
					Vec2 Pos = GetPos();
					(*it)->SetPos(Vec2(Pos.x - 40.f, Pos.y));

					((CUI*)(*it))->SetUIOFF(false);
					CUIMgr::GetInst()->SetFocusedUI((CUI*)(*it));
					SetUIOFF(true);

					step2childnumUI->Addforcenum();
					step2childstatusUI->Addforcenum();

					m_SuccessSound->Play();
					m_SuccessSound->SetVolume(100.f);
					break;
				}
			}
			else
			{
				// 실패확률이 되면
				if ((*it)->GetName() == L"MainFailStep4UI")
				{
					Vec2 Pos = GetPos();
					(*it)->SetPos(Vec2(Pos.x - 40.f, Pos.y));

					((CUI*)(*it))->SetUIOFF(false);
					CUIMgr::GetInst()->SetFocusedUI((CUI*)(*it));
					SetUIOFF(true);

					step2childnumUI->Subforcenum();
					step2childstatusUI->Subforcenum();

					m_FailSound->Play();
					m_FailSound->SetVolume(100.f);
					break;
				}
			}
			
		}
	}
}

