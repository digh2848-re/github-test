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

		// ���� ����
		SaveTileData();
	}

	if (KEY_TAP(KEY::F))
	{
		//CUIMgr::GetInst()->SetFocusedUI(m_pUI);

		// ���� ����
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
	//���ʹ�ư�� Ŭ���Ǿ������� ������
	if (KEY_TAP(KEY::LBTN))
	{

		// ���콺��ǥ�� ī�޶���ǥ(renderingPos)
		// �ű⿡ �ش��ϴ� ������ǥ�� ��ȯ�ؾ���
		Vec2 vMousePos = MOUSE_POS;
		vMousePos = CCamera::GetInst()->GetRealPos(vMousePos);

		int iTileX = (int)GetTileX();
		int iTileY = (int)GetTileY();

		int iCol = (int)vMousePos.x / TILE_SIZE;
		int iRow = (int)vMousePos.y / TILE_SIZE;

		// ���� ���� / ���� ���� ����ó��
		if (vMousePos.x < 0.f || iTileX <= iCol
			|| vMousePos.y < 0.f || iTileY <= iRow)
		{
			return;
		}

		UINT iIdx = iRow * iTileX + iCol;

		const vector<CObject*>& vecTile = GetGroupObject(GROUP_TYPE::TILE);
		// �ε��� ����
		((CTile*)vecTile[iIdx])->AddImgIdx();
	}


}

void CScene_Tool::Enter()
{
	/*
	// TOOL SCENE ���� ����� �޴��� ���δ�.
	CCore::GetInst()->DockingMenu();

	// Ÿ�� ����
	CreateTile(5, 5);

	// UI �ϳ� ������
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
	
	// �ڽ� UI �־��ְ�
	pPanelUI->AddChild(pBtnUI);

	// �θ� ���������� ȣ������
	// �� obj �׷츮��Ʈ���� �ֻ��� �θ𳢸��� ������
	AddObject(pPanelUI, GROUP_TYPE::UI);

	 // ���纻 UI
	 CUI* pClonePanel = pPanelUI->Clone();
	 pClonePanel->SetPos(pClonePanel->GetPos() + Vec2(-300.f,0.f));
	 // ���纻�� Ŭ���� ����ȯ �ǰ� �ϰ������
	 // ((CBtnUI*)pClonePanel->GetChildUI()[0])->SetClickedCallBack(&ChangeScene, 0, 0);
	 
	 AddObject(pClonePanel, GROUP_TYPE::UI);
	 
	 // Ư��Ű ������ ��Ŀ�� �غ�����
	 m_pUI = pClonePanel; 

	// Camera Look ����
	// �ػ� ���� ��ġ	
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
	ofn.nMaxFile = sizeof(szName);  //�迭�� ũ��
	ofn.lpstrFilter = L"ALL\0*.*\0Tile\0*.tile\0";  // �ƹ��̸�.�ƹ�Ȯ����
	ofn.nFilterIndex = 0; // ó�� ���Ͱ� 0��-> ALL
	ofn.lpstrFileTitle = nullptr;
	ofn.nMaxFileTitle = 0;

	//�ʱ� ���
	wstring strTileFolder = CPathMgr::GetInst()->GetContentPath();
	strTileFolder += L"tile";
	ofn.lpstrInitialDir = strTileFolder.c_str();
	
	ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;
	
	// ��� ���(���̾�α�)
	// ���� true ��� false
	if (GetSaveFileName(&ofn))
	{
		SaveTile(szName);
	}

}

void CScene_Tool::SaveTile(const wstring& _strFilePath)
{
	
	// ���� �����
	// 2����Ʈ ����
	// ���� �ڷ����� Ŀ�� ������Ʈ
	FILE* pFile = nullptr;
	_wfopen_s(&pFile, _strFilePath.c_str(),L"wb");

	// ���� ���� ����
	assert(pFile);

	// ������ ����
	
	// Ÿ�� ���� ���� ���� ����
	UINT xCount = GetTileX();
	UINT yCount = GetTileY();

	fwrite(&xCount, sizeof(UINT),1,pFile);
	fwrite(&yCount, sizeof(UINT), 1, pFile);

	const vector<CObject*>& vecTile = GetGroupObject(GROUP_TYPE::TILE);

	// ������ Ÿ�ϸ��� ������ ���������� �����ض�
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
	ofn.nMaxFile = sizeof(szName);  //�迭�� ũ��
	ofn.lpstrFilter = L"ALL\0*.*\0Tile\0*.tile\0";  // �ƹ��̸�.�ƹ�Ȯ����
	ofn.nFilterIndex = 0; // ó�� ���Ͱ� 0��-> ALL
	ofn.lpstrFileTitle = nullptr;
	ofn.nMaxFileTitle = 0;

	//�ʱ� ���
	wstring strTileFolder = CPathMgr::GetInst()->GetContentPath();
	strTileFolder += L"tile";
	ofn.lpstrInitialDir = strTileFolder.c_str();

	ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;

	// ��� ���(���̾�α�)
	// �ҷ����� true ��� false
	if (GetOpenFileName(&ofn))
	{
		// �ҷ������ scene ���� �ҷ��ü� �ֱ⶧���� ����η� �ؾ���
		// �����θ� ©�������
		wstring strRelativePath = CPathMgr::GetInst()->GetRelativePath(szName);
		LoadTile(strRelativePath);
	}
}


// ===================================================
// ��ưUI �߻��� �����Ҽ� �ִ� �Լ��������� �������� �з�
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
		if (LOWORD(wParam) == IDOK)  // ok ��ư
		{
			// ��ư�� ���� ���� �Է¹��� ����
			// ���� �Է� ���ް� ����ó��
			// �Էµ� ���� ������ ���� �Լ�
			UINT iXCount = GetDlgItemInt(hDlg, IDC_EDIT1, nullptr, false);
			UINT iYCount = GetDlgItemInt(hDlg, IDC_EDIT2, nullptr, false);

			// �ش� �Լ��� �����Լ��̱⶧���� ���Ŵ������� ����� ������ ����
			CScene* pCurScene = CSceneMgr::GetInst()->GetCurScene();

			// ToolScene Ȯ��
			CScene_Tool* pToolScene = dynamic_cast<CScene_Tool*>(pCurScene);
			assert(pToolScene);

			pToolScene->DeleteGroup(GROUP_TYPE::TILE);
			pToolScene->CreateTile(iXCount, iYCount);


			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		else if(LOWORD(wParam) == IDCANCEL)  // ��ҹ�ư
		{	// �ƹ��͵� ���ϰ� �����Ŵ
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}

		break;
	}
	return (INT_PTR)FALSE;
}