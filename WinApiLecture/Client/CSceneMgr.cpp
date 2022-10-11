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
	// �� ���� ����
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
	// Scene ����
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

	// ���� �� ����
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
	// ����� ������� �ҷ��� �׷�� �����صΰ�(MyDeleteAll���� ��������)
	m_pCurScene->Exit();

	m_pCurScene = m_arrScene[(UINT)_eNext];
	// ���⼭ ������ ����ִ� �׷��� �����Ұ� ���ְ�
	// �ٲ���� �� �׷캤�͸� clear ���ֱ�
	// �׸��� ���������� ���� �����͵� nullptr�� �ٽ� �ʱ�ȭ ��Ű��
	
	// 1. �÷��̾� ������ ������ �÷��̾� ���� clear �����ֱ�
	m_pCurScene->AddObject((*m_PlayerGroup).front(), GROUP_TYPE::PLAYER);
	(*m_PlayerGroup).clear();

	// 2. �� ��ü ������ ������ �꺤�� clear �����ֱ�
	if (m_PetGroup != nullptr)
	{
		vector<CObject*>::iterator iter1 = (*m_PetGroup).begin();
		for (; iter1 != (*m_PetGroup).end(); ++iter1)
		{
			m_pCurScene->AddObject((*iter1), GROUP_TYPE::PET);
		}
		(*m_PetGroup).clear();
	}
	

	// 3. UI�׷� ��ü ������ ������ UI���� clear �����ֱ�
	vector<CObject*>::iterator iter2 = (*m_UIGroup).begin();
	for (; iter2 != (*m_UIGroup).end(); ++iter2)
	{
		m_pCurScene->AddObject((*iter2), GROUP_TYPE::UI);
	}
	(*m_UIGroup).clear();

	// �� �־��� ������ �׷캤�͸� ����Ű�� �����͵��� ������ ���� �� nullptr�� �ʱ�ȭ ���ѵ�
	m_PlayerGroup = nullptr;
	m_PetGroup = nullptr;
	m_UIGroup = nullptr;


	m_pCurScene->Enter();
}