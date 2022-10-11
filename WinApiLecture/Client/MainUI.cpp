#include "pch.h"
#include "MainUI.h"

#include "CKeyMgr.h"
#include "CTexture.h"
#include "CResMgr.h"
#include "SelectGDI.h"

MainUI::MainUI()
	: CUI(false) // 카메라 영향 안받음
{
	m_mainUITex = CResMgr::GetInst()->LoadTexture(L"MainUI", L"texture\\mainUI.bmp");

}


MainUI::~MainUI()
{
}

void MainUI::update()
{
	CUI::update();
}

void MainUI::render(HDC _dc)
{
	

	// 텍스쳐 그리자
	//TransparentBlt(_dc
	//	// 실제 좌상단 위치와 크기
	//	, (int)vPos.x
	//	, (int)vPos.y
	//	, 1024
	//	, 93
	//	// 텍스쳐 정보
	//	, m_mainUITex->GetDC()
	//	// bmp 파일 내에서 자를 좌상단
	//	, (int)0
	//	, (int)0
	//	, (int)1024
	//	, (int)93
	//	, RGB(255, 255, 255));

	//BitBlt(_dc
	//	, (int)vPos.x
	//	, (int)vPos.y
	//	, 1024
	//	, 93
	//	,m_mainUITex->GetDC()
	//	,
	//	0, 0, SRCCOPY);


	//// child ui render


	CUI::render(_dc);
}

void MainUI::MouseOn()
{
	
}

void MainUI::MouseLbtnDown()
{

}


void MainUI::MouseLbtnUp()
{

}