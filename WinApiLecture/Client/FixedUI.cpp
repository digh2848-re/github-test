#include "pch.h"
#include "FixedUI.h"

#include "CSceneMgr.h"
#include "CScene.h"
#include "CKeyMgr.h"
#include "CPlayer.h"

#include "CTexture.h"
#include "CResMgr.h"
#include "CTimeMgr.h"

FixedUI::FixedUI()
	: CUI(false) // 카메라 영향 안받음
{
	m_starDir = 1;
	m_starSpeed = 150.f;
}

FixedUI::FixedUI(FIXED_TEX _index)
	: CUI(false) // 카메라 영향 안받음
{
	m_index = _index;
	texArr[0] = CResMgr::GetInst()->LoadTexture(L"PlayerstatusbarUI", L"texture\\playerstatusbarUI.bmp");
	texArr[1] = CResMgr::GetInst()->LoadTexture(L"QuickslotUI", L"texture\\quickslotUI.bmp");
	texArr[2] = CResMgr::GetInst()->LoadTexture(L"MOVESTARUI", L"texture\\ForceUI\\star.bmp");
	texArr[3] = CResMgr::GetInst()->LoadTexture(L"QUEST1STEP1UI", L"texture\\QuestChat\\Quest1step1.bmp");
	texArr[4] = CResMgr::GetInst()->LoadTexture(L"QUEST1STEP2UI", L"texture\\QuestChat\\Quest1step2.bmp");
	texArr[5] = CResMgr::GetInst()->LoadTexture(L"QUEST2STEP1UI", L"texture\\QuestChat\\Quest2step1.bmp");
	texArr[6] = CResMgr::GetInst()->LoadTexture(L"QUEST2STEP2UI", L"texture\\QuestChat\\Quest2step2.bmp");
	texArr[7] = CResMgr::GetInst()->LoadTexture(L"QUEST3STEP1UI", L"texture\\QuestChat\\Quest3step1.bmp");
	texArr[8] = CResMgr::GetInst()->LoadTexture(L"QUEST3STEP2UI", L"texture\\QuestChat\\Quest3step2.bmp");
	texArr[9] = CResMgr::GetInst()->LoadTexture(L"BossstatusbarUI", L"texture\\BOSS_HpBar_Back.bmp");
	levelnum = 1;
	m_starDir = 1;
	m_starSpeed = 150.f;
	meso = 0;
	skillpoint = 1;
}


FixedUI::~FixedUI()
{
}


void FixedUI::update()
{
	if (IsOFF)
	{
		return;
	}

	if (m_index == FIXED_TEX::TEXT_FIXED)
	{
		CPlayer* playernum = (CPlayer*)CSceneMgr::GetInst()->GetCurScene()->GetPlayer();

		levelnum = playernum->GetLevel();
		
		

	}
	else if (m_index == FIXED_TEX::INVENTORY_MESO)
	{
		CPlayer* player = (CPlayer*)CSceneMgr::GetInst()->GetCurScene()->GetPlayer();

		meso = player->GetMeso();
	}


	// 스타 UI 좌우로 움직여야함
	if (m_index == FIXED_TEX::STAR)
	{
		float offsetPosX = GetPos().x;

		

		if (offsetPosX < 0.f)
		{
			offsetPosX = 0.f;
			m_starDir = 1;
		}
		else if(offsetPosX > 160.f)
		{
			offsetPosX = 160.f;
			m_starDir = -1;
		}

		offsetPosX += m_starSpeed * fDT * m_starDir;

		SetPos(Vec2(offsetPosX, GetPos().y));
	}


	CUI::update();
}

