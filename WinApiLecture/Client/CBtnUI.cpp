
#include "pch.h"
#include "CBtnUI.h"
#include "SelectGDI.h"
#include "CResMgr.h"
#include "CTexture.h"
#include "CKeyMgr.h"
#include "CSceneMgr.h"
#include "CPlayer.h"
#include "CUIMgr.h"
#include "CSound.h"
#include "FixedUI.h"
// ����
/*
�гξȿ� �̹����� ����Ҽ� �ִ� ��ư���� ����

�̹����� Ÿ���� �������� ������ �ȴ�

���� �� �гο� �� ��������

�г� Ŭ������ �ڽ����� ������ ��ȯ ��ư ����

��ȯ ��ư�� ������ �Ǹ� ���� �г� �̹����� �ٲ�

�������� �Ѿ�ٰ� ������ ��ư���� ��������ʰ�
����ִ� ��ư���� �̹����� ������ �ٸ��Ŵ�

���� ��� ������ ���������� ���빰�� ��ƴ���� ©���ٸ�
�׷��� ���ù��� ���� �̹����� �ȶ��� �ȴ�
�� ���ù��� ���� �͵��� ����� �ϴµ�
�ڱⰡ ����ϴ� �̹����� ������ ������ ���ϸ� ��

�ᱹ ���� UI���� ���� ���� ��
Ư�� Ÿ���� ��ư�� ��������
���� �׷����� Ÿ�� ��ġ���ٰ� Ŭ���ϸ�
���� Ÿ���� ������ �°� ��ȭ��������Ѵ�
*/

CBtnUI::CBtnUI()
	: CUI(false)	
	, m_pFunc(nullptr)
	, m_param1(0)
	, m_param2(0)
	, m_pSceneInst(nullptr)
	, m_pSceneFunc(nullptr)
	, Tex_index(BUTTON_TEX::NONE)
{

}

CBtnUI::CBtnUI(BUTTON_TEX _index)
	: CUI(false)
	, m_pFunc(nullptr)
	, m_param1(0)
	, m_param2(0)
	, m_pSceneInst(nullptr)
	, m_pSceneFunc(nullptr)
	, FirstMouseDown(true)
{
	Tex_index = _index;
	ButtonTex[0] = CResMgr::GetInst()->LoadTexture(L"ClothItemBtnUI", L"texture\\ButtonUI\\ClothItem.bmp");
	ButtonTex[1] = CResMgr::GetInst()->LoadTexture(L"WeaponItemBtnUI", L"texture\\ButtonUI\\WeaponItem.bmp");
	ButtonTex[2] = CResMgr::GetInst()->LoadTexture(L"HpItemBtnUI", L"texture\\ButtonUI\\hp.bmp");
	ButtonTex[3] = CResMgr::GetInst()->LoadTexture(L"MpItemBtnUI", L"texture\\ButtonUI\\mp.bmp");
	ButtonTex[4] = CResMgr::GetInst()->LoadTexture(L"Skill1BtnUI", L"texture\\ButtonUI\\skill1.bmp");
	ButtonTex[5] = CResMgr::GetInst()->LoadTexture(L"Skill1ClickBtnUI", L"texture\\ButtonUI\\skillbutton.bmp");
	ButtonTex[6] = CResMgr::GetInst()->LoadTexture(L"Skill2BtnUI", L"texture\\ButtonUI\\skill2.bmp");
	ButtonTex[7] = CResMgr::GetInst()->LoadTexture(L"Skill2ClickBtnUI", L"texture\\ButtonUI\\skillbutton.bmp");
	ButtonTex[8] = CResMgr::GetInst()->LoadTexture(L"Skill3BtnUI", L"texture\\ButtonUI\\skill3.bmp");
	ButtonTex[9] = CResMgr::GetInst()->LoadTexture(L"Skill3ClickBtnUI", L"texture\\ButtonUI\\skillbutton.bmp");
	ButtonTex[10] = CResMgr::GetInst()->LoadTexture(L"Skill4BtnUI", L"texture\\ButtonUI\\skill4.bmp");
	ButtonTex[11] = CResMgr::GetInst()->LoadTexture(L"Skill4ClickBtnUI", L"texture\\ButtonUI\\skillbutton.bmp");
	ButtonTex[12] = CResMgr::GetInst()->LoadTexture(L"ForceItemBtnUI", L"texture\\ButtonUI\\ForceItem.bmp");
	ButtonTex[13] = CResMgr::GetInst()->LoadTexture(L"PanelUIExit", L"texture\\ButtonUI\\PanelUIExit.bmp");

	m_vDragStart = Vec2(0.f, 0.f); 

	m_StarSound = CResMgr::GetInst()->FindSound(L"STAR_SOUND");
	m_ClickSound = CResMgr::GetInst()->FindSound(L"MOUSEOVER_SOUND");
}

