#include "pch.h"
#include "BossMonster.h"

#include "CResMgr.h"
#include "CTexture.h"
#include "CCollider.h"
#include "CAnimator.h"
#include "CAnimation.h"
#include "CKeyMgr.h"
#include "CTimeMgr.h"

#include "CRigidBody.h"
#include "CGravity.h"
#include "CPlayer.h"
#include "BossSkill1.h"
#include "BossSkill2.h"
#include "SkillMotion.h"
#include "DamageEffect.h"
#include "CSound.h"
#include "Skill3.h"

BossMonster::BossMonster(int _dividePhase)
	: m_eCurState(B0SS_MONSTER_STATE::IDLE)
	, m_ePreState(B0SS_MONSTER_STATE::IDLE)
	, m_iCurDir(-1)
	, m_iPreDir(-1)
	, m_patternIndex(0)
	, IsInjure(false)
	, InjureTime(0.)
	// 스킬 이펙트를 위한 변수 2개
	, m_delaytime(0.)
	, m_motiondir(1)
	// 데미지 이펙트 위한 변수 5개....
	, m_damagetime1(0.8)
	, m_damagetime2(0.5)
	, m_damagepos(Vec2(0.f, 0.f))
	, m_i(0)
	, m_damagedir(1)
	, onemoreItem(true)
	, DamageEffectNum(5)
	, m_BossHP(100.f)

