#include "pch.h"
#include "Pet.h"
#include "CPlayer.h"

#include "CResMgr.h"
#include "CTexture.h"
#include "CCollider.h"
#include "CAnimator.h"
#include "CAnimation.h"
#include "CKeyMgr.h"
#include "CTimeMgr.h"

#include "CRigidBody.h"
#include "CGravity.h"
#include "Item.h"

Pet::Pet(Vec2 pos,CPlayer* _player)
	: m_eCurState(PET_STATE::IDLE)
	, m_ePreState(PET_STATE::WALK)
	, m_iCurDir(1)
	, m_iPreDir(1)
	, m_IsPetLadder(false)
	, m_IsTranport(false)
{
	SetPos(pos);
	my_player = _player;

	CreateCollider();
	GetCollider()->SetOffsetPos(Vec2(0.f, 0.f));
	GetCollider()->SetScale(Vec2(50.f, 50.f));

	CreateRigidBody();
	CreateGravity();

	// ������Ʈ �ִϸ����� ����
	CTexture* petidleleft = CResMgr::GetInst()->LoadTexture(L"PetLeftIdle", L"texture\\Pet\\Petwalkleft.bmp");
	CTexture* petidleright = CResMgr::GetInst()->LoadTexture(L"PetRightIdle", L"texture\\Pet\\Petwalkright.bmp");
	CTexture* petwalkleft = CResMgr::GetInst()->LoadTexture(L"PetLeftWalk", L"texture\\Pet\\Petwalkleft.bmp");
	CTexture* petwalkright = CResMgr::GetInst()->LoadTexture(L"PetRightWalk", L"texture\\Pet\\Petwalkright.bmp");
	CTexture* petjumpleft = CResMgr::GetInst()->LoadTexture(L"PetLeftJump", L"texture\\Pet\\Petjumpleft.bmp");
	CTexture* petjumpright = CResMgr::GetInst()->LoadTexture(L"PetRightJump", L"texture\\Pet\\Petjumpright.bmp");
	CTexture* petladder = CResMgr::GetInst()->LoadTexture(L"PetLadder", L"texture\\Pet\\Petladder.bmp");
	CTexture* petteleport = CResMgr::GetInst()->LoadTexture(L"PetTeleport", L"texture\\Pet\\Petteleport.bmp");

	CTexture* petdeerleft = CResMgr::GetInst()->LoadTexture(L"PetDeerLeft", L"texture\\Pet\\deer_left.bmp");
	CTexture* petdeerright = CResMgr::GetInst()->LoadTexture(L"PetDeerRight", L"texture\\Pet\\deer_right.bmp");


	CreateAnimator();

	GetAnimator()->CreateAnimation(L"PET_IDLE_LEFT", petidleleft, Vec2(0.f, 0.f), Vec2(37.f, 47.f), Vec2(37.f, 0.f), 0.1f, 6);
	GetAnimator()->CreateAnimation(L"PET_IDLE_RIGHT", petidleright, Vec2(0.f, 0.f), Vec2(37.f, 47.f), Vec2(37.f, 0.f), 0.1f, 6);
	GetAnimator()->CreateAnimation(L"PET_WALK_LEFT", petwalkleft, Vec2(0.f, 0.f), Vec2(37.f, 47.f), Vec2(37.f, 0.f), 0.1f, 6);
	GetAnimator()->CreateAnimation(L"PET_WALK_RIGHT", petwalkright, Vec2(0.f, 0.f), Vec2(37.f, 47.f), Vec2(37.f, 0.f), 0.1f, 6);
	GetAnimator()->CreateAnimation(L"PET_JUMP_LEFT", petjumpleft, Vec2(0.f, 0.f), Vec2(36.f, 44.f), Vec2(36.f, 0.f), 0.1f, 1);
	GetAnimator()->CreateAnimation(L"PET_JUMP_RIGHT", petjumpright, Vec2(0.f, 0.f), Vec2(36.f, 44.f), Vec2(36.f, 0.f), 0.1f, 1);
	GetAnimator()->CreateAnimation(L"PET_LADDER", petladder, Vec2(0.f, 0.f), Vec2(35.f, 44.f), Vec2(35.f, 0.f), 0.1f, 1);
	GetAnimator()->CreateAnimation(L"PET_TELEPORT", petteleport, Vec2(0.f, 0.f), Vec2(44.f, 44.f), Vec2(0.f, 44.f), 0.1f, 2);

	GetAnimator()->CreateAnimation(L"DEER_IDLE_LEFT", petdeerleft, Vec2(0.f, 0.f), Vec2(50.f, 50.f), Vec2(50.f, 0.f), 0.1f, 5);
	GetAnimator()->CreateAnimation(L"DEER_IDLE_RIGHT", petdeerright, Vec2(0.f, 0.f), Vec2(50.f, 50.f), Vec2(50.f, 0.f), 0.1f, 5);
	GetAnimator()->CreateAnimation(L"DEER_WALK_LEFT", petdeerleft, Vec2(0.f, 50.f), Vec2(50.f, 50.f), Vec2(50.f, 0.f), 0.1f, 3);
	GetAnimator()->CreateAnimation(L"DEER_WALK_RIGHT", petdeerright, Vec2(0.f, 50.f), Vec2(50.f, 50.f), Vec2(50.f, 0.f), 0.1f, 3);
	GetAnimator()->CreateAnimation(L"DEER_JUMP_LEFT", petdeerleft, Vec2(0.f, 100.f), Vec2(50.f, 50.f), Vec2(50.f, 0.f), 0.1f, 1);
	GetAnimator()->CreateAnimation(L"DEER_JUMP_RIGHT", petdeerright, Vec2(0.f, 100.f), Vec2(50.f, 50.f), Vec2(50.f, 0.f), 0.1f, 1);
	GetAnimator()->CreateAnimation(L"DEER_LADDER", petdeerleft, Vec2(0.f, 150.f), Vec2(50.f, 50.f), Vec2(50.f, 0.f), 0.1f, 1);
	GetAnimator()->CreateAnimation(L"DEER_TELEPORT", petdeerleft, Vec2(0.f, 100.f), Vec2(50.f, 50.f), Vec2(50.f, 0.f), 0.1f, 1);
}


