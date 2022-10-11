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
	: CUI(false) // ī�޶� ���� �ȹ���
	, FirstMouseDown(true)
{
	m_vDragStart = Vec2(0.f, 0.f);
}

CPanelUI::CPanelUI(PANEL_TEX _index)
	: CUI(false) // ī�޶� ���� �ȹ���
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

	// �ڽ��� ���â UI�̸�
	if (GetName().compare(L"equipmainUI") == 0)
	{
		// �ڽ��߿� ��ư UI ã���鼭
		vector<CUI*>& veccheck = GetChildBtnUI();
		vector<CUI*>::iterator it = veccheck.begin();

		bool IsWeapon = false;
		bool IsCloth = false;

		// ��ü ��ȸ�ϰ� ����
		for (; it != veccheck.end(); ++it)
		{
			CBtnUI* temp = dynamic_cast<CBtnUI*>(*it);
			// ���� �ؽ��� ��ư ����?
			if (temp->GetTexindex() == BUTTON_TEX::WEAPON)
			{
				IsWeapon = true;
			}// �� �ؽ��� ��ư ����?
			else if (temp->GetTexindex() == BUTTON_TEX::CLOTH)
			{
				IsCloth = true;
			}

		}

		CPlayer* player = (CPlayer*)(CSceneMgr::GetInst()->GetCurScene()->GetPlayer());

		// 1. �ƹ��͵� ������ - NOWEAR ����
		if (!IsWeapon && !IsCloth)
		{
			player->SetWearState(PlayerWearState::NO_WEAR);
		} // 2. ���⸸ �������- WEAPON���� ����
		else if (IsWeapon && !IsCloth)
		{
			player->SetWearState(PlayerWearState::WEAPON_WEAR);
		} // �Ѵ� ���� ��� - all�� ����
		else if (IsWeapon && IsCloth)
		{
			player->SetWearState(PlayerWearState::ALL_WEAR);
		}
		// �ʸ�������� ó�����Ҳ���

	}

	// �ڽ��� ��ȭstep1 UI�̸�
	// �ϴ� �߸ŷ� ���콺 UP��ư ������ Enforcestep1�̸� �̺�Ʈ �߻�
	if (m_index == PANEL_TEX::ENFORCESTEP1)
	{
		vector<CUI*> Step1ChildUI = GetChildBtnUI();

		if (BUTTON_TEX::FORCEITEM == ((CBtnUI*)Step1ChildUI.front())->GetTexindex())
		{
			// �ڽ� ��ư UI �ٽ� NONE���� �ʱ�ȭ �����ֱ�
			((CBtnUI*)Step1ChildUI.front())->SetTex_index(BUTTON_TEX::NONE);

			// 1.  �ڱ��ڽ� ������
			SetUIOFF(true);
			
			// 2. STEP2 UI ���� ��Ŀ���ϱ�
			
			// 2-1. ��ü UI�׷찡����� FORCE STEP2 UI ã�Ƽ� 
			vector<CObject*> UIvec = CSceneMgr::GetInst()->GetCurScene()->GetUIGroup();
			vector<CObject*>::iterator it = UIvec.begin();

			for (; it != UIvec.end(); ++it)
			{
				// step2ã����
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

	// UI�� Tile�� ����ϰ� �»�� ��ġ�� ��ǥ�� �� ����
	Vec2 vPos = GetFinalPos();
	Vec2 vScale = GetScale();
	
	

	// ī�޶� ���� ������
	if (GetCamAffected())
	{
		// ������ ��ǥ�� �޾ƿ;��Ѵ�.
		vPos = CCamera::GetInst()->GetRenderPos(vPos);
	}

	TransparentBlt(_dc
		// ���� �»�� ��ġ�� ũ��
		, (int)vPos.x
		, (int)vPos.y
		, vScale.x
		, vScale.y
		// �ؽ��� ����
		, texArr[(UINT)m_index]->GetDC()
		// bmp ���� ������ �ڸ� �»��
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

	// Drag ��
	// ���콺 ��������
	if (IsLbtnDown())
	{
		if (FirstMouseDown)
		{
			m_vDragStart = MOUSE_POS;
			FirstMouseDown = false;
		}
			

		// ���̰� ���
		Vec2 vDiff = MOUSE_POS - m_vDragStart;

		Vec2 vCurPos = GetPos();
		// ���̰� ������
		vCurPos += vDiff;

		//if (vCurPos.x + GetScale().x < 1024.f || vCurPos.x >= 0 || vCurPos.y >=0 || vCurPos.y + GetScale().y < 768.f)
		//{
		//	SetPos(vCurPos);
		//}

		SetPos(vCurPos);

		// �׸��� �ٽ� ������ġ ���� ������ ����
		m_vDragStart = MOUSE_POS;
	}
}

void CPanelUI::MouseLbtnDown()
{
	if (IsOFF)
		return;

	// ���콺 �������� ��ġ��
	m_vDragStart = MOUSE_POS;



}


void CPanelUI::MouseLbtnUp()
{
	if (IsOFF)
		return;

}

void CPanelUI::MouseLbtnClicked()
{
	

	// ��ȭ step3UI �̸�
	if (GetName() == L"MainEnforceStep3UI")
	{	
		

		srand((UINT)time(nullptr));
		int randnum = (rand() % 100) + 1;


		// �ϴ� ������ �θ���
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

				// �ϴ� �ݺ��� ���߼�ȸ ���� �Ⱦ �ϵ��ڵ����� �ھƵ�
				step2childnumUI = (FIexedTextUI*)(step2UI->GetChildUI().front());
				step2childstatusUI = (FIexedTextUI*)(step2UI->GetChildUI().back());
			}
		}


		// ����ó��
		if (step2UI == nullptr || step2childnumUI == nullptr || step2childstatusUI == nullptr)
		{
			assert(true);
		}

		vector<CObject*>::iterator it = groupvec.begin();



		for (; it != groupvec.end(); ++it)
		{
			

			if (randnum <= step2childstatusUI->GetSuccessPercent())
			{
				// ����Ȯ���� �Ǹ�
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
				// ����Ȯ���� �Ǹ�
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