{

	CreateCollider();
	GetCollider()->SetScale(Vec2(150.f, 100.f));

	CTexture* BossStandRight = CResMgr::GetInst()->LoadTexture(L"SerenStandRight", L"texture\\Boss\\seren_stand_right.bmp");
	CTexture* BossStandLeft = CResMgr::GetInst()->LoadTexture(L"SerenStandLeft", L"texture\\Boss\\seren_stand_left.bmp");
	CTexture* BossAttack1Right = CResMgr::GetInst()->LoadTexture(L"SerenAttack1Right", L"texture\\Boss\\seren_attack1_right.bmp");
	CTexture* BossAttack1Left = CResMgr::GetInst()->LoadTexture(L"SerenAttack1Left", L"texture\\Boss\\seren_attack1_left.bmp");
	CTexture* BossAttack2Right = CResMgr::GetInst()->LoadTexture(L"SerenAttack2Right", L"texture\\Boss\\seren_attack2_right.bmp");
	CTexture* BossAttack2Left = CResMgr::GetInst()->LoadTexture(L"SerenAttack2Left", L"texture\\Boss\\seren_attack2_left.bmp");
	CTexture* BossAttack3Right = CResMgr::GetInst()->LoadTexture(L"SerenAttack3Right", L"texture\\Boss\\seren_attack3_right.bmp");
	CTexture* BossAttack3Left = CResMgr::GetInst()->LoadTexture(L"SerenAttack3Left", L"texture\\Boss\\seren_attack3_left.bmp");
	CTexture* BossSkill2Right = CResMgr::GetInst()->LoadTexture(L"SerenSkill2Right", L"texture\\Boss\\seren_skill2_right.bmp");
	CTexture* BossSkill2Left = CResMgr::GetInst()->LoadTexture(L"SerenSkill2Left", L"texture\\Boss\\seren_skill2_left.bmp");

	CreateAnimator();


	GetAnimator()->CreateAnimation(L"SEREN_STAND_RIGHT", BossStandRight, Vec2(0.f, 0.f), Vec2(429.f, 444.f), Vec2(429.f, 0.f), 0.1f, 16);
	GetAnimator()->CreateAnimation(L"SEREN_STAND_LEFT", BossStandLeft, Vec2(0.f, 0.f), Vec2(429.f, 444.f), Vec2(429.f, 0.f), 0.1f, 16);
	
	GetAnimator()->CreateAnimation(L"SEREN_ATTACK1_RIGHT", BossAttack1Right, Vec2(0.f, 0.f), Vec2(1794.f, 564.f), Vec2(0.f, 564.f), 0.05f, 36);
	GetAnimator()->CreateAnimation(L"SEREN_ATTACK1_LEFT", BossAttack1Left, Vec2(0.f, 0.f), Vec2(1794.f, 564.f), Vec2(0.f, 564.f), 0.05f, 36);
	
	GetAnimator()->CreateAnimation(L"SEREN_ATTACK2_RIGHT", BossAttack2Right, Vec2(0.f, 0.f), Vec2(829.f, 543.f), Vec2(829.f, 0.f), 0.05f, 27);
	GetAnimator()->CreateAnimation(L"SEREN_ATTACK2_LEFT", BossAttack2Left, Vec2(0.f, 0.f), Vec2(829.f, 543.f), Vec2(829.f, 0.f), 0.05f, 27);

	GetAnimator()->CreateAnimation(L"SEREN_ATTACK3_RIGHT", BossAttack3Right, Vec2(0.f, 0.f), Vec2(958.f, 745.f), Vec2(958.f, 0.f), 0.05f, 30);
	GetAnimator()->CreateAnimation(L"SEREN_ATTACK3_LEFT", BossAttack3Left, Vec2(0.f, 0.f), Vec2(958.f, 745.f), Vec2(958.f, 0.f), 0.05f, 30);

	GetAnimator()->CreateAnimation(L"SEREN_SKILL2_RIGHT", BossSkill2Right, Vec2(0.f, 0.f), Vec2(868.f, 656.f), Vec2(0.f, 656.f), 0.05f, 36);
	GetAnimator()->CreateAnimation(L"SEREN_SKILL2_LEFT", BossSkill2Left, Vec2(0.f, 0.f), Vec2(868.f, 656.f), Vec2(0.f, 656.f), 0.05f, 36);


	m_SKill1time = 0.f;
	m_Skill1Delaytime = 0.f;
	m_SKill2time = 0.f;
	m_Skill2Delaytime = 0.f;
	m_SKill3time = 0.f;
	m_Skill3Delaytime = 0.f;

	if (_dividePhase == 1)
	{
		pattern[0] = { 300.f ,B0SS_MONSTER_STATE::ATTACK2 ,		 1.0f };
		pattern[1] = { 300.f ,B0SS_MONSTER_STATE::ATTACK3 ,		 1.0f };
		pattern[2] = { 990.f ,B0SS_MONSTER_STATE::ATTACK4 ,		 1.0f };
		pattern[3] = { 500.f ,B0SS_MONSTER_STATE::ATTACK1 ,		 1.0f };
		pattern[4] = { 900.f ,B0SS_MONSTER_STATE::ATTACK4 ,		 1.0f };
		pattern[5] = { 300.f ,B0SS_MONSTER_STATE::ATTACK3 ,		 1.0f };
		pattern[6] = { 300.f ,B0SS_MONSTER_STATE::ATTACK2 ,	     1.0f };
		pattern[7] = { 500.f ,B0SS_MONSTER_STATE::ATTACK1 ,		 1.0f };
		pattern[8] = { 300.f ,B0SS_MONSTER_STATE::ATTACK3 ,		 1.0f };
		pattern[9] = { 500.f ,B0SS_MONSTER_STATE::ATTACK1 ,		 1.0f };
	}
	else if (_dividePhase == 2)
	{
		pattern[0] = { 990.f ,B0SS_MONSTER_STATE::ATTACK5 ,		 0.5f };
		pattern[1] = { 990.f ,B0SS_MONSTER_STATE::ATTACK5 ,		 0.5f };
		pattern[2] = { 990.f ,B0SS_MONSTER_STATE::ATTACK4 ,		 0.5f };
		pattern[3] = { 300.f ,B0SS_MONSTER_STATE::ATTACK3 ,		 0.5f };
		pattern[4] = { 300.f ,B0SS_MONSTER_STATE::ATTACK2 ,		 0.5f };
		pattern[5] = { 500.f ,B0SS_MONSTER_STATE::ATTACK1 ,		 0.5f };
		pattern[6] = { 990.f ,B0SS_MONSTER_STATE::ATTACK5 ,	     0.5f };
		pattern[7] = { 990.f ,B0SS_MONSTER_STATE::ATTACK5 ,		 0.5f };
		pattern[8] = { 500.f ,B0SS_MONSTER_STATE::ATTACK1 ,		 0.5f };
		pattern[9] = { 990.f ,B0SS_MONSTER_STATE::ATTACK4 ,		 0.5f };
	}
	
	m_patternDelayTime = 0.f;
	m_patternIndex = 0;
	m_attack5State = 0;
	m_attack5dir = -1;


	m_HitSound[0] = CResMgr::GetInst()->FindSound(L"LEVEL_UP_SOUND1");
	m_HitSound[1] = CResMgr::GetInst()->FindSound(L"LEVEL_UP_SOUND2");
	m_HitSound[2] = CResMgr::GetInst()->FindSound(L"LEVEL_UP_SOUND3");
	m_HitSound[3] = CResMgr::GetInst()->FindSound(L"LEVEL_UP_SOUND4");
	m_HitSound[4] = CResMgr::GetInst()->FindSound(L"LEVEL_UP_SOUND5");
	m_HitSound[5] = CResMgr::GetInst()->FindSound(L"LEVEL_UP_SOUND6");
	m_HitSound[6] = CResMgr::GetInst()->FindSound(L"LEVEL_UP_SOUND7");
	m_HitSound[7] = CResMgr::GetInst()->FindSound(L"LEVEL_UP_SOUND8");
	m_HitSound[8] = CResMgr::GetInst()->FindSound(L"LEVEL_UP_SOUND9");
	m_HitSound[9] = CResMgr::GetInst()->FindSound(L"LEVEL_UP_SOUND10");
	m_HitSound[10] = CResMgr::GetInst()->FindSound(L"LEVEL_UP_SOUND11");
	m_HitSound[11] = CResMgr::GetInst()->FindSound(L"LEVEL_UP_SOUND12");
	m_HitSound[12] = CResMgr::GetInst()->FindSound(L"LEVEL_UP_SOUND13");
	m_HitSound[13] = CResMgr::GetInst()->FindSound(L"LEVEL_UP_SOUND14");
	m_HitSound[14] = CResMgr::GetInst()->FindSound(L"LEVEL_UP_SOUND15");

	sound_index = 0;
}