Pet::~Pet()
{
}

void Pet::update()
{
	update_move();

	update_state();

	update_animation();
	

	//switch (m_eCurState)
	//{
	//case PET_STATE::IDLE:
	//{
	//	std::cout << "STATE : IDLE" << '\n';
	//	std::cout << "Direction : " << m_iCurDir << '\n';
	//}
	//break;
	//case PET_STATE::WALK:
	//{
	//	std::cout << "STATE : WALK" << '\n';
	//	std::cout << "Direction : " << m_iCurDir << '\n';
	//}
	//break;
	//case PET_STATE::JUMP:
	//{
	//	std::cout << "STATE : JUMP" << '\n';
	//	std::cout << "Direction : " << m_iCurDir << '\n';
	//}
	//break;
	//case PET_STATE::LADDER:
	//{
	//	std::cout << "STATE : LADDER" << '\n';
	//	std::cout << "Direction : " << m_iCurDir << '\n';
	//}
	//break;
	//case PET_STATE::TELEPORT:
	//{
	//	std::cout << "STATE : TELEPORT" << '\n';
	//	std::cout << "Direction : " << m_iCurDir << '\n';
	//}
	//break;
	//}
	//
	//Vec2 pos = GetPos();
	//std::cout << pos.x << "   " << pos.y << '\n';

	m_ePreState = m_eCurState;
	m_iPreDir = m_iCurDir;
}

void Pet::render(HDC _dc)
{
	component_render(_dc);
}

