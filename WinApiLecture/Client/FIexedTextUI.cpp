#include "pch.h"
#include "FIexedTextUI.h"



FIexedTextUI::FIexedTextUI()
	: CUI(false)
{
	m_forcenum = 1;
	m_successpercent = 50;
	m_failpercent = 50;

	

	m_font = CreateFont(          // object의 생성
		20,                  // 문자 폭
		0,                  // 문자 높이 
		0,                   // 기울기 각도
		0,                   // 문자 방향
		FW_BOLD,			// 문자 굵기
		FALSE,               // 문자 기울림 모양
		FALSE,               // 밑 줄
		FALSE,               // 취소선
		DEFAULT_CHARSET,     // 문자 셋
		OUT_DEFAULT_PRECIS,  // 출력 정확도
		CLIP_DEFAULT_PRECIS, // 킬립핑 정확도
		DEFAULT_QUALITY,     // 출력의 질
		DEFAULT_PITCH,       // 자간 거리
		L"메이플스토리 가늘게"               // 문자 모양
	);
}


FIexedTextUI::~FIexedTextUI()
{
	DeleteObject(m_font);
}

void FIexedTextUI::render(HDC _dc)
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

	// 배경 투명
	SetBkMode(_dc, TRANSPARENT);
	// 색상
	

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
		wstring str2 = L" 성";
		wstring str3 = str1 + str2;
		DrawText(_dc, str3.c_str(), str3.length(), &rect, DT_WORDBREAK);
	}
	else if (GetName() == L"step2ForceStatusUI")
	{
		SetTextColor(_dc, 0x00FFFFFF);

		wstring strFirstline1 = std::to_wstring(m_forcenum);
		wstring strFirstline2 = L" 성 > ";
		wstring strFirstline3 = std::to_wstring(m_forcenum+1);
		wstring strFirstline4 = L" 성 \n";
		wstring strFirst = strFirstline1 + strFirstline2 + strFirstline3 + strFirstline4;
		wstring strSecondline1 = L"성공확률 : ";
		wstring strSecondline2 = std::to_wstring(m_successpercent);
		wstring strSecondline3 = L" % \n";
		wstring strSecond = strSecondline1 + strSecondline2 + strSecondline3;
		wstring strThirdline1 = L"실패(유지)확률 : ";
		wstring strThirdline2 = std::to_wstring(m_failpercent);
		wstring strThirdline3 = L" % \n";
		wstring strThird = strThirdline1 + strThirdline2 + strThirdline3;
		wstring strFourth = L"개발력 : +1";
		wstring strTotal = strFirst + strSecond + strThird + strFourth;

		DrawText(_dc, strTotal.c_str(), strTotal.length(), &rect, DT_WORDBREAK);
	}
	

	

	
	m_font = (HFONT)SelectObject(_dc, oldfont);
}