BossMonster::~BossMonster()
{
}


void BossMonster::update()
{
	if (m_BossHP < 0.f)
	{
		SetDead();
	}


	// 부상동안 무적상태
	if (IsInjure)
	{
		//InjureTime += fDT;
		m_BossHP -= 10.0f * fDT;

		//if (InjureTime > 1.5)
		//{
		//	IsInjure = false;
		//	InjureTime = 0.;
		//	m_damagepos.y = 0.f;
		//}
	}


	if (m_patternIndex > 9)
		m_patternIndex = 0;

	if (IsInjure)
	{
		CreateEffect();
	}

	update_action();


	update_animation();

	m_ePreState = m_eCurState;
	m_iPreDir = m_iCurDir;



}

void BossMonster::render(HDC _dc)
{
	component_render(_dc);
}

void BossMonster::update_action()
{
	switch (m_ePreState)
	{
	case B0SS_MONSTER_STATE::IDLE:
	{
		//============================================
		// pattern 사이에서 지연시킬때

		// pattern delay 걸려면 여기서하고 break 해주자
		if (m_patternDelayTime < pattern[m_patternIndex].delaytime)
		{
			m_patternDelayTime += fDT;
			m_eCurState = B0SS_MONSTER_STATE::IDLE;
			break;
		}

		//============================================
		// 플레이어 따라가기 위한 코드

		Vec2 playerpos = target_player->GetPos();
		Vec2 mypos = GetPos();

		// 플레이어를 따라갈 방향 정하는 벡터
		Vec2 vectorDir = playerpos - mypos;

		// 플레이어와 보스 몬스터 사이의 거리
		float Diff = vectorDir.Length();

		// 보스 몬스터가 움직일 방향
		Vec2 Dir = vectorDir.Normalize();

		// 보스 몬스터의 현재 방향state를 세팅하고
		// Dir 소수점이라 0되버림..
		if (Dir.x > 0.f)
		{
			m_iCurDir = +1;
		}
		else
		{
			m_iCurDir = -1;
		}

		//=============================================
		// 인식범위에 따라
		if (Diff > pattern[m_patternIndex].RecognField)
		{
			// Idle 상태 계속 유지하면서 따라가기
			mypos.x += (m_iCurDir) * 100.f * DT;
			SetPos(mypos);
		
			m_eCurState = B0SS_MONSTER_STATE::IDLE;

		}
		else
		{
			// IDLE 상태에서 pattern안에 있던 state로 변경
			m_eCurState = pattern[m_patternIndex].state;

			m_SKill1time = 0.f;
			m_Skill1Delaytime = 0.f;
			m_SKill2time = 0.f;
			m_Skill2Delaytime = 0.f;
			m_SKill3time = 0.f;
			m_Skill3Delaytime = 0.f;
			m_SKill4time = 0.f;
			m_Skill4Delaytime = 0.f;
			m_SKill5time = 0.f;
			m_Skill5Delaytime = 0.f;
		}

	}
	break;
	case B0SS_MONSTER_STATE::ATTACK1:
	{
		// Attack1 총 시간
		if (m_SKill1time > 1.8f)
		{

			m_eCurState = B0SS_MONSTER_STATE::IDLE;
			m_patternDelayTime = 0.f;
			m_patternIndex++;
		}
		else
		{
			if (m_Skill1Delaytime > 1.2f)
			{
				Vec2 mypos = GetPos();
				mypos.x += (m_iCurDir) * 1000.f * fDT;
				SetPos(mypos);
			}
		}


		m_Skill1Delaytime += fDT;
		m_SKill1time += fDT;
	}
	break;
	case B0SS_MONSTER_STATE::ATTACK2:
	{
		// Attack1 총 시간
		if (m_SKill2time > 1.35f)
		{

			m_eCurState = B0SS_MONSTER_STATE::IDLE;
			m_patternDelayTime = 0.f;
			m_patternIndex++;
		}
		else
		{
			if (m_Skill2Delaytime > 0.3f)
			{
				Vec2 mypos = GetPos();
				mypos.x += (m_iCurDir) * 200.f * fDT;
				SetPos(mypos);
			}
		}


		m_Skill2Delaytime += fDT;
		m_SKill2time += fDT;
	}
	break;
	case B0SS_MONSTER_STATE::ATTACK3:
	{
		// Attack1 총 시간
		if (m_SKill3time > 1.5f)
		{

			m_eCurState = B0SS_MONSTER_STATE::IDLE;
			m_patternDelayTime = 0.f;
			m_patternIndex++;
		}
		else
		{
			if (m_Skill3Delaytime > 0.85f)
			{
				Vec2 mypos = GetPos();
				mypos.x += (m_iCurDir) * 200.f * fDT;
				SetPos(mypos);
			}
		}


		m_Skill3Delaytime += fDT;
		m_SKill3time += fDT;
	}
	break;
	case B0SS_MONSTER_STATE::ATTACK4:
	{
		// Attack1 총 시간
		if (m_SKill4time > 2.f)
		{
			CreateSkill1();
			m_eCurState = B0SS_MONSTER_STATE::IDLE;
			m_patternDelayTime = 0.f;
			m_patternIndex++;
		}
		else
		{
			if (m_Skill4Delaytime > 0.5f)
			{
	
			}
		}


		m_Skill4Delaytime += fDT;
		m_SKill4time += fDT;
	}
	break;
	case B0SS_MONSTER_STATE::ATTACK5:
	{
		// Attack1 총 시간
		if (m_SKill5time > 1.75f)
		{

			m_eCurState = B0SS_MONSTER_STATE::IDLE;
			m_attack5State = 0;
			m_patternDelayTime = 0.f;
			m_attack5dir *= -1;
			m_patternIndex++;
		}
		else
		{
			if (m_Skill5Delaytime > 0.2f)
			{
				CreateSkill2(m_attack5State);
				m_attack5State++;
				m_Skill5Delaytime = 0.f;
			}
		}


		m_Skill5Delaytime += fDT;
		m_SKill5time += fDT;
	}
	break;
	}

	
	

}

