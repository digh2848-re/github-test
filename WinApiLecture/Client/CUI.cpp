#include "CUI.h"

#include "CKeyMgr.h"
#include "CCamera.h"

#include "SelectGDI.h"


CUI::CUI(bool _bCamAff)
	: m_pParentUI(nullptr)
	, m_bCamAffected(_bCamAff) // ī�޶� ���� ���� ����
	, m_bMouseOn(false)
	, IsDrag(false)
	, IsOFF(false)
{
}

CUI::CUI(const CUI& _origin)
	: CObject(_origin) // ��������� ����ϸ� �θ��ʵ� ��������� ���
	, m_pParentUI(nullptr)
	, m_bCamAffected(_origin.m_bCamAffected)
	, m_bMouseOn(false)
	, m_bLbtnDown(false)
	, IsDrag(false)
	, IsOFF(false)
{
	// ���� ����
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

	// �ڽ� update ��


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
	// UI�� �������¸� �ǵ��� ����
	if (IsOFF)
	{
		m_bMouseOn = false;
		m_bLbtnDown = false;
		return;
	}
		

	// UI�� �ִϸ����ͳ� �ݶ��̴� ������ �ֱ� ������
	CObject::finalupdate();

	// UI �� ���� ��ǥ�� ���Ѵ�.
	if (GetParent())
	{
		// �ڱ� �ڽ� offset ��ġ ���� �ް�
		m_vFinalPos = GetPos();

		// �θ� �����ش�
		Vec2 vParentPos = GetParent()->GetFinalPos();
		m_vFinalPos += vParentPos;
	}
	else
	{
		// �ڽ��� �ֻ��� �θ��� �ڱ� ��ġ�� �� finalPos
		m_vFinalPos = GetPos(); 
	}

	// UI Mouse üũ
	MouseOnCheck();

	// �ڽĵ鵵 finalupdate ������
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

	//// UI�� Tile�� ����ϰ� �»�� ��ġ�� ��ǥ�� �� ����
	//Vec2 vPos = GetFinalPos();
	//Vec2 vScale = GetScale();
	//
	//// ī�޶� ���� ������
	//if (m_bCamAffected)
	//{
	//	// ������ ��ǥ�� �޾ƿ;��Ѵ�.
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

	// ���콺 üũ ��ĵ� ī�޶� ����޴����� ���� ��ǥ�� �޶���
	if (m_bCamAffected)
	{
		vMousePos = CCamera::GetInst()->GetRealPos(vMousePos);
	}

	// �巡�����̸� �������� �÷��ٲ���
	if (IsDrag)
	{
		// UI ���� �ȿ� ���콺 ��ǥ�� ������
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
		// UI ���� �ȿ� ���콺 ��ǥ�� ������
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