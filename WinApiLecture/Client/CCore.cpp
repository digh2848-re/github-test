#include "pch.h"
#include "CCore.h"

#include "CTimeMgr.h"
#include "CKeyMgr.h"
#include "CSceneMgr.h"
#include "CObject.h"
#include "CPathMgr.h"
#include "CCollisionMgr.h"
#include "CEventMgr.h" 
#include "CCamera.h"
#include "CUIMgr.h"

#include "CResMgr.h"
#include "CTexture.h"
#include "SelectGDI.h"

#include "resource.h"
#include "CSound.h"
#include "CSoundMgr.h"

CCore::CCore()
	:m_hWnd(0)
	, m_ptResolution{}
	, m_hDC(0)
	, m_arrBrush{}
	, m_arrPen{}
{

}


CCore::~CCore()
{
	ReleaseDC(m_hWnd, m_hDC);


	for (int i = 0; i < (UINT)PEN_TYPE::END; ++i)
	{
		DeleteObject(m_arrPen[i]);
	}

	//메뉴 전체 삭제
	DestroyMenu(m_hMenu);

#ifdef _DEBUG

	FreeConsole();

#endif // _DEBUG

}



// 동적할당을 이용한 싱글톤
//CCore* CCore::g_pInst = nullptr;

int CCore::init(HWND _hWnd, POINT _ptResolution)
{
	m_hWnd = _hWnd;
	m_ptResolution = _ptResolution;


	// 해상도에 맞게 윈도우 크기 조정
	ChangeWindowSize(Vec2((float)_ptResolution.x, (float)_ptResolution.y) , false);

	// 메뉴바 생성
	m_hMenu = LoadMenu(nullptr, MAKEINTRESOURCEW(IDC_CLIENT));


	m_hDC = GetDC(m_hWnd);

	// 더블 버퍼링 용도의 비트맵과 DC 를 만든다.
	// 전체 픽셀 묶음 -> 비트맵 데이터

	
	//m_hDC = GetDC(m_hWnd);

	// 이중 버퍼링 용도의 텍스쳐 한장을 만든다.
	m_pMemTex = CResMgr::GetInst()->CreateTexture(L"BackBuffer",(UINT)m_ptResolution.x, (UINT)m_ptResolution.y);
	
	
	

	////  화면 DC와 호환성을 가지는 비트맵을 만듬
	//m_hBit = CreateCompatibleBitmap(m_hDC, m_ptResolution.x, m_ptResolution.y);
	//
	//// 내부적인 비트맵에 그릴수 잇는 DC가 필요
	//m_memDC = CreateCompatibleDC(m_hDC);
	//
	//// DC한테 만들어진 비트맵을 선택하라고 전달
	//// 반환값은 이전에 쓰던 비트맵
	//HBITMAP hOldBit = (HBITMAP)SelectObject(m_memDC, m_hBit);
	//
	//// 옛날 비트맵 제거해버림
	//DeleteObject(hOldBit);

	// 자주 사용 할 펜 및 브러쉬 생성
	CreateBrushPen();

	


	// Manager 초기화
	CPathMgr::GetInst()->init();
	CTimeMgr::GetInst()->init();
	CKeyMgr::GetInst()->init();
	CCamera::GetInst()->init();
	CSoundMgr::GetInst()->init();

	CResMgr::GetInst()->LoadSound(L"LEVEL_UP_SOUND1", L"sound\\hit.wav");
	CResMgr::GetInst()->LoadSound(L"LEVEL_UP_SOUND2", L"sound\\hit.wav");
	CResMgr::GetInst()->LoadSound(L"LEVEL_UP_SOUND3", L"sound\\hit.wav");
	CResMgr::GetInst()->LoadSound(L"LEVEL_UP_SOUND3", L"sound\\hit.wav");
	CResMgr::GetInst()->LoadSound(L"LEVEL_UP_SOUND4", L"sound\\hit.wav");
	CResMgr::GetInst()->LoadSound(L"LEVEL_UP_SOUND5", L"sound\\hit.wav");
	CResMgr::GetInst()->LoadSound(L"LEVEL_UP_SOUND6", L"sound\\hit.wav");
	CResMgr::GetInst()->LoadSound(L"LEVEL_UP_SOUND7", L"sound\\hit.wav");
	CResMgr::GetInst()->LoadSound(L"LEVEL_UP_SOUND8", L"sound\\hit.wav");
	CResMgr::GetInst()->LoadSound(L"LEVEL_UP_SOUND9", L"sound\\hit.wav");
	CResMgr::GetInst()->LoadSound(L"LEVEL_UP_SOUND10", L"sound\\hit.wav");
	CResMgr::GetInst()->LoadSound(L"LEVEL_UP_SOUND11", L"sound\\hit.wav");
	CResMgr::GetInst()->LoadSound(L"LEVEL_UP_SOUND12", L"sound\\hit.wav");
	CResMgr::GetInst()->LoadSound(L"LEVEL_UP_SOUND13", L"sound\\hit.wav");
	CResMgr::GetInst()->LoadSound(L"LEVEL_UP_SOUND14", L"sound\\hit.wav");
	CResMgr::GetInst()->LoadSound(L"LEVEL_UP_SOUND15", L"sound\\hit.wav");


	CResMgr::GetInst()->LoadSound(L"SUCCESS_SOUND", L"sound\\ForceSuccess.wav");
	CResMgr::GetInst()->LoadSound(L"FAIL_SOUND", L"sound\\ForceFail.wav");
	CResMgr::GetInst()->LoadSound(L"STAR_SOUND", L"sound\\ForceStar.wav");
	CResMgr::GetInst()->LoadSound(L"PORTAL_SOUND", L"sound\\Portal.wav");
	CResMgr::GetInst()->LoadSound(L"PICKUPITEM_SOUND", L"sound\\PickUpItem.wav");
	CResMgr::GetInst()->LoadSound(L"MOUSEOVER_SOUND", L"sound\\mouseover.wav");
	CResMgr::GetInst()->LoadSound(L"TOMB_SOUND", L"sound\\Tombstone.wav");
	CResMgr::GetInst()->LoadSound(L"LEVEL_UP_SOUND", L"sound\\levelup.wav");
	CResMgr::GetInst()->LoadSound(L"QUEST_ALERT_SOUND", L"sound\\QuestAlert.wav");
	CResMgr::GetInst()->LoadSound(L"QUEST_CLEAR_SOUND", L"sound\\QuestClear.wav");
	CResMgr::GetInst()->LoadSound(L"SKILL2_SOUND", L"sound\\skillsound.wav");
	CResMgr::GetInst()->LoadSound(L"SKILL3_SOUND", L"sound\\skill3.wav");

	// Sound 로드 테스트
	CResMgr::GetInst()->LoadSound(L"BGM_01", L"sound\\FunnyTimeMaker.wav");
	CResMgr::GetInst()->LoadSound(L"BGM_02", L"sound\\FantasticThinking.wav");
	CResMgr::GetInst()->LoadSound(L"BGM_03", L"sound\\LetsMarch.wav");
	CResMgr::GetInst()->LoadSound(L"BGM_04", L"sound\\DragonNest.wav");

	CSceneMgr::GetInst()->init();


#ifdef _DEBUG

	//if (::AllocConsole() == TRUE)
	//{
	//	FILE* nfp[3];
	//	freopen_s(nfp + 0, "CONOUT$", "rb", stdin);
	//	freopen_s(nfp + 1, "CONOUT$", "wb", stdout);
	//	freopen_s(nfp + 2, "CONOUT$", "wb", stderr);
	//	std::ios::sync_with_stdio();
	//}

#endif // _DEBUG



  	return S_OK; 
}


