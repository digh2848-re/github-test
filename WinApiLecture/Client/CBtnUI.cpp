
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
// 숙제
/*
패널안에 이미지를 출력할수 있는 버튼들을 넣자

이미지는 타일의 조각들을 넣으면 된다

만약 한 패널에 다 못담으면

패널 클래스의 자식으로 페이지 전환 버튼 만들어서

전환 버튼을 누르게 되면 다음 패널 이미지로 바뀜

페이지가 넘어간다고 이전의 버튼들이 사라지진않고
띄워주는 버튼들의 이미지의 종류가 다른거다

예를 들어 마지막 페이지에서 내용물이 반틈에서 짤린다면
그러면 세팅받지 못한 이미지를 안띄우면 된다
즉 세팅받지 못한 것들은 존재는 하는데
자기가 담당하는 이미지가 없으면 렌더링 안하면 됨

결국 위에 UI같은 것을 만들어낸 후
특정 타일의 버튼을 누른다음
실제 그려지는 타일 위치에다가 클릭하면
누른 타일의 종류에 맞게 변화시켜줘야한다
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
	// 고정된 위치는 offset 개념으로 갈꺼임
	m_FixedPos = GetPos();
}

void CBtnUI::update()
{
	Vec2 vPos = GetPos();

	// 드래그중인데 마우스 속도가 너무 빨라 mouseoff상태이면
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
		//// UI도 Tile과 비슷하게 좌상단 위치를 좌표로 할 것임
		//Vec2 vPos = GetFinalPos();
		//Vec2 vScale = GetScale();
		//
		//// 카메라 영향 받으면
		//if (GetCamAffected())
		//{
		//	// 렌더링 좌표로 받아와야한다.
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
			, ButtonTex[(UINT)Tex_index]->GetDC()
			// bmp 파일 내에서 자를 좌상단
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
	// Drag 중 ( 드래그하는 버튼UI 아니면 안할꺼임
	// 마우스 누른순간
	if (IsLbtnDown()								&&
		Tex_index != BUTTON_TEX::NONE				&&				// 텍스쳐 없는 버튼이면 드래그안시킴
		Tex_index != BUTTON_TEX::SKILL1CLICK		&&				// 스킬버튼누르는 텍스쳐면 드래그안시킴
		Tex_index != BUTTON_TEX::SKILL2CLICK		&&
		Tex_index != BUTTON_TEX::SKILL3CLICK		&&
		Tex_index != BUTTON_TEX::SKILL4CLICK		&&
		Tex_index != BUTTON_TEX::EXIT
		)
	{
		// 게임시작하고 처음 클릭이면
		if (FirstMouseDown)
		{
			m_vDragStart = MOUSE_POS;
			FirstMouseDown = false;
		}


		IsDrag = true;

		// 차이값 계산
		Vec2 vDiff = MOUSE_POS - m_vDragStart;

		Vec2 vCurPos = GetPos();
		// 차이값 더해줌
		vCurPos += vDiff;

		SetPos(vCurPos);

		// 그리고 다시 시작위치 변한 값으로 세팅
		m_vDragStart = MOUSE_POS;
	}
	else
	{

		int a = 0;
	}

}

void CBtnUI::MouseLbtnDown()
{
	// 마우스 누른순간 위치값
	m_vDragStart = MOUSE_POS;

	// 스킬버튼 누를시 부모 찾은다음 자식인 FixedUI 찾아낸다음  숫자 증가
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
	// 드래그중에서 어디에 놓게 된다면
	if (IsDrag)
	{
		// 최상위 부모 다 가지고와서
		vector<CObject*>& groupvec =(CSceneMgr::GetInst()->GetCurScene())->GetUIGroup();

		vector<CObject*>::iterator it = groupvec.begin();

		for( ;it != groupvec.end() ; ++it)
		{
			// 부모에서 자식까지 다 확인하기
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
					// 만약 강화step1 UI자식 버튼UI이랑 바뀌면 
					if ((*iter)->GetParent()->GetName() == L"MainEnforceStep1UI")
					{
						// 상대방만 바꾸고 자신을 그냥 그대로 둠
						dynamic_cast<CBtnUI*>(*iter)->SetTex_index(Tex_index);
					}
					else
					{
						// 버튼 텍스쳐 바꾸는데
						BUTTON_TEX youIndex = dynamic_cast<CBtnUI*>(*iter)->GetTexindex();
						dynamic_cast<CBtnUI*>(*iter)->SetTex_index(Tex_index);
						Tex_index = youIndex;
					}


				}
			}
		}


	}

	IsDrag = false;
	// 원래 위치로 옮김
	SetPos(m_FixedPos);


}


void CBtnUI::MouseLbtnClicked()
{
	m_ClickSound->Play();
	m_ClickSound->SetVolume(100.f);

	// 종료버튼UI이면
	if (Tex_index == BUTTON_TEX::EXIT)
	{
		GetParent()->SetUIOFF(true);
	}

	// 강화 step2 UI에서 확인 취소 이벤트 처리
	if (Tex_index == BUTTON_TEX::NONE)
	{
		// 취소버튼 클릭상태이면
		if (GetName() == L"stepCancelBtnUI")
		{
			// 부모 UI 꺼버림
			GetParent()->SetUIOFF(true);
		} // 확인버튼이면 끄고 다른 ui 커야함
		else if (GetName() == L"stepOkBtnUI")
		{
			
			// STEP3 UI 켜야함
			// 최상위 부모 다 가지고와서
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

		// Dead UI 버튼 누르면
		if (GetName() == L"DeadBtnUI")
		{
			// 플레이어 부활
			CPlayer* player = (CPlayer*)(CSceneMgr::GetInst()->GetCurScene())->GetPlayer();
			player->SetDead(false);
			player->SetHp(100);
			player->SetOffGraviRigid(false);
			Vec2 pos = player->GetPos();
			pos.y -= 0.f;
			player->SetPos(pos);
			// 자기 부모 UI 다시 꺼야함
			GetParent()->SetUIOFF(true);
		}
	}

	// 일단 안씀
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