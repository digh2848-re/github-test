#include "pch.h"
#include "CEventMgr.h"

#include "CObject.h"
#include "CSceneMgr.h"
#include "CScene.h"

#include "AI.h"
#include "CState.h"

#include "CUIMgr.h"

CEventMgr::CEventMgr()
{

}


CEventMgr::~CEventMgr()
{

}

void CEventMgr::update()
{
	// dead 상태 벡터 비우기
	// ===================================================
	// 이전 프레임에서 등록해둔 Dead Object 들을 삭제한다.
	// ===================================================
	for (size_t i = 0; i < m_vecDead.size(); ++i)
	{
		delete m_vecDead[i];
	}
	m_vecDead.clear();


	// ==========
	// Event 처리
	// ==========

	for (size_t i = 0; i < m_vecEvent.size(); ++i)
	{
		Excute(m_vecEvent[i]);
	}

	m_vecEvent.clear();
}


void CEventMgr::Excute(const tEvent& _eve)
{
	switch (_eve.eEven)
	{
	case EVENT_TYPE::CREATE_OBJECT:
	{
		// lParam : Object Adress
		// wParam : Group Type
		CObject* pNewObj = (CObject*)_eve.lParam;
		GROUP_TYPE eType = (GROUP_TYPE)_eve.wParam;
		
		CSceneMgr::GetInst()->GetCurScene()->AddObject(pNewObj, eType);
	}
		break;
	case EVENT_TYPE::DELETE_OBJECT:
	{
		// lParam : Object Adress 삭제될 대상
		// Object 를 Dead 상태로 변경
		// 삭제예정 오브젝트들을 모아둔다.
		CObject* pDeadObj = (CObject*)_eve.lParam;

		// 같은 프레임에 똑같은 오브젝트 삭제처리 여러개가 들어올경우 예외처리
		if (!pDeadObj->IsDead())
		{
			pDeadObj->SetDead();
			m_vecDead.push_back(pDeadObj);
		}
		
	}
		break;
	case EVENT_TYPE::SCENE_CHANGE:
	{
		// IParam : Next Scene Type

		// 이벤트 시점에 호출한 뒤 실제로 씬을 바꿔주는 곳
		CSceneMgr::GetInst()->ChangeScene((SCENE_TYPE)_eve.lParam);

		// 씬 전환 일어날때 포커싱된 UI nullptr로 초기화
		CUIMgr::GetInst()->SetFocusedUI(nullptr);
	}
		break;
	case EVENT_TYPE::CHANCE_AI_STATE:
	{
		// IParam : AI
		// wParam : Next Type
		AI* pAI = (AI*)_eve.lParam;
		MON_STATE eNextState = (MON_STATE)_eve.wParam;

		pAI->ChangeState(eNextState);
	}
		break;
	}
}