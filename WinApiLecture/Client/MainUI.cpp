#include "pch.h"
#include "MainUI.h"

#include "CKeyMgr.h"
#include "CTexture.h"
#include "CResMgr.h"
#include "SelectGDI.h"

MainUI::MainUI()
	: CUI(false) // ī�޶� ���� �ȹ���
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
	

	// �ؽ��� �׸���
	//TransparentBlt(_dc
	//	// ���� �»�� ��ġ�� ũ��
	//	, (int)vPos.x
	//	, (int)vPos.y
	//	, 1024
	//	, 93
	//	// �ؽ��� ����
	//	, m_mainUITex->GetDC()
	//	// bmp ���� ������ �ڸ� �»��
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