void Pet::update_move()
{
	CRigidBody* pRigid = GetRigidBody();

	Vec2 Playerpos = my_player->GetPos();
	Vec2 Petpos = GetPos();

	// �������ϴ� ����
	Vec2 Dir = Playerpos - Petpos;
		 Dir = Dir.Normalize();


	// ��ٸ� �켱
	// ���� �÷��̾ ��ٸ��� ź�ٸ�
	if (my_player->GetIsLadder())
	{
		m_IsPetLadder = true;
		m_IsLadder = true;
		
		
		SetPos(Playerpos);
	}
	else
	{
		// �÷��̾ ��ٸ����� ������������ ������Ű��
		if (m_IsPetLadder)
		{
			pRigid->SetVelocity(Vec2(my_player->GetRigidBody()->GetVelocity().x, my_player->GetRigidBody()->GetVelocity().y));
		}
		else
		{
			// y�� ����
			if (abs(Playerpos.y - Petpos.y) > 300.f || abs(Playerpos.x - Petpos.x) > 500.f)
			{
				m_IsTranport = true;
				SetPos(Playerpos);
			}
			else 
			{
				// ��� �÷��̾��� x�� �Ÿ��� �����̻� �־����� �÷��̾� ������ ����´�
				if (abs(Playerpos.x - Petpos.x) > 100.f)
				{
					pRigid->SetVelocity(Vec2(150.f * Dir.x, pRigid->GetVelocity().y));
					pRigid->AddForce(Vec2(200.f * Dir.x, 0.f));
				}
			}

		}
		
		m_IsLadder = false;
		m_IsPetLadder = false;
	}
	





}

void Pet::update_state()
{
	CRigidBody* pRigid = GetRigidBody();
	CGravity* pGravi = GetGravity();

	// ���� ������ ���� ���� ���鲨��
	switch (m_ePreState)
	{
	case PET_STATE::IDLE:
	{
		// ������ ��ٸ�ź�� üũ�Ǹ� �ٷ� ��ٸ����� 
		if (m_IsPetLadder == true)
		{
			m_eCurState = PET_STATE::LADDER;
		}
		else if(m_IsTranport==true)
		{
			m_eCurState = PET_STATE::TELEPORT;
		}
		else if ((pRigid->GetVelocity().x > 5.f || pRigid->GetVelocity().x < -5.f) &&
			(pRigid->GetVelocity().y < 1.f && pRigid->GetVelocity().y > -1.f))
		{
			m_eCurState = PET_STATE::WALK;

			// x�ӵ�üũ
			// x�ӵ�üũ
			if (pRigid->GetVelocity().x > 1.f)
			{
				m_iCurDir = 1;
			}
			else if (pRigid->GetVelocity().x < -1.f)
			{
				m_iCurDir = -1;
			}
		}
		else if (
			(pRigid->GetVelocity().y > 1.f && pRigid->GetVelocity().y < -1.f)
			)
		{
			m_eCurState = PET_STATE::JUMP;

			// x�ӵ�üũ
			if (pRigid->GetVelocity().x > 1.f)
			{
				m_iCurDir = 1;
			}
			else if (pRigid->GetVelocity().x < -1.f)
			{
				m_iCurDir = -1;
			}
		}
		else
		{
			m_eCurState = PET_STATE::IDLE;
		}
	}
		break;
	case PET_STATE::WALK:
	{
		// ������ ��ٸ�ź�� üũ�Ǹ� �ٷ� ��ٸ����� 
		if (m_IsPetLadder == true)
		{
			m_eCurState = PET_STATE::LADDER;
		}
		else if (m_IsTranport == true)
		{
			m_eCurState = PET_STATE::TELEPORT;
		}
		else if ((pRigid->GetVelocity().x < 5.f && pRigid->GetVelocity().x > -5.f))
		{
			m_eCurState = PET_STATE::IDLE;
		}
		else if (
			(pRigid->GetVelocity().y > 1.f && pRigid->GetVelocity().y < -1.f)
			)
		{
			m_eCurState = PET_STATE::JUMP;

			// x�ӵ�üũ
			if (pRigid->GetVelocity().x > 1.f)
			{
				m_iCurDir = 1;
			}
			else if (pRigid->GetVelocity().x < -1.f)
			{
				m_iCurDir = -1;
			}
		}
		else
		{
			m_eCurState = PET_STATE::WALK;

			// x�ӵ�üũ
			if (pRigid->GetVelocity().x > 1.f)
			{
				m_iCurDir = 1;
			}
			else if (pRigid->GetVelocity().x < -1.f)
			{
				m_iCurDir = -1;
			}
		}
	}
		break;
	case PET_STATE::JUMP:
	{
		// ������ ��ٸ�ź�� üũ�Ǹ� �ٷ� ��ٸ����� 
		if (m_IsPetLadder == true)
		{
			m_eCurState = PET_STATE::LADDER;
		}
		else if (m_IsTranport == true)
		{
			m_eCurState = PET_STATE::TELEPORT;
		}
		// JUMP -> IDLE ���� ���ҷ���
		else if (
			(pRigid->GetVelocity().y < 1.f && pRigid->GetVelocity().y > -1.f) &&
			(pRigid->GetVelocity().x < 0.01f && pRigid->GetVelocity().x > -0.01f)
			)
		{
			m_eCurState = PET_STATE::IDLE;
		}
		// JUMP -> WALK ���� ���ҷ���
		else if (
			(pRigid->GetVelocity().x > 1.f || pRigid->GetVelocity().x < -1.f) &&
			(pRigid->GetVelocity().y < 1.f && pRigid->GetVelocity().y > -1.f)
			)
		{
			m_eCurState = PET_STATE::WALK;

			// x�ӵ�üũ
			if (pRigid->GetVelocity().x > 1.f)
			{
				m_iCurDir = 1;
			}
			else if (pRigid->GetVelocity().x < -1.f)
			{
				m_iCurDir = -1;
			}
		}
		else
		{
			m_eCurState = PET_STATE::JUMP;

			// x�ӵ�üũ
			if (pRigid->GetVelocity().x > 1.f)
			{
				m_iCurDir = 1;
			}
			else if (pRigid->GetVelocity().x < -1.f)
			{
				m_iCurDir = -1;
			}
		}
	}
		break;
	case PET_STATE::LADDER:
	{
		if (m_IsPetLadder == true)
		{
			m_eCurState = PET_STATE::LADDER;
		}
		else if (
			(pRigid->GetVelocity().y < 1.f && pRigid->GetVelocity().y > -1.f)
			)
		{
			m_eCurState = PET_STATE::IDLE;
		}
		else
		{
			m_eCurState = PET_STATE::JUMP;

			// x�ӵ�üũ
			if (pRigid->GetVelocity().x > 1.f)
			{
				m_iCurDir = 1;
			}
			else if (pRigid->GetVelocity().x < -1.f)
			{
				m_iCurDir = -1;
			}
		}
	}
	break;
	case PET_STATE::TELEPORT:
	{
		m_eCurState = PET_STATE::JUMP;
		m_IsTranport = false;
	}
	break;
	}
}

