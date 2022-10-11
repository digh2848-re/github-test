#include "CUI.h"

#include "CKeyMgr.h"
#include "CCamera.h"

#include "SelectGDI.h"


CUI::CUI(bool _bCamAff)
	: m_pParentUI(nullptr)
	, m_bCamAffected(_bCamAff) // 카메라 영향 받지 않음
	, m_bMouseOn(false)
	, IsDrag(false)
	, IsOFF(false)
{
}

CUI::CUI(const CUI& _origin)
	: CObject(_origin) // 복사생성자 명시하면 부모쪽도 복사생성자 명시
	, m_pParentUI(nullptr)
	, m_bCamAffected(_origin.m_bCamAffected)
	, m_bMouseOn(false)
	, m_bLbtnDown(false)
	, IsDrag(false)
	, IsOFF(false)
{
	// 깊은 복사
	for (size_t i = 0; i < _origin.m_vecChildUI.size(); ++i)
	{
		AddChild(_origin.m_vecChildUI[i]->Clone());

	}
}

CUI::~CUI()
{
	Safe_Delete_Vec(m_vecChildUI);
}


void CUI::start()
{
	start_child();
}

void CUI::start_child()
{
	for (size_t i = 0; i < m_vecChildUI.size(); i++)
	{
		m_vecChildUI[i]->start();
	}
}

void CUI::update()
{
	if (IsOFF)
		return;

	// 자신 update 후


	//child ui update
	update_child();
}

void CUI::update_child()
{
	for (size_t i = 0; i < m_vecChildUI.size(); i++)
	{
		m_vecChildUI[i]->update();
	}
}

void CUI::finalupdate()
{
	// UI가 꺼진상태면 건들지 말자
	if (IsOFF)
	{
		m_bMouseOn = false;
		m_bLbtnDown = false;
		return;
	}
		

	// UI가 애니메이터나 콜라이더 가질수 있기 때문에
	CObject::finalupdate();

	// UI 의 최종 좌표를 구한다.
	if (GetParent())
	{
		// 자기 자신 offset 위치 먼저 받고
		m_vFinalPos = GetPos();

		// 부모껄 더해준다
		Vec2 vParentPos = GetParent()->GetFinalPos();
		m_vFinalPos += vParentPos;
	}
	else
	{
		// 자신이 최상의 부모라면 자기 위치가 곧 finalPos
		m_vFinalPos = GetPos(); 
	}

	// UI Mouse 체크
	MouseOnCheck();

	// 자식들도 finalupdate 돌려줌
	finalupdate_child();

}

void CUI::finalupdate_child()
{
	for (size_t i = 0; i < m_vecChildUI.size(); i++)
	{
		m_vecChildUI[i]->finalupdate();
	}
}

void CUI::render(HDC _dc)
{
	if (IsOFF)
		return;

	//// UI도 Tile과 비슷하게 좌상단 위치를 좌표로 할 것임
	//Vec2 vPos = GetFinalPos();
	//Vec2 vScale = GetScale();
	//
	//// 카메라 영향 받으면
	//if (m_bCamAffected)
	//{
	//	// 렌더링 좌표로 받아와야한다.
	//	vPos = CCamera::GetInst()->GetRenderPos(vPos);
	//}
	//
	//if (m_bLbtnDown)
	//{
	//	SelectGDI select(_dc, PEN_TYPE::GREEN);
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


	// child ui render
	render_child(_dc);
}

void CUI::render_child(HDC _dc)
{
	for (size_t i = 0; i < m_vecChildUI.size(); i++)
	{
		m_vecChildUI[i]->render(_dc);
	}
}

void CUI::MouseOnCheck()
{
	if (IsOFF)
	{
		return;
	}

	Vec2 vMousePos = MOUSE_POS;
	Vec2 vScale = GetScale();

	// 마우스 체크 방식도 카메라 영향받는지에 따라 좌표가 달라짐
	if (m_bCamAffected)
	{
		vMousePos = CCamera::GetInst()->GetRealPos(vMousePos);
	}

	// 드래그중이면 범위판정 늘려줄꺼임
	if (IsDrag)
	{
		// UI 범위 안에 마우스 좌표가 들어오면
		if (m_vFinalPos.x-50.f <= vMousePos.x && vMousePos.x <= m_vFinalPos.x + vScale.x + 50.f
			&& m_vFinalPos.y - 50.f <= vMousePos.y && vMousePos.y <= m_vFinalPos.y + vScale.y + 50.f)
		{
			m_bMouseOn = true;
		}
		else
		{
			m_bMouseOn = false;
		}
	}
	else
	{
		// UI 범위 안에 마우스 좌표가 들어오면
		if (m_vFinalPos.x <= vMousePos.x && vMousePos.x <= m_vFinalPos.x + vScale.x
			&& m_vFinalPos.y <= vMousePos.y && vMousePos.y <= m_vFinalPos.y + vScale.y)
		{
			m_bMouseOn = true;
		}
		else
		{
			m_bMouseOn = false;
		}
	}
}



void CUI::MouseOn()
{

}

void CUI::MouseLbtnDown()
{

}

void CUI::MouseLbtnUp()
{

}

void CUI::MouseLbtnClicked()
{

}