CBtnUI::~CBtnUI()
{
}

void CBtnUI::start()
{
	// ������ ��ġ�� offset �������� ������
	m_FixedPos = GetPos();
}

void CBtnUI::update()
{
	Vec2 vPos = GetPos();

	// �巡�����ε� ���콺 �ӵ��� �ʹ� ���� mouseoff�����̸�
	if (IsDrag && !IsMouseOn())
	{
		IsDrag = false;
		SetPos(m_FixedPos);
	}


	CUI::update();
}

void CBtnUI::render(HDC _dc)
{
	if (Tex_index == BUTTON_TEX::NONE)
	{
		//// UI�� Tile�� ����ϰ� �»�� ��ġ�� ��ǥ�� �� ����
		//Vec2 vPos = GetFinalPos();
		//Vec2 vScale = GetScale();
		//
		//// ī�޶� ���� ������
		//if (GetCamAffected())
		//{
		//	// ������ ��ǥ�� �޾ƿ;��Ѵ�.
		//	vPos = CCamera::GetInst()->GetRenderPos(vPos);
		//}
		//
		//if (IsLbtnDown())
		//{
		//	PEN_TYPE ePen = PEN_TYPE::GREEN;
		//
		//	SelectGDI p(_dc, ePen);
		//	SelectGDI b(_dc, BRUSH_TYPE::HOLLOW);
		//
		//	Rectangle(_dc
		//		, int(vPos.x)
		//		, int(vPos.y)
		//		, int(vPos.x + vScale.x)
		//		, int(vPos.y + vScale.y)
		//	);
		//}
		//else
		//{
		//	Rectangle(_dc
		//		, int(vPos.x)
		//		, int(vPos.y)
		//		, int(vPos.x + vScale.x)
		//		, int(vPos.y + vScale.y)
		//	);
		//
		//}
	}
	else
	{
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
			, ButtonTex[(UINT)Tex_index]->GetDC()
			// bmp ���� ������ �ڸ� �»��
			, (int)0
			, (int)0
			, vScale.x
			, vScale.y
			, RGB(255, 0, 255));
	}


	//CUI::render(_dc);
}

void CBtnUI::MouseOn()
{
	// Drag �� ( �巡���ϴ� ��ưUI �ƴϸ� ���Ҳ���
	// ���콺 ��������
	if (IsLbtnDown()								&&
		Tex_index != BUTTON_TEX::NONE				&&				// �ؽ��� ���� ��ư�̸� �巡�׾Ƚ�Ŵ
		Tex_index != BUTTON_TEX::SKILL1CLICK		&&				// ��ų��ư������ �ؽ��ĸ� �巡�׾Ƚ�Ŵ
		Tex_index != BUTTON_TEX::SKILL2CLICK		&&
		Tex_index != BUTTON_TEX::SKILL3CLICK		&&
		Tex_index != BUTTON_TEX::SKILL4CLICK		&&
		Tex_index != BUTTON_TEX::EXIT
		)
	{
		// ���ӽ����ϰ� ó�� Ŭ���̸�
		if (FirstMouseDown)
		{
			m_vDragStart = MOUSE_POS;
			FirstMouseDown = false;
		}


		IsDrag = true;

		// ���̰� ���
		Vec2 vDiff = MOUSE_POS - m_vDragStart;

		Vec2 vCurPos = GetPos();
		// ���̰� ������
		vCurPos += vDiff;

		SetPos(vCurPos);

		// �׸��� �ٽ� ������ġ ���� ������ ����
		m_vDragStart = MOUSE_POS;
	}
	else
	{

		int a = 0;
	}

}

