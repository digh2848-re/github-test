#include "pch.h"
#include "CPlayer.h"

#include "CSceneMgr.h"
#include "CScene.h"
#include "CKeyMgr.h"
#include "CTimeMgr.h" 

#include "CMissile.h"

#include "CResMgr.h"
#include "CTexture.h"
#include "CCollider.h"
#include "CAnimator.h"
#include "CAnimation.h"

#include "CRigidBody.h"
#include "CGravity.h"
#include "Skill.h"
#include "Skill2.h"
#include "Skill3.h"
#include "LevelSkill.h"
#include "WideSkill.h"
#include "Item.h"

#include "Pet.h"
#include "CSound.h"
#include "Tomb.h"
#include "CUI.h"

#include "PlayerDamageEffect.h"

CPlayer::CPlayer()
	: m_eCurState(PLAYER_STATE::IDLE)
	, m_ePrevState(PLAYER_STATE::WALK)
	, m_iCurDir(1)
	, m_iPreDir(1)
	, m_IsInJury(false)
	, InjureTime(0.)
	, curWearState(PlayerWearState::NO_WEAR)  // �ؽ��� �ٲٱ����� ����
	, changeWear(false)
	, jumpDelay(false)
	, m_Level(1)
	, m_Exp(0)
	, m_MaxExp(20)
	, m_mypet1(nullptr)
	, m_HP(100)
	, IsDead(false)
	, DeadSize(Vec2(43.f,69.f))
	, m_Meso(30000)
{
	// Texture �ε��ϱ�
	//m_pTex=CResMgr::GetInst()->LoadTexture(L"PlayerTex", L"texture\\Player.bmp");

	// ������Ʈ �ݶ��̴� ����
	CreateCollider();
	GetCollider()->SetOffsetPos(Vec2(0.f, 0.f));
	GetCollider()->SetScale(Vec2(50.f,70.f));

	CreateRigidBody();

	// ������Ʈ �ִϸ����� ����
	CTexture* pLeftTex = CResMgr::GetInst()->LoadTexture(L"PlayerLeftIdle", L"texture\\Player\\basic_left.bmp");
	CTexture* pRightTex = CResMgr::GetInst()->LoadTexture(L"PlayerRightIdle", L"texture\\Player\\basic_right.bmp");
	CTexture* pWeaponLeftTex = CResMgr::GetInst()->LoadTexture(L"PlayerWeaponLeft", L"texture\\Player\\weapon_left.bmp");
	CTexture* pWeaponRightTex = CResMgr::GetInst()->LoadTexture(L"PlayerWeaponRight", L"texture\\Player\\weapon_right.bmp");
	CTexture* pAllLeftTex = CResMgr::GetInst()->LoadTexture(L"PlayerAllLeft", L"texture\\Player\\allwear_left.bmp");
	CTexture* pAllRightTex = CResMgr::GetInst()->LoadTexture(L"PlayerAllRight", L"texture\\Player\\allwear_right.bmp");
	DeadTex = CResMgr::GetInst()->LoadTexture(L"PlayerDead", L"texture\\Player\\PlayerDead.bmp");

	//CTexture* test = CResMgr::GetInst()->LoadTexture(L"Test", L"texture\\skill.bmp");
	

	CreateAnimator();
	
	//GetAnimator()->CreateAnimation(L"TEST", test, Vec2(0.f, 0.f), Vec2(600.f, 398.f), Vec2(600.f, 0.f), 0.07f, 31);


	GetAnimator()->CreateAnimation(L"IDLE_LEFT", pLeftTex, Vec2(0.f, 0.f), Vec2(100.f, 100.f), Vec2(100.f, 0.f), 0.2f, 4);
	GetAnimator()->CreateAnimation(L"IDLE_RIGHT", pRightTex, Vec2(0.f, 0.f), Vec2(100.f, 100.f), Vec2(100.f, 0.f), 0.2f, 4);
	GetAnimator()->CreateAnimation( L"WALK_LEFT", pLeftTex, Vec2(0.f, 100.f), Vec2(100.f, 100.f), Vec2(100.f, 0.f), 0.2f, 4);
	GetAnimator()->CreateAnimation(L"WALK_RIGHT", pRightTex, Vec2(0.f, 100.f), Vec2(100.f, 100.f), Vec2(100.f, 0.f), 0.2f, 4);
	GetAnimator()->CreateAnimation(L"JUMP_LEFT", pLeftTex, Vec2(0.f, 200.f), Vec2(100.f, 100.f), Vec2(100.f, 0.f), 0.2f, 1);
	GetAnimator()->CreateAnimation(L"JUMP_RIGHT", pRightTex, Vec2(0.f, 200.f), Vec2(100.f, 100.f), Vec2(100.f, 0.f), 0.2f, 1);
	GetAnimator()->CreateAnimation(L"LADDER", pLeftTex, Vec2(0.f, 900.f), Vec2(100.f, 100.f), Vec2(100.f, 0.f), 0.2f, 2);
	
	GetAnimator()->CreateAnimation(L"WEAPON_IDLE_LEFT", pWeaponLeftTex, Vec2(0.f, 0.f), Vec2(100.f, 100.f), Vec2(100.f, 0.f), 0.2f, 4);
	GetAnimator()->CreateAnimation(L"WEAPON_IDLE_RIGHT", pWeaponRightTex, Vec2(0.f, 0.f), Vec2(100.f, 100.f), Vec2(100.f, 0.f), 0.2f, 4);
	GetAnimator()->CreateAnimation(L"WEAPON_WALK_LEFT", pWeaponLeftTex, Vec2(0.f, 100.f), Vec2(100.f, 100.f), Vec2(100.f, 0.f), 0.2f, 4);
	GetAnimator()->CreateAnimation(L"WEAPON_WALK_RIGHT", pWeaponRightTex, Vec2(0.f, 100.f), Vec2(100.f, 100.f), Vec2(100.f, 0.f), 0.2f, 4);
	GetAnimator()->CreateAnimation(L"WEAPON_JUMP_LEFT", pWeaponLeftTex, Vec2(0.f, 200.f), Vec2(100.f, 100.f), Vec2(100.f, 0.f), 0.2f, 1);
	GetAnimator()->CreateAnimation(L"WEAPON_JUMP_RIGHT", pWeaponRightTex, Vec2(0.f, 200.f), Vec2(100.f, 100.f), Vec2(100.f, 0.f), 0.2f, 1);
	GetAnimator()->CreateAnimation(L"WEAPON_LADDER", pWeaponLeftTex, Vec2(0.f, 900.f), Vec2(100.f, 100.f), Vec2(100.f, 0.f), 0.2f, 2);

	GetAnimator()->CreateAnimation(L"ALL_IDLE_LEFT", pAllLeftTex, Vec2(0.f, 0.f), Vec2(100.f, 100.f), Vec2(100.f, 0.f), 0.2f, 4);
	GetAnimator()->CreateAnimation(L"ALL_IDLE_RIGHT", pAllRightTex, Vec2(0.f, 0.f), Vec2(100.f, 100.f), Vec2(100.f, 0.f), 0.2f, 4);
	GetAnimator()->CreateAnimation(L"ALL_WALK_LEFT", pAllLeftTex, Vec2(0.f, 100.f), Vec2(100.f, 100.f), Vec2(100.f, 0.f), 0.2f, 4);
	GetAnimator()->CreateAnimation(L"ALL_WALK_RIGHT", pAllRightTex, Vec2(0.f, 100.f), Vec2(100.f, 100.f), Vec2(100.f, 0.f), 0.2f, 4);
	GetAnimator()->CreateAnimation(L"ALL_JUMP_LEFT", pAllLeftTex, Vec2(0.f, 200.f), Vec2(100.f, 100.f), Vec2(100.f, 0.f), 0.2f, 1);
	GetAnimator()->CreateAnimation(L"ALL_JUMP_RIGHT", pAllRightTex, Vec2(0.f, 200.f), Vec2(100.f, 100.f), Vec2(100.f, 0.f), 0.2f, 1);
	GetAnimator()->CreateAnimation(L"ALL_LADDER", pAllLeftTex, Vec2(0.f, 900.f), Vec2(100.f, 100.f), Vec2(100.f, 0.f), 0.2f, 2);

	
	// �߷� ������Ʈ ����
	CreateGravity();

	//GetAnimator()->Play(L"WALK_RIGHT", true);

	//CAnimation* pAnim = GetAnimator()->FindAnimation(L"WALK_LEFT");
	//
	//// ��ü ������ offset 100�ø�
	//for(UINT i=0;i<pAnim->GetMaxFrame();i++)
	//	pAnim->GetFrame(i).vOffset = Vec2(0.f, -100.f);


	m_levelupSound = CResMgr::GetInst()->FindSound(L"LEVEL_UP_SOUND");
	m_tombSound = CResMgr::GetInst()->FindSound(L"TOMB_SOUND");
}


