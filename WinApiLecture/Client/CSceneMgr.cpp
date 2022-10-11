#include "pch.h"
#include "CSceneMgr.h"
#include "CScene_Start.h"
#include "CScene_Tool.h"
#include "CScene_town.h"
#include "CEventMgr.h"
#include "CObject.h"
#include "Scene_Middle.h"
#include "Scene_Phase1.h"
#include "Scene_Phase2.h"


CSceneMgr::CSceneMgr()
	: m_arrScene{}
	, m_pCurScene(nullptr)
	, m_PlayerGroup(nullptr)
	, m_PetGroup(nullptr)
	, m_UIGroup(nullptr)
{
}


CSceneMgr::~CSceneMgr()
{
	// 씬 전부 삭제
	for (UINT i = 0; i < (UINT)SCENE_TYPE::END; ++i)
	{
		if (nullptr != m_arrScene[i])
		{
			delete m_arrScene[i];
		}
	}
}

void CSceneMgr::init()
{
	// Scene 생성
	m_arrScene[(UINT)SCENE_TYPE::START] = new CScene_Start;
	m_arrScene[(UINT)SCENE_TYPE::START]->SetName(L"Start_Scene");

	m_arrScene[(UINT)SCENE_TYPE::TOWN] = new CScene_town;
	m_arrScene[(UINT)SCENE_TYPE::TOWN]->SetName(L"Town_Scene");

	m_arrScene[(UINT)SCENE_TYPE::MIDDLE] = new Scene_Middle;
	m_arrScene[(UINT)SCENE_TYPE::MIDDLE]->SetName(L"Middle_Scene");

	m_arrScene[(UINT)SCENE_TYPE::BOSSSPHASE1] = new Scene_Phase1;
	m_arrScene[(UINT)SCENE_TYPE::BOSSSPHASE1]->SetName(L"Phase1_Scene");

	m_arrScene[(UINT)SCENE_TYPE::BOSSSPHASE2] = new Scene_Phase2;
	m_arrScene[(UINT)SCENE_TYPE::BOSSSPHASE2]->SetName(L"Phase2_Scene");

	// 현재 씬 지정
	m_pCurScene = m_arrScene[(UINT)SCENE_TYPE::START];
	m_pCurScene->Enter();

}

void CSceneMgr::update()
{
	m_pCurScene->update();

	m_pCurScene->finalupdate();	
}

void CSceneMgr::render(HDC _dc)
{
	m_pCurScene->render(_dc);
}


void CSceneMgr::ChangeScene(SCENE_TYPE _eNext)
{
	// 현재씬 벗어나기전 불러올 그룹들 저장해두고(MyDeleteAll에서 저장했음)
	m_pCurScene->Exit();

	m_pCurScene = m_arrScene[(UINT)_eNext];
	// 여기서 기존에 들고있던 그룹중 복사할거 해주고
	// 바뀌기전 씬 그룹벡터를 clear 해주기
	// 그리고 복사했으면 벡터 포인터들 nullptr로 다시 초기화 시키기
	
	// 1. 플레이어 복사후 이전씬 플레이어 벡터 clear 시켜주기
	m_pCurScene->AddObject((*m_PlayerGroup).front(), GROUP_TYPE::PLAYER);
	(*m_PlayerGroup).clear();

	// 2. 펫 전체 복사후 이전씬 펫벡터 clear 시켜주기
	if (m_PetGroup != nullptr)
	{
		vector<CObject*>::iterator iter1 = (*m_PetGroup).begin();
		for (; iter1 != (*m_PetGroup).end(); ++iter1)
		{
			m_pCurScene->AddObject((*iter1), GROUP_TYPE::PET);
		}
		(*m_PetGroup).clear();
	}
	

	// 3. UI그룹 전체 복사후 이전씬 UI벡터 clear 시켜주기
	vector<CObject*>::iterator iter2 = (*m_UIGroup).begin();
	for (; iter2 != (*m_UIGroup).end(); ++iter2)
	{
		m_pCurScene->AddObject((*iter2), GROUP_TYPE::UI);
	}
	(*m_UIGroup).clear();

	// 다 넣어준 다음에 그룹벡터를 가리키는 포인터들은 다음을 위해 다 nullptr로 초기화 시켜둠
	m_PlayerGroup = nullptr;
	m_PetGroup = nullptr;
	m_UIGroup = nullptr;


	m_pCurScene->Enter();
}