void BossMonster::CreateSkill1()
{
	Vec2 pos = GetPos();

	if (m_iCurDir == -1)
	{
		pos.x -= 200.f;
	}
	else
	{
		pos.x += 200.f;
	}

	CObject* MoveSkill1 = new BossSkill1(pos, m_iCurDir);
	MoveSkill1->SetName(L"BOSSSkill1");

	CreateObject(MoveSkill1, GROUP_TYPE::BOSSSKILL);
}

void BossMonster::CreateSkill2(int _Order)
{
	Vec2 pos = GetPos();

	if (m_attack5dir == 1)
	{
		pos.x -= (1500.f - (300.f * _Order));
	}
	else
	{
		pos.x += (1500.f - (300.f * _Order));
	}
	
	pos.y -= 600.f;
	CObject* MoveSkill2 = new BossSkill2(pos, m_attack5dir);
	MoveSkill2->SetName(L"BOSSSkill2");

	CreateObject(MoveSkill2, GROUP_TYPE::BOSSSKILL);
	

}

void BossMonster::update_animation()
{
	// 이전 상태와 현재 상태가 다르면 애니메이션 변경
	if (m_ePreState == m_eCurState && m_iCurDir == m_iPreDir)
	{
		return;
	}

	switch (m_eCurState)
	{
	case B0SS_MONSTER_STATE::IDLE:
	{
		if (-1 == m_iCurDir)
		{
			GetAnimator()->Play(L"SEREN_STAND_LEFT", true);
		}
		else
		{
			GetAnimator()->Play(L"SEREN_STAND_RIGHT", true);
		}
	}
	break;
	case B0SS_MONSTER_STATE::ATTACK1:
	{
		if (-1 == m_iCurDir)
		{
			GetAnimator()->Play(L"SEREN_ATTACK1_LEFT", true);
		}
		else
		{
			GetAnimator()->Play(L"SEREN_ATTACK1_RIGHT", true);
		}
	}
	break;
	case B0SS_MONSTER_STATE::ATTACK2:
	{
		if (-1 == m_iCurDir)
		{
			GetAnimator()->Play(L"SEREN_ATTACK2_LEFT", true);
		}
		else
		{
			GetAnimator()->Play(L"SEREN_ATTACK2_RIGHT", true);
		}
	}
	break;
	case B0SS_MONSTER_STATE::ATTACK3:
	{
		if (-1 == m_iCurDir)
		{
			GetAnimator()->Play(L"SEREN_ATTACK3_LEFT", true);
		}
		else
		{
			GetAnimator()->Play(L"SEREN_ATTACK3_RIGHT", true);
		}
	}
	break;
	case B0SS_MONSTER_STATE::ATTACK4:
	{
		if (-1 == m_iCurDir)
		{
			GetAnimator()->Play(L"SEREN_STAND_LEFT", true);
		}
		else
		{
			GetAnimator()->Play(L"SEREN_STAND_RIGHT", true);
		}
	}
	break;
	case B0SS_MONSTER_STATE::ATTACK5:
	{
		if (-1 == m_iCurDir)
		{
			GetAnimator()->Play(L"SEREN_SKILL2_LEFT", true);
		}
		else
		{
			GetAnimator()->Play(L"SEREN_SKILL2_RIGHT", true);
		}
	}
	break;
	}
}

