#include "pch.h"
#include "CCollisionMgr.h"

#include "CSceneMgr.h"
#include "CScene.h"
#include "CObject.h"
#include "CCollider.h"

CCollisionMgr::CCollisionMgr()
	: m_arrCheck{}
{
}


CCollisionMgr::~CCollisionMgr()
{

}



void CCollisionMgr::update()
{
	for (UINT iRow = 0; iRow < (UINT)GROUP_TYPE::END; iRow++)
	{
		// 다하는거 방지하기 위해서 iCol의 시작점을 ROW로 설정
		for (UINT iCol = iRow; iCol < (UINT)GROUP_TYPE::END; iCol++)
		{
			if (m_arrCheck[iRow] & (1 << iCol))
			{
				CollisionGroupUpdate((GROUP_TYPE)iRow, (GROUP_TYPE)iCol);
			}
		}
	}
}

// 현재 씬이 해당 그룹의 충돌 타입을 주면 object 벡터를 받아와서 로직 처리
void CCollisionMgr::CollisionGroupUpdate(GROUP_TYPE _eLeft, GROUP_TYPE _eRight)
{
	// 현재씬 정보 받아서
	CScene* pCurScene = CSceneMgr::GetInst()->GetCurScene();

	// 원본 자체를 참조형태로 받음
	const vector<CObject*>& vecLeft = pCurScene->GetGroupObject(_eLeft);
	const vector<CObject*>& vecRight = pCurScene->GetGroupObject(_eRight);


	map<ULONGLONG, bool>::iterator iter;

	for (size_t i = 0; i < vecLeft.size(); i++)
	{
		// 충돌체를 보유하지 않는 경우
		if (vecLeft[i]->GetCollider() == nullptr)
			continue;

		for (size_t j = 0; j < vecRight.size(); j++)
		{
			// 충돌체가 없거나, 자기 자신과의 충돌인 경우
			if (vecRight[j]->GetCollider() == nullptr 
				|| vecLeft[i] == vecRight[j])
				continue;


			CCollider* pLeftCol = vecLeft[i]->GetCollider();
			CCollider* pRightCol = vecRight[j]->GetCollider();
			
			// 이전 프레임 flag 추가

			// 두 충돌체 조합 아이디 생성
			// 4byte 씩 4byte씩 저장해서 총 8byte
			COLLIDER_ID ID;
			ID.Left_id = pLeftCol->GetID();
			ID.Right_id = pRightCol->GetID();

			iter = m_mapColInfo.find(ID.ID);


			// 두 충돌체 처음 조사한 경우 ( 맵 자체에 등록되지도 않음)
			// 즉 충돌 정보가 미 등록 상태인 경우 등록(충돌하지 않았다 로)
			if (m_mapColInfo.end() == iter)
			{
				// 맵 등록
				m_mapColInfo.insert(make_pair(ID.ID, false));

				// 다시 찾기
				iter = m_mapColInfo.find(ID.ID);
			}

			if(IsCollision(pLeftCol, pRightCol))
			{
				// 1. 현재 충돌 중이다.

				if (iter->second)
				{
					// 1-1. 이전 프레임에도 충돌 중이다.
					// 충돌 간의 오브젝트 중 하나라도 삭제될 예정이면
					if (vecLeft[i]->IsDead() || vecRight[j]->IsDead())
					{						
						// 충돌 중을 벗어나게 해주어야한다
						pLeftCol->OnCollisionExit(pRightCol);
						pRightCol->OnCollisionExit(pLeftCol);
						iter->second = false;
					}
					else
					{
						pLeftCol->OnCollision(pRightCol);
						pRightCol->OnCollision(pLeftCol);
					}
					
				}
				else
				{
					// 1-2. 이전 프레임에는 충돌하지 않음
					// 충돌 간의 오브젝트 중 하나라도 삭제 안된다면
					if (!vecLeft[i]->IsDead() && !vecRight[j]->IsDead())
					{
						pLeftCol->OnCollisionEnter(pRightCol);
						pRightCol->OnCollisionEnter(pLeftCol);
						iter->second = true;
					}
					else
					{
						// 충돌되는 시점에 삭제되는경우
						// 너무 아다리가 맞는 상황 그냥 충돌처리 하지말자
						// 즉 그냥 아무 것도 실행 안시킴
						// 이거 다음 프레임이 (둘중 하나 dead상태로) 이전 프레임에는 충돌하지않음으로써 2-1 / 1-1 case 둘중에 하나 나옴
					}

					
				}

			}
			else
			{
				// 2. 현재 충돌하고 있지 않다.

				if (iter->second)
				{
					// 2-1. 이전 프레임에 충돌하고 있었다.
					pLeftCol->OnCollisionExit(pRightCol);
					pRightCol->OnCollisionExit(pLeftCol);
					iter->second = false;
				}
				

			}
			
		}
	}


}

bool CCollisionMgr::IsCollision(CCollider* pLeftCol, CCollider* pRightCol)
{
	// 
	Vec2 vLeftPos = pLeftCol->GetFinalPos();
	Vec2 vLeftScale = pLeftCol->GetScale();

	Vec2 vRightPos = pRightCol->GetFinalPos();
	Vec2 vRightScale = pRightCol->GetScale();

	if (abs(vRightPos.x - vLeftPos.x) <= (vLeftScale.x + vRightScale.x) / 2.f
		&& abs(vRightPos.y - vLeftPos.y) <= (vLeftScale.y + vRightScale.y) / 2.f)
	{
		return true;
	}

	return false;
}

void CCollisionMgr::CheckGroup(GROUP_TYPE _eLeft, GROUP_TYPE _eRight)
{
	// 더 작은 값이 그룹 타입을 행으로,
	// 큰 값을 열(비트)로 사용

	

	UINT iRow=(UINT)_eLeft;
	UINT iCol = (UINT)_eRight;

	//  ROW를 작게하기 위해서 비교
	if (iCol < iRow)
	{
		iRow = (UINT)_eRight;
		iCol = (UINT)_eLeft;
	}

	// 비트열 계산
	if (m_arrCheck[iRow] & (1 << iCol))
	{	// 충돌 끄기
		m_arrCheck[iRow] &= ~(1 << iCol);
	}
	else
	{   // 충돌 켜기
		m_arrCheck[iRow] |= (1 << iCol);
	}

}


