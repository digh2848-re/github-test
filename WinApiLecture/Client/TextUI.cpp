#include "pch.h"
#include "TextUI.h"

#include "CKeyMgr.h"
#include "CTexture.h"
#include "CResMgr.h"
#include "SelectGDI.h"
#include "CTimeMgr.h"

TextUI::TextUI(ITEM_TYPE _type)
	: CUI(false) // 카메라 영향 안받음
{
	m_deadtime = 0.;
	m_Texttype = _type;

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
	SetTextColor(_dc, 0x00FFFFFF);


	HFONT oldfont = (HFONT)SelectObject(_dc, m_font);


	wstring str;

	switch (m_Texttype)
	{
	case ITEM_TYPE::MONEY_1:
		str = L"메소를 얻었습니다. (+15)";
		break;
	case ITEM_TYPE::MONEY_2:
		str = L"메소를 얻었습니다. (+250)";
		break;
	case ITEM_TYPE::MONEY_3:
		str = L"메소를 얻었습니다. (+1000)";
		break;
	}

	TextOut(_dc, (int)vPos.x, (int)vPos.y, str.c_str(), str.length());
	
	m_font = (HFONT)SelectObject(_dc, oldfont);
}