void FixedUI::render(HDC _dc)
{
	if (IsOFF)
	{
		return;
	}

	if (m_index == FIXED_TEX::NONE)
	{

	}
	else if(m_index == FIXED_TEX::TEXT_FIXED)
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
		SetTextColor(_dc, 0xFFFFFFFF);
		HFONT oldfont, font;

		font = CreateFont(          // object의 생성
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

		oldfont = (HFONT)SelectObject(_dc, font);

		if (levelnum == 2)
		{

			int a = 0;
		}

		wstring PreStr = L"LV  ";
		wstring str = std::to_wstring(levelnum);
		PreStr += str;
		wstring BackStr = L"	   nonamed";
		PreStr += BackStr;



		TextOut(_dc, (int)vPos.x, (int)vPos.y, PreStr.c_str(), PreStr.length());
	}
	else if (m_index == FIXED_TEX::INVENTORY_MESO)
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
		SetTextColor(_dc, 0xFFFFFFFF);
		HFONT oldfont, font;

		font = CreateFont(          // object의 생성
			15,                  // 문자 폭
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

		oldfont = (HFONT)SelectObject(_dc, font);

		if (levelnum == 2)
		{

			int a = 0;
		}

		wstring PreStr = L"메소 :              ";
		wstring str = std::to_wstring(meso);
		wstring finalStr = PreStr + str;
	



		TextOut(_dc, (int)vPos.x, (int)vPos.y, finalStr.c_str(), finalStr.length());
	}
	else if (m_index == FIXED_TEX::SKILL1_TEXT)
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
		SetTextColor(_dc, 0xFFFFFFFF);
		HFONT oldfont, font;

		font = CreateFont(          // object의 생성
			15,                  // 문자 폭
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

		oldfont = (HFONT)SelectObject(_dc, font);

		RECT rect = { vPos.x,
				  vPos.y,
				  vPos.x + vScale.x,
				  vPos.y + vScale.y
		};

		wstring PreStr = L"캐논볼 \n";
		wstring str1 = std::to_wstring(skillpoint);
		wstring str2 = L" \\ 5";
		wstring str3 = str1 + str2;
		wstring Finalstr = PreStr + str3;
		DrawText(_dc, Finalstr.c_str(), Finalstr.length(), &rect, DT_WORDBREAK);
	}
	else if (m_index == FIXED_TEX::SKILL2_TEXT)
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
	SetTextColor(_dc, 0xFFFFFFFF);
	HFONT oldfont, font;

	font = CreateFont(          // object의 생성
		15,                  // 문자 폭
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

	oldfont = (HFONT)SelectObject(_dc, font);

	RECT rect = { vPos.x,
			  vPos.y,
			  vPos.x + vScale.x,
			  vPos.y + vScale.y
	};

	wstring PreStr = L"전함 노틸러스 \n";
	wstring str1 = std::to_wstring(skillpoint);
	wstring str2 = L" \\ 5";
	wstring str3 = str1 + str2;
	wstring Finalstr = PreStr + str3;
	DrawText(_dc, Finalstr.c_str(), Finalstr.length(), &rect, DT_WORDBREAK);
	}
	else if (m_index == FIXED_TEX::SKILL3_TEXT)
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
	SetTextColor(_dc, 0xFFFFFFFF);
	HFONT oldfont, font;

	font = CreateFont(          // object의 생성
		15,                  // 문자 폭
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

	oldfont = (HFONT)SelectObject(_dc, font);

	RECT rect = { vPos.x,
			  vPos.y,
			  vPos.x + vScale.x,
			  vPos.y + vScale.y
	};

	wstring PreStr = L"레인보우  \n";
	wstring str1 = std::to_wstring(skillpoint);
	wstring str2 = L" \\ 5";
	wstring str3 = str1 + str2;
	wstring Finalstr = PreStr + str3;
	DrawText(_dc, Finalstr.c_str(), Finalstr.length(), &rect, DT_WORDBREAK);
	}
	else if (m_index == FIXED_TEX::SKILL4_TEXT)
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
	SetTextColor(_dc, 0xFFFFFFFF);
	HFONT oldfont, font;

	font = CreateFont(          // object의 생성
		15,                  // 문자 폭
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

	oldfont = (HFONT)SelectObject(_dc, font);

	RECT rect = { vPos.x,
			  vPos.y,
			  vPos.x + vScale.x,
			  vPos.y + vScale.y
	};

	wstring PreStr = L"더블 점프 \n";
	wstring str1 = std::to_wstring(skillpoint);
	wstring str2 = L" \\ 5";
	wstring str3 = str1 + str2;
	wstring Finalstr = PreStr + str3;
	DrawText(_dc, Finalstr.c_str(), Finalstr.length(), &rect, DT_WORDBREAK);
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
		, texArr[(UINT)m_index]->GetDC()
		// bmp 파일 내에서 자를 좌상단
		, (int)0
		, (int)0
		, vScale.x
		, vScale.y
		, RGB(255, 0, 255));

	}

	CUI::render(_dc);
}

void FixedUI::MouseOn()
{
	if (IsOFF)
	{
		return;
	}
}

void FixedUI::MouseLbtnDown()
{
	if (IsOFF)
	{
		return;
	}

	if (m_index == FIXED_TEX::QUEST1_STEP1 ||
		m_index == FIXED_TEX::QUEST1_STEP2 ||
		m_index == FIXED_TEX::QUEST2_STEP1 ||
		m_index == FIXED_TEX::QUEST2_STEP2 ||
		m_index == FIXED_TEX::QUEST3_STEP1 ||
		m_index == FIXED_TEX::QUEST3_STEP2
		)
	{
		SetUIOFF(true);
	}
}


void FixedUI::MouseLbtnUp()
{

}