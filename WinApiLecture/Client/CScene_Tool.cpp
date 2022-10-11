#include "pch.h"
#include "CScene_Tool.h"
#include "CKeyMgr.h"
#include "CTile.h"
#include "CCore.h"
#include "CResMgr.h"
#include "CSceneMgr.h"
#include "CPathMgr.h"

#include "resource.h"

#include "CUIMgr.h"
#include "CPanelUI.h"
#include "CBtnUI.h"

void ChangeScene(DWORD_PTR, DWORD_PTR);

CScene_Tool::CScene_Tool()
	: m_pUI(nullptr)
{
}


CScene_Tool::~CScene_Tool()
{
}


void CScene_Tool::update()
{
	
	CScene::update();

	SetTileIdx();

	if (KEY_TAP(KEY::B))
	{
		//CUIMgr::GetInst()->SetFocusedUI(m_pUI);

		// 파일 저장
		SaveTileData();
	}

	if (KEY_TAP(KEY::F))
	{
		//CUIMgr::GetInst()->SetFocusedUI(m_pUI);

		// 파일 저장
		//LoadTile(L"tile\\Test.tile");
		LoadTileData();
	}

	if (KEY_TAP(KEY::E))
	{
		CUIMgr::GetInst()->SetFocusedUI(m_pUI);
	}

}

void CScene_Tool::SetTileIdx()
{
	//왼쪽버튼이 클릭되었을때만 수행함
	if (KEY_TAP(KEY::LBTN))
	{

		// 마우스좌표는 카메라좌표(renderingPos)
		// 거기에 해당하는 실제좌표로 전환해야함
		Vec2 vMousePos = MOUSE_POS;
		vMousePos = CCamera::GetInst()->GetRealPos(vMousePos);

		int iTileX = (int)GetTileX();
		int iTileY = (int)GetTileY();

		int iCol = (int)vMousePos.x / TILE_SIZE;
		int iRow = (int)vMousePos.y / TILE_SIZE;

		// 행의 범위 / 열의 범위 예외처리
		if (vMousePos.x < 0.f || iTileX <= iCol
			|| vMousePos.y < 0.f || iTileY <= iRow)
		{
			return;
		}

		UINT iIdx = iRow * iTileX + iCol;

		const vector<CObject*>& vecTile = GetGroupObject(GROUP_TYPE::TILE);
		// 인덱스 증가
		((CTile*)vecTile[iIdx])->AddImgIdx();
	}


}

void CScene_Tool::Enter()
{
	/*
	// TOOL SCENE 에서 사용할 메뉴를 붙인다.
	CCore::GetInst()->DockingMenu();

	// 타일 생성
	CreateTile(5, 5);

	// UI 하나 만들어보기
	Vec2 vResolution = CCore::GetInst()->GetResolution();

	CUI* pPanelUI = new CPanelUI;
	pPanelUI->SetName(L"ParentUI");
	pPanelUI->SetScale(Vec2(300.f, 150.f));
	pPanelUI->SetPos(Vec2( vResolution.x - pPanelUI->GetScale().x, 0.f));
	
	
	CBtnUI* pBtnUI = new CBtnUI;
	pBtnUI->SetName(L"ChildUI");
	pBtnUI->SetScale(Vec2(100.f, 40.f));
	pBtnUI->SetPos(Vec2(0.f, 0.f));
	pBtnUI->SetClickedCallBack(this,(SCENE_MEMFUNC)&CScene_Tool::SaveTileData);
	
	// 자식 UI 넣어주고
	pPanelUI->AddChild(pBtnUI);

	// 부모가 계층적으로 호출해줌
	// 즉 obj 그룹리스트에선 최상위 부모끼리만 존재함
	AddObject(pPanelUI, GROUP_TYPE::UI);

	 // 복사본 UI
	 CUI* pClonePanel = pPanelUI->Clone();
	 pClonePanel->SetPos(pClonePanel->GetPos() + Vec2(-300.f,0.f));
	 // 복사본만 클릭시 씬전환 되게 하고싶을떄
	 // ((CBtnUI*)pClonePanel->GetChildUI()[0])->SetClickedCallBack(&ChangeScene, 0, 0);
	 
	 AddObject(pClonePanel, GROUP_TYPE::UI);
	 
	 // 특정키 눌릴떄 포커싱 해볼려고
	 m_pUI = pClonePanel; 

	// Camera Look 지정
	// 해상도 절반 위치	
	CCamera::GetInst()->SetLookAt(vResolution / 2.f);

	*/

}

void CScene_Tool::Exit()
{
	CCore::GetInst()->DivideMenu();

	DeleteAll();
}

