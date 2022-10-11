#include "pch.h"
#include "FIexedTextUI.h"



FIexedTextUI::FIexedTextUI()
	: CUI(false)
{
	m_forcenum = 1;
	m_successpercent = 50;
	m_failpercent = 50;

	

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


FIexedTextUI::~FIexedTextUI()
{
	DeleteObject(m_font);
}

void FIexedTextUI::render(HDC _dc)
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
	

	HFONT oldfont = (HFONT)SelectObject(_dc, m_font);

	RECT rect = { vPos.x,
				  vPos.y,
				  vPos.x + vScale.x,
				  vPos.y + vScale.y
	};

	if (GetName() == L"step2ForceNumUI")
	{
		SetTextColor(_dc, 0xFFFFFFFF);

		wstring str1 = std::to_wstring(m_forcenum);
		wstring str2 = L" ��";
		wstring str3 = str1 + str2;
		DrawText(_dc, str3.c_str(), str3.length(), &rect, DT_WORDBREAK);
	}
	else if (GetName() == L"step2ForceStatusUI")
	{
		SetTextColor(_dc, 0x00FFFFFF);

		wstring strFirstline1 = std::to_wstring(m_forcenum);
		wstring strFirstline2 = L" �� > ";
		wstring strFirstline3 = std::to_wstring(m_forcenum+1);
		wstring strFirstline4 = L" �� \n";
		wstring strFirst = strFirstline1 + strFirstline2 + strFirstline3 + strFirstline4;
		wstring strSecondline1 = L"����Ȯ�� : ";
		wstring strSecondline2 = std::to_wstring(m_successpercent);
		wstring strSecondline3 = L" % \n";
		wstring strSecond = strSecondline1 + strSecondline2 + strSecondline3;
		wstring strThirdline1 = L"����(����)Ȯ�� : ";
		wstring strThirdline2 = std::to_wstring(m_failpercent);
		wstring strThirdline3 = L" % \n";
		wstring strThird = strThirdline1 + strThirdline2 + strThirdline3;
		wstring strFourth = L"���߷� : +1";
		wstring strTotal = strFirst + strSecond + strThird + strFourth;

		DrawText(_dc, strTotal.c_str(), strTotal.length(), &rect, DT_WORDBREAK);
	}
	

	

	
	m_font = (HFONT)SelectObject(_dc, oldfont);
}
