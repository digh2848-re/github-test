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
	, curWearState(PlayerWearState::NO_WEAR)  // 텍스쳐 바꾸기위한 변수
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
	// Texture 로딩하기
	//m_pTex=CResMgr::GetInst()->LoadTexture(L"PlayerTex", L"texture\\Player.bmp");

	// 컴포넌트 콜라이더 내용
	CreateCollider();
	GetCollider()->SetOffsetPos(Vec2(0.f, 0.f));
	GetCollider()->SetScale(Vec2(50.f,70.f));

	CreateRigidBody();

	// 컴포넌트 애니메이터 내용
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

	
	// 중력 컴포넌트 생성
	CreateGravity();

	//GetAnimator()->Play(L"WALK_RIGHT", true);

	//CAnimation* pAnim = GetAnimator()->FindAnimation(L"WALK_LEFT");
	//
	//// 전체 프레임 offset 100올림
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

	// 텍스쳐 바꿀때마다 사다리타는거 바꿔줘야함
	//GetAnimator()->SetIsLadderStop(false);
}


void CPlayer::update()
{

	// 매 프레임마다 점프키 눌렸던거 초기화 시켜줌
	m_IspushLadder = false;

	// Dead상태체크
	if (m_HP <= 0)
	{
		// 죽을때 딱한번 y축으로 살짝 올림
		if (!IsDead)
		{

			// 무덤 이미지 내고
			Vec2 pos = GetPos();
			CObject* pTomb = new Tomb(pos);
			pTomb->SetName(L"pTomb");
			CreateObject(pTomb, GROUP_TYPE::TOMB);

			// 소리내고
			m_tombSound->Play();
			m_tombSound->SetVolume(100.f);

			// UI 띄우고 포커싱해야함
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
	else // 안죽을때 하는 것들
	{


		// 부상동안 무적상태
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

		// 경험치 로직
		// 레벨업
		if (m_Exp > m_MaxExp)
		{
			m_Level++;
			m_Exp = 0;
			// 지금보다 1.5배 경험치통 더 커지게
			m_MaxExp = m_MaxExp + m_MaxExp / 2;

			m_levelupSound->Play();
			m_levelupSound->SetVolume(80.f);
			// 레벨업 스킬
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

		// 이전상태 비교를 위해 저장 ( update문 맨 마지막에 둠)
	// 충돌같은 lateupdate때 상태 변화가 발생하면 다음 프레임때 update_animation에 걸리게 됨
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

	 //부상상태이면 무적뿐만 아니라 다른 움직임 안됨
	if (m_IsInJury)
	{
		return;
	}

	// 이제 움직임은 힘을 누적해주는 방식으로 할 것임
	CRigidBody* pRigid = GetRigidBody();

	if (KEY_TAP(KEY::F))
	{
		// F키눌릴때마다 충돌했는지 안햇는지 체크할꺼임
		m_IspushLadder = true;
	}



	if (KEY_TAP(KEY::P))
	{
		CreatePet();
	}


	if (!m_IsLadder)
	{
		// 좌우로 움직임
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

		// 점프키 입력
		if (KEY_TAP(KEY::SPACE))
		{
			if (m_ePrevState == PLAYER_STATE::JUMP)
			{
				if (!jumpDelay)
				{
					// 이단점프 스킬
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
	else // 사다리 타고 있을때
	{
		if (KEY_HOLD(KEY::W))
		{
			// 리지드바디 쓰지말고 Y축 변화주자
			Vec2 pos = GetPos();
			pos.y -= 100.f* fDT;
			SetPos(Vec2(pos.x,pos.y));
			GetAnimator()->SetIsLadderStop(false);
		}
		else if (KEY_HOLD(KEY::S))
		{
			// 리지드바디 쓰지말고 Y축 변화주자
			Vec2 pos = GetPos();
			pos.y += 100.f* fDT;
			SetPos(Vec2(pos.x, pos.y));
			GetAnimator()->SetIsLadderStop(false);
		}
		else
		{
			GetAnimator()->SetIsLadderStop(true);
		}
		

		// 점프키 입력
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
	// 양쪽 키를 동시 누를 경우? 일단 그대로 둠

	// 부상입으면 상태체크만하고 넘어가자
	if (m_IsInJury)
	{
		m_eCurState = PLAYER_STATE::INJURE;
		return;
	}

	CRigidBody* pRigid = GetRigidBody();
	CGravity* pGravi = GetGravity();
	
	// 이전 프레임 상태 보고 만들꺼임
	switch (m_ePrevState)
	{
	case PLAYER_STATE::IDLE:
	{
		// 그전에 사다리탄거 체크되면 바로 사다리상태 
		if (m_IsLadder == true)
		{
			m_eCurState = PLAYER_STATE::LADDER;
		}
		// walk 상태로 변경
		// 변경된 y축은 0근처이고  x축 속도가 0 근처가 아니면( WALK로 변경)
		else if ((pRigid->GetVelocity().x > 5.f || pRigid->GetVelocity().x < -5.f) &&
			(pRigid->GetVelocity().y < 1.f && pRigid->GetVelocity().y > -1.f) )
		{
			m_eCurState = PLAYER_STATE::WALK;

			
			// x속도체크
			// x속도체크
			if (pRigid->GetVelocity().x > 1.f)
			{
				m_iCurDir = 1;
			}
			else if (pRigid->GetVelocity().x < -1.f)
			{
				m_iCurDir = -1;
			}

		}
		// jump 상태로 변경
		// y축만 그라운드 상태가 false 로써 이전프레임에 충돌을 나왔거나(일단 보류) / y축 속도가 0근처가 아니면
		else if (pGravi->GetGround() == false ||
			(pRigid->GetVelocity().y > 1.f && pRigid->GetVelocity().y < -1.f)
			)
		{
			m_eCurState = PLAYER_STATE::JUMP;

			// x속도체크
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
		// 그전에 사다리탄거 체크되면 바로 사다리상태 
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

			// x속도체크
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

			// x속도체크
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
		// 그전에 사다리탄거 체크되면 바로 사다리상태 
		if (m_IsLadder == true)
		{
			m_eCurState = PLAYER_STATE::LADDER;
			jumpDelay = false;
		}
		// JUMP -> IDLE 상태 변할려면
		else if (
			(pRigid->GetVelocity().y < 1.f && pRigid->GetVelocity().y > -1.f) &&
			(pRigid->GetVelocity().x < 0.01f && pRigid->GetVelocity().x > -0.01f)
			)
		{
			pRigid->SetMaxVelocity(Vec2(200.f, 600.f));
			jumpDelay = false;
			m_eCurState = PLAYER_STATE::IDLE;
		}
		// JUMP -> WALK 상태 변할려면
		else if (
			(pRigid->GetVelocity().x > 1.f || pRigid->GetVelocity().x < -1.f) &&
			(pRigid->GetVelocity().y < 1.f && pRigid->GetVelocity().y > -1.f)
			)
		{
			pRigid->SetMaxVelocity(Vec2(200.f, 600.f));
			jumpDelay = false;
			m_eCurState = PLAYER_STATE::WALK;

			// x속도체크
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

			// x속도체크
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

			// x속도체크
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
	// 이전 상태와 현재 상태가 다르면 애니메이션 변경
	if (m_ePrevState == m_eCurState && m_iCurDir == m_iPreDir)
	{
		// 예외상황 부상입었을땐 무시 / 옷입는상태 바뀌면
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
	// 항상 중력 작용
	// 땅에 있을땐 중력이 없다고 침
	// 점프시 즉시 속도 줘서 보정해서 구현
	// 하지만 점프시 중력 적용
	// 2단점프시 중력가속도 없이 속도 바로 주어줘야함
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
	// 씬에 직접 넣지말고 이벤트 매니저를 통해
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
		// UI도 Tile과 비슷하게 좌상단 위치를 좌표로 할 것임
		Vec2 vPos = GetPos();
		Vec2 vScale = DeadSize;

		vPos = CCamera::GetInst()->GetRenderPos(vPos);


		TransparentBlt(_dc
			// 실제 좌상단 위치와 크기
			, (int)vPos.x
			, (int)vPos.y
			, vScale.x
			, vScale.y
			// 텍스쳐 정보
			, DeadTex->GetDC()
			// bmp 파일 내에서 자를 좌상단
			, (int)0
			, (int)0
			, 43
			, 69
			, RGB(255, 0, 255));
	}
	else
	{
		// 컴포넌트(충돌체, etc...) 가 있는 경우 렌더링
		component_render(_dc);
	}
}


void CPlayer::OnCollisionEnter(CCollider* _pOther)
{
	CObject* pOtherObj = _pOther->GetObj();
	if (L"Ground" == pOtherObj->GetName())
	{
		// 내가 높은 위치였다면 땅에 있다고 해야함
		Vec2 vPos = GetPos();
		if (vPos.y < pOtherObj->GetPos().y)
		{
			//m_eCurState = PLAYER_STATE::IDLE;
		}

	}

	if (L"Ladder1" == pOtherObj->GetName())
	{
		// 충돌할때 사다리 타는 키 눌린상태이면
		if (m_IspushLadder)
		{
			m_IsLadder = true;

			// 사다리 정중앙으로 세팅해야함
			float ladderX = pOtherObj->GetPos().x;
			SetPos(Vec2(ladderX , GetPos().y));

			// x축 속력을 없애자
			GetRigidBody()->SetVelocity(Vec2(0.f, 0.f));
		}
		
	}

	// 몬스터랑 충돌했을때
	if ((L"Monster" == pOtherObj->GetName() ||
		 L"SerenMonster" == pOtherObj->GetName() ||
		 L"BOSSSkill1" == pOtherObj->GetName() ||
		L"BOSSSkill2" == pOtherObj->GetName()
		)
		&& !m_IsInJury)
	{
		Vec2 temppos = GetRigidBody()->GetVelocity();

		// 딱 한번 HP 깍을려고
		m_HP -= 20;

		// 이펙트 생성
		CreatePlayerEffect();

		m_IsInJury = true;

		// 보는 방향에 따라
		if (m_iCurDir == 1)
		{
			GetRigidBody()->SetVelocity(Vec2(-100.f, -200.f));
		}
		else
		{
			GetRigidBody()->SetVelocity(Vec2(100.f, -200.f));
		}
		
	}

	//// 아이템과 충돌할떄
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
		// 충돌할때 사다리 타는 키 눌린상태이면
		if (m_IspushLadder)
		{
			m_IsLadder = true;

			// 사다리 정중앙으로 세팅해야함
			float ladderX = pOtherObj->GetPos().x;
			SetPos(Vec2(ladderX, GetPos().y));

			// x축 속력을 없애자
			GetRigidBody()->SetVelocity(Vec2(0.f, 0.f));
		}
	}

	

	//// 아이템과 충돌할떄
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
		// 사다리 타는거 해제
		// 사다리 타지도 않앗는데 충돌 되는 경우 막기 위해서
		if (m_IsLadder)
		{
			m_IsLadder = false;
			CRigidBody* pRigid = GetRigidBody();
			// 탈출할때 속도자체를 0줌
			pRigid->SetVelocity(Vec2(0.f, 0.f));
		}
		
		
	}
}