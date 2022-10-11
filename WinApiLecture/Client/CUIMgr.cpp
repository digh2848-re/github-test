#include "pch.h"
#include "CUIMgr.h"

#include "CSceneMgr.h"
#include "CScene.h"
#include "CUI.h"

#include "CKeyMgr.h"
#include "CPanelUI.h"
#include "CBtnUI.h"

CUIMgr::CUIMgr()
	: m_pFocusedUI(nullptr)
{
}


CUIMgr::~CUIMgr()
{
}

void CUIMgr::update()
{
	// 1. FocusedUI 확인 (기존 것 / 새로운 것)

	// 이전에는 모든 UI다 가지고 이벤트 처리했음
	// 이제 포커싱된 UI만 가지고 갈꺼임
	// 즉 전체 벡터UI에서 포커싱 된 것을 찾아야함

	m_pFocusedUI = GetFocusedUI();

	// 허공 클릭시 예외처리
	if (!m_pFocusedUI)
	{
		return;
	}

	// 2. FocusedUI 내에서, 부모 UI 포함, 자식 UI들 중 실제 타켓팅 된 UI를 가져온다.

	// 낮은계층 싹다 확인한 후 타켓팅된 UI
	// 포커싱된 것이 바뀌면 안되기때문에 지역변수로
	
	CUI* pTargetUI = GetTargetedUI(m_pFocusedUI);
	
	//cout << pTargetUI << '\n';

	// 마우스 왼쪽버튼 막 눌럿는지
	bool bLbtnTap = KEY_TAP(KEY::LBTN);
	// 마우스 왼쪽버튼 딱 뗀 순간
	bool bLbtnAway = KEY_AWAY(KEY::LBTN);

	// 마우스 클릭에 관한 이벤트 함수 호출 해줄꺼임
	// 타켓팅 된거 없으면 안해도 됨
	if (nullptr != pTargetUI)
	{
		pTargetUI->MouseOn();

		// TAP이나 AWAY 둘다 공존할 수 없기 때문에
		if (bLbtnTap)
		{
			
			pTargetUI->MouseLbtnDown();
			// UI가 down 되었다고 체크한뒤
			pTargetUI->m_bLbtnDown = true;
		}
		else if (bLbtnAway)
		{
			pTargetUI->MouseLbtnUp();

			// 타켓 UI 이전에 DOWN된거 있었다면
			if (pTargetUI->m_bLbtnDown)
			{
				// 해당 UI에 클릭된거 이벤트 해줌
				pTargetUI->MouseLbtnClicked();
			}

			// 타켓팅된 UI만 이벤트함수때 false 하는 곳
			// 왼쪽버튼 떼면, 눌렸던 체크 다시 해제한다.
			pTargetUI->m_bLbtnDown = false;
		}
		
	}

}

// 특정 키 눌럿을때 해당 UI 강제적으로 포커싱 시킬때
void CUIMgr::SetFocusedUI(CUI* _pUI)
{
	

	// 1. 원래 있던 포커싱된 UI 일치하는 경우 
	// 2. 모든 포커싱 해제요청할때(nullptr 전달)
	// 아무것도 발생안함
	if (m_pFocusedUI == _pUI || _pUI == nullptr)
	{
		m_pFocusedUI = _pUI;
		return;
	}
	
	// 포커싱 세팅하구
	m_pFocusedUI = _pUI;



	// 씬에 있는 UI 그룹 얻어옴
	CScene* pCurScene = CSceneMgr::GetInst()->GetCurScene();

	// 이곳에는 모든 부모 UI가 들어있다
	vector<CObject*>& vecUI = pCurScene->GetUIGroup();


	vector<CObject*>::iterator iter = vecUI.begin();

	// 전체 벡터중에서
	for (; iter != vecUI.end(); ++iter)
	{
		// 특정 포커싱 UI만 찾아서
		if (m_pFocusedUI == *iter)
		{
			break;
		}
	}

	// 벡터 내에서 맨 뒤로 순번 교체
	vecUI.erase(iter);
	vecUI.push_back(m_pFocusedUI);

}