void BossMonster::CreateEffect()
{
	Vec2 pos = GetPos();

	// 테스트용 스킬 모션
	m_delaytime += fDT;

	if (m_delaytime > 0.07f)
	{
		m_delaytime = 0.;

		if (m_motiondir == 1)
		{
			m_motiondir = 2;

			CObject* pTestmotion = new SkillMotion(Vec2(pos.x, pos.y));
			pTestmotion->SetName(L"SKILLMOTION");

			CreateObject(pTestmotion, GROUP_TYPE::EFFECT);



		}
		else if (m_motiondir == 2)
		{
			m_motiondir = 3;

			CObject* pTestmotion = new SkillMotion(Vec2(pos.x + 25.f, pos.y - 25.f));
			pTestmotion->SetName(L"SKILLMOTION");

			CreateObject(pTestmotion, GROUP_TYPE::EFFECT);


		}
		else if (m_motiondir == 3)
		{
			m_motiondir = 4;

			CObject* pTestmotion = new SkillMotion(Vec2(pos.x, pos.y - 25.f));
			pTestmotion->SetName(L"SKILLMOTION");

			CreateObject(pTestmotion, GROUP_TYPE::EFFECT);


		}
		else if (m_motiondir == 4)
		{
			m_motiondir = 1;

			CObject* pTestmotion = new SkillMotion(Vec2(pos.x - 25.f, pos.y));
			pTestmotion->SetName(L"SKILLMOTION");

			CreateObject(pTestmotion, GROUP_TYPE::EFFECT);

		}


	}



	m_damagetime1 += fDT;

	if (m_damagetime1 > 1.0)
	{
		CreateDamageUI();
	}
}