CPlayer::~CPlayer()
{
	
}

void CPlayer::SetWearState(PlayerWearState _curWearState)
{
	curWearState = _curWearState;
	changeWear = true;

	// �ؽ��� �ٲܶ����� ��ٸ�Ÿ�°� �ٲ������
	//GetAnimator()->SetIsLadderStop(false);
}


void CPlayer::update()
{

	// �� �����Ӹ��� ����Ű ���ȴ��� �ʱ�ȭ ������
	m_IspushLadder = false;

	// Dead����üũ
	if (m_HP <= 0)
	{
		// ������ ���ѹ� y������ ��¦ �ø�
		if (!IsDead)
		{

			// ���� �̹��� ����
			Vec2 pos = GetPos();
			CObject* pTomb = new Tomb(pos);
			pTomb->SetName(L"pTomb");
			CreateObject(pTomb, GROUP_TYPE::TOMB);

			// �Ҹ�����
			m_tombSound->Play();
			m_tombSound->SetVolume(100.f);

			// UI ���� ��Ŀ���ؾ���
			vector<CObject*>& groupvec = (CSceneMgr::GetInst()->GetCurScene())->GetUIGroup();

			vector<CObject*>::iterator it = groupvec.begin();

			for (; it != groupvec.end(); ++it)
			{
				if ((*it)->GetName() == L"MainDeadUI")
				{
					((CUI*)(*it))->SetUIOFF(false);
				}
			}

		}

		IsDead = true;

 

	}
	else // �������� �ϴ� �͵�
	{


		// �λ󵿾� ��������
		if (m_IsInJury)
		{
			

			InjureTime += fDT;

			if (InjureTime > 2.0)
			{
				m_IsInJury = false;
				InjureTime = 0.;
				m_eCurState = PLAYER_STATE::IDLE;
			}
		}

		// ����ġ ����
		// ������
		if (m_Exp > m_MaxExp)
		{
			m_Level++;
			m_Exp = 0;
			// ���ݺ��� 1.5�� ����ġ�� �� Ŀ����
			m_MaxExp = m_MaxExp + m_MaxExp / 2;

			m_levelupSound->Play();
			m_levelupSound->SetVolume(80.f);
			// ������ ��ų
			CreateLevelSkill();
		}

		update_move();

		update_state();

		//GetAnimator()->Play(L"TEST", true);
		update_animation();



		if (KEY_TAP(KEY::B))
		{
			SetPos(Vec2(5450.f, 920.f));
		}

		GetAnimator()->update();

		// �������� �񱳸� ���� ���� ( update�� �� �������� ��)
	// �浹���� lateupdate�� ���� ��ȭ�� �߻��ϸ� ���� �����Ӷ� update_animation�� �ɸ��� ��
		m_ePrevState = m_eCurState;
		m_iPreDir = m_iCurDir;
	}
	

	



	/*
#ifdef _DEBUG

	switch (m_eCurState)
	{
	case PLAYER_STATE::IDLE:
	{
		std::cout << "STATE : IDLE" << '\n';
		std::cout << "Direction : " << m_iCurDir << '\n';
	}
	break;
	case PLAYER_STATE::WALK:
	{
		std::cout << "STATE : WALK" << '\n';
		std::cout << "Direction : " << m_iCurDir << '\n';
	}
	break;
	case PLAYER_STATE::JUMP:
	{
		std::cout << "STATE : JUMP" << '\n';
		std::cout << "Direction : " << m_iCurDir << '\n';
	}
	break;
	case PLAYER_STATE::LADDER:
	{
		std::cout << "STATE : LADDER" << '\n';
		std::cout << "Direction : " << m_iCurDir << '\n';
	}
	break;
	case PLAYER_STATE::INJURE:
	{
		std::cout << "STATE : INJURE" << '\n';
		std::cout << "Direction : " << m_iCurDir << '\n';
	}
	break;
	}
	
#endif
	CRigidBody* pRigid = GetRigidBody();
	std::cout << "velocity : " << pRigid->GetVelocity().x << "      " << pRigid->GetVelocity().y << '\n';
	*/

}


