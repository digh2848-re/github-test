#include "pch.h"
#include "CMonFactory.h"

#include "CMonster.h"
#include "AI.h"

#include "CIdleState.h"
#include "CTraceState.h"

#include "CRigidBody.h"

CMonster* CMonFactory::CreateMonster(MON_TYPE _eType, Vec2 _vPos, int n)
{
	CMonster* pMon = nullptr;

	switch (_eType)
	{
	case MON_TYPE::NORMAL:
	{
		if (n == -1)
		{
			pMon = new CMonster;
			pMon->SetPos(_vPos);

			// 몬스터 정보 세팅
			tMonInfo info = {};
			info.m_fAtt = 10.f;
			info.m_fAttRnagle = 50.f;
			info.m_fRecogRange = 100.f;
			info.m_fHp = 20.f;
			info.m_fSpeed = 50.f;
			info.m_vCenterPos = _vPos;

			// 150 200 사이
			info.m_fMaxDistance = rand() % 50 + 150.f;

			if (rand() % 2 == 0)
			{
				info.m_iDir = 1;
			}
			else
			{
				info.m_iDir = -1;
			}



			info.m_MaxChangetime = rand() % 5 + 3.;


			pMon->SetMonInfo(info);

			pMon->CreateRigidBody();
			pMon->GetRigidBody()->SetMass(1.f);


			AI* pAI = new AI;
			pAI->AddState(new CIdleState);
			pAI->AddState(new CTraceState);
			pAI->SetCurState(MON_STATE::IDLE);


			pMon->SetAI(pAI);
		}
		else
		{
			pMon = new CMonster(1);
			pMon->SetPos(_vPos);

			// 몬스터 정보 세팅
			tMonInfo info = {};
			info.m_fAtt = 10.f;
			info.m_fAttRnagle = 50.f;
			info.m_fRecogRange = 100.f;
			info.m_fHp = 20.f;
			info.m_fSpeed = 50.f;
			info.m_vCenterPos = _vPos;

			// 150 200 사이
			info.m_fMaxDistance = rand() % 50 + 150.f;

			if (rand() % 2 == 0)
			{
				info.m_iDir = 1;
			}
			else
			{
				info.m_iDir = -1;
			}



			info.m_MaxChangetime = rand() % 5 + 3.;


			pMon->SetMonInfo(info);

			pMon->CreateRigidBody();
			pMon->GetRigidBody()->SetMass(1.f);


			AI* pAI = new AI;
			pAI->AddState(new CIdleState);
			pAI->AddState(new CTraceState);
			pAI->SetCurState(MON_STATE::IDLE);


			pMon->SetAI(pAI);
		}
		

	}
		break;
	case MON_TYPE::RANGE:

		break;
	}

	assert(pMon);

	return pMon;
}