void Pet::update_animation()
{
	// ���� ���¿� ���� ���°� �ٸ��� �ִϸ��̼� ����
	if (m_ePreState == m_eCurState && m_iCurDir == m_iPreDir)
	{
		return;
	}

	switch (m_eCurState)
	{
	case PET_STATE::IDLE:
	{
		if (-1 == m_iCurDir)
		{
			GetAnimator()->Play(L"DEER_IDLE_LEFT", true);
		}
		else
		{
			GetAnimator()->Play(L"DEER_IDLE_RIGHT", true);
		}
	}
	break;
	case PET_STATE::WALK:
	{
		if (-1 == m_iCurDir)
		{
			GetAnimator()->Play(L"DEER_WALK_LEFT", true);
		}
		else
		{
			GetAnimator()->Play(L"DEER_WALK_RIGHT", true);
		}
	}
	break;
	case PET_STATE::JUMP:
	{
		if (-1 == m_iCurDir)
		{
			GetAnimator()->Play(L"DEER_JUMP_LEFT", true);
		}
		else
		{
			GetAnimator()->Play(L"DEER_JUMP_RIGHT", true);
		}
	}
	break;
	case PET_STATE::LADDER:
	{
		GetAnimator()->Play(L"DEER_LADDER", true);
	}
	break;
	case PET_STATE::TELEPORT:
	{
		GetAnimator()->Play(L"DEER_TELEPORT", true);
	}
	break;
	}

}


void Pet::OnCollisionEnter(CCollider* _pOther)
{
	CObject* pOtherObj = _pOther->GetObj();

	// �����۰� �浹�ҋ�
	if (L"ItemMeso" == pOtherObj->GetName())
	{
		dynamic_cast<Item*>(pOtherObj)->SetIsEat(true);
	}
}

void Pet::OnCollision(CCollider* _pOther)
{
	CObject* pOtherObj = _pOther->GetObj();

	// �����۰� �浹�ҋ�
	if (L"ItemMeso" == pOtherObj->GetName())
	{
		dynamic_cast<Item*>(pOtherObj)->SetIsEat(true);
	}
}

void Pet::OnCollisionExit(CCollider* _pOther)
{

}