void CPlayer::update_move()
{
	if (KEY_TAP(KEY::U))
	{
		CreateMoveSkill();
	}

	if (KEY_TAP(KEY::I))
	{
		CreateWideSkill();
	}

	if (KEY_TAP(KEY::O))
	{
		CreateSkill3();
	}

	 //�λ�����̸� �����Ӹ� �ƴ϶� �ٸ� ������ �ȵ�
	if (m_IsInJury)
	{
		return;
	}

	// ���� �������� ���� �������ִ� ������� �� ����
	CRigidBody* pRigid = GetRigidBody();

	if (KEY_TAP(KEY::F))
	{
		// FŰ���������� �浹�ߴ��� ���޴��� üũ�Ҳ���
		m_IspushLadder = true;
	}



	if (KEY_TAP(KEY::P))
	{
		CreatePet();
	}


	if (!m_IsLadder)
	{
		// �¿�� ������
		if (KEY_HOLD(KEY::A))
		{
			pRigid->AddForce(Vec2(-200.f, 0.f));
		}

		if (KEY_HOLD(KEY::D))
		{
			pRigid->AddForce(Vec2(200.f, 0.f));
		}

		if (KEY_TAP(KEY::A))
		{
			pRigid->SetVelocity(Vec2(-100.f, pRigid->GetVelocity().y));
		}

		if (KEY_TAP(KEY::D))
		{
			pRigid->SetVelocity(Vec2(100.f, pRigid->GetVelocity().y));
		}

		// ����Ű �Է�
		if (KEY_TAP(KEY::SPACE))
		{
			if (m_ePrevState == PLAYER_STATE::JUMP)
			{
				if (!jumpDelay)
				{
					// �̴����� ��ų
					if (m_iPreDir == 1)
					{
						pRigid->SetMaxVelocity(Vec2(520.f, 600.f));
						pRigid->SetVelocity(Vec2(520.f, -400.f));
					}
					else
					{
						pRigid->SetMaxVelocity(Vec2(520.f, 600.f));
						pRigid->SetVelocity(Vec2(-520.f, -400.f));
					}

					CreateJumpSkill();
					jumpDelay = true;
				}
			}
			else
			{
				pRigid->SetVelocity(Vec2(GetRigidBody()->GetVelocity().x, -400.f));
			}
		}
	}
	else // ��ٸ� Ÿ�� ������
	{
		if (KEY_HOLD(KEY::W))
		{
			// ������ٵ� �������� Y�� ��ȭ����
			Vec2 pos = GetPos();
			pos.y -= 100.f* fDT;
			SetPos(Vec2(pos.x,pos.y));
			GetAnimator()->SetIsLadderStop(false);
		}
		else if (KEY_HOLD(KEY::S))
		{
			// ������ٵ� �������� Y�� ��ȭ����
			Vec2 pos = GetPos();
			pos.y += 100.f* fDT;
			SetPos(Vec2(pos.x, pos.y));
			GetAnimator()->SetIsLadderStop(false);
		}
		else
		{
			GetAnimator()->SetIsLadderStop(true);
		}
		

		// ����Ű �Է�
		if (KEY_TAP(KEY::SPACE))
		{
			if (KEY_TAP(KEY::D) || KEY_HOLD(KEY::D))
			{
				pRigid->SetVelocity(Vec2(100.f, -200.f));
				m_IsLadder = false;
			}
			else if (KEY_TAP(KEY::A) || KEY_HOLD(KEY::A))
			{
				pRigid->SetVelocity(Vec2(-100.f, -200.f));
				m_IsLadder = false;
			}
			
		}

		
	}
	

}