void CBtnUI::MouseLbtnDown()
{
	// ���콺 �������� ��ġ��
	m_vDragStart = MOUSE_POS;

	// ��ų��ư ������ �θ� ã������ �ڽ��� FixedUI ã�Ƴ�����  ���� ����
	if (Tex_index == BUTTON_TEX::SKILL2CLICK)
	{
		vector<CUI*> childUI = GetParent()->GetChildUI();
		vector<CUI*>::iterator it = childUI.begin();

		for (; it != childUI.end(); it++)
		{
			if ((*it)->GetName() == L"skill2TextUI")
			{
				if (((FixedUI*)(*it))->GetSkillpoint() >= 4)
				{
					Tex_index = BUTTON_TEX::NONE;
					((FixedUI*)(*it))->AddSkillpoint();
					break;
				}

				((FixedUI*)(*it))->AddSkillpoint();
				break;
			}
		}

	}
	else if (Tex_index == BUTTON_TEX::SKILL1CLICK)
	{
		vector<CUI*> childUI = GetParent()->GetChildUI();
		vector<CUI*>::iterator it = childUI.begin();

		for (; it != childUI.end(); it++)
		{
			if ((*it)->GetName() == L"skill1TextUI")
			{
				if (((FixedUI*)(*it))->GetSkillpoint() >= 4)
				{
					Tex_index = BUTTON_TEX::NONE;
					((FixedUI*)(*it))->AddSkillpoint();
					break;
				}

				((FixedUI*)(*it))->AddSkillpoint();
				break;
			}
		}
	}
	else if (Tex_index == BUTTON_TEX::SKILL3CLICK)
	{
		vector<CUI*> childUI = GetParent()->GetChildUI();
		vector<CUI*>::iterator it = childUI.begin();

		for (; it != childUI.end(); it++)
		{
			if ((*it)->GetName() == L"skill3TextUI")
			{
				if (((FixedUI*)(*it))->GetSkillpoint() >= 4)
				{
					Tex_index = BUTTON_TEX::NONE;
					((FixedUI*)(*it))->AddSkillpoint();
					break;
				}

				((FixedUI*)(*it))->AddSkillpoint();
				break;
			}
		}
	}
	else if (Tex_index == BUTTON_TEX::SKILL4CLICK)
	{
		vector<CUI*> childUI = GetParent()->GetChildUI();
		vector<CUI*>::iterator it = childUI.begin();

		for (; it != childUI.end(); it++)
		{
			if ((*it)->GetName() == L"skill4TextUI")
			{
				if (((FixedUI*)(*it))->GetSkillpoint() >= 4)
				{
					Tex_index = BUTTON_TEX::NONE;
					((FixedUI*)(*it))->AddSkillpoint();
					break;
				}

				((FixedUI*)(*it))->AddSkillpoint();
				break;
			}
		}
	}

}


