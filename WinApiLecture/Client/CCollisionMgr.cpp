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
		// ���ϴ°� �����ϱ� ���ؼ� iCol�� �������� ROW�� ����
		for (UINT iCol = iRow; iCol < (UINT)GROUP_TYPE::END; iCol++)
		{
			if (m_arrCheck[iRow] & (1 << iCol))
			{
				CollisionGroupUpdate((GROUP_TYPE)iRow, (GROUP_TYPE)iCol);
			}
		}
	}
}

// ���� ���� �ش� �׷��� �浹 Ÿ���� �ָ� object ���͸� �޾ƿͼ� ���� ó��
void CCollisionMgr::CollisionGroupUpdate(GROUP_TYPE _eLeft, GROUP_TYPE _eRight)
{
	// ����� ���� �޾Ƽ�
	CScene* pCurScene = CSceneMgr::GetInst()->GetCurScene();

	// ���� ��ü�� �������·� ����
	const vector<CObject*>& vecLeft = pCurScene->GetGroupObject(_eLeft);
	const vector<CObject*>& vecRight = pCurScene->GetGroupObject(_eRight);


	map<ULONGLONG, bool>::iterator iter;

	for (size_t i = 0; i < vecLeft.size(); i++)
	{
		// �浹ü�� �������� �ʴ� ���
		if (vecLeft[i]->GetCollider() == nullptr)
			continue;

		for (size_t j = 0; j < vecRight.size(); j++)
		{
			// �浹ü�� ���ų�, �ڱ� �ڽŰ��� �浹�� ���
			if (vecRight[j]->GetCollider() == nullptr 
				|| vecLeft[i] == vecRight[j])
				continue;


			CCollider* pLeftCol = vecLeft[i]->GetCollider();
			CCollider* pRightCol = vecRight[j]->GetCollider();
			
			// ���� ������ flag �߰�

			// �� �浹ü ���� ���̵� ����
			// 4byte �� 4byte�� �����ؼ� �� 8byte
			COLLIDER_ID ID;
			ID.Left_id = pLeftCol->GetID();
			ID.Right_id = pRightCol->GetID();

			iter = m_mapColInfo.find(ID.ID);


			// �� �浹ü ó�� ������ ��� ( �� ��ü�� ��ϵ����� ����)
			// �� �浹 ������ �� ��� ������ ��� ���(�浹���� �ʾҴ� ��)
			if (m_mapColInfo.end() == iter)
			{
				// �� ���
				m_mapColInfo.insert(make_pair(ID.ID, false));

				// �ٽ� ã��
				iter = m_mapColInfo.find(ID.ID);
			}

			if(IsCollision(pLeftCol, pRightCol))
			{
				// 1. ���� �浹 ���̴�.

				if (iter->second)
				{
					// 1-1. ���� �����ӿ��� �浹 ���̴�.
					// �浹 ���� ������Ʈ �� �ϳ��� ������ �����̸�
					if (vecLeft[i]->IsDead() || vecRight[j]->IsDead())
					{						
						// �浹 ���� ����� ���־���Ѵ�
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
					// 1-2. ���� �����ӿ��� �浹���� ����
					// �浹 ���� ������Ʈ �� �ϳ��� ���� �ȵȴٸ�
					if (!vecLeft[i]->IsDead() && !vecRight[j]->IsDead())
					{
						pLeftCol->OnCollisionEnter(pRightCol);
						pRightCol->OnCollisionEnter(pLeftCol);
						iter->second = true;
					}
					else
					{
						// �浹�Ǵ� ������ �����Ǵ°��
						// �ʹ� �ƴٸ��� �´� ��Ȳ �׳� �浹ó�� ��������
						// �� �׳� �ƹ� �͵� ���� �Ƚ�Ŵ
						// �̰� ���� �������� (���� �ϳ� dead���·�) ���� �����ӿ��� �浹�����������ν� 2-1 / 1-1 case ���߿� �ϳ� ����
					}

					
				}

			}
			else
			{
				// 2. ���� �浹�ϰ� ���� �ʴ�.

				if (iter->second)
				{
					// 2-1. ���� �����ӿ� �浹�ϰ� �־���.
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
	// �� ���� ���� �׷� Ÿ���� ������,
	// ū ���� ��(��Ʈ)�� ���

	

	UINT iRow=(UINT)_eLeft;
	UINT iCol = (UINT)_eRight;

	//  ROW�� �۰��ϱ� ���ؼ� ��
	if (iCol < iRow)
	{
		iRow = (UINT)_eRight;
		iCol = (UINT)_eLeft;
	}

	// ��Ʈ�� ���
	if (m_arrCheck[iRow] & (1 << iCol))
	{	// �浹 ����
		m_arrCheck[iRow] &= ~(1 << iCol);
	}
	else
	{   // �浹 �ѱ�
		m_arrCheck[iRow] |= (1 << iCol);
	}

}