// 마우스 클릭으로 포커싱 전환
CUI* CUIMgr::GetFocusedUI()
{
	// 씬에 있는 UI 그룹 얻어옴
	CScene* pCurScene = CSceneMgr::GetInst()->GetCurScene();
	// 이곳에는 모든 부모 UI가 들어있다
	vector<CObject*>& vecUI = pCurScene->GetUIGroup();

	// 최소 포커싱 변화일어날려면 마우스 왼쪽버튼 눌러야함
	// 마우스 왼쪽버튼 막 눌럿는지
	bool bLbtnTap = KEY_TAP(KEY::LBTN);

	// 기존 포커싱 UI 를 받아두고 변경되었는지 확인한다.
	CUI* pFocusedUI = m_pFocusedUI;

	//  왼쪽 TAP 이벤트 발생하지않으면 기존 포커싱 유지
	if (!bLbtnTap)
	{
		return pFocusedUI;
	}

	// 왼쪽 TAP이 발생했다는 전제하

	// 단 허공에 클릭했을 경우(전체 UI들중 아무도 포커싱된게 없을때)
	vector<CObject*>::iterator targetiter = vecUI.end();
	vector<CObject*>::iterator iter = vecUI.begin();

	for (; iter != vecUI.end(); ++iter)
	{
		// UI 꺼진거 체크해줌
		//if (dynamic_cast<CPanelUI*>(*iter)->GetIsOFF())
		//{
		//	continue;
		//}

		// 일단 UI위에 올라온것만 후보로 둔다
		if (((CUI*)* iter)->IsMouseOn())
		{
			// 차례로 타켓팅 이터레이터 바꿔줌
			targetiter = iter;
		}
	}

	// 예외처리
	// 이번에 Focus 된 UI 가 없다
	if (targetiter == vecUI.end())
	{
		return nullptr;
	}

	// 최종 타켓팅 포커스 UI에 등록
	pFocusedUI = (CUI*)(*targetiter);

	// 벡터 내에서 맨 뒤로 순번 교체
	vecUI.erase(targetiter);
	vecUI.push_back(pFocusedUI);

	return pFocusedUI;
}





// 부모로부터 자식을 UI를 찾아줄꺼임
// 즉 우선순위가 가장 낮은 자식에 있으니깐 targeting 계속 바뀜
CUI* CUIMgr::GetTargetedUI(CUI* _pParentUI)
{
	bool bLbtnAway = KEY_AWAY(KEY::LBTN);


	// 1. 부모 UI 포함, 모든 자식들을 검사 한다.
	// 검사하는 순서가 중요 ( level 순회)
	// 큐역할을 할 리스트 사용
	CUI* pTargetUI = nullptr;


	// 컨테이너 맨날 쓸꺼니깐 매번 생성못하게 static 하자
	static list<CUI*> queue;

	// 타켓이 바뀐거 이전 UI나 비타켓 UI 왼쪽버튼 뗄경우 flag체크
	static vector<CUI*> vecNoneTarget;

	// static이니깐 이전프레임꺼 싹다 비우고
	queue.clear();
	vecNoneTarget.clear();

	queue.push_back(_pParentUI);

	while (!queue.empty())
	{
		// 큐에서 데이터 하나 꺼내기
		CUI* pUI = queue.front();
		queue.pop_front();

		// 큐에서 꺼내온 UI 가 TargetUI 인지 확인
		// 2. 타켓 UI 둘 중, 더 우선순위가 높은 기준은 더 낮은 계층의 자식 UI
		if (pUI->IsMouseOn())
		{

			// 일단 임시방편( 자식 둘다 버튼 UI이고 상위부모가 같은경우)
			if (dynamic_cast<CBtnUI*>(pTargetUI) &&
				dynamic_cast<CBtnUI*>(pUI) &&
				pTargetUI->GetParent() == pUI->GetParent()
				)
			{
				// 그중에서 드래그하는게 우선순위 되어야함
				if (dynamic_cast<CBtnUI*>(pTargetUI)->GetDrag())
				{
					vecNoneTarget.push_back(pUI);
				}
				else
				{
					// 타켓팅UI가 처음엔 nullptr이니깐 요건 제외하고
					// 타켓팅 변경될시 이전에꺼 벡터에 넣음
					if (nullptr != pTargetUI)
					{
						vecNoneTarget.push_back(pTargetUI);
					}

					// 이게 타켓인가? 일단 상위계층에서 체크해둠
					// while문 다 돌고나면 결국 낮은계층으로 세팅됨
					pTargetUI = pUI;
				}

			}
			else // 아니면 원래 로직대로 처리
			{
				// 타켓팅UI가 처음엔 nullptr이니깐 요건 제외하고
				// 타켓팅 변경될시 이전에꺼 벡터에 넣음
				if (nullptr != pTargetUI)
				{
					vecNoneTarget.push_back(pTargetUI);
				}

				// 이게 타켓인가? 일단 상위계층에서 체크해둠
				// while문 다 돌고나면 결국 낮은계층으로 세팅됨
				pTargetUI = pUI;
			}
			
		}
		else // 모든 UI 다 체크해야하는 것들
		{

			// 비타켓팅 일단 넣음
			vecNoneTarget.push_back(pUI);
		}
		
		
		// 밑에 자식들 다 큐에 넣을꺼임
		const vector<CUI*>& vecChild = pUI->GetChildUI();
		
		for (size_t i = 0; i < vecChild.size(); i++)
		{
			queue.push_back(vecChild[i]);
		}


	}


	// 왼쪽버튼 떼면, 눌렸던 체크 다시 해제한다.
	if (bLbtnAway)
	{
		// 최종 타켓팅된거 빼고 다 떼질경우 눌렷던 체크 다 해제
		for (size_t i = 0; i < vecNoneTarget.size(); i++)
		{
			vecNoneTarget[i]->m_bLbtnDown = false;
		}
	}

	

	return pTargetUI;
}