void CCore::progress()
{
	/*
	static int callcount = 0;
	++callcount;

	static int iPrevCount = GetTickCount();
	int iCurCount= GetTickCount();
	if (iCurCount - iPrevCount > 1000)
	{
		iPrevCount = iCurCount;
	}
	*/



	// ==============
	// Manager Update
	// ==============
	CTimeMgr::GetInst()->update();
	CKeyMgr::GetInst()->update();
	CCamera::GetInst()->update();

	// ============
	// Scene Update
	// ============
	CSceneMgr::GetInst()->update();

	// 충돌 체크
	CCollisionMgr::GetInst()->update();

	// UI 이벤트 체크
	CUIMgr::GetInst()->update();



	// =========
	// Rendering
	// =========
	// 화면 Clear
	Clear();
	
	CSceneMgr::GetInst()->render(m_pMemTex->GetDC());
	CCamera::GetInst()->render(m_pMemTex->GetDC());

	// 픽셀 단위로 비트맵 복사
	BitBlt(m_hDC, 0, 0, m_ptResolution.x, m_ptResolution.y
		, m_pMemTex->GetDC(), 0, 0, SRCCOPY);
	
	CTimeMgr::GetInst()->render();

	// ===============
	// 이벤트 지연처리
	// ===============
	CEventMgr::GetInst()->update();
}

void CCore::Clear()
{
	SelectGDI gdi(m_pMemTex->GetDC(), BRUSH_TYPE::BLACK);
	
	// 사각형 테두리가 펜으로 1픽셀 그려지기때문에 -1,+1해줌 
	Rectangle(m_pMemTex->GetDC(), -1, -1, m_ptResolution.x + 1, m_ptResolution.y + 1);


}

void CCore::CreateBrushPen()
{
	// hollow brush
	m_arrBrush[(UINT)BRUSH_TYPE::HOLLOW] = (HBRUSH)GetStockObject(HOLLOW_BRUSH);
	m_arrBrush[(UINT)BRUSH_TYPE::BLACK] = (HBRUSH)GetStockObject(BLACK_BRUSH);

	// red pen
	m_arrPen[(UINT)PEN_TYPE::RED] = CreatePen(PS_SOLID, 1, RGB(255, 0, 0));
	// green pen
	m_arrPen[(UINT)PEN_TYPE::GREEN] = CreatePen(PS_SOLID, 1, RGB(0, 255, 0));
	// blue pen
	m_arrPen[(UINT)PEN_TYPE::BLUE] = CreatePen(PS_SOLID, 1, RGB(0, 0, 255));


}


void CCore::DockingMenu()
{
	// TOOL SCENE 에서 사용할 메뉴를 붙인다.
	SetMenu( m_hWnd, m_hMenu);
	ChangeWindowSize(GetResolution(), true);
}

void CCore::DivideMenu()
{
	SetMenu(m_hWnd, nullptr);
	ChangeWindowSize(GetResolution(), true);
}


void CCore::ChangeWindowSize(Vec2 _vResolution, bool _bMenu)
{
	// 해상도에 맞게 윈도우 크기 조정
	RECT rt = { 0,0,_vResolution.x,_vResolution.y };
	::AdjustWindowRect(&rt, WS_OVERLAPPEDWINDOW, false);

	// 핸들 / 몰겟음 / 어느 기준으로(좌상단)  / 가로세로 길이 / flag
	SetWindowPos(m_hWnd, nullptr, 100, 100, rt.right - rt.left, rt.bottom - rt.top, 0);
}


