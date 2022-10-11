#include "pch.h"
#include "CIdleState.h"

#include "CSceneMgr.h"
#include "CScene.h"

#include "CPlayer.h"
#include "CMonster.h"
#include "CRigidBody.h"
#include "CTimeMgr.h"


CIdleState::CIdleState()
	: CState(MON_STATE::IDLE)
{
	m_repeatTime = 0.;
	change = -1;
}


CIdleState::~CIdleState()
{
}

void CIdleState::Enter()
{
	

}

void CIdleState::Exit()
{

}

void CIdleState::update()
{
	CPlayer* pPlayer = (CPlayer*)CSceneMgr::GetInst()->GetCurScene()->GetPlayer();

	// Player �� ��ġ üũ
	Vec2 vPlayerPos = pPlayer->GetPos();

	// ������ ���� �ȿ� ������ �������·� ��ȯ
	CMonster* pMonster = GetMonster();
	Vec2 vMonPos = pMonster->GetPos();

	tMonInfo tempInfo = pMonster->GetInfo();
	CRigidBody* pRigid = pMonster->GetRigidBody();


	Vec2 vDiff = vPlayerPos - vMonPos;
	float fLen = vDiff.Length();




	//// �÷��̾ ������ �νĹ��� ������ ����
	//// ���� ���������� ���������� �̺�Ʈ ó��
	//if (fLen < pMonster->GetInfo().m_fRecogRange)
	//{
	//	ChangeAIState(GetAI(), MON_STATE::TRACE); 
	//}
	
	// ���� �������� �ð��� m_fSpeed ��ŭ �̵�


	// normal monster�϶�
	m_repeatTime += fDT;

	if (m_repeatTime > tempInfo.m_MaxChangetime)
	{
		m_repeatTime = 0.;
		change *= -1;
	}


	if (change == 1)
	{
		vMonPos.x += fDT * tempInfo.m_fSpeed * tempInfo.m_iDir;

		float fDist = abs(tempInfo.m_vCenterPos.x - vMonPos.x) - tempInfo.m_fMaxDistance;

		if (fDist > 0.f)
		{
			tempInfo.m_iDir *= -1;
			vMonPos.x += fDist * tempInfo.m_iDir;
		}

		pMonster->SetCurState(MONSTER_STATE::WALK);
		pMonster->SetPos(vMonPos);
		pMonster->SetMonInfo(tempInfo);
	}
	else
	{
		pMonster->SetCurState(MONSTER_STATE::IDLE);
	}
	



	


}