void CPlayer::update_state()
{
	// ���� Ű�� ���� ���� ���? �ϴ� �״�� ��

	// �λ������� ����üũ���ϰ� �Ѿ��
	if (m_IsInJury)
	{
		m_eCurState = PLAYER_STATE::INJURE;
		return;
	}

	CRigidBody* pRigid = GetRigidBody();
	CGravity* pGravi = GetGravity();
	
	// ���� ������ ���� ���� ���鲨��
	switch (m_ePrevState)
	{
	case PLAYER_STATE::IDLE:
	{
		// ������ ��ٸ�ź�� üũ�Ǹ� �ٷ� ��ٸ����� 
		if (m_IsLadder == true)
		{
			m_eCurState = PLAYER_STATE::LADDER;
		}
		// walk ���·� ����
		// ����� y���� 0��ó�̰�  x�� �ӵ��� 0 ��ó�� �ƴϸ�( WALK�� ����)
		else if ((pRigid->GetVelocity().x > 5.f || pRigid->GetVelocity().x < -5.f) &&
			(pRigid->GetVelocity().y < 1.f && pRigid->GetVelocity().y > -1.f) )
		{
			m_eCurState = PLAYER_STATE::WALK;

			
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
		// jump ���·� ����
		// y�ุ �׶��� ���°� false �ν� ���������ӿ� �浹�� ���԰ų�(�ϴ� ����) / y�� �ӵ��� 0��ó�� �ƴϸ�
		else if (pGravi->GetGround() == false ||
			(pRigid->GetVelocity().y > 1.f && pRigid->GetVelocity().y < -1.f)
			)
		{
			m_eCurState = PLAYER_STATE::JUMP;

			// x�ӵ�üũ
			if (pRigid->GetVelocity().x > 1.f)
			{
				m_iCurDir = 1;
			}
			else if(pRigid->GetVelocity().x < -1.f)
			{
				m_iCurDir = -1;
			}

		}
		else
		{
			m_eCurState = PLAYER_STATE::IDLE;
		}
		
	}
		break;
	case PLAYER_STATE::WALK:
	{
		// ������ ��ٸ�ź�� üũ�Ǹ� �ٷ� ��ٸ����� 
		if (m_IsLadder == true)
		{
			m_eCurState = PLAYER_STATE::LADDER;
		}
		else if ((pRigid->GetVelocity().x < 5.f && pRigid->GetVelocity().x > -5.f))
		{
			m_eCurState = PLAYER_STATE::IDLE;
		}
		else if (pGravi->GetGround() == false ||
			(pRigid->GetVelocity().y > 1.f && pRigid->GetVelocity().y < -1.f)
			)
		{
			m_eCurState = PLAYER_STATE::JUMP;

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
			m_eCurState = PLAYER_STATE::WALK;

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
	case PLAYER_STATE::JUMP:
	{
		// ������ ��ٸ�ź�� üũ�Ǹ� �ٷ� ��ٸ����� 
		if (m_IsLadder == true)
		{
			m_eCurState = PLAYER_STATE::LADDER;
			jumpDelay = false;
		}
		// JUMP -> IDLE ���� ���ҷ���
		else if (
			(pRigid->GetVelocity().y < 1.f && pRigid->GetVelocity().y > -1.f) &&
			(pRigid->GetVelocity().x < 0.01f && pRigid->GetVelocity().x > -0.01f)
			)
		{
			pRigid->SetMaxVelocity(Vec2(200.f, 600.f));
			jumpDelay = false;
			m_eCurState = PLAYER_STATE::IDLE;
		}
		// JUMP -> WALK ���� ���ҷ���
		else if (
			(pRigid->GetVelocity().x > 1.f || pRigid->GetVelocity().x < -1.f) &&
			(pRigid->GetVelocity().y < 1.f && pRigid->GetVelocity().y > -1.f)
			)
		{
			pRigid->SetMaxVelocity(Vec2(200.f, 600.f));
			jumpDelay = false;
			m_eCurState = PLAYER_STATE::WALK;

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
			m_eCurState = PLAYER_STATE::JUMP;

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
	case PLAYER_STATE::LADDER:
	{
		if (m_IsLadder == true)
		{
			m_eCurState = PLAYER_STATE::LADDER;
		}
		else if(
			(pRigid->GetVelocity().y < 1.f && pRigid->GetVelocity().y > -1.f)
			)
		{
			m_eCurState = PLAYER_STATE::IDLE;
		}
		else
		{
			m_eCurState = PLAYER_STATE::JUMP;

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
	}

	
}

void CPlayer::update_animation()
{
	// ���� ���¿� ���� ���°� �ٸ��� �ִϸ��̼� ����
	if (m_ePrevState == m_eCurState && m_iCurDir == m_iPreDir)
	{
		// ���ܻ�Ȳ �λ��Ծ����� ���� / ���Դ»��� �ٲ��
		if (m_IsInJury || changeWear )
		{
			changeWear = false;
		}
		else
		{
			return;
		}

	}


	switch (m_eCurState)
	{
	case PLAYER_STATE::IDLE:
	{
		switch (curWearState)
		{
		case PlayerWearState::NO_WEAR:
		{
			if (-1 == m_iCurDir)
			{
				GetAnimator()->Play(L"IDLE_LEFT", true);
			}
			else
			{
				GetAnimator()->Play(L"IDLE_RIGHT", true);
			}

		}
			break;
		case PlayerWearState::WEAPON_WEAR:
		{
			if (-1 == m_iCurDir)
			{
				GetAnimator()->Play(L"WEAPON_IDLE_LEFT", true);
			}
			else
			{
				GetAnimator()->Play(L"WEAPON_IDLE_RIGHT", true);
			}

		}
			break;
		case PlayerWearState::ALL_WEAR:
		{
			if (-1 == m_iCurDir)
			{
				GetAnimator()->Play(L"ALL_IDLE_LEFT", true);
			}
			else
			{
				GetAnimator()->Play(L"ALL_IDLE_RIGHT", true);
			}

		}
			break;
		}
	}
	break;
	case PLAYER_STATE::WALK:
	{

		switch (curWearState)
		{
		case PlayerWearState::NO_WEAR:
		{
			if (-1 == m_iCurDir)
			{
				GetAnimator()->Play(L"WALK_LEFT", true);
			}
			else
			{
				GetAnimator()->Play(L"WALK_RIGHT", true);
			}
		}
			break;
		case PlayerWearState::WEAPON_WEAR:
		{
			if (-1 == m_iCurDir)
			{
				GetAnimator()->Play(L"WEAPON_WALK_LEFT", true);
			}
			else
			{
				GetAnimator()->Play(L"WEAPON_WALK_RIGHT", true);
			}
		}
			break;
		case PlayerWearState::ALL_WEAR:
		{
			if (-1 == m_iCurDir)
			{
				GetAnimator()->Play(L"ALL_WALK_LEFT", true);
			}
			else
			{
				GetAnimator()->Play(L"ALL_WALK_RIGHT", true);
			}
		}
			break;
		}

		
	}
	break;
	case PLAYER_STATE::JUMP:
	{
		m_eCurState = PLAYER_STATE::JUMP;

		//if (GetRigidBody())
		//{
		//	GetRigidBody()->AddVelocity(Vec2(0.f, -200.f));
		//}

		switch (curWearState)
		{
		case PlayerWearState::NO_WEAR:
		{
			if (-1 == m_iCurDir)
			{
				GetAnimator()->Play(L"JUMP_LEFT", true);
			}
			else
			{
				GetAnimator()->Play(L"JUMP_RIGHT", true);
			}
		}
			break;
		case PlayerWearState::WEAPON_WEAR:
		{
			if (-1 == m_iCurDir)
			{
				GetAnimator()->Play(L"WEAPON_JUMP_LEFT", true);
			}
			else
			{
				GetAnimator()->Play(L"WEAPON_JUMP_RIGHT", true);
			}
		}
			break;
		case PlayerWearState::ALL_WEAR:
		{
			if (-1 == m_iCurDir)
			{
				GetAnimator()->Play(L"ALL_JUMP_LEFT", true);
			}
			else
			{
				GetAnimator()->Play(L"ALL_JUMP_RIGHT", true);
			}
		}
			break;
		}

		
	}
	break;
	case PLAYER_STATE::LADDER:
	{
		switch (curWearState)
		{
		case PlayerWearState::NO_WEAR:
			GetAnimator()->Play(L"LADDER", true);
			break;
		case PlayerWearState::WEAPON_WEAR:
			GetAnimator()->Play(L"WEAPON_LADDER", true);
			break;
		case PlayerWearState::ALL_WEAR:
			GetAnimator()->Play(L"ALL_LADDER", true);
			break;
		}

		
	}
	break;
	case PLAYER_STATE::INJURE:
	{
		CRigidBody* pRigid = GetRigidBody();

		if (GetGravity()->GetGround() == true || 
			(pRigid->GetVelocity().y < 10.f && pRigid->GetVelocity().y > -10.f)
			)
		{

			switch (curWearState)
			{
			case PlayerWearState::NO_WEAR:
			{
				if (-1 == m_iCurDir)
				{
					GetAnimator()->Play(L"IDLE_LEFT", true);
				}
				else
				{
					GetAnimator()->Play(L"IDLE_RIGHT", true);
				}
			}
				break;
			case PlayerWearState::WEAPON_WEAR:
			{
				if (-1 == m_iCurDir)
				{
					GetAnimator()->Play(L"WEAPON_IDLE_LEFT", true);
				}
				else
				{
					GetAnimator()->Play(L"WEAPON_IDLE_RIGHT", true);
				}
			}
				break;
			case PlayerWearState::ALL_WEAR:
			{
				if (-1 == m_iCurDir)
				{
					GetAnimator()->Play(L"ALL_IDLE_LEFT", true);
				}
				else
				{
					GetAnimator()->Play(L"ALL_IDLE_RIGHT", true);
				}
			}
				break;
			}
		}
		else
		{
			switch (curWearState)
			{
			case PlayerWearState::NO_WEAR:
			{
				if (-1 == m_iCurDir)
				{
					GetAnimator()->Play(L"JUMP_LEFT", true);
				}
				else
				{
					GetAnimator()->Play(L"JUMP_RIGHT", true);
				}
			}
				break;
			case PlayerWearState::WEAPON_WEAR:
			{
				if (-1 == m_iCurDir)
				{
					GetAnimator()->Play(L"WEAPON_JUMP_LEFT", true);
				}
				else
				{
					GetAnimator()->Play(L"WEAPON_JUMP_RIGHT", true);
				}
			}
				break;
			case PlayerWearState::ALL_WEAR:
			{
				if (-1 == m_iCurDir)
				{
					GetAnimator()->Play(L"ALL_JUMP_LEFT", true);
				}
				else
				{
					GetAnimator()->Play(L"ALL_JUMP_RIGHT", true);
				}
			}
				break;
			}

			
		}

	}
	break;
	case PLAYER_STATE::DEAD:
	{
	
	}
	break;
	}
}

void CPlayer::update_gravity()
{
	// �׻� �߷� �ۿ�
	// ���� ������ �߷��� ���ٰ� ħ
	// ������ ��� �ӵ� �༭ �����ؼ� ����
	// ������ ������ �߷� ����
	// 2�������� �߷°��ӵ� ���� �ӵ� �ٷ� �־������
	GetRigidBody()->AddForce(Vec2(0.f, 100.f));
}

void CPlayer::CreateMissile()
{
	Vec2 vMissilePos = GetPos();
	vMissilePos.y -= GetScale().y / 2.f;

	// Missile Object
	CMissile* pMissile = new CMissile;
	pMissile->SetName(L"Missile_Player");
	pMissile->SetPos(vMissilePos);
	pMissile->SetScale(Vec2(25.f, 25.f));
	pMissile->SetDir(Vec2(0.f, -1.f));

	//CScene* pCurScene=CSceneMgr::GetInst()->GetCurScene();
	//pCurScene->AddObject(pMissile,GROUP_TYPE::DEFAULT);
	// ���� ���� �������� �̺�Ʈ �Ŵ����� ����
	//CreateObject(pMissile, GROUP_TYPE::PROJ_PLAYER);

}

void CPlayer::CreateMoveSkill()
{
	Vec2 pos = GetPos();

	if (m_iCurDir== -1)
	{
		pos.x -= 200.f;
	}
	else
	{
		pos.x += 200.f;
	}


	CObject* pmoveSkill = new Skill(pos, m_iCurDir);
	pmoveSkill->SetName(L"Skill");

	CreateObject(pmoveSkill, GROUP_TYPE::SKILL);
	
}

void CPlayer::CreateSkill3()
{
	Vec2 pos = GetPos();

	if (m_iCurDir == -1)
	{
		pos.x -= 300.f;
		pos.y -= 50.f;
	}
	else
	{
		pos.x += 300.f;
		pos.y -= 50.f;
	}


	CObject* pmoveSkill = new Skill3(pos, m_iCurDir);
	pmoveSkill->SetName(L"Skill3");

	CreateObject(pmoveSkill, GROUP_TYPE::SKILL);
}


void CPlayer::CreateJumpSkill()
{
	Vec2 pos = GetPos();

	if (m_iCurDir == -1)
	{
		pos.x += 50.f;
	}
	else
	{
		pos.x -= 50.f;
	}

	CObject* pmoveSkill = new Skill2(pos, m_iPreDir);
	pmoveSkill->SetName(L"JumpSkill");

	CreateObject(pmoveSkill, GROUP_TYPE::SKILL);
}

void CPlayer::CreateLevelSkill()
{
	Vec2 pos = GetPos();

	pos.y -= 150.f;

	CObject* pLevelSkill = new LevelSkill(pos);
	pLevelSkill->SetName(L"LevelSkill");

	CreateObject(pLevelSkill, GROUP_TYPE::LEVELSKILL);
}

void CPlayer::CreatePet()
{
	Vec2 pos = GetPos();

	CObject* pet = new Pet(pos,this);
	pet->SetName(L"Pet1");
	m_mypet1 = pet;
	CreateObject(pet, GROUP_TYPE::PET);
}

void CPlayer::CreateWideSkill()
{
	Vec2 pos = GetPos();

	CObject* pWideSkill = new WideSkill(pos);
	pWideSkill->SetName(L"wideSkill");

	CreateObject(pWideSkill, GROUP_TYPE::WIDESKILL);
}


void  CPlayer::CreatePlayerEffect()
{
	Vec2 damagepos = GetPos();
	damagepos.y -= 100.f;

	CObject* pDamageEffect = new PlayerDamageEffect(damagepos, PLAYER_EFFECT_TYPE::NORMAL, 1);

	pDamageEffect->SetName(L"PlayerDamageEffect");

	CreateObject(pDamageEffect, GROUP_TYPE::DAMAGE_EFFECT);
}


void CPlayer::render(HDC _dc)
{
	if (IsDead)
	{
		// UI�� Tile�� ����ϰ� �»�� ��ġ�� ��ǥ�� �� ����
		Vec2 vPos = GetPos();
		Vec2 vScale = DeadSize;

		vPos = CCamera::GetInst()->GetRenderPos(vPos);


		TransparentBlt(_dc
			// ���� �»�� ��ġ�� ũ��
			, (int)vPos.x
			, (int)vPos.y
			, vScale.x
			, vScale.y
			// �ؽ��� ����
			, DeadTex->GetDC()
			// bmp ���� ������ �ڸ� �»��
			, (int)0
			, (int)0
			, 43
			, 69
			, RGB(255, 0, 255));
	}
	else
	{
		// ������Ʈ(�浹ü, etc...) �� �ִ� ��� ������
		component_render(_dc);
	}
}


void CPlayer::OnCollisionEnter(CCollider* _pOther)
{
	CObject* pOtherObj = _pOther->GetObj();
	if (L"Ground" == pOtherObj->GetName())
	{
		// ���� ���� ��ġ���ٸ� ���� �ִٰ� �ؾ���
		Vec2 vPos = GetPos();
		if (vPos.y < pOtherObj->GetPos().y)
		{
			//m_eCurState = PLAYER_STATE::IDLE;
		}

	}

	if (L"Ladder1" == pOtherObj->GetName())
	{
		// �浹�Ҷ� ��ٸ� Ÿ�� Ű ���������̸�
		if (m_IspushLadder)
		{
			m_IsLadder = true;

			// ��ٸ� ���߾����� �����ؾ���
			float ladderX = pOtherObj->GetPos().x;
			SetPos(Vec2(ladderX , GetPos().y));

			// x�� �ӷ��� ������
			GetRigidBody()->SetVelocity(Vec2(0.f, 0.f));
		}
		
	}

	// ���Ͷ� �浹������
	if ((L"Monster" == pOtherObj->GetName() ||
		 L"SerenMonster" == pOtherObj->GetName() ||
		 L"BOSSSkill1" == pOtherObj->GetName() ||
		L"BOSSSkill2" == pOtherObj->GetName()
		)
		&& !m_IsInJury)
	{
		Vec2 temppos = GetRigidBody()->GetVelocity();

		// �� �ѹ� HP ��������
		m_HP -= 20;

		// ����Ʈ ����
		CreatePlayerEffect();

		m_IsInJury = true;

		// ���� ���⿡ ����
		if (m_iCurDir == 1)
		{
			GetRigidBody()->SetVelocity(Vec2(-100.f, -200.f));
		}
		else
		{
			GetRigidBody()->SetVelocity(Vec2(100.f, -200.f));
		}
		
	}

	//// �����۰� �浹�ҋ�
	//if (L"ItemMeso" == pOtherObj->GetName())
	//{
	//	dynamic_cast<Item*>(pOtherObj)->SetIsEat(true);		
	//}

}

void CPlayer::OnCollision(CCollider* _pOther)
{
	CObject* pOtherObj = _pOther->GetObj();

	if (L"Ladder1" == pOtherObj->GetName())
	{
		// �浹�Ҷ� ��ٸ� Ÿ�� Ű ���������̸�
		if (m_IspushLadder)
		{
			m_IsLadder = true;

			// ��ٸ� ���߾����� �����ؾ���
			float ladderX = pOtherObj->GetPos().x;
			SetPos(Vec2(ladderX, GetPos().y));

			// x�� �ӷ��� ������
			GetRigidBody()->SetVelocity(Vec2(0.f, 0.f));
		}
	}

	

	//// �����۰� �浹�ҋ�
	//if (L"ItemMeso" == pOtherObj->GetName())
	//{
	//	dynamic_cast<Item*>(pOtherObj)->SetIsEat(true);
	//}
}

void CPlayer::OnCollisionExit(CCollider* _pOther)
{
	CObject* pOtherObj = _pOther->GetObj();

	if (L"Ladder1" == pOtherObj->GetName())
	{
		// ��ٸ� Ÿ�°� ����
		// ��ٸ� Ÿ���� �ʾѴµ� �浹 �Ǵ� ��� ���� ���ؼ�
		if (m_IsLadder)
		{
			m_IsLadder = false;
			CRigidBody* pRigid = GetRigidBody();
			// Ż���Ҷ� �ӵ���ü�� 0��
			pRigid->SetVelocity(Vec2(0.f, 0.f));
		}
		
		
	}
}