void BossMonster::CreateDamageUI()
{
	if (m_damagepos.y == 0.f)
	{
		m_damagepos = GetPos();
		m_damagepos.y -= 100.f;
	}

	m_damagetime2 += fDT;

	if (sound_index > 14)
		sound_index = 0;

	if (m_damagetime2 > 0.1)
	{
		m_damagetime2 = 0.;
		m_damagedir *= -1;
		CObject* pDamageEffect = new DamageEffect(m_damagepos, EFFECT_TYPE::NORMAL, m_damagedir);

		pDamageEffect->SetName(L"VocalnoEffect");

		CreateObject(pDamageEffect, GROUP_TYPE::DAMAGE_EFFECT);

		m_HitSound[sound_index]->Play();
		m_HitSound[sound_index]->SetVolume(50.f);

		m_damagepos.y -= 30.f;
		m_damagepos.x += 10.f * m_damagedir;

		m_i++;
		if (m_i == DamageEffectNum)
		{
			m_damagetime1 = 0.;
			m_i = 0;
			m_damagepos.y = 0.f;
		}
	}

	sound_index++;
}

void BossMonster::OnCollisionEnter(CCollider* _pOther)
{

}

void BossMonster::OnCollision(CCollider* _pOther)
{
	CObject* pOtherObj = _pOther->GetObj();

	if (pOtherObj->GetName() == L"Skill3")
	{
		if (((Skill3*)(pOtherObj))->GetIsTarget())
		{
			IsInjure = true;
			DamageEffectNum = 7;
		}

	}


	if (pOtherObj->GetName() == L"Skill")
	{
		IsInjure = true;
		DamageEffectNum = 15;
	}

	if (pOtherObj->GetName() == L"wideSkill")
	{
		IsInjure = true;
		DamageEffectNum = 8;
	}
}

void BossMonster::OnCollisionExit(CCollider* _pOther)
{
	CObject* pOtherObj = _pOther->GetObj();

	if (pOtherObj->GetName() == L"Skill")
	{
		IsInjure = false;
	}
	
	if (pOtherObj->GetName() == L"wideSkill")
	{
		IsInjure = false;
	}

	if (pOtherObj->GetName() == L"Skill3")
	{
		IsInjure = false;

	}
}