void CBtnUI::MouseLbtnUp()
{
	// �巡���߿��� ��� ���� �ȴٸ�
	if (IsDrag)
	{
		// �ֻ��� �θ� �� ������ͼ�
		vector<CObject*>& groupvec =(CSceneMgr::GetInst()->GetCurScene())->GetUIGroup();

		vector<CObject*>::iterator it = groupvec.begin();

		for( ;it != groupvec.end() ; ++it)
		{
			// �θ𿡼� �ڽı��� �� Ȯ���ϱ�
			vector<CUI*>& vec = dynamic_cast<CUI*>(*it)->GetChildBtnUI();

			vector<CUI*>::iterator iter = vec.begin();

			if (vec.empty())
				continue;

			Vec2 myPos = CCamera::GetInst()->GetRenderPos(GetFinalPos());
			Vec2 myScale = GetScale();
			myPos += myScale / 2.f;

			

			for (; iter != vec.end(); iter++)
			{
				Vec2 YouPos = CCamera::GetInst()->GetRenderPos((*iter)->GetFinalPos());
				Vec2 YouScale = (*iter)->GetScale();

				if (myPos.x < YouPos.x + YouScale.x &&
					myPos.x > YouPos.x &&
					myPos.y < YouPos.y + YouScale.y &&
					myPos.y > YouPos.y)
				{
					// ���� ��ȭstep1 UI�ڽ� ��ưUI�̶� �ٲ�� 
					if ((*iter)->GetParent()->GetName() == L"MainEnforceStep1UI")
					{
						// ���游 �ٲٰ� �ڽ��� �׳� �״�� ��
						dynamic_cast<CBtnUI*>(*iter)->SetTex_index(Tex_index);
					}
					else
					{
						// ��ư �ؽ��� �ٲٴµ�
						BUTTON_TEX youIndex = dynamic_cast<CBtnUI*>(*iter)->GetTexindex();
						dynamic_cast<CBtnUI*>(*iter)->SetTex_index(Tex_index);
						Tex_index = youIndex;
					}


				}
			}
		}


	}

	IsDrag = false;
	// ���� ��ġ�� �ű�
	SetPos(m_FixedPos);


}


void CBtnUI::MouseLbtnClicked()
{
	m_ClickSound->Play();
	m_ClickSound->SetVolume(100.f);

	// �����ưUI�̸�
	if (Tex_index == BUTTON_TEX::EXIT)
	{
		GetParent()->SetUIOFF(true);
	}

	// ��ȭ step2 UI���� Ȯ�� ��� �̺�Ʈ ó��
	if (Tex_index == BUTTON_TEX::NONE)
	{
		// ��ҹ�ư Ŭ�������̸�
		if (GetName() == L"stepCancelBtnUI")
		{
			// �θ� UI ������
			GetParent()->SetUIOFF(true);
		} // Ȯ�ι�ư�̸� ���� �ٸ� ui Ŀ����
		else if (GetName() == L"stepOkBtnUI")
		{
			
			// STEP3 UI �Ѿ���
			// �ֻ��� �θ� �� ������ͼ�
			vector<CObject*>& groupvec = (CSceneMgr::GetInst()->GetCurScene())->GetUIGroup();

			vector<CObject*>::iterator it = groupvec.begin();

			for (; it != groupvec.end(); ++it)
			{
				if ((*it)->GetName() == L"MainEnforceStep3UI")
				{
					Vec2 parentPos = GetParent()->GetPos();
					(*it)->SetPos(Vec2(parentPos.x+70.f, parentPos.y+70.f));

					((CUI*)(*it))->SetUIOFF(false);
					CUIMgr::GetInst()->SetFocusedUI((CUI*)(*it));

					m_StarSound->Play();
					m_StarSound->SetVolume(100.f);
					break;
				}
			}
		}

		// Dead UI ��ư ������
		if (GetName() == L"DeadBtnUI")
		{
			// �÷��̾� ��Ȱ
			CPlayer* player = (CPlayer*)(CSceneMgr::GetInst()->GetCurScene())->GetPlayer();
			player->SetDead(false);
			player->SetHp(100);
			player->SetOffGraviRigid(false);
			Vec2 pos = player->GetPos();
			pos.y -= 0.f;
			player->SetPos(pos);
			// �ڱ� �θ� UI �ٽ� ������
			GetParent()->SetUIOFF(true);
		}
	}

	// �ϴ� �Ⱦ�
	if (m_pFunc != nullptr)
	{
		m_pFunc(m_param1, m_param2);
	}

	if (m_pSceneInst && m_pSceneFunc)
	{
		((*m_pSceneInst).*m_pSceneFunc)();
	}


}

void CBtnUI::SetClickedCallBack(CScene* _pScene, SCENE_MEMFUNC _pSceneFunc)
{
	m_pSceneInst = _pScene;
	m_pSceneFunc = _pSceneFunc;
}