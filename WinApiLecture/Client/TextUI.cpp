#include "pch.h"
#include "TextUI.h"

#include "CKeyMgr.h"
#include "CTexture.h"
#include "CResMgr.h"
#include "SelectGDI.h"
#include "CTimeMgr.h"

TextUI::TextUI(ITEM_TYPE _type)
	: CUI(false) // ī�޶� ���� �ȹ���
{
	m_deadtime = 0.;
	m_Texttype = _type;

	m_font = CreateFont(          // object�� ����
		20,                  // ���� ��
		0,                  // ���� ���� 
		0,                   // ���� ����
		0,                   // ���� ����
		FW_BOLD,			// ���� ����
		FALSE,               // ���� ��︲ ���
		FALSE,               // �� ��
		FALSE,               // ��Ҽ�
		DEFAULT_CHARSET,     // ���� ��
		OUT_DEFAULT_PRECIS,  // ��� ��Ȯ��
		CLIP_DEFAULT_PRECIS, // ų���� ��Ȯ��
		DEFAULT_QUALITY,     // ����� ��
		DEFAULT_PITCH,       // �ڰ� �Ÿ�
		L"�����ý��丮 ���ð�"               // ���� ���
	);


}


TextUI::~TextUI()
{
	DeleteObject(m_font);
}

void TextUI::update()
{
	if (m_deadtime > 3.)
	{
		SetDead();
	}

	m_deadtime += DT;
}

void TextUI::render(HDC _dc)
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

	// ��� ����
	SetBkMode(_dc, TRANSPARENT);
	// ����
	SetTextColor(_dc, 0x00FFFFFF);


	HFONT oldfont = (HFONT)SelectObject(_dc, m_font);


	wstring str;

	switch (m_Texttype)
	{
	case ITEM_TYPE::MONEY_1:
		str = L"�޼Ҹ� ������ϴ�. (+15)";
		break;
	case ITEM_TYPE::MONEY_2:
		str = L"�޼Ҹ� ������ϴ�. (+250)";
		break;
	case ITEM_TYPE::MONEY_3:
		str = L"�޼Ҹ� ������ϴ�. (+1000)";
		break;
	}

	TextOut(_dc, (int)vPos.x, (int)vPos.y, str.c_str(), str.length());
	
	m_font = (HFONT)SelectObject(_dc, oldfont);
}