void CScene_Tool::SaveTileData()
{
	OPENFILENAME ofn = {};

	wchar_t szName[256] = {};

	ofn.lStructSize = sizeof(OPENFILENAME);
	ofn.hwndOwner = CCore::GetInst()->GetMainHwnd();
	ofn.lpstrFile = szName;
	ofn.nMaxFile = sizeof(szName);  //배열의 크기
	ofn.lpstrFilter = L"ALL\0*.*\0Tile\0*.tile\0";  // 아무이름.아무확장자
	ofn.nFilterIndex = 0; // 처음 필터값 0번-> ALL
	ofn.lpstrFileTitle = nullptr;
	ofn.nMaxFileTitle = 0;

	//초기 경로
	wstring strTileFolder = CPathMgr::GetInst()->GetContentPath();
	strTileFolder += L"tile";
	ofn.lpstrInitialDir = strTileFolder.c_str();
	
	ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;
	
	// 모달 방식(다이얼로그)
	// 저장 true 취소 false
	if (GetSaveFileName(&ofn))
	{
		SaveTile(szName);
	}

}

void CScene_Tool::SaveTile(const wstring& _strFilePath)
{
	
	// 파일 입출력
	// 2바이트 오픈
	// 파일 자료형도 커널 오브젝트
	FILE* pFile = nullptr;
	_wfopen_s(&pFile, _strFilePath.c_str(),L"wb");

	// 파일 열기 실패
	assert(pFile);

	// 데이터 저장
	
	// 타일 가로 세로 개수 저장
	UINT xCount = GetTileX();
	UINT yCount = GetTileY();

	fwrite(&xCount, sizeof(UINT),1,pFile);
	fwrite(&yCount, sizeof(UINT), 1, pFile);

	const vector<CObject*>& vecTile = GetGroupObject(GROUP_TYPE::TILE);

	// 각각의 타일마다 저장할 정보있으면 저장해라
	for (size_t i = 0; i < vecTile.size(); i++)
	{
		((CTile*)vecTile[i])->Save(pFile);
	}

	fclose(pFile);

}


void CScene_Tool::LoadTileData()
{
	OPENFILENAME ofn = {};

	wchar_t szName[256] = {};

	ofn.lStructSize = sizeof(OPENFILENAME);
	ofn.hwndOwner = CCore::GetInst()->GetMainHwnd();
	ofn.lpstrFile = szName;
	ofn.nMaxFile = sizeof(szName);  //배열의 크기
	ofn.lpstrFilter = L"ALL\0*.*\0Tile\0*.tile\0";  // 아무이름.아무확장자
	ofn.nFilterIndex = 0; // 처음 필터값 0번-> ALL
	ofn.lpstrFileTitle = nullptr;
	ofn.nMaxFileTitle = 0;

	//초기 경로
	wstring strTileFolder = CPathMgr::GetInst()->GetContentPath();
	strTileFolder += L"tile";
	ofn.lpstrInitialDir = strTileFolder.c_str();

	ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;

	// 모달 방식(다이얼로그)
	// 불러오기 true 취소 false
	if (GetOpenFileName(&ofn))
	{
		// 불러오기는 scene 마다 불러올수 있기때문에 상대경로로 해야함
		// 절대경로를 짤라줘야함
		wstring strRelativePath = CPathMgr::GetInst()->GetRelativePath(szName);
		LoadTile(strRelativePath);
	}
}


// ===================================================
// 버튼UI 발생시 저장할수 있는 함수포인터의 내용으로 분류
// ===================================================

void ChangeScene(DWORD_PTR, DWORD_PTR)
{
	ChangeScene(SCENE_TYPE::START);
}

// ======================
// Tile Count Window Proc
// ======================

INT_PTR CALLBACK TileCountProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
		return (INT_PTR)TRUE;

	case WM_COMMAND:
		if (LOWORD(wParam) == IDOK)  // ok 버튼
		{
			// 버튼이 눌린 순간 입력받은 숫자
			// 글자 입력 못받게 예외처리
			// 입력된 숫자 가지고 오는 함수
			UINT iXCount = GetDlgItemInt(hDlg, IDC_EDIT1, nullptr, false);
			UINT iYCount = GetDlgItemInt(hDlg, IDC_EDIT2, nullptr, false);

			// 해당 함수는 전역함수이기때문에 씬매니저에서 현재씬 가지고 오자
			CScene* pCurScene = CSceneMgr::GetInst()->GetCurScene();

			// ToolScene 확인
			CScene_Tool* pToolScene = dynamic_cast<CScene_Tool*>(pCurScene);
			assert(pToolScene);

			pToolScene->DeleteGroup(GROUP_TYPE::TILE);
			pToolScene->CreateTile(iXCount, iYCount);


			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		else if(LOWORD(wParam) == IDCANCEL)  // 취소버튼
		{	// 아무것도 안하고 종료시킴
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}

		break;
	}
	return (INT_PTR)